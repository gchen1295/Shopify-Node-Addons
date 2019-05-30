#ifndef _HTTP_TEST_H_
#define _HTTP_TEST_H_

#pragma once
#include <napi.h>
#include <napi.h>
#include <iostream>
#include <iostream>
#include <vector>
#include <cpr/cpr.h>


namespace apifunctions{

std::string createLicense();
std::string authLicense(std::string key, std::string hwid);
std::string createTask( std::string website, std::string keywords, std::string size, int numTasks, int numcheckouts );

//Functions wrappers
Napi::String PostWrapper(const Napi::CallbackInfo &info);
Napi::String AuthWrapper(const Napi::CallbackInfo &info);
Napi::String NewTaskWrapper(const Napi::CallbackInfo &info);

Napi::Object Init(Napi::Env env, Napi::Object exports);
}


#endif // !_HTTP_TEST_H_