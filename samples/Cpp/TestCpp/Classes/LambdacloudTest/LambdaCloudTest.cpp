#include "LambdacloudTest.h"
#include "../testResource.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "LambdaClient.h"
#include "LambdaDevice.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "DeviceInfo.h"
#import "Reachability.h"
#import "LogAgent.h"
#import "LogSpout.h"
#import "LogRequest.h"
#import "LogSender.h"
#import "LogSdkConfig.h"
#import "LogAgent.h"
#import "LogUtil.h"
#endif
#ifdef __cplusplus
#include <string>
#endif
#ifdef __OBJC__
#include <Foundation/Foundation.h>
#endif
#include <map>
#include <vector>
#include <ctime>
#include <iostream>


USING_NS_CC;
USING_NS_CC_EXT;

std::string getISOTime()
{
    time_t now;
    time(&now);
    char buf[sizeof "2011-10-08T07:07:09+08:00"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    std::string date(buf);
    return date;
}

LambdaCloudTest::LambdaCloudTest()
: m_labelStatusCode(NULL)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    const int MARGIN = 40;
    const int SPACE = 35;
    
    CCLabelTTF *label = CCLabelTTF::create("LambdaCloud Test", "Arial", 28);
    label->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN));
    addChild(label, 0);
    
    CCMenu *menuRequest = CCMenu::create();
    menuRequest->setPosition(CCPointZero);
    addChild(menuRequest);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    // Set logsdk debug flag true
    lambdacloud::LambdaClient::debugLogSdk(true);
    
    // Set log interval 10 seconds
    lambdacloud::LambdaClient::setSendInterval(10);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [LogAgent setDebugMode:true];
#endif
    // Send Stress Test Logs
    CCLabelTTF *labelDemo = CCLabelTTF::create("Stress Test, 15days x 1000messages/day", "Arial", 22);
    CCMenuItemLabel *itemDemo = CCMenuItemLabel::create(labelDemo, this, menu_selector(LambdaCloudTest::onMenuSendStressTestLogsClicked));
    itemDemo->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemDemo);
    
    // Get Device Info
    CCLabelTTF *labelGet = CCLabelTTF::create("Test Get Device Info", "Arial", 22);
    CCMenuItemLabel *itemGet = CCMenuItemLabel::create(labelGet, this, menu_selector(LambdaCloudTest::onMenuGetDeviceInfoClicked));
    itemGet->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - SPACE));
    menuRequest->addChild(itemGet);
    
    // Send Basic Message
    CCLabelTTF *labelPost = CCLabelTTF::create("Test Send Basic Message", "Arial", 22);
    CCMenuItemLabel *itemPost = CCMenuItemLabel::create(labelPost, this, menu_selector(LambdaCloudTest::onMenuSendBasicMessageClicked));
    itemPost->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE));
    menuRequest->addChild(itemPost);
    
    // Send Login Info
    CCLabelTTF *labelPostLogin = CCLabelTTF::create("Test Send Login Message", "Arial", 22);
    CCMenuItemLabel *itemPostLogin = CCMenuItemLabel::create(labelPostLogin, this, menu_selector(LambdaCloudTest::onMenuSendLoginMessageClicked));
    itemPostLogin->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 3 * SPACE));
    menuRequest->addChild(itemPostLogin);
    
    // Response Code Label
    m_labelStatusCode = CCLabelTTF::create("HTTP Status Code", "Marker Felt", 20);
    m_labelStatusCode->setPosition(ccp(winSize.width / 2,  winSize.height - MARGIN - 6 * SPACE));
    addChild(m_labelStatusCode);
}

LambdaCloudTest::~LambdaCloudTest()
{
}

void LambdaCloudTest::onMenuSendStressTestLogsClicked(cocos2d::CCObject *sender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // 配置token和参数
    [LogAgent setToken:@"d029dfc9-c74f-4f31-b896-998f7d18fcfc"];
    [LogAgent SetMaxQueueSize:20000];
    int num =0;
    NSInteger userId =100000;
    for (int session=0; session<10000; session++) {
        
        try {
            NSString *isoTime = [NSString stringWithUTF8String:getISOTime().c_str()];
            // NSString *userId = [NSString stringWithUTF8String:userid.c_str()];
            
            NSString *networkStatus = [DeviceInfo getInternetConnectionStatus];
            NSString *deviceInfo = [DeviceInfo getDeviceName];
            NSString *operationInfo = [DeviceInfo getOperationInfo];
            NSString *systemOs = [DeviceInfo getSystemOS];
            
            NSString *string = [[NSString alloc]initWithFormat:@"日志类型[LambdaCloud设备信息],时间[%@],用户[%d],操作系统[%@],操作系统版本[%@],设备名称[%@],网络状态[%@]", isoTime, userId++,operationInfo,systemOs,deviceInfo,networkStatus];
            [LogAgent addLog:string];
            NSLog(@"日志：%@",string);
            CCLog("总数：%d",++num);
            
        } catch (std::exception e) {
            CCLOGERROR("got exception when recording login info, detail is %s", e.what());
        }
    }
    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_labelStatusCode->setString("For Android Test is null");
#endif
}

void LambdaCloudTest::onMenuGetDeviceInfoClicked(cocos2d::CCObject *sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLog("LambdaCloudTest getDeviceName %s", lambdacloud::LambdaDevice::getDeviceName().c_str());
    CCLog("LambdaCloudTest getCarrierName %s", lambdacloud::LambdaDevice::getCarrierName().c_str());
    CCLOG("LambdaCloudTest getApplicationPlatform %s", lambdacloud::LambdaDevice::getApplicationPlatform().c_str());
    CCLog("LambdaCloudTest getNetworkStatus %s", lambdacloud::LambdaDevice::getNetworkStatus().c_str());
    CCLog("LambdaCloudTest getOsVersion %s", lambdacloud::LambdaDevice::getOsVersion().c_str());
    CCLog("LambdaCloudTest getScreenDimension %s", lambdacloud::LambdaDevice::getScreenDimension().c_str());
    CCLog("LambdaCloudTest getImei %s", lambdacloud::LambdaDevice::getImei().c_str());
    CCLog("LambdaCloudTest getAppList %s",lambdacloud::LambdaDevice::getAppList().c_str());
    
    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [LogUtil debug:@"LambdaCloudIosTest getDeviceName" message:[DeviceInfo getDeviceName]];
    [LogUtil debug:@"LambdaCloudIosTest getInternetcConnectionStatus" message:[DeviceInfo getInternetConnectionStatus]];
    [LogUtil debug:@"LambdaCloudIosTest getOperationInfo" message:[DeviceInfo getOperationInfo]];
    [LogUtil debug:@"LambdaCloudIosTest getSystemOS" message:[DeviceInfo getSystemOS]];
    [LogUtil debug:@"LambdaCloudIosTest getBatterypower" message:[DeviceInfo getBatteryPower]];
    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
    
#endif
}

