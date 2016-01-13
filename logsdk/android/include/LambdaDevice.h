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

#ifndef __cocos2d_libs__LambdaDevice__
#define __cocos2d_libs__LambdaDevice__

#include <stdio.h>
#include <string>

namespace lambdacloud {
    
#define LAMBDA_NETWORK_STATUS_NOT_REACHABLE         "NOT_REACHABLE"
#define LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WIFI    "WIFI"
#define LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WWAN    "WWAN"
    
#define LAMBDA_PLATFORM_IPHONE      "IPHONE"
#define LAMBDA_PLATFORM_IPAD        "IPAD"
#define LAMBDA_PLATFORM_ANDROID     "ANDROID"
#define LAMBDA_PLATFORM_WP          "WP"
#define LAMBDA_PLATFORM_WIN         "WIN"
#define LAMBDA_PLATFORM_WINRT       "WINRT"
#define LAMBDA_PLATFORM_MAC         "MAC"
#define LAMBDA_PLATFORM_OTHERS      "OTHERS"
    
#define LAMBDA_DEVICE_INFO_UNKNOWN  "UNKNOWN"
    
    class LambdaDevice
    {
    public:
    	static void init();
        static std::string getAppList(void);
        static std::string getApplicationPlatform(void);
        static std::string getCarrierName(void);
        static std::string getDeviceName(void);
        static std::string getNetworkStatus(void);
        static std::string getOsVersion(void);
        static std::string getScreenDimension(void);
        static std::string getImei(void);
        static std::string getLocation(void);
        static std::string getBatteryPower(void);
        
    };
}

#endif /* defined(__SDKTest1__LambdaDevice__) */
