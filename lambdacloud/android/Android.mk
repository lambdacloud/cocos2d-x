LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := lambdacloud

LOCAL_MODULE_FILENAME := liblambdacloud

LOCAL_SRC_FILES := LambdaClient.cpp \
                   LambdaDeviceAndroid.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += libwebsockets_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,external/libwebsockets/android)
$(call import-module,extensions)