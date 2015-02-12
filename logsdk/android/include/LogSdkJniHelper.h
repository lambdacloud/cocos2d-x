#ifndef cocos2d_logsdkjnihelper_h
#define cocos2d_logsdkjnihelper_h

#include <jni.h>
#include <string>
#include <vector>

namespace lambdacloud
{
	typedef struct _LogSdkJniMethodInfo
	{
		JNIEnv* env;
		jclass classID;
		jmethodID methodID;
	}LogSdkJniMethodInfo;

	class LogSdkJniHelper
	{
	private:
		static JavaVM* m_jvm;
	private:
	    static JNIEnv* getEnv();
	    static JNIEnv* cacheEnv(JavaVM* jvm);
	    static jclass getClassId(const char* className);
	public:
		static void setJavaVM(JavaVM* jvm);
		
	    static bool getStaticMethodInfo(LogSdkJniMethodInfo& info, const char* className, const char* methodName, const char* methodParam);
		
	    static bool getMethodInfo(LogSdkJniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
		
	    static jobject cStringArrayToJArray(std::vector<std::string> *array);

	    static std::string jstring2string(jstring jstr);
	};
}
#endif
