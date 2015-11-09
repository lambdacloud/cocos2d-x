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


#ifndef __cocos2d_libs__LambdaClient__
#define __cocos2d_libs__LambdaClient__

#include <map>
#include <stdio.h>
#include <string>
#include <vector>

namespace lambdacloud {
    
    
    /**
     * This class is used to upload events to lambdacloud.
     **/
    class LambdaClient
    {
    public:
        
        /** API to set sending interval for lambdacloud sdk.
         
         Lambdacloud sdk will send logs in period, by default the interval is 10 seconds.
         */
        static void setSendInterval(int intervalInSecond);
        
        /** 设置最大等待发送数。SDK会先将要发送的日志缓存下来，然后周期性的发送。如果两次发送之间缓存的日志数超过了最大值，新进来的日志会被抛弃掉。
            如果需要在短时间内记录大量的日志，建议适当调大此值。
            默认值为100。
         */
        static void setMaxQueueSize(int queueSize);
        
        /** Turn it on to output some debug info for lambdacloud sdk.
         */
        static void debugLogSdk(bool debug);
        
        /** API to set app token before sending any event to lambdacloud.
         
         Token is an unique array of chars to identify the application who is sending events to lambdacloud.
         Please remember to call this API before sending any event. 
         If you haven't received a token yet, please contract lambdacloud.
         */
        static void setToken(const char* token);
        
        /** Old style API to send events, will be deprecated in future.
         
         @param log
         Event should be in specific format, for example 日志类型[your_logtype],时间[2011-10-08T07:07:09+08:00],用户[userid],key1[value1],key2[value2].
         In the log, keys like '日志类型', '时间', '用户' are necessary parts.
         
         @return true, if everything is ok. Else false.
         */
        static bool writeLog(const char* log);
        
        /** Old style API to send events, will be deprecated in future.
         
         @param log
         Event should be in specific format, for example 日志类型[your_logtype],时间[2011-10-08T07:07:09+08:00],用户[userid],key1[value1],key2[value2].
         In the log, keys like '日志类型', '时间', '用户' are necessary parts.
         
         @param tags
         Tags for this event, seperated with comma.
         
         @return true, if everything is ok. Else false.
         */
        static bool writeLog(const char* log, const char* tags);
        
