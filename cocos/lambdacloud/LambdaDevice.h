//
//  LambdaDevice.h
//  SDKTest1
//
//  Created by sky4star on 14/12/23.
//
//

#ifndef __cocos2d_libs__LambdaDevice__
#define __cocos2d_libs__LambdaDevice__

#include <stdio.h>
#include <string>

namespace lambdacloud {
    
#define lambdaNetworkStatusNotReachable     0
#define lambdaNetworkStatusReachableViaWiFi 1
#define lambdaNetworkStatusReachableViaWWAN 2
    
#define lambdaPlatformIPhone 0
#define lambdaPlatformIPad 1
#define lambdaPlatformAndroid 2
#define lambdaPlatformWp 3
#define lambdaPlatformWin 4
#define lambdaPlatformWinRT 5
#define lambdaPlatformMac 6
#define lambdaPlatformOthers 7
    
#define lambdaUnknown "unknown"
    
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
