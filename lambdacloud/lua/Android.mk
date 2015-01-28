LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := lua_lambdacloud

LOCAL_MODULE_FILENAME := lib_lua_lambdacloud

LOCAL_SRC_FILES := LuaLambdaCloud.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/../include 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/ 

LOCAL_WHOLE_STATIC_LIBRARIES := lambdacloud
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)

$(call import-module,lambdacloud/android)
$(call import-module,scripting/lua/proj.android)