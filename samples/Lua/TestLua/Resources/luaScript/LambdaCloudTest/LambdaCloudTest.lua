local function LambdaCloudMainLayer()
    local layer   = CCLayer:create()
    local winSize = CCDirector:sharedDirector():getWinSize()
        
    local MARGIN = 40
    local SPACE  = 35
    local sendTextStatus  = nil

    local label = CCLabelTTF:create("LambdaCloud Test", "Arial", 28)
    label:setPosition(ccp( winSize.width / 2, winSize.height - MARGIN))
    layer:addChild(label, 0)

    local menuRequest = CCMenu:create()
    menuRequest:setPosition(ccp(0, 0))
    layer:addChild(menuRequest)

    --Get Device Info Test
    local function onMenuGetDeviceInfoClicked()
        print("LambdaCloudTest getDeviceName "..lambdacloud.LambdaDevice:getDeviceName());
	    print("LambdaCloudTest getCarrierName "..lambdacloud.LambdaDevice:getCarrierName());
	    print("LambdaCloudTest getApplicationPlatform "..lambdacloud.LambdaDevice:getApplicationPlatform());
	    print("LambdaCloudTest getNetworkStatus "..lambdacloud.LambdaDevice:getNetworkStatus());
	    sendTextStatus:setString("sent, please check log to verify result");
    end
    local getDeviceInfoText = CCLabelTTF:create("Get Device Info Test", "Arial", 22)
    local getDeviceInfoMenu = CCMenuItemLabel:create(getDeviceInfoText)
    getDeviceInfoMenu:registerScriptTapHandler(onMenuGetDeviceInfoClicked)
    getDeviceInfoMenu:setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - SPACE))
    menuRequest:addChild(getDeviceInfoMenu)

    --Send Basic Message Test
    local function onMenuSendBasicMessageClicked()
        local tags = CCArray:create();
        tags:addObject(CCString:create("test"));
        tags:addObject(CCString:create("lua"));
	    lambdacloud.LambdaClient:getInstance():setToken("C2D56BC4-D336-4248-9A9F-B0CC8F906671");
		lambdacloud.LambdaClient:getInstance():writeLog("this is a test log from lua test project on cocos v2", tags)
	    sendTextStatus:setString("sent, please check log to verify result");
    end
    local sendBasicMessageTest = CCLabelTTF:create("Send Basic Message Test", "Arial", 22)
    local sendBasicMessageMenu = CCMenuItemLabel:create(sendBasicMessageTest)
    sendBasicMessageMenu:registerScriptTapHandler(onMenuSendBasicMessageClicked)
    sendBasicMessageMenu:setPosition(ccp(winSize.width / 2, winSize.height - MARGIN - 2 * SPACE))
    menuRequest:addChild(sendBasicMessageMenu)

    --Send Text Status Label
    sendTextStatus = CCLabelTTF:create("after clicking a test, please check the log to verify the result...", "Arial", 14,CCSizeMake(160, 100),kCCVerticalTextAlignmentCenter,kCCVerticalTextAlignmentTop)
    sendTextStatus:setAnchorPoint(ccp(0, 0))
    sendTextStatus:setPosition(ccp(0, 25))
    layer:addChild(sendTextStatus)

    local function OnExit(strEventName)
        if "exit" == strEventName then
            --TODO should we close lambdacloud client expilicly?
        end
    end
    layer:registerScriptHandler(OnExit)

    return layer
end

-------------------------------------
--  LambdaCloud Test
-------------------------------------
function LambdaCloudTestMain()
	local scene = CCScene:create()

	scene:addChild(LambdaCloudMainLayer())
	scene:addChild(CreateBackMenuItem())

	return scene
end
