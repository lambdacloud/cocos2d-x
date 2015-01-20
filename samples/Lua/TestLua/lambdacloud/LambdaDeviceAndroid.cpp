/*
 Copyright (c) 2014, LambdaCloud
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

#include "LambdaDevice.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#include <stdlib.h>
#include <android/log.h>

USING_NS_CC;
using namespace lambdacloud;

std::string LambdaDevice::getCarrierName(void)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "android/telephony/TelephonyManager", "getNetworkOperatorName",
                                       "()L"))
    {
        jstring jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        return JniHelper::jstring2string(jstr);
    }
    
    return "";

}

int LambdaDevice::getNetworkStatus(void)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/lambdacloud/sdk/LambdaNetworkUtil", "getInternetConnectionStatus",
                                       "()I"))
    {
        jint ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        return ret;
    }
 
    return LAMBDA_NETWORK_STATUS_NOT_REACHABLE;
}

int LambdaDevice::getApplicationPlatform(void)
{
    return LAMBDA_PLATFORM_ANDROID;
}

std::string LambdaDevice::getDeviceName(void)
{
    return getStaticStringField("android/os/Build", "MODEL");
}

std::string LambdaDevice::getStaticStringField(const char* className, const char* fieldName)
{
    if ((nullptr == className) || (nullptr == fieldName))
    {
        CCLOG("className and fieldName should not be null");
        return LAMBDA_DEVICE_STATUS_UNKNOWN;
    }
    
    JNIEnv *env = JniHelper::getEnv();
    if (!env)
    {
        CCLOG("Failed to get the environment using GetEnv()");
        return LAMBDA_DEVICE_STATUS_UNKNOWN;
    }
    
    jclass classID = env->FindClass(className);
    if (!classID)
    {
        CCLOG("Failed to find class %s", className);
        env->ExceptionClear();
        return LAMBDA_DEVICE_STATUS_UNKNOWN;
    }
    
    jfieldID fieldID = env->GetStaticFieldID(classID, fieldName, "Ljava/lang/String;");
    if(!fieldID)
    {
        CCLOG("Failed to find field of %s", fieldName);
        env->ExceptionClear();
        return LAMBDA_DEVICE_STATUS_UNKNOWN;
    }
    
    jstring jstr = (jstring)env->GetStaticObjectField(classID, fieldID);
    return JniHelper::jstring2string(jstr);
}
#endif