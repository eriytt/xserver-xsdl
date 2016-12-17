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

#ifndef _FBDEV_H_
#define _FBDEV_H_
#include <stdio.h>
#include <unistd.h>
#include "kdrive.h"

#ifdef RANDR
#include "randrstr.h"
#endif

typedef struct _fakePriv {
    CARD8	*base;
    int		bytes_per_line;
} FakePriv;
    
typedef struct _fakeScrPriv {
    Rotation	randr;
    Bool	shadow;
} FakeScrPriv;

extern KdCardFuncs  fakeFuncs;

Bool
fakeInitialize (KdCardInfo *card, FakePriv *priv);

Bool
fakeCardInit (KdCardInfo *card);

Bool
fakeScreenInit (KdScreenInfo *screen);

Bool
fakeScreenInitialize (KdScreenInfo *screen, FakeScrPriv *scrpriv);
    
Bool
fakeInitScreen (ScreenPtr pScreen);

Bool
fakeFinishInitScreen (ScreenPtr pScreen);

Bool
fakeCreateResources (ScreenPtr pScreen);

void
fakePreserve (KdCardInfo *card);

Bool
fakeEnable (ScreenPtr pScreen);

Bool
fakeDPMS (ScreenPtr pScreen, int mode);

void
fakeDisable (ScreenPtr pScreen);

void
fakeRestore (KdCardInfo *card);

void
fakeScreenFini (KdScreenInfo *screen);

void
fakeCardFini (KdCardInfo *card);

void
fakeGetColors (ScreenPtr pScreen, int n, xColorItem *pdefs);

void
fakePutColors (ScreenPtr pScreen, int n, xColorItem *pdefs);

Bool
fakeMapFramebuffer (KdScreenInfo *screen);

void *
fakeWindowLinear (ScreenPtr	pScreen,
		   CARD32	row,
		   CARD32	offset,
		   int		mode,
		   CARD32	*size,
		   void		*closure);

void
fakeSetScreenSizes (ScreenPtr pScreen);

Bool
fakeUnmapFramebuffer (KdScreenInfo *screen);

Bool
fakeSetShadow (ScreenPtr pScreen);

Bool
fakeCreateColormap (ColormapPtr pmap);
    
#ifdef RANDR
Bool
fakeRandRGetInfo (ScreenPtr pScreen, Rotation *rotations);

Bool
fakeRandRSetConfig (ScreenPtr		pScreen,
		     Rotation		randr,
		     int		rate,
		     RRScreenSizePtr	pSize);
Bool
fakeRandRInit (ScreenPtr pScreen);

#endif

extern KdPointerDriver FakePointerDriver;

extern KdKeyboardDriver	FakeKeyboardDriver;

extern KdOsFuncs   VRXOsFuncs;

#include <android/log.h>
#define VRX_LOG_TAG "VRXserver:"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, VRX_LOG_TAG __FILE__, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, VRX_LOG_TAG __FILE__, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, VRX_LOG_TAG __FILE__, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, VRX_LOG_TAG __FILE__, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, VRX_LOG_TAG __FILE__, __VA_ARGS__)

typedef struct {
  int scancode;
  Bool down;
} VRXKeyEvent;

typedef struct {
  int x, y;
} VRXMotionEvent;

typedef enum {
  VRX_E_KEY,
  VRX_E_MOTION
} VRXEventType;

typedef union {
  VRXKeyEvent key;
  VRXMotionEvent motion;
} VRXEvent;

typedef struct _vrx_input_event {
  VRXEventType type;
  VRXEvent event;
  struct _vrx_input_event *next;
} VRXInputEvent;

extern VRXInputEvent *vrx_event_queue;
extern KdKeyboardInfo *vrxKbd;
extern KdPointerInfo *vrxMouse;

#endif /* _FBDEV_H_ */
