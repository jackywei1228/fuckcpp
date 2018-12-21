#include <jni.h>
#include <string>


JNIEnv *myenv = NULL;


extern "C" JNIEXPORT jstring

JNICALL
Java_me_ifonly_fuckcpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++,And fuck you!";
    myenv = env;
    return env->NewStringUTF(hello.c_str());
}


