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

#ifndef __cocos2d_libs__LambdaDevice__
#define __cocos2d_libs__LambdaDevice__

#include <stdio.h>
#include <string>

namespace lambdacloud {
    
#define LAMBDA_NETWORK_STATUS_NOT_REACHABLE     0
#define LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WIFI 1
#define LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WWAN 2
    
#define LAMBDA_PLATFORM_IPHONE 0
#define LAMBDA_PLATFORM_IPAD 1
#define LAMBDA_PLATFORM_ANDROID 2
#define LAMBDA_PLATFORM_WP 3
#define LAMBDA_PLATFORM_WIN 4
#define LAMBDA_PLATFORM_WINRT 5
#define LAMBDA_PLATFORM_MAC 6
#define LAMBDA_PLATFORM_OTHERS 7
    
#define LAMBDA_DEVICE_STATUS_UNKNOWN "unknown"
    
    class LambdaDevice
    {
    public:
        static std::string getCarrierName(void);
        static int getNetworkStatus(void);
        static std::string getDeviceName(void);
        static int getApplicationPlatform(void);
        
    private:
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        static std::string getStaticStringField(const char* className, const char* fieldName);
        #endif
    };
}

#endif /* defined(__SDKTest1__LambdaDevice__) */
