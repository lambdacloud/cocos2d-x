#include "LambdacloudTest.h"
#include "../testResource.h"
#include "LambdaClient.h"
#include "LambdaDevice.h"
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
    
    // give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
    
}

void LambdaCloudTest::onMenuSendBasicMessageClicked(cocos2d::CCObject *sender)
{
    std::string tags = "test, cpp, debug";
    lambdacloud::LambdaClient::setToken("C2D56BC4-D336-4248-9A9F-B0CC8F906671");
    lambdacloud::LambdaClient::writeLog("this is a test log from cpp test project on cocos v2", tags.c_str());
    
    // give a hit
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
        ss << "日志类型[LambdaCloud设备信息],时间[" << getISOTime() << "],用户[" << userid << "],操作系统["
         << platform << "],网络状态[" << networkStatus << "],手机品牌[" << deviceName << "],运营商信息[" << carrierName << "]";
        std::string message(ss.str());
        
        // Send msg without tag
        lambdacloud::LambdaClient::setToken("56a32e77-8ff8-4a89-8b20-1b5da28698b3");
        lambdacloud::LambdaClient::writeLog(message.c_str());
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
