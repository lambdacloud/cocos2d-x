#include "LambdacloudTest.h"
#include "../testResource.h"
#include "LambdaClient.h"
#include "LambdaDevice.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <sstream>

USING_NS_CC;
USING_NS_CC_EXT;

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

////////////////////////////////////////////////////////
//
// 模拟测试预定义信息
//
////////////////////////////////////////////////////////

// 用户名，服务器名，用户id，渠道都是一一对应的
std::string usernames[10] = {"战戮弑神", "逆霜", "夜乘风凉", "实在", "银白之手", "指間烟味", "Lafont", "功夫茶香", "獠牙保初吻", "車过来"};
int userids[10] = {120001, 120002, 120003, 120004, 120005, 120006, 120007, 120008, 120009, 120010};
std::string servernames[10] = {"悲伤沼泽", "银色黎明", "灰谷森林", "无尽之海", "西部荒野", "悲伤沼泽", "瓦斯琪尔", "西部荒野", "灵魂之戒", "瓦斯琪尔"};
std::string branches[10] = {"苹果官方", "苹果官方", "苹果越狱", "豌豆夹账号", "当乐账号", "91账号", "360越狱", "龙图专服", "龙图混服", "多酷账号"};

// 物品，任务，章节等会被随机使用
std::string equipments[20] = {"灵魂石", "方玉指环", "冲锋盾", "鬼手卷轴", "经验药水", "古之耐歌", "元气之球", "阿托斯", "暗灭", "暗影符", "板甲", "标枪", "大剑", "反伤甲", "飞鞋", "纷争", "风杖", "鬼手", "黑黄", "红杖"};
std::string quests[13] = {"点石成金", "抽到手软", "副本杀手", "精英副本杀手", "时光之主", "试炼王者", "技能升级", "装备附魔", "时光之穴-矮人军工厂", "时光之穴-潮汐神庙", "英雄试炼-女武神的对决", "英雄试炼-折戟山谷", "英雄试炼-诅咒之城"};
std::string chapters[21] = {"第一章 异界战场", "第一章 异界战场", "第一章 异界战场", "第二章 英雄学院", "第二章 英雄学院", "第二章 英雄学院", "第二章 英雄学院", "第二章 英雄学院", "第三章 娜迦海", "第三章 娜迦海", "第三章 娜迦海", "第三章 娜迦海", "第四章 暗夜岛", "第四章 暗夜岛", "第四章 暗夜岛", "第五章 日光森林", "第五章 日光森林", "第六章 荆棘山谷", "第六章 荆棘山谷", "第六章 荆棘山谷", "第六章 荆棘山谷"};
std::string rounds[21] = {"英雄指挥官", "传送阵", "雷神之锤", "狙击", "歌声中的回忆", "巨人", "卷入战场", "战场中央", "夜晚的回忆", "破船", "森林大火", "美杜莎的凝视", "风暴雨", "迷雾之岛", "港口小镇", "西圣殿", "游侠营地", "祖尔布", "剑圣", "远古遗迹", "提尔湖"};
std::string packages[6] = {"黄铜礼包", "白银礼包", "黄金礼包", "钻石礼包", "VIP-I礼包", "VIP-II礼包"};
int random_active_user_per_day = 7;
int demo_year = 2015;
int demo_month = 10;
int demo_start_day = 16;
int demo_end_day = 30;
int demo_session_times = 10;

