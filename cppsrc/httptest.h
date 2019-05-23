#include <napi.h>

namespace apifunctions{

std::string createLicense(std::string url);
//std::string getLicense(std::string key);
std::string authLicense(std::string key, std::string hwid);

//Functions wrappers
Napi::String PostWrapper(const Napi::CallbackInfo &info);
Napi::String AuthWrapper(const Napi::CallbackInfo &info);

Napi::Object Init(Napi::Env env, Napi::Object exports);
}