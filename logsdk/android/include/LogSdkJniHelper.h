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
