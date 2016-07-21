#include <jni.h>

#include "vrx.h"

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
  LOGI("nativeRunX");
  return android_main(8, argv, envp);
}