        /** This is to send channel info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param channelID
         Unique id to identify which channel user comes from, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendChannelInfo(const char* userID, const char* channelID, std::map<std::string, std::string>* props);
        
        /** This is to send user login info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param serverID
         Unique id to identify the server which user locates in, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendLoginInfo(const char* userID, const char* serverID, std::map<std::string, std::string>* props);
        
        /** This is to send user logout info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendLogoutInfo(const char* userID, std::map<std::string, std::string>* props);
        
        /** This is to mark user with tags.
         
         If there is more than one major tag on user, you could call this API multiple times.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param tag
         Major tag label for user.
         
         @param subtag
         Subtag under the root tag, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendUserTag(const char* userID, const char* tag, const char* subtag);
        
        /** This is to send level begin info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param levelName
         Unique id to identify the level which user locates in, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendLevelBeginInfo(const char* userID, const char* levelName, std::map<std::string, std::string>* props);
        
        /** This is to send level complete info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param levelName
         Unique id to identify the level which user locates in, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendLevelCompleteInfo(const char* userID, const char* levelName, std::map<std::string, std::string>* props);
        
        /** This is to send level fail info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param levelName
         Unique id to identify the level which user just failed, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendLevelFailInfo(const char* userID, const char* levelName, std::map<std::string, std::string>* props);
        
        /** This is to send task begin info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param taskName
         Unique id to identify the task which user is trying to accomplish, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendTaskBeginInfo(const char* userID, const char* taskName, std::map<std::string, std::string>* props);
        
        /** This is to send task complete info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param taskName
         Unique id to identify the task which user just accomplished, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendTaskCompleteInfo(const char* userID, const char* taskName, std::map<std::string, std::string>* props);
        
        /** This is to send task complete info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param taskName
         Unique id to identify the task which user just failed, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendTaskFailInfo(const char* userID, const char* taskName, std::map<std::string, std::string>* props);
        
        /** This is to send getting item info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param itemName
         Unique id to identify the item which user just gained, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendGetItemInfo(const char* userID, const char* itemName, std::map<std::string, std::string>* props);
        
        /** This is to send buying item info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param itemName
         Unique id to identify the item which user just brought, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendBuyItemInfo(const char* userID, const char* itemName, std::map<std::string, std::string>* props);
        
        /** This is to send consuming item info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param itemName
         Unique id to identify the item which user just used, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendConsumeItemInfo(const char* userID, const char* itemName, std::map<std::string, std::string>* props);
        
        /** This is to send gaining app coin info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param coinType
         Type of coin, in case there is more than one coin type in your app, null is also acceptable.
         
         @param gain
         The coin user just gained in the app.
         
         @param total
         Total number of this type of coin the user owns.
         
         @param reason
         The reason user gains, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendGainCoinInfo(const char* userID, const char* coinType, long gain, long total, const char* reason, std::map<std::string, std::string>* props);
        
        /** This is to send consuming app coin info.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param coinType
         Type of coin, in case there is more than one coin type in your app, null is also acceptable.
         
         @param use
         The coin user just used in the app.
         
         @param total
         Total number of this type of coin the user owns after this consumption.
         
         @param reason
         The reason user consume coins, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendConsumeCoinInfo(const char* userID, const char* coinType, long use, long total, const char* reason, std::map<std::string, std::string>* props);
        
        /** This is to collect and send some device info.
         
         Currently, we will try to collect the following device info:
         1. Platform info, like android or ios
         2. Network status, is user connecting with wifi or wwan
         3. Device brand name and model 
         4. Operator name
         5. Detailed os version
         6. Screen demension, like 800x600
         7. EMEI to identify user device
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendDeviceInfo(const char* userID, std::map<std::string, std::string>* props);
        
        /** This is to send payment info of real money.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param orderID
         Unique id to identify the payment transaction, null is also acceptable.
         
         @param iapID
         Unique id to identify the gift bag, null is also acceptable.
         
         @param amount
         How much the user just payed, null is also acceptable.
         
         @param currencyType
         The type of currency user just payed, null is also acceptable.
         
         @param paymentType
         The way user used to pay this bill, like ali or paypal, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendCurrencyPaymentInfo(const char* userID, const char* orderID, const char* iapID, const char* amount, const char* currencyType, const char* paymentType, std::map<std::string, std::string>* props);
        
        /** This is to send any customized event.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param logtype
         Please specify different log types for different events. Both english and chinese name is accepable. This is a necessary parameter.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
        */
        static bool sendCustomizedInfo(const char* userID, const char* logtype, std::map<std::string, std::string>* props);
        
        /** This is to send any customized funnel info for further analyze.
         
         @param userID
         Unique id to identify user. This is a necessary parameter.
         
         @param funnelType
         Please specify different funnel types for different funnel analyze. Both english and chinese name is accepable. This is a necessary parameter.
         
         @param stepName
         Specify an unique name for each step in a funnel. This is a necessary parameter.
         
         @param stepStatus
         Status of current step, null is also acceptable.
         
         @param description
         Additional description for current step, null is also acceptable.
         
         @param props
         Send any customized info through this map, null is also acceptable.
         
         @return true, if everything is ok. Else false.
         */
        static bool sendCustomizedFunnel(const char* userID, const char* funnelType, const char* stepName, const char* stepStatus, const char* description, std::map<std::string, std::string>* props);
        
        /** This is to get current version of lambdacloud sdk.
         
         @return detailed sdk version
         */
        static std::string getVersion();

        /* 发送应用名日志

         @param userID
         用户身份标识
         
         */
        static bool sendAppList(const char* userID);
    };
}

#endif /* defined(__cocos2d_libs__LambdaClient__) */
