#include "LambdacloudTest.h"
#include "../testResource.h"
#include "LambdaClient.h"
#include "LambdaDevice.h"
#include <map>
#include <string>
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
    
    // Set logsdk debug flag true
    lambdacloud::LambdaClient::debugLogSdk(true);

    // Set log interval 10 seconds
    lambdacloud::LambdaClient::setSendInterval(10);

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
    
    // Send Demo Test Logs
    CCLabelTTF *labelPostLogin = CCLabelTTF::create("Test Send Demo Test Logs, 15 days x 1000 messages/day", "Arial", 22);
    CCMenuItemLabel *itemDemo = CCMenuItemLabel::create(labelPostLogin, this, menu_selector(LambdaCloudTest::onMenuSendDemoTestLogsClicked));
    itemDemo->setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 4 * SPACE));
    menuRequest->addChild(itemDemo);

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
    CCLog("LambdaCloudTest getDeviceName %s", lambdacloud::LambdaDevice::getDeviceName().c_str());
    CCLog("LambdaCloudTest getCarrierName %s", lambdacloud::LambdaDevice::getCarrierName().c_str());
    CCLOG("LambdaCloudTest getApplicationPlatform %s", lambdacloud::LambdaDevice::getApplicationPlatform().c_str());
    CCLog("LambdaCloudTest getNetworkStatus %s", lambdacloud::LambdaDevice::getNetworkStatus().c_str());
    CCLog("LambdaCloudTest getOsVersion %s", lambdacloud::LambdaDevice::getOsVersion().c_str());
    CCLog("LambdaCloudTest getScreenDimension %s", lambdacloud::LambdaDevice::getScreenDimension().c_str());
    CCLog("LambdaCloudTest getImei %s", lambdacloud::LambdaDevice::getImei().c_str());

    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
    
}

void LambdaCloudTest::onMenuSendBasicMessageClicked(cocos2d::CCObject *sender)
{
	// Send a test log with each API
    std::map<std::string, std::string> props;
    props.insert(std::pair<std::string, std::string>("prop_1", "value_1"));
    props.insert(std::pair<std::string, std::string>("prop_2", "value_2"));
    lambdacloud::LambdaClient::setToken("d029dfc9-c74f-4f31-b896-998f7d18fcfc");
    std::string userId = "test_user";
    std::string channelId = "test_channel";
    std::string timestamp = getISOTime();
    lambdacloud::LambdaClient::sendChannelInfo(userId.c_str(), channelId.c_str(), timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLoginInfo(userId.c_str(), "test_server", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLogoutInfo(userId.c_str(), timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendUserTag(userId.c_str(), "test_tag", timestamp.c_str(), "test_sub_tag");
    lambdacloud::LambdaClient::sendLevelBeginInfo(userId.c_str(), "test_level", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLevelCompleteInfo(userId.c_str(), "test_level", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLevelFailInfo(userId.c_str(), "test_level", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendTaskBeginInfo(userId.c_str(), "test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendTaskCompleteInfo(userId.c_str(), "test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendTaskFailInfo(userId.c_str(), "test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendGetItemInfo(userId.c_str(), "test_item", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendBuyItemInfo(userId.c_str(), "test_item", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendConsumeItemInfo(userId.c_str(), "test_item", timestamp.c_str(), &props);
    CCLog("LambdaCloudTest sendConsumeItemInfo done");
    lambdacloud::LambdaClient::sendGainCoinInfo(userId.c_str(), "test_coin_type", 100L, 900L, "complate_test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendConsumeCoinInfo(userId.c_str(), "test_coin_type", 200L, 700L, "complate_test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendDeviceInfo(userId.c_str(), timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendCurrencyPaymentInfo(userId.c_str(), "test_order", "test_iap", "1000", "RMB", "unionpay", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendCustomizedInfo(userId.c_str(), "test_customized_event", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendCustomizedFunnel(userId.c_str(), "新手漏斗", "登陆游戏", "成功", NULL, timestamp.c_str(), &props);
    std::string version = lambdacloud::LambdaClient::getVersion();
    CCLog("lambdacloud sdk version %s", version.c_str());

    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
}

void LambdaCloudTest::onMenuSendLoginMessageClicked(cocos2d::CCObject *sender)
{
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
}

/*
 * 模拟10个玩家在15天里面的游戏日志，用于系统演练测试使用
 * 1.
 */
void LambdaCloudTest::onMenuSendDemoTestLogsClicked(cocos2d::CCObject *sender)
{


    // Give a hit
    m_labelStatusCode->setString("sent...please check log to verify");

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