void LambdaCloudTest::onMenuSendBasicMessageClicked(cocos2d::CCObject *sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // Send a test log with each API
    std::map<std::string, std::string> props;
    props.insert(std::pair<std::string, std::string>("prop_1", "value_1"));
    props.insert(std::pair<std::string, std::string>("prop_2", "value_2"));
    lambdacloud::LambdaClient::setToken("d029dfc9-c74f-4f31-b896-998f7d18fcfc");
    std::string userId = "test_user";
    std::string channelId = "test_channel";
    lambdacloud::LambdaClient::sendChannelInfo(userId.c_str(), channelId.c_str(), &props);
    lambdacloud::LambdaClient::sendLoginInfo(userId.c_str(), "test_server", &props);
    lambdacloud::LambdaClient::sendLogoutInfo(userId.c_str(), &props);
    lambdacloud::LambdaClient::sendUserTag(userId.c_str(), "test_tag", "test_sub_tag");
    lambdacloud::LambdaClient::sendLevelBeginInfo(userId.c_str(), "test_level", &props);
    lambdacloud::LambdaClient::sendLevelCompleteInfo(userId.c_str(), "test_level", &props);
    lambdacloud::LambdaClient::sendLevelFailInfo(userId.c_str(), "test_level", &props);
    lambdacloud::LambdaClient::sendTaskBeginInfo(userId.c_str(), "test_task", &props);
    lambdacloud::LambdaClient::sendTaskCompleteInfo(userId.c_str(), "test_task", &props);
    lambdacloud::LambdaClient::sendTaskFailInfo(userId.c_str(), "test_task", &props);
    lambdacloud::LambdaClient::sendGetItemInfo(userId.c_str(), "test_item", &props);
    lambdacloud::LambdaClient::sendBuyItemInfo(userId.c_str(), "test_item", &props);
    lambdacloud::LambdaClient::sendConsumeItemInfo(userId.c_str(), "test_item", &props);
    CCLog("LambdaCloudTest sendConsumeItemInfo done");
    lambdacloud::LambdaClient::sendGainCoinInfo(userId.c_str(), "test_coin_type", 100L, 900L, "complate_test_task", &props);
    lambdacloud::LambdaClient::sendConsumeCoinInfo(userId.c_str(), "test_coin_type", 200L, 700L, "complate_test_task", &props);
    lambdacloud::LambdaClient::sendDeviceInfo(userId.c_str(), &props);
    std::string methods= "getDeviceName,getOperatorInfo";
    lambdacloud::LambdaClient::sendDeviceInfo(userId.c_str(), methods.c_str(), &props);
    lambdacloud::LambdaClient::sendCurrencyPaymentInfo(userId.c_str(), "test_order", "test_iap", "1000", "RMB", "unionpay", &props);
    lambdacloud::LambdaClient::sendCustomizedInfo(userId.c_str(), "test_customized_event", &props);
    lambdacloud::LambdaClient::sendCustomizedFunnel(userId.c_str(), "新手漏斗", "登陆游戏", "成功", NULL, &props);
    lambdacloud::LambdaClient::sendAppList(userId.c_str());
    
    std::string version = lambdacloud::LambdaClient::getVersion();
    CCLog("lambdacloud sdk version %s", version.c_str());
    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //测试数据
    NSString *userId = @"testId";
    NSArray *methods = [[NSArray alloc]initWithObjects:@"getDeviceName",@"getSystemOs",@"getOperationInfo",@"getBatteryPower",@"getLocation", nil];
    NSString *channelId = @"testChannelId";
    NSString *serverId = @"testServerId";
    NSString *beginLevelName = @"大闹天宫";
    NSString *completeLevelName = @"三打白骨精";
    NSString *failLevelName = @"女儿国";
    NSString *beginTaskName = @"高老庄娶亲";
    NSString *completeTaskName = @"情迷盘丝洞";
    NSString *failTaskName = @"八戒大战流沙河";
    NSString *getItemName = @"金箍棒";
    NSString *buyItemName = @"恢复魔力值药水";
    NSString *consumeItmeName = @"长生不老丹药";
    NSString *coinType = @"钻石";
    long gain = 1000;
    long use = 388;
    long total = 3000;
    NSString *gainReason = @"打败黑风怪";
    NSString *useReason = @"被白骨精打伤";
    NSString *orderId = @"支付宝：12345667889";
    NSString *iapId = @"付费模式";
    NSString *amount = @"200";
    NSString *currencyType = @"RMB";
    NSString *paymentType = @"支付宝";
    NSString *logType = @"partner_info";
    NSMutableDictionary *properties = [[NSMutableDictionary alloc]initWithObjectsAndKeys:@"孙悟空",@"大师兄",@"猪八戒",@"二师兄",@"沙僧",@"三师兄",nil];
    NSString *funnelType = @"da_nao_tian_gong";
    NSString *stepName = @"da_zhan_erlangshen";
    NSString *stepStatus = @"begin";
    NSString *decsription = @"大战二郎神";
    
    [LogAgent setToken:@"d029dfc9-c74f-4f31-b896-998f7d18fcfc"];
    //发送所有设备信息日志测试
    [LogAgent sendDeviceInfo:userId properties:NULL];
    //发送指定设备信息日志测试
    [LogAgent sendDeviceInfo:userId methods:methods properties:NULL];
    //渠道信息日志发送接口测试
    [LogAgent sendChannelInfo:userId channelId:channelId properties:NULL];
    //登录信息日志发送接口测试
    [LogAgent sendLoginInfo:userId serverId:serverId properties:NULL];
    //登出信息日志发送接口测试
    [LogAgent sendLogoutInfo:userId  properties:NULL];
    //开始关卡信息日志发送接口测试
    [LogAgent sendLevelBeginInfo:userId levelName:beginLevelName properties:NULL];
    //完成关卡信息日志发送接口测试
    [LogAgent sendLevelComleteInfo:userId levelName:completeLevelName properties:NULL];
    //失败关卡信息日志发送接口测试
    [LogAgent sendLevelFailInfo:userId levelName:failLevelName properties:NULL];
    //开始任务信息日志发送接口测试
    [LogAgent sendTaskBeginInfo:userId taskName:beginTaskName properties:NULL];
    //完成任务信息日志发送接口测试
    [LogAgent sendTaskComleteInfo:userId taskName:completeTaskName properties:NULL];
    //失败任务信息日志发送接口测试
    [LogAgent sendTaskFailInfo:userId taskName:failTaskName properties:NULL];
    //获得物品信息日志发送接口测试
    [LogAgent sendGetItemInfo:userId itemName:getItemName properties:NULL];
    //购买物品信息日志发送接口测试
    [LogAgent sendBuyItemInfo:userId itemName:buyItemName properties:NULL];
    //消耗物品信息日志发送接口测试
    [LogAgent sendConsumeItemInfo:userId itemName:consumeItmeName properties:NULL];
    //获得金币信息日志发送接口测试
    [LogAgent sendGainCoinInfo:userId coinType:coinType gain:gain total:total reason:gainReason properties:NULL];
    //消耗金币信息日志发送接口测试
    [LogAgent sendConsumeCoinInfo:userId coinType:coinType use:use total:total reason:useReason properties:NULL];
    //支付信息日志发送接口测试
    [LogAgent sendCurrencyPaymentInfo:userId orderId:orderId iapId:iapId amount:amount currencyType:currencyType paymentType:paymentType properties:NULL];
    //自定义日志发送接口测试
    [LogAgent sendCustomizedInfo:userId logType:logType properties:properties];
    //自定义日志发送接口测试
    [LogAgent sendCustomizedFunnel:userId funnelType:funnelType stepName:stepName stepStatus:stepStatus description:decsription properties:NULL];
#endif
    
}

