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

#include "LambdaDevice.h"
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <CoreTelephony/CTCarrier.h>
#import "ReachabilityIOSMac.h"
#import "CCApplication.h"
#import "sys/utsname.h"

using namespace lambdacloud;

std::string LambdaDevice::getCarrierName(void)
{
    try
    {
        CTTelephonyNetworkInfo *netinfo = [[CTTelephonyNetworkInfo alloc] init];
        CTCarrier *carrier = [netinfo subscriberCellularProvider];
        if (carrier != nil)
        {
            std::string carrierName = [[carrier carrierName] UTF8String];
            [netinfo release];
            return carrierName;
        }
        else
        {
            [netinfo release];
            return LAMBDA_DEVICE_INFO_UNKNOWN;
        }
    } catch (const std::exception& ex) {
        CCLOGERROR("LambdaDevice got an exception while reading carrier name, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("LambdaDevice got a string exception while reading carrier name, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("LambdaDevice got an unknown exception while reading carrier name");
    }
    return LAMBDA_DEVICE_INFO_UNKNOWN;
}

std::string LambdaDevice::getNetworkStatus(void)
{
    try
    {
        NetworkStatus status = [[ReachabilityIOSMac reachabilityForInternetConnection] currentReachabilityStatus];
        if (status == ReachableViaWiFi)
            return LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WIFI;
        if (status == ReachableViaWWAN)
            return LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WWAN;
        return LAMBDA_NETWORK_STATUS_NOT_REACHABLE;
    } catch (const std::exception& ex) {
        CCLOGERROR("LambdaDevice got an exception while getting network status, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("LambdaDevice got a string exception while reading network status, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("LambdaDevice got an unknown exception while reading network status");
    }
    return LAMBDA_DEVICE_INFO_UNKNOWN;
}

std::string LambdaDevice::getApplicationPlatform(void)
{
    try
    {
        auto platform = cocos2d::CCApplication::sharedApplication()->getTargetPlatform();
        if (platform == cocos2d::kTargetIphone)
            return LAMBDA_PLATFORM_IPHONE;
        else if (platform == cocos2d::kTargetIpad)
            return LAMBDA_PLATFORM_IPAD;
        else if (platform == cocos2d::kTargetMacOS)
            return LAMBDA_PLATFORM_MAC;
        return LAMBDA_PLATFORM_OTHERS;
    } catch (const std::exception& ex) {
        CCLOGERROR("LambdaDevice got an exception while getting platform info, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("LambdaDevice got a string exception while getting platform info, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("LambdaDevice got an unknown exception while getting platform info");
    }
    return LAMBDA_DEVICE_INFO_UNKNOWN;
}

std::string LambdaDevice::getDeviceName(void)
{
    try
    {
        struct utsname systemInfo;
        uname(&systemInfo);
        NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
        return [deviceString UTF8String];
    } catch (const std::exception& ex) {
        CCLOGERROR("LambdaDevice got an exception while reading device name, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("LambdaDevice got a string exception while reading device name, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("LambdaDevice got an unknown exception while reading device name");
    }
    return LAMBDA_DEVICE_INFO_UNKNOWN;
}