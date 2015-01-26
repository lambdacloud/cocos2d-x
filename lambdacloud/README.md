LambdaCloudSDK (for Cocos2dx v2)
================================

How to integrate LambdaCloudSDK to your project

For IOS
1. Add following folders into your project
   lambdacloud/include/
   lambdacloud/ios
2. Add required libararies into your project. 
   a. click project
   b. navigate to build phases－link binary with libraries
   c. add CoreTelephony.framework and SystemConfiguration.framework


For IOS Lua
1. Add following folders into your project
   lambdacloud/include/
   lambdacloud/ios
   lambdacloud/lua
2. Add required libararies into your project. 
   a. click project
   b. navigate to build phases－link binary with libraries
   c. add CoreTelephony.framework and SystemConfiguration.framework
3. Register lua method for lambdaclou by adding following lines to AppDelegate.cpp
   #include "LuaLambdaCloud.h"
   
   bool AppDelegate::applicationDidFinishLaunching()
   {
   
      ...

      pStack = pEngine->getLuaStack();
      tolua_s = pStack->getLuaState();
      tolua_LambdaCloud_open(tolua_s);


For Android
1. Add references to your android.mk (and jni/android.mk if necessary)
   LOCAL_WHOLE_STATIC_LIBRARIES += lambdacloud
   $(call import-module,lambdacloud/android)
2. Add required permission settings to your AndroidManifest.xml
   <uses-permission android:name="android.permission.INTERNET"/>
   <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
   <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
   <uses-permission android:name="android.permission.READ_PHONE_STATE"/>
3. Add lambdacloud java file to your project
   a. in Eclipse, right click your project, then navigate to Java Build Path
   b. click Link Source and choose "lambdacloud/android/src" 
   c. you may need to rename the folder name in the wizard dialogue


For Android Lua
1. Add references to your jni/android.mk 
   LOCAL_WHOLE_STATIC_LIBRARIES += lambdacloud
   LOCAL_WHOLE_STATIC_LIBRARIES += lua_lambdacloud
   $(call import-module,lambdacloud/android)
   $(call import-module,lambdacloud/lua)
2. Add required permission settings to your AndroidManifest.xml
   <uses-permission android:name="android.permission.INTERNET"/>
   <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
   <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
   <uses-permission android:name="android.permission.READ_PHONE_STATE"/>
3. Add lambdacloud java file to your project
   a. in Eclipse, right click your project, then navigate to Java Build Path
   b. click Link Source and choose "lambdacloud/android/src" 
   c. you may need to rename the folder name in the wizard dialogue
4. Register lua method for lambdaclou by adding following lines to AppDelegate.cpp
   #include "LuaLambdaCloud.h"

   bool AppDelegate::applicationDidFinishLaunching()
   {

   ...

   pStack = pEngine->getLuaStack();
   tolua_s = pStack->getLuaState();
   tolua_LambdaCloud_open(tolua_s);

================================

How to test your android proj in GenyMotion
GenyMotion is a fantastic Android simulator, with much better performance than Android's original simulator.
1. Download GeneMotion and choose the coresponding virtual device
2. If you are compiling your proj with ARM system image, you have to download and drop a Genymotion ARM Translation zip file into your virtual device and reboot it.
   a. i am using Genymotion-ARM-Translation_v1.1.zip
   b. reboot by YOUR_SDK_ROOT> ./platform-tools/adb reboot
3. Install Eclipse GenyMotion plugin
4. Start the virtual device in your Eclipse and run your project as Android application

Trouble shooting
1. "unfortunately app has stopped" with "java.lang.IllegalArgumentException: No config chosen" in your LogCat
   in your main java file
   glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);


