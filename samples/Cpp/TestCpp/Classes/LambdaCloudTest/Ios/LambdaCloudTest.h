//
//  LambdacloudTest.h
//  TestCpp
//
//  Created by sky4star on 15/1/20.
//
//

#ifndef __TestCpp__LambdacloudTest__
#define __TestCpp__LambdacloudTest__

#include "../../testBasic.h"
#include "cocos-ext.h"

class LambdaCloudTest : public CCLayer
{
public:
    LambdaCloudTest();
    virtual ~LambdaCloudTest();
    
    //Menu Callbacks
    void onMenuGetDeviceInfoClicked(cocos2d::CCObject *sender);
    void onMenuSendBasicMessageClicked(cocos2d::CCObject *sender);
    void onMenuSendLoginMessageClicked(cocos2d::CCObject *sender);
    void onMenuSendStressTestLogsClicked(cocos2d::CCObject *sender);
private:
    cocos2d::CCLabelTTF* m_labelStatusCode;
};

class LambdaCloudTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* defined(__TestCpp__LambdacloudTest__) */
