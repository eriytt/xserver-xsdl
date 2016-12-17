/*
 * Copyright © 2004 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <pthread.h>

#ifdef HAVE_CONFIG_H
#include <kdrive-config.h>
#endif
#include "vrx.h"

static int
FakeInit (void)
{
    return 1;
}

static void
FakeEnable (void)
{
}

static Bool
FakeSpecialKey (KeySym sym)
{
    return FALSE;
}

static void
FakeDisable (void)
{
}

static void
FakeFini (void)
{
}

pthread_mutex_t inputLock = PTHREAD_MUTEX_INITIALIZER;

static void
VRXPollInput(void)
{
  VRXInputEvent *head;
  VRXInputEvent *oldHead;

  pthread_mutex_lock(&inputLock);
  head = vrx_event_queue;
  vrx_event_queue = 0;
  pthread_mutex_unlock(&inputLock);

  while (head != 0)
    {
      switch(head->type)
	{
	case VRX_E_KEY:
	  LOGI("Really enqueuing key event");
	  KdEnqueueKeyboardEvent(vrxKbd,
				 (unsigned char)(head->event.key.scancode),
				 (unsigned char)(!head->event.key.down));
	  break;
	case VRX_E_MOTION:
	  KdEnqueuePointerEvent(vrxMouse,
				0,
				head->event.motion.x,
				head->event.motion.y,
				0);
	  break;
	default:
	  LOGE("Unknown input event type %d", head->type);
	}

      oldHead = head;
      head = head->next;
      free(oldHead);
    }
}

KdOsFuncs   VRXOsFuncs = {
    FakeInit,
    FakeEnable,
    FakeSpecialKey,
    FakeDisable,
    FakeFini,
    VRXPollInput
};

