//
//  LambdaClient.h
//  cocos2d_libs
//
//  Created by sky4star on 14/12/14.
//
//

#ifndef __cocos2d_libs__LambdaClient__
#define __cocos2d_libs__LambdaClient__

#include <stdio.h>
#include "base/ccMacros.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

namespace lambdacloud {
    class CC_DLL LambdaClient : public cocos2d::Ref
    {
    public:
        static LambdaClient* getInstance();
        void setToken(const std::string& token);
        void writeLog(const std::string& log, std::vector<std::string> tags);
        void debugLog();
        
    private:
        LambdaClient();
        virtual ~LambdaClient();
        bool init(void);
        std::string generateJsonData(const std::string& log, std::vector<std::string> tags);
        void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    };
}

#endif /* defined(__cocos2d_libs__LambdaClient__) */
