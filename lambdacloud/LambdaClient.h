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


#ifndef __cocos2d_libs__LambdaClient__
#define __cocos2d_libs__LambdaClient__

#include <stdio.h>
#include "cocoa/CCObject.h"
#include "ccMacros.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace lambdacloud {
    
    
    /**
     * This class is used to upload events to lambdacloud.
     **/
    class CC_DLL LambdaClient : public cocos2d::CCObject
    {
    public:
        static LambdaClient* getInstance();
        void setToken(const std::string& token);
        void writeLog(const std::string& log, cocos2d::CCArray *tags);
        void debugLog();
        
    private:
        LambdaClient();
        virtual ~LambdaClient();
        bool init(void);
        std::string generateJsonData(const std::string& log, cocos2d::CCArray *tags);
        void onHttpRequestCompleted(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response);
    };
}

#endif /* defined(__cocos2d_libs__LambdaClient__) */
