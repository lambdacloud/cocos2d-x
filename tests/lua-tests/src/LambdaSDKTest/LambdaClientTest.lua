require("json")

local function LambdaClientTest()
    local layer = cc.Layer:create()
    local winSize = cc.Director:getInstance():getWinSize()
    local margin = 40
    local space  = 35

    local function init()
        local label = cc.Label:createWithTTF("Lambda SDK Test", s_arialPath, 28)
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setPosition(cc.p(winSize.width / 2, winSize.height - margin))
        layer:addChild(label, 0)

        --Response Code Label
        local labelStatusCode = cc.Label:createWithTTF("HTTP Status Code", s_markerFeltFontPath, 20)
        labelStatusCode:setAnchorPoint(cc.p(0.5, 0.5))
        labelStatusCode:setPosition(cc.p(winSize.width / 2,  winSize.height - margin - 6 * space))
        layer:addChild(labelStatusCode)

        local menuRequest = cc.Menu:create()
        menuRequest:setPosition(cc.p(0,0))
        layer:addChild(menuRequest)

        --Get
        local function onMenuSendBasicLogClicked()
            lambdacloud.LambdaClient:getInstance():setToken("C2D56BC4-D336-4248-9A9F-B0CC8F906671");
            lambdacloud.LambdaClient:getInstance():writeLog("Test onMenuSendBasicLogClicked", {})
            labelStatusCode:setString("send request to lambdacloud, please check log in console")
        end

        local labelBasicLog  = cc.Label:createWithTTF("Test Send Basic Log", s_arialPath, 22)
        labelBasicLog:setAnchorPoint(cc.p(0.5, 0.5))
        local itemBasicLog =  cc.MenuItemLabel:create(labelBasicLog)
        itemBasicLog:registerScriptTapHandler(onMenuSendBasicLogClicked)
        itemBasicLog:setPosition(cc.p(winSize.width / 2, winSize.height - margin - space))
        menuRequest:addChild(itemBasicLog)
    end

    local function onNodeEvent(eventName)
        if "enter" == eventName then
            init()
        end
    end

    layer:registerScriptHandler(onNodeEvent)

    return layer
end

function LambdaClientTestMain()
    local scene = cc.Scene:create()
    scene:addChild(LambdaClientTest())
    scene:addChild(CreateBackMenuItem())
    return scene
end
