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

#include "LambdaClient.h"

using namespace lambdacloud;

const char* c_url = "http://api.lambdacloud.com/log";
const int c_successReponseCode = 204;
const std::string c_jsonHeader = "Content-Type: application/json";
static LambdaClient* s_lambdaClient = NULL;
std::string m_token;

LambdaClient* LambdaClient::getInstance()
{
    if (s_lambdaClient == NULL) {
        s_lambdaClient = new LambdaClient();
    }
        
    return s_lambdaClient;
}

void LambdaClient::setToken(const std::string& token)
{
    m_token = token;
    CCLOG("set token %s", token.c_str());
}

void LambdaClient::writeLog(const std::string& log)
{
    writeLog(log, NULL);
}

void LambdaClient::writeLog(const std::string& log, cocos2d::CCArray *tags)
{
    if (log.empty())
    {
        CCLOG("log should not be empty");
        return;
    }
    
    try {
        cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
    
        CCLOG("Lambdaclient will write log:%s to server", log.c_str());
    
        // Set headers
        std::vector<std::string> pHeaders;
        pHeaders.push_back("Token: " + m_token);
        pHeaders.push_back(c_jsonHeader);
        request->setHeaders(pHeaders);
    
        // Set url and request type
        request->setUrl(c_url);
        request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
    
        // Set data
        std::string jsonContent = generateJsonData(log, tags);
        request->setRequestData(jsonContent.c_str(), jsonContent.length());
    
        // Set callback and send out
        request->setResponseCallback(this, httpresponse_selector(LambdaClient::onHttpRequestCompleted));
        cocos2d::extension::CCHttpClient::getInstance()->send(request);
    
        // Release request
        request->release();
    } catch (const std::exception& ex) {
        CCLOGERROR("Lambdacloud client got an exception while sending log, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("Lambdacloud client got a string exception while sending log, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("Lambdacloud client got an unknown exception while sending log");
    }
    return;
}

std::string LambdaClient::generateJsonData(const std::string& log, cocos2d::CCArray *tags)
{
    rapidjson::Document document;
    document.SetObject();
    document.AddMember("message", log.c_str(), document.GetAllocator());
    rapidjson::Value tagObjs(rapidjson::kArrayType);
    
    if (tags != NULL) {
        cocos2d::CCObject* cctagObj = NULL;
        CCARRAY_FOREACH(tags, cctagObj)
        {
            cocos2d::CCString* ccstring = (cocos2d::CCString*)cctagObj;
            if (ccstring != NULL)
            {
                std::string tag = ccstring->m_sString;
                tagObjs.PushBack(tag.c_str(), document.GetAllocator());
            }
        }
        document.AddMember("tags", tagObjs, document.GetAllocator());
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}

void LambdaClient::onHttpRequestCompleted(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    //TODO shall we record some logs for lambda request callback
    // Check not null
    if (!response)
    {
        CCLOG("response in null in onHttpRequestCompleted");
        return;
    }
    
    // Check if completed
    if (response->getResponseCode() != c_successReponseCode)
    {
        CCLOG("request failed with message %s", response->getErrorBuffer());
        return;
    }
    else
    {
        CCLOG("response status code:%d", response->getResponseCode());
        CCLOG("response data:%s", response->getResponseData()->data());
        return;
    }
}

LambdaClient::LambdaClient()
{
    // Nothing to init at present
}

LambdaClient::~LambdaClient()
{
    // Nothing to dispose at present
}


