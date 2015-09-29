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

bool LambdaClient::sendLoginInfo(const char* userID, const char* serverID, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendLoginInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendLoginInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jServerID = methodInfo.env->NewStringUTF(serverID);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jServerID, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jServerID);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendLoginInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendLoginInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendLoginInfo");
    }
}

bool LambdaClient::sendLogoutInfo(const char* userID, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendLogoutInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendLogoutInfo", "(Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendLogoutInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendLogoutInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendLogoutInfo");
    }
}

bool LambdaClient::sendUserTag(const char* userID, const char* tag, const char* subtag)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendUserTag method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendUserTag", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jTag = methodInfo.env->NewStringUTF(tag);
            jstring jSubTag = methodInfo.env->NewStringUTF(subtag);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jTag, jSubTag);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jTag);
            methodInfo.env->DeleteLocalRef(jSubTag);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendUserTag, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendUserTag, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendUserTag");
    }
}

bool LambdaClient::sendLevelBeginInfo(const char* userID, const char* levelName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendLevelBeginInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendLevelBeginInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jLevelName = methodInfo.env->NewStringUTF(levelName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jLevelName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jLevelName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendLevelBeginInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendLevelBeginInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendLevelBeginInfo");
    }
}

bool LambdaClient::sendLevelCompleteInfo(const char* userID, const char* levelName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendLevelCompleteInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendLevelCompleteInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jLevelName = methodInfo.env->NewStringUTF(levelName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jLevelName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jLevelName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendLevelCompleteInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendLevelCompleteInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendLevelCompleteInfo");
    }
}

bool LambdaClient::sendLevelFailInfo(const char* userID, const char* levelName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendLevelFailInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendLevelFailInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jLevelName = methodInfo.env->NewStringUTF(levelName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jLevelName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jLevelName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendLevelFailInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendLevelFailInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendLevelFailInfo");
    }
}

bool LambdaClient::sendTaskBeginInfo(const char* userID, const char* taskName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendTaskBeginInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendTaskBeginInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jTaskName = methodInfo.env->NewStringUTF(taskName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jTaskName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jTaskName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendTaskBeginInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendTaskBeginInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendTaskBeginInfo");
    }
}

bool LambdaClient::sendTaskCompleteInfo(const char* userID, const char* taskName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendTaskCompleteInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendTaskCompleteInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jTaskName = methodInfo.env->NewStringUTF(taskName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jTaskName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jTaskName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendTaskCompleteInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendTaskCompleteInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendTaskCompleteInfo");
    }
}

bool LambdaClient::sendTaskFailInfo(const char* userID, const char* taskName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendTaskFailInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendTaskFailInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jTaskName = methodInfo.env->NewStringUTF(taskName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jTaskName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jTaskName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendTaskFailInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendTaskFailInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendTaskFailInfo");
    }
}

bool LambdaClient::sendGetItemInfo(const char* userID, const char* itemName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendGetItemInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendGetItemInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jItemName = methodInfo.env->NewStringUTF(itemName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jItemName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jItemName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendGetItemInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendGetItemInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendGetItemInfo");
    }
}

bool LambdaClient::sendBuyItemInfo(const char* userID, const char* itemName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendBuyItemInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendBuyItemInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jItemName = methodInfo.env->NewStringUTF(itemName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jItemName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jItemName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendBuyItemInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendBuyItemInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendBuyItemInfo");
    }
}

bool LambdaClient::sendConsumeItemInfo(const char* userID, const char* itemName, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendConsumeItemInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendConsumeItemInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jItemName = methodInfo.env->NewStringUTF(itemName);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jItemName, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jItemName);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendConsumeItemInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendConsumeItemInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendConsumeItemInfo");
    }
}

bool LambdaClient::sendGainCoinInfo(const char* userID, const char* coinType, long gain, long total, const char* reason, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendGainCoinInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendGainCoinInfo", "(Ljava/lang/String;Ljava/lang/String;JJLjava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jCoinType = methodInfo.env->NewStringUTF(coinType);
            jlong jGain = gain;
            jlong jTotal = total;
            jstring jReason = methodInfo.env->NewStringUTF(reason);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jCoinType, jGain, jTotal, jReason, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jCoinType);
            methodInfo.env->DeleteLocalRef(jReason);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendGainCoinInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendGainCoinInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendGainCoinInfo");
    }
}

bool LambdaClient::sendConsumeCoinInfo(const char* userID, const char* coinType, long use, long total, const char* reason, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendConsumeCoinInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendConsumeCoinInfo", "(Ljava/lang/String;Ljava/lang/String;JJLjava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jCoinType = methodInfo.env->NewStringUTF(coinType);
            jlong jUse = use;
            jlong jTotal = total;
            jstring jReason = methodInfo.env->NewStringUTF(reason);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jCoinType, jUse, jTotal, jReason, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jCoinType);
            methodInfo.env->DeleteLocalRef(jReason);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendConsumeCoinInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendConsumeCoinInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendConsumeCoinInfo");
    }
}

bool LambdaClient::sendDeviceInfo(const char* userID, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendDeviceInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendDeviceInfo", "(Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendDeviceInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendDeviceInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendDeviceInfo");
    }
}

bool LambdaClient::sendCurrencyPaymentInfo(const char* userID, const char* orderID, const char* iapID, const char* amount, const char* currencyType, const char* paymentType, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendCurrencyPaymentInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendCurrencyPaymentInfo",
                                                 "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jOrderID = methodInfo.env->NewStringUTF(orderID);
            jstring jIapID = methodInfo.env->NewStringUTF(iapID);
            jstring jAmount = methodInfo.env->NewStringUTF(amount);
            jstring jCurrencyType = methodInfo.env->NewStringUTF(currencyType);
            jstring jPaymentType = methodInfo.env->NewStringUTF(paymentType);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jOrderID, jIapID, jAmount, jCurrencyType, jPaymentType, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jOrderID);
            methodInfo.env->DeleteLocalRef(jIapID);
            methodInfo.env->DeleteLocalRef(jAmount);
            methodInfo.env->DeleteLocalRef(jCurrencyType);
            methodInfo.env->DeleteLocalRef(jPaymentType);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendCurrencyPaymentInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendCurrencyPaymentInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendCurrencyPaymentInfo");
    }
}

bool LambdaClient::sendCustomizedInfo(const char* userID, const char* logtype, std::map<std::string, std::string>* props)
{
    if (NULL == userID)
    {
        LOGE("parameter userID should not be null while calling sendCustomizedInfo method");
        return false;
    }
    
    try
    {
        LogSdkJniMethodInfo methodInfo;
        if (LogSdkJniHelper::getStaticMethodInfo(methodInfo, "com/lambdacloud/sdk/android/LogAgent", "sendCustomizedInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)Z"))
        {
            jstring jUserID = methodInfo.env->NewStringUTF(userID);
            jstring jLogType = methodInfo.env->NewStringUTF(logtype);
            jobject jProps = LogSdkJniHelper::cMapToJMap(props);
            jboolean added = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jUserID, jLogType, jProps);
            methodInfo.env->DeleteLocalRef(jUserID);
            methodInfo.env->DeleteLocalRef(jLogType);
            methodInfo.env->DeleteLocalRef(jProps);
            return (bool)added;
        }
    } catch (const std::exception& ex) {
        LOGE("LambdaClient got an exception while calling sendCustomizedInfo, detail is %s", ex.what());
    } catch (const std::string& ex) {
        LOGE("LambdaClient got a string exception while calling sendCustomizedInfo, detail is %s", ex.c_str());
    } catch (...) {
        LOGE("LambdaClient got an unknown exception while calling sendCustomizedInfo");
    }

}

