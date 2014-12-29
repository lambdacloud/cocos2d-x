//
//  LambdaDeviceAndroid.cpp
//  SDKTest1
//
//  Created by sky4star on 14/12/23.
//
//

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
    
    return LAMBDA_DEVICE_STATUS_UNKNOWN;

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