#include "vrx.h"

#include <errno.h>
#include <jni.h>

extern int android_main(int argc, char *argv[], char *envp[]);
extern char *vrxGetFramebuffer(void);

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
		  "-screen", "1024x1024x24",
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

JNI_METHOD(jint, nativeGetFrameBufferPointer)(JNIEnv *env, jobject thiz) {
  char *fp = vrxGetFramebuffer();
  LOGI("Framebuffer @%p", fp);
  return (jint)fp;
}
