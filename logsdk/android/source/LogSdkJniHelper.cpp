/*
 Copyright (c) 2015, LambdaCloud
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#include "LogSdkJniHelper.h"
#include <pthread.h>
#include <android/log.h>

#define  LOG_TAG    "LogSdkJniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace lambdacloud;

static pthread_key_t m_key;

JavaVM* LogSdkJniHelper::m_jvm = NULL;

void LogSdkJniHelper::setJavaVM(JavaVM* jvm)
{
    pthread_t thisthread = pthread_self();
    LOGD("LogSdkJniHelper::setJVM(%p), pthread_self() = %ld", jvm, thisthread);
    m_jvm = jvm;
    pthread_key_create(&m_key, NULL);
}

JNIEnv* LogSdkJniHelper::getEnv()
{
    JNIEnv* env = (JNIEnv*)pthread_getspecific(m_key);
    if (NULL == env)
    {
        env = LogSdkJniHelper::cacheEnv(m_jvm);
    }
    return env;
}

JNIEnv* LogSdkJniHelper::cacheEnv(JavaVM* jvm)
{
    JNIEnv* env = NULL;
    jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    
    switch (ret)
    {
        case JNI_OK:
            pthread_setspecific(m_key, env);
            return env;
        case JNI_EDETACHED:
            if (jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                LOGE("Failed to get the environment using AttachCurrentThread()");
                return NULL;
            }
            else
            {
                pthread_setspecific(m_key, env);
                return env;
            }
        case JNI_EVERSION:
            LOGE("JNI interface version 1.4 not supported");
        default:
            LOGE("Failed to get the environment using GetEnv()");
            return NULL;
    }
}

jclass LogSdkJniHelper::getClassId(const char* className)
{
    if (NULL == className) {
        return NULL;
    }
    
    JNIEnv* env = LogSdkJniHelper::getEnv();
    jclass _clazz = (jclass)env->FindClass(className);
    if (NULL == _clazz)
    {
        LOGE("Classloader failed to find class of %s", className);
        env->ExceptionClear();
    }
    return _clazz;
}

bool LogSdkJniHelper::getStaticMethodInfo(LogSdkJniMethodInfo& info, const char* className, const char* methodName, const char* methodParam)
{
    if ((NULL == className) ||
        (NULL == methodName) ||
        (NULL == methodParam)) {
        return false;
    }
    
    JNIEnv *env = LogSdkJniHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return false;
    }
    
    jclass classID = LogSdkJniHelper::getClassId(className);
    if (!classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }
    
    jmethodID methodID = env->GetStaticMethodID(classID, methodName, methodParam);
    if (! methodID) {
        LOGE("Failed to find static method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }
    
    info.classID = classID;
    info.env = env;
    info.methodID = methodID;
    return true;
}

bool LogSdkJniHelper::getMethodInfo(LogSdkJniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
{
    if ((NULL == className) ||
        (NULL == methodName) ||
        (NULL == paramCode)) {
        return false;
    }
    
    JNIEnv *env = LogSdkJniHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return false;
    }
    
    jclass classID = LogSdkJniHelper::getClassId(className);
    if (! classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }
    
    jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
    if (! methodID) {
        LOGE("Failed to find static method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }
    
    methodinfo.classID = classID;
    methodinfo.env = env;
    methodinfo.methodID = methodID;
    return true;
}

jobject LogSdkJniHelper::cStringArrayToJArray(std::vector<std::string> *array)
{
    if (NULL == array)
    {
        return NULL;
    }
    JNIEnv* env = LogSdkJniHelper::getEnv();
    jstring emptyStr = env->NewStringUTF("");
    jobjectArray data = (jobjectArray)env->NewObjectArray(array->size(), env->FindClass("java/lang/String"), emptyStr);
    for (int i=0; i<array->size(); i++)
    {
        jstring jstr = env->NewStringUTF((*array)[i].c_str());
        env->SetObjectArrayElement(data, 0, jstr);
        env->DeleteLocalRef(jstr);
    }
    env->DeleteLocalRef(emptyStr);
    return data;
}


std::string LogSdkJniHelper::jstring2string(jstring jstr)
{
    if (NULL == jstr)
    {
        return NULL;
    }
    JNIEnv* env = LogSdkJniHelper::getEnv();
    if (!env)
    {
        return NULL;
    }
    const char* chars = env->GetStringUTFChars(jstr, NULL);
    std::string ret(chars);
    env->ReleaseStringUTFChars(jstr, chars);
    return ret;
}

jobject LogSdkJniHelper::cMapToJMap(std::map<std::string, std::string>* map)
{
    if (NULL == map)
    {
        return NULL;
    }
    
    LogSdkJniMethodInfo methodInfo;
    getMethodInfo(methodInfo, "java/util/HashMap", "<init>", "()V");
    jobject obj = methodInfo.env->NewObject(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    
    getMethodInfo(methodInfo, "java/util/HashMap", "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    std::map<std::string, std::string>::iterator it;
    for(it = map->begin(); it != map->end(); ++it)
    {
        jstring key = methodInfo.env->NewStringUTF(it->first.c_str());
        jstring value = methodInfo.env->NewStringUTF(it->second.c_str());
        jobject returnObj = methodInfo.env->CallObjectMethod(obj, methodInfo.methodID, key, value);
        methodInfo.env->DeleteLocalRef(key);
        methodInfo.env->DeleteLocalRef(value);
        methodInfo.env->DeleteLocalRef(returnObj);
    }
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    
    return obj;
}