void LambdaCloudTest::onMenuSendLoginMessageClicked(cocos2d::CCObject *sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    // Collect device info and upload during initialize
    try {
        std::string userid = "userid";
        std::stringstream ss;
        std::string platform = lambdacloud::LambdaDevice::getApplicationPlatform();
        std::string networkStatus = lambdacloud::LambdaDevice::getNetworkStatus();
        std::string deviceName = lambdacloud::LambdaDevice::getDeviceName();
        std::string carrierName = lambdacloud::LambdaDevice::getCarrierName();
        std::string osVersion = lambdacloud::LambdaDevice::getOsVersion();
        std::string screenDimension = lambdacloud::LambdaDevice::getScreenDimension();
        std::string imei = lambdacloud::LambdaDevice::getImei();
        
        ss << "日志类型[LambdaCloud设备信息],时间[" << getISOTime() << "],用户[" << userid << "],操作系统["
        << platform << "],网络状态[" << networkStatus << "],手机品牌[" << deviceName << "],运营商信息[" << carrierName << "],操作系统版本[" << osVersion << "],分辨率["
        << screenDimension << "],imei[" << imei << "]";
        std::string message(ss.str());
        
        // Send msg without tag
        lambdacloud::LambdaClient::setToken("d029dfc9-c74f-4f31-b896-998f7d18fcfc");
        lambdacloud::LambdaClient::writeLog(message.c_str());
    } catch (std::exception e) {
        CCLOGERROR("got exception when recording login info, detail is %s", e.what());
    }
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    [LogAgent setToken:@"d029dfc9-c74f-4f31-b896-998f7d18fcfc"];
    NSString *isoTime = [NSString stringWithUTF8String:getISOTime().c_str()];
    NSString *userId = @"userId";
    NSString *networkStatus = [DeviceInfo getInternetConnectionStatus];
    //NSString *deviceInfo = [DeviceInfo getDeviceName];
    NSString *deviceInfo = @"BLANK";
    if ([DeviceInfo getDeviceName]){
        deviceInfo = [DeviceInfo getDeviceName];
    }
    NSString *batteryPower = [DeviceInfo getBatteryPower];
    NSString *operationInfo = [DeviceInfo getOperationInfo];
    NSString *systemOs = [DeviceInfo getSystemOS];
    NSString *string = [[NSString alloc]initWithFormat:@"日志类型[LambdaCloud设备信息],时间[%@],用户[%@],操作系统[%@],操作系统版本[%@],设备名称[%@],网络状态[%@],电量[%@]", isoTime, userId ,operationInfo,systemOs,deviceInfo,networkStatus, batteryPower];
    [LogAgent addLog:string];
    [DeviceInfo getLocation:userId];
#endif
    
}

////////////////////////////////////////////////////////
//
// ExtensionsTestScene
//
////////////////////////////////////////////////////////

void LambdaCloudTestScene::runThisTest()
{
    CCLayer* pLayer = new LambdaCloudTest();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}
