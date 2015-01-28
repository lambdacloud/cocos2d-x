#include "LambdacloudTest.h"
#include "../testResource.h"
#include "LambdaClient.h"
#include "LambdaDevice.h"
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;

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
    
    // Response Code Label
    m_labelStatusCode = CCLabelTTF::create("HTTP Status Code", "Marker Felt", 20);
    m_labelStatusCode->setPosition(ccp(winSize.width / 2,  winSize.height - MARGIN - 6 * SPACE));
    addChild(m_labelStatusCode);
}

LambdaCloudTest::~LambdaCloudTest()
{
    CCHttpClient::getInstance()->destroyInstance();
}

void LambdaCloudTest::onMenuGetDeviceInfoClicked(cocos2d::CCObject *sender)
{
    CCLog("LambdaCloudTest getDeviceName %s", lambdacloud::LambdaDevice::getDeviceName().c_str());
    CCLog("LambdaCloudTest getCarrierName %s", lambdacloud::LambdaDevice::getCarrierName().c_str());
    CCLOG("LambdaCloudTest getApplicationPlatform %d", lambdacloud::LambdaDevice::getApplicationPlatform());
    CCLog("LambdaCloudTest getNetworkStatus %d", lambdacloud::LambdaDevice::getNetworkStatus());
    
    // give a hit
    m_labelStatusCode->setString("sent...please check log to verify");
    
}

void LambdaCloudTest::onMenuSendBasicMessageClicked(cocos2d::CCObject *sender)
{
    CCArray* tags = CCArray::create();
    tags->addObject(CCString::create("test"));
    tags->addObject(CCString::create("cpp"));
    lambdacloud::LambdaClient* client = lambdacloud::LambdaClient::getInstance();
    client->debugLog();
    client->setToken("C2D56BC4-D336-4248-9A9F-B0CC8F906671");
    client->writeLog("this is a test log from cpp test project on cocos v2", tags);
    
    // give a hit
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
