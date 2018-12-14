#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring

JNICALL
Java_me_ifonly_fuckcpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++,And fuck you!";
    return env->NewStringUTF(hello.c_str());
}
