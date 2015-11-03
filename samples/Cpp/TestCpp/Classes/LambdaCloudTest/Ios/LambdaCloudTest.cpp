#include "LambdaCloudTest.h"
#include "../../testResource.h"
#include <map>
#ifdef __cplusplus
#include <string>
#endif

// same for objc, so your C and C++ sources compile with no error:
#ifdef __OBJC__
#include <Foundation/Foundation.h>
#endif
//#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#import "DeviceInfo.h"
#import "Reachability.h"
#import "LogAgent.h"
#import "LogSpout.h"
#import "LogRequest.h"
#import "LogSender.h"
#import "LogSdkConfig.h"


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
    
    // Set logsdk debug flag true
   // lambdacloud::LambdaClient::debugLogSdk(true);
    // Set log interval 10 seconds
    //lambdacloud::LambdaClient::setSendInterval(10);

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

void LambdaCloudTest::onMenuGetDeviceInfoClicked(cocos2d::CCObject *sender)
{
    NSLog(@"LambdaCloudIosTest getDeviceName: %@",[DeviceInfo getDeviceName]);
    NSLog(@"LambdaCloudIosTest getInternetcConnectionStatus: %@",[DeviceInfo getInternetConnectionStatus]);
    NSLog(@"LambdaCloudIosTest getOperationInfo: %@",[DeviceInfo getOperationInfo]);
    NSLog(@"LambdaCloudIosTest getSystemOS: %@",[DeviceInfo getSystemOS]);
    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
    
}

void LambdaCloudTest::onMenuSendBasicMessageClicked(cocos2d::CCObject *sender)
{
//	// Send a test log with each API
//    std::map<std::string, std::string> props;
//    props.insert(std::pair<std::string, std::string>("prop_1", "value_1"));
//    props.insert(std::pair<std::string, std::string>("prop_2", "value_2"));
//    lambdacloud::LambdaClient::setToken("d029dfc9-c74f-4f31-b896-998f7d18fcfc");
//    [LogAgent setToken:@"d029dfc9-c74f-4f31-b896-998f7d18fcfc"];
//    std::string userId = "test_user";
//    std::string channelId = "test_channel";
//    lambdacloud::LambdaClient::sendChannelInfo(userId.c_str(), channelId.c_str(), &props);
    
//    lambdacloud::LambdaClient::sendLoginInfo(userId.c_str(), "test_server", &props);
//    lambdacloud::LambdaClient::sendLogoutInfo(userId.c_str(), &props);
//    lambdacloud::LambdaClient::sendUserTag(userId.c_str(), "test_tag", "test_sub_tag");
//    lambdacloud::LambdaClient::sendLevelBeginInfo(userId.c_str(), "test_level", &props);
//    lambdacloud::LambdaClient::sendLevelCompleteInfo(userId.c_str(), "test_level", &props);
//    lambdacloud::LambdaClient::sendLevelFailInfo(userId.c_str(), "test_level", &props);
//    lambdacloud::LambdaClient::sendTaskBeginInfo(userId.c_str(), "test_task", &props);
//    lambdacloud::LambdaClient::sendTaskCompleteInfo(userId.c_str(), "test_task", &props);
//    lambdacloud::LambdaClient::sendTaskFailInfo(userId.c_str(), "test_task", &props);
//    lambdacloud::LambdaClient::sendGetItemInfo(userId.c_str(), "test_item", &props);
//    lambdacloud::LambdaClient::sendBuyItemInfo(userId.c_str(), "test_item", &props);
//    lambdacloud::LambdaClient::sendConsumeItemInfo(userId.c_str(), "test_item", &props);
//    CCLog("LambdaCloudTest sendConsumeItemInfo done");
//    lambdacloud::LambdaClient::sendGainCoinInfo(userId.c_str(), "test_coin_type", 100L, 900L, "complate_test_task", &props);
//    lambdacloud::LambdaClient::sendConsumeCoinInfo(userId.c_str(), "test_coin_type", 200L, 700L, "complate_test_task", &props);
//    lambdacloud::LambdaClient::sendDeviceInfo(userId.c_str(), &props);
//    lambdacloud::LambdaClient::sendCurrencyPaymentInfo(userId.c_str(), "test_order", "test_iap", "1000", "RMB", "unionpay", &props);
//    lambdacloud::LambdaClient::sendCustomizedInfo(userId.c_str(), "test_customized_event", &props);
//    lambdacloud::LambdaClient::sendCustomizedFunnel(userId.c_str(), "新手漏斗", "登陆游戏", "成功", NULL, &props);
//    std::string version = lambdacloud::LambdaClient::getVersion();
//    CCLog("lambdacloud sdk version %s", version.c_str());
//
    // Give a hit
  //  m_labelStatusCode->setString("sent...please check log to verify");
    m_labelStatusCode->setString("sorry..this test has been cancelled!");

}

void LambdaCloudTest::onMenuSendLoginMessageClicked(cocos2d::CCObject *sender)
{
    // Collect device info and upload during initialize
    try {
        NSString *isoTime = [NSString stringWithUTF8String:getISOTime().c_str()];
        NSString *userId = @"userId";
        NSString *networkStatus = [DeviceInfo getInternetConnectionStatus];
        NSString *deviceInfo = [DeviceInfo getDeviceName];
        NSString *operationInfo = [DeviceInfo getOperationInfo];
        NSString *systemOs = [DeviceInfo getSystemOS];

        NSString *string = [[NSString alloc]initWithFormat:@"日志类型[LambdaCloud设备信息],时间[%@],用户[%@],操作系统[%@],操作系统版本[%@],设备名称[%@],网络状态[%@]", isoTime, userId ,operationInfo,systemOs,deviceInfo,networkStatus];
        NSLog(@"%@",string);

        [LogAgent setToken:@"d029dfc9-c74f-4f31-b896-998f7d18fcfc"];
        [LogAgent addLog:string];

    } catch (std::exception e) {
        CCLOGERROR("got exception when recording login info, detail is %s", e.what());
    }
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
