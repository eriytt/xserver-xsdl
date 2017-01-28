#include "vrx.h"

#include <errno.h>
#include <jni.h>
#include <pthread.h>

extern int android_main(int argc, char *argv[], char *envp[]);
extern char *vrxGetFramebuffer(void);
extern void VRXMouseMotionEvent(int x, int y, int relative);
extern KdKeyboardInfo *vrxKbd;
extern KdPointerInfo *vrxMouse;

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_towersmatrix_vrx_xserver_VRXServer_##method_name

JNI_METHOD(jint, nativeRunX)(JNIEnv *env, jobject thiz, jstring j_filesDirectory) {
  char *envp[] = { NULL };
  char *argv[] = {"xserver-vrx",
		  "-nolock",
		  "-noreset",
		  "-nopn",
		  "-nolisten", "unix",
		  "-screen", "2048x2048x24",
		  "-exec", "/data/data/com.towersmatrix.vrx/files/usr/bin/xhost +",
		  0 };
		
  jboolean iscopy;
  const char *filesDirectory = (*env)->GetStringUTFChars(env, j_filesDirectory, &iscopy);
  if (setenv("SECURE_STORAGE_DIR", filesDirectory, 1))
    {
      LOGE("Failed to set base data dir in environment: %s", strerror(errno));
      return errno;
    }

  LOGI("nativeRunX");
  return android_main((sizeof(argv) / sizeof(char*)) - 1, argv, envp);
}

extern pthread_mutex_t inputLock;

JNI_METHOD(void, nativeKeyEvent)(JNIEnv *env, jobject thiz, jint scancode, jboolean down) {
  //LOGI("Enqueueing key event, scancode %d, down = %d", scancode, down);

  VRXInputEvent *new_event = malloc(sizeof(VRXInputEvent));
  if (new_event == 0)
    {
      LOGE("Failed to enque input event: %s", strerror(errno));
      return;
    }

  new_event->type = VRX_E_KEY;
  new_event->event.key.scancode = scancode;
  new_event->event.key.down = down;
  new_event->next = 0;

  pthread_mutex_lock(&inputLock);
  if (vrx_event_queue == 0)
    {
      vrx_event_queue = new_event;
      pthread_mutex_unlock(&inputLock);
      return;
    }

  VRXInputEvent *tail = vrx_event_queue;
  while (tail->next != 0) tail = tail->next;
  tail->next = new_event;
  pthread_mutex_unlock(&inputLock);
}

JNI_METHOD(void, nativeMouseMotionEvent)(JNIEnv *env, jobject thiz, jint x, jint y) {
  //LOGI("Enqueueing motion event, x=%d, y=%d", x, y);
  VRXMouseMotionEvent(x, y, 1);
}