std::string getISOTime()
{
    time_t now;
    time(&now);
    char buf[sizeof "2011-10-08T07:07:09+08:00"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    std::string date(buf);
    return date;
}

void sendLoginMessage(std::string userid, std::string userName, std::string server, std::string branch, std::string timestamp) {
    int level = std::rand() % 20 + 1;
    int coin = std::rand() % 100000;
    std::map<std::string, std::string> props;
    props.insert(std::pair<std::string, std::string>("user_name", userName));
    props.insert(std::pair<std::string, std::string>("imei", lambdacloud::LambdaDevice::getImei()));
    props.insert(std::pair<std::string, std::string>("user_level", SSTR(level)));
    props.insert(std::pair<std::string, std::string>("current_coin", SSTR(coin)));
    props.insert(std::pair<std::string, std::string>("branch", branch));

	lambdacloud::LambdaClient::sendLoginInfo(userid.c_str(), server.c_str(), timestamp.c_str(), &props);
}

void sendDeviceMessage(std::string userid, std::string timestamp) {
	lambdacloud::LambdaClient::sendDeviceInfo(userid.c_str(), timestamp.c_str(), NULL);
}

void sendLogoutMessage(std::string userid, std::string timestamp) {
	lambdacloud::LambdaClient::sendLogoutInfo(userid.c_str(), timestamp.c_str(), NULL);
}

void sendTopupMessage(std::string userid, std::string timestamp) {
	int price = std::rand() % 100;
	int diamond = price * 10;
	int packageIndex = std::rand() % sizeof(packages)/sizeof(packages[0]);
	std::map<std::string, std::string> props;
	props.insert(std::pair<std::string, std::string>("packge_price", SSTR(price)));
	props.insert(std::pair<std::string, std::string>("diamond_gained", SSTR(diamond)));
	lambdacloud::LambdaClient::sendCurrencyPaymentInfo(userid.c_str(), packages[packageIndex].c_str(), NULL, SSTR(price).c_str(), NULL, NULL, timestamp.c_str(), &props);
}

void sendDailyQuestMessage(std::string userid, std::string timestamp) {
	int diamond = std::rand() % 100;
	int questIndex = std::rand() % sizeof(quests)/sizeof(quests[0]);
	std::map<std::string, std::string> props;
	props.insert(std::pair<std::string, std::string>("diamond_gained", SSTR(diamond)));
	lambdacloud::LambdaClient::sendTaskCompleteInfo(userid.c_str(), quests[questIndex].c_str(), timestamp.c_str(), &props);
}

void sendLevelSuccessMessage(std::string userid, std::string timestamp) {
	int diamond = std::rand() % 100;
	int roundIndex = std::rand() % sizeof(rounds)/sizeof(rounds[0]);
	int chapterIndex = std::rand() % sizeof(chapters)/sizeof(chapters[0]);
	std::map<std::string, std::string> props;
	props.insert(std::pair<std::string, std::string>("diamond_gained", SSTR(diamond)));
	props.insert(std::pair<std::string, std::string>("chapter_name", chapters[chapterIndex]));
	lambdacloud::LambdaClient::sendLevelCompleteInfo(userid.c_str(), rounds[roundIndex].c_str(), timestamp.c_str(), &props);
}

void sendLevelFailMessage(std::string userid, std::string timestamp) {;
	std::map<std::string, std::string> props;
	int roundIndex = std::rand() % sizeof(rounds)/sizeof(rounds[0]);
	int chapterIndex = std::rand() % sizeof(chapters)/sizeof(chapters[0]);
	props.insert(std::pair<std::string, std::string>("chapter_name", chapters[chapterIndex]));
	lambdacloud::LambdaClient::sendLevelFailInfo(userid.c_str(), rounds[roundIndex].c_str(), timestamp.c_str(), &props);
}

void sendBuyItemMessage(std::string userid, std::string timestamp) {
	int coin = std::rand() % 10;
	int number = std::rand() % 3;
	int itemIndex = std::rand() % sizeof(equipments)/sizeof(equipments[0]);
	std::map<std::string, std::string> props;
	props.insert(std::pair<std::string, std::string>("ldp_coin_consumed", SSTR(coin)));
	props.insert(std::pair<std::string, std::string>("item_num", SSTR(number)));
    lambdacloud::LambdaClient::sendBuyItemInfo(userid.c_str(), equipments[itemIndex].c_str(), timestamp.c_str(), &props);
}

void sendSellItemMessage(std::string userid, std::string timestamp) {
	int coin = std::rand() % 10;
	int number = std::rand() % 3;
	int itemIndex = std::rand() % sizeof(equipments)/sizeof(equipments[0]);
	std::map<std::string, std::string> props;
	props.insert(std::pair<std::string, std::string>("ldp_coin_gained", SSTR(coin)));
	props.insert(std::pair<std::string, std::string>("ldp_item_name", equipments[itemIndex]));
	props.insert(std::pair<std::string, std::string>("item_num", SSTR(number)));
    lambdacloud::LambdaClient::sendCustomizedInfo(userid.c_str(), "ldp_item_sell", timestamp.c_str(), &props);
}

// 使用session id作为小时，使用index作为分钟，这样可以有效地将回话分隔开
std::string genTimestamp(int year, int month, int day, int session, int index) {
	//2011-10-08T07:07:09+08:00
	std::stringstream ss;

	// 年
	ss << year << "-";

	// 月
	if (month < 10)
		ss << "0";
	ss << month << "-";

	// 日
	if (day < 10)
		ss << "0";
	ss << day << "T";

	// session 作为小时
	if (session < 10)
		ss << "0" << session;
	else if (session < 23)
		ss << session;
	else
		ss << "23";
	ss << ":";

	// index 作为分钟
	if (index < 10)
		ss << "0" << index;
	else if (index > 40)
		ss << 40;
	else
		ss << index;

	// 时区
	ss << "+08:00";
    return ss.str();
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
    CCLabelTTF *labelDemo = CCLabelTTF::create("Demo Test, 15days x 1000messages/day", "Arial", 22);
    CCMenuItemLabel *itemDemo = CCMenuItemLabel::create(labelDemo, this, menu_selector(LambdaCloudTest::onMenuSendDemoTestLogsClicked));
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
    std::string userid = "test_user";
    std::string channelId = "test_channel";
    std::string timestamp = getISOTime();
    lambdacloud::LambdaClient::sendChannelInfo(userid.c_str(), channelId.c_str(), timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLoginInfo(userid.c_str(), "test_server", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLogoutInfo(userid.c_str(), timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendUserTag(userid.c_str(), "test_tag", timestamp.c_str(), "test_sub_tag");
    lambdacloud::LambdaClient::sendLevelBeginInfo(userid.c_str(), "test_level", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLevelCompleteInfo(userid.c_str(), "test_level", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendLevelFailInfo(userid.c_str(), "test_level", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendTaskBeginInfo(userid.c_str(), "test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendTaskCompleteInfo(userid.c_str(), "test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendTaskFailInfo(userid.c_str(), "test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendGetItemInfo(userid.c_str(), "test_item", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendBuyItemInfo(userid.c_str(), "test_item", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendConsumeItemInfo(userid.c_str(), "test_item", timestamp.c_str(), &props);
    CCLog("LambdaCloudTest sendConsumeItemInfo done");
    lambdacloud::LambdaClient::sendGainCoinInfo(userid.c_str(), "test_coin_type", 100L, 900L, "complate_test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendConsumeCoinInfo(userid.c_str(), "test_coin_type", 200L, 700L, "complate_test_task", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendDeviceInfo(userid.c_str(), timestamp.c_str(), NULL);
    lambdacloud::LambdaClient::sendCurrencyPaymentInfo(userid.c_str(), "test_order", "test_iap", "1000", "RMB", "unionpay", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendCustomizedInfo(userid.c_str(), "test_customized_event", timestamp.c_str(), &props);
    lambdacloud::LambdaClient::sendCustomizedFunnel(userid.c_str(), "新手漏斗", "登陆游戏", "成功", NULL, timestamp.c_str(), &props);
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
 * 使用一系列预定义的字段
 * 每天每个用户大概创建10段对话，中间间隔超过15分钟
 * 每天随机抽取一部分用户游戏，并不是使用所有用户
 */
void LambdaCloudTest::onMenuSendDemoTestLogsClicked(cocos2d::CCObject *sender)
{
	// 配置token和参数
	lambdacloud::LambdaClient::setToken("18317FF3-2E16-40B4-B4F7-69F352996255");
	lambdacloud::LambdaClient::setMaxQueueSize(20000);

	// 设置随机种子
	std::srand(std::time(0));

	// 创建一个用户索引表
	int userIndices[10];
	for (int i=0; i<10; i++) {
		userIndices[i] = i;
	}

	// 遍历每天
	for (int day=demo_start_day; day<demo_end_day; day++) {
		CCLog("遍历每天, %d", day);
		// 随机混乱所有用户
		std::random_shuffle(&userIndices[0], &userIndices[9]);

		// 遍历所有选中的用户
		for (int i=0; i<random_active_user_per_day; i++) {
			CCLog("遍历所有选中的用户, %d", i);
			int index = userIndices[i];
			std::string userid = SSTR(userids[index]);

			// 遍历每个会话
			for (int session=1; session<demo_session_times; session++) {
				int logIndex = 0;

				// 登陆游戏
				std::string timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
				std::string userName = usernames[index];
				std::string serverName = servernames[index];
				std::string branchName = branches[index];
				sendLoginMessage(userid, userName, serverName, branchName, timestamp);
				CCLog("登陆游戏");

				// 设备信息
				timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
				sendDeviceMessage(userid, timestamp);
				CCLog("设备信息");

				// 零次或多次充值信息
				int times = std::rand() % 3;
				for (; times > 0; times--) {
					timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
					sendTopupMessage(userid, timestamp);
				}
				CCLog("零次或多次充值信息");

				// 零次或多次完成任务
				times = std::rand() % 3;
				for (; times > 0; times--) {
					timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
					sendDailyQuestMessage(userid, timestamp);
				}
				CCLog("零次或多次完成任务");

				// 零次或多次完成关卡
				times = std::rand() % 3;
				for (; times > 0; times--) {
					timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
					sendLevelSuccessMessage(userid, timestamp);
				}
				CCLog("零次或多次完成关卡");

				// 零次或多次关卡失败
				times = std::rand() % 3;
				for (; times > 0; times--) {
					timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
					sendLevelFailMessage(userid, timestamp);
				}
				CCLog("零次或多次关卡失败");

				// 零次或多次购买道具
				times = std::rand() % 3;
				for (; times > 0; times--) {
					timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
					sendBuyItemMessage(userid, timestamp);
				}
				CCLog("零次或多次购买道具");

				// 零次或多次卖出道具
				times = std::rand() % 3;
				for (; times > 0; times--) {
					timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
					sendSellItemMessage(userid, timestamp);
				}
				CCLog("零次或多次卖出道具");

				// 退出信息
				timestamp = genTimestamp(demo_year, demo_month, day, session, logIndex++);
				sendLogoutMessage(userid, timestamp);
				CCLog("退出信息");
			}
		}
	}

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
