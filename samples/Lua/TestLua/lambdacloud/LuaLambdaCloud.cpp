/*
** Lua binding: LambdaCloud
** Generated automatically by tolua++-1.0.92 on Tue Jan 20 23:23:31 2015.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

#include "LambdaClient.h"
#include "LambdaDevice.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_LambdaCloud_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"std::vector<std::string>");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"lambdacloud::LambdaClient");
 tolua_usertype(tolua_S,"lambdacloud::LambdaDevice");
}

/* method: getInstance of class  lambdacloud::LambdaClient */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaClient_getInstance00
static int tolua_LambdaCloud_lambdacloud_LambdaClient_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"lambdacloud::LambdaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   lambdacloud::LambdaClient* tolua_ret = (lambdacloud::LambdaClient*)  lambdacloud::LambdaClient::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"lambdacloud::LambdaClient");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setToken of class  lambdacloud::LambdaClient */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaClient_setToken00
static int tolua_LambdaCloud_lambdacloud_LambdaClient_setToken00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"lambdacloud::LambdaClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  lambdacloud::LambdaClient* self = (lambdacloud::LambdaClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string token = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setToken'", NULL);
#endif
  {
   self->setToken(token);
   tolua_pushcppstring(tolua_S,(const char*)token);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setToken'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeLog of class  lambdacloud::LambdaClient */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaClient_writeLog00
static int tolua_LambdaCloud_lambdacloud_LambdaClient_writeLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"lambdacloud::LambdaClient",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::vector<std::string>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  lambdacloud::LambdaClient* self = (lambdacloud::LambdaClient*)  tolua_tousertype(tolua_S,1,0);
  const std::string log = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  std::vector<std::string> tags = *((std::vector<std::string>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'writeLog'", NULL);
#endif
  {
   self->writeLog(log,tags);
   tolua_pushcppstring(tolua_S,(const char*)log);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: debugLog of class  lambdacloud::LambdaClient */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaClient_debugLog00
static int tolua_LambdaCloud_lambdacloud_LambdaClient_debugLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"lambdacloud::LambdaClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  lambdacloud::LambdaClient* self = (lambdacloud::LambdaClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'debugLog'", NULL);
#endif
  {
   self->debugLog();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'debugLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCarrierName of class  lambdacloud::LambdaDevice */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaDevice_getCarrierName00
static int tolua_LambdaCloud_lambdacloud_LambdaDevice_getCarrierName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"lambdacloud::LambdaDevice",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  lambdacloud::LambdaDevice::getCarrierName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCarrierName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNetworkStatus of class  lambdacloud::LambdaDevice */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaDevice_getNetworkStatus00
static int tolua_LambdaCloud_lambdacloud_LambdaDevice_getNetworkStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"lambdacloud::LambdaDevice",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  lambdacloud::LambdaDevice::getNetworkStatus();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNetworkStatus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeviceName of class  lambdacloud::LambdaDevice */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaDevice_getDeviceName00
static int tolua_LambdaCloud_lambdacloud_LambdaDevice_getDeviceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"lambdacloud::LambdaDevice",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  lambdacloud::LambdaDevice::getDeviceName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeviceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getApplicationPlatform of class  lambdacloud::LambdaDevice */
#ifndef TOLUA_DISABLE_tolua_LambdaCloud_lambdacloud_LambdaDevice_getApplicationPlatform00
static int tolua_LambdaCloud_lambdacloud_LambdaDevice_getApplicationPlatform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"lambdacloud::LambdaDevice",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  lambdacloud::LambdaDevice::getApplicationPlatform();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getApplicationPlatform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LambdaCloud_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"lambdacloud",0);
  tolua_beginmodule(tolua_S,"lambdacloud");
   tolua_cclass(tolua_S,"LambdaClient","lambdacloud::LambdaClient","CCObject",NULL);
   tolua_beginmodule(tolua_S,"LambdaClient");
    tolua_function(tolua_S,"getInstance",tolua_LambdaCloud_lambdacloud_LambdaClient_getInstance00);
    tolua_function(tolua_S,"setToken",tolua_LambdaCloud_lambdacloud_LambdaClient_setToken00);
    tolua_function(tolua_S,"writeLog",tolua_LambdaCloud_lambdacloud_LambdaClient_writeLog00);
    tolua_function(tolua_S,"debugLog",tolua_LambdaCloud_lambdacloud_LambdaClient_debugLog00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LAMBDA_NETWORK_STATUS_NOT_REACHABLE",LAMBDA_NETWORK_STATUS_NOT_REACHABLE);
  tolua_constant(tolua_S,"LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WIFI",LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WIFI);
  tolua_constant(tolua_S,"LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WWAN",LAMBDA_NETWORK_STATUS_REACHABLE_VIA_WWAN);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_IPHONE",LAMBDA_PLATFORM_IPHONE);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_IPAD",LAMBDA_PLATFORM_IPAD);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_ANDROID",LAMBDA_PLATFORM_ANDROID);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_WP",LAMBDA_PLATFORM_WP);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_WIN",LAMBDA_PLATFORM_WIN);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_WINRT",LAMBDA_PLATFORM_WINRT);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_MAC",LAMBDA_PLATFORM_MAC);
  tolua_constant(tolua_S,"LAMBDA_PLATFORM_OTHERS",LAMBDA_PLATFORM_OTHERS);
  tolua_module(tolua_S,"lambdacloud",0);
  tolua_beginmodule(tolua_S,"lambdacloud");
   tolua_cclass(tolua_S,"LambdaDevice","lambdacloud::LambdaDevice","",NULL);
   tolua_beginmodule(tolua_S,"LambdaDevice");
    tolua_function(tolua_S,"getCarrierName",tolua_LambdaCloud_lambdacloud_LambdaDevice_getCarrierName00);
    tolua_function(tolua_S,"getNetworkStatus",tolua_LambdaCloud_lambdacloud_LambdaDevice_getNetworkStatus00);
    tolua_function(tolua_S,"getDeviceName",tolua_LambdaCloud_lambdacloud_LambdaDevice_getDeviceName00);
    tolua_function(tolua_S,"getApplicationPlatform",tolua_LambdaCloud_lambdacloud_LambdaDevice_getApplicationPlatform00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LambdaCloud (lua_State* tolua_S) {
 return tolua_LambdaCloud_open(tolua_S);
};
#endif

