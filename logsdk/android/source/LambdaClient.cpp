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

#include "LambdaClient.h"
#include "cocos2d.h"
#include <jni.h>
#include "LogSdkJniHelper.h"

#include <stdlib.h>
#include <android/log.h>

#define  LOG_TAG    "LambdaClient"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
 
USING_NS_CC;
using namespace lambdacloud;

void LambdaClient::setSendInterval(int intervalInMs)
{
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "setSendInteval", "(I)V"))
        {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, intervalInMs);
            return;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while setting send interval, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while setting send interval, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while setting send interval");
    }
}

void LambdaClient::debugLogSdk(bool debug)
{
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "debugLogSdk", "(Z)V"))
        {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, debug);
            return;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while setting debug flag, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while setting debug flag, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while setting debug flag");
    }
}

void LambdaClient::setToken(const char* token)
{
    if (NULL == token)
    {
        LOGE("parameter token should not be null while calling setToken method");
        return;
    }

    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "setToken", "(Ljava/lang/String;)V"))
        {
            jstring jToken = methodInfo.env->NewStringUTF(token);
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jToken);
            methodInfo.env->DeleteLocalRef(jToken);
            return;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while setting token, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while setting token, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while setting token");
    }
}

bool LambdaClient::writeLog(const char* log)
{
    if (NULL == log)
    {
        LOGE("parameter log should not be null while calling writeLog method");
        return false;
    }

    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendLog", "(Ljava/lang/String;)Z"))
        {
            jstring jLog = methodInfo.env->NewStringUTF(log);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jLog);
            methodInfo.env->DeleteLocalRef(jLog);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while writing log, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while writing log, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while writing log");
    }
}

bool LambdaClient::writeLog(const char* log, const char* tags)
{
    if (NULL == log)
    {
        LOGE("parameter log should not be null while calling writeLog method");
        return false;
    }

    if (NULL == tags)
    {
        return writeLog(log);
    }

    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendLog", "(Ljava/lang/String;Ljava/lang/String;)Z"))
        {
            jstring jLog = methodInfo.env->NewStringUTF(log);
            jstring jTags = methodInfo.env->NewStringUTF(tags);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jLog, jTags);
            methodInfo.env->DeleteLocalRef(jLog);
            methodInfo.env->DeleteLocalRef(jTags);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while writing log, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while writing log, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while writing log");
    }
}



bool LambdaClient::sendChannelInfo(const char* userID, const char* channelID, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendChannelInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendChannelInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jChannelID = methodInfo.env->NewStringUTF(channelID);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jChannelID, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jChannelID);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendChannelInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendChannelInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendChannelInfo");
    }
}

