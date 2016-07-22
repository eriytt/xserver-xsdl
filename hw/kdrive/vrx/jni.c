#include "vrx.h"

#include <errno.h>
#include <jni.h>

extern int android_main(int argc, char *argv[], char *envp[]);

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_towersmatrix_vrx_xserver_VRXServer_##method_name

JNI_METHOD(jint, nativeRunX)(JNIEnv *env, jobject obj) {
  char *envp[] = { NULL };
  char *argv[] = {"xserver-vrx",
		  "-nolock",
		  "-noreset",
		  "-nopn",
		  "-nolisten", "unix",
		  "-screen", "1024x1024x24",
		  0 };
  if (setenv("SECURE_STORAGE_DIR", "/data/data/com.towersmatrix.vrx/files", 1))
    {
      LOGE("Failed to set base data dir in environment: %s", strerror(errno));
      return errno;
    }

  LOGI("nativeRunX");
  return android_main(8, argv, envp);
}
