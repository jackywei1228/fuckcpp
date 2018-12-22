#include <jni.h>
#include <string>
#include "JKRoAi.h"
#include "JKTypes.h"
#include "JKPaser.hpp"

JNIEnv *myenv = NULL;


extern "C" JNIEXPORT jstring

JNICALL
Java_me_ifonly_fuckcpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++,And fuck you!";
    myenv = env;
    JKRoAi* roAi = new JKRoAi();
    JKPaser* paser = new JKPaser("debug");
    roAi->login();
    LOGD("%s","fuck U");
    return env->NewStringUTF(hello.c_str());
}


