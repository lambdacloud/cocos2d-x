LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_lambdacloud_static

LOCAL_MODULE_FILENAME := liblambdacloud

LOCAL_SRC_FILES := LambdaClient.cpp \
LambdaDeviceAndroid.cpp 

LOCAL_EXPORT_C_INCLUDES :=

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)./

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static
LOCAL_STATIC_LIBRARIES += cocos_network_static

include $(BUILD_STATIC_LIBRARY)
