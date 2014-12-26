#include "lua_cocos2dx_lambdacloud_auto.hpp"
#include "LambdaClient.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_lambdacloud_LambdaClient_debugLog(lua_State* tolua_S)
{
    int argc = 0;
    lambdacloud::LambdaClient* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LambdaClient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (lambdacloud::LambdaClient*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_lambdacloud_LambdaClient_debugLog'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_lambdacloud_LambdaClient_debugLog'", nullptr);
            return 0;
        }
        cobj->debugLog();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LambdaClient:debugLog",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_lambdacloud_LambdaClient_debugLog'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_lambdacloud_LambdaClient_writeLog(lua_State* tolua_S)
{
    int argc = 0;
    lambdacloud::LambdaClient* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LambdaClient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (lambdacloud::LambdaClient*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_lambdacloud_LambdaClient_writeLog'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::vector<std::string> arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LambdaClient:writeLog");

        ok &= luaval_to_std_vector_string(tolua_S, 3, &arg1, "cc.LambdaClient:writeLog");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_lambdacloud_LambdaClient_writeLog'", nullptr);
            return 0;
        }
        cobj->writeLog(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LambdaClient:writeLog",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_lambdacloud_LambdaClient_writeLog'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_lambdacloud_LambdaClient_setToken(lua_State* tolua_S)
{
    int argc = 0;
    lambdacloud::LambdaClient* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LambdaClient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (lambdacloud::LambdaClient*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_lambdacloud_LambdaClient_setToken'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LambdaClient:setToken");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_lambdacloud_LambdaClient_setToken'", nullptr);
            return 0;
        }
        cobj->setToken(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LambdaClient:setToken",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_lambdacloud_LambdaClient_setToken'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_lambdacloud_LambdaClient_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LambdaClient",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_lambdacloud_LambdaClient_getInstance'", nullptr);
            return 0;
        }
        lambdacloud::LambdaClient* ret = lambdacloud::LambdaClient::getInstance();
        object_to_luaval<lambdacloud::LambdaClient>(tolua_S, "cc.LambdaClient",(lambdacloud::LambdaClient*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.LambdaClient:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_lambdacloud_LambdaClient_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_lambdacloud_LambdaClient_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LambdaClient)");
    return 0;
}

int lua_register_cocos2dx_lambdacloud_LambdaClient(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.LambdaClient");
    tolua_cclass(tolua_S,"LambdaClient","cc.LambdaClient","",nullptr);

    tolua_beginmodule(tolua_S,"LambdaClient");
        tolua_function(tolua_S,"debugLog",lua_cocos2dx_lambdacloud_LambdaClient_debugLog);
        tolua_function(tolua_S,"writeLog",lua_cocos2dx_lambdacloud_LambdaClient_writeLog);
        tolua_function(tolua_S,"setToken",lua_cocos2dx_lambdacloud_LambdaClient_setToken);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_lambdacloud_LambdaClient_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(lambdacloud::LambdaClient).name();
    g_luaType[typeName] = "cc.LambdaClient";
    g_typeCast["LambdaClient"] = "cc.LambdaClient";
    return 1;
}
TOLUA_API int register_all_cocos2dx_lambdacloud(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"lambdacloud",0);
	tolua_beginmodule(tolua_S,"lambdacloud");

	lua_register_cocos2dx_lambdacloud_LambdaClient(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

