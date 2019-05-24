#include <napi.h>

namespace Shopify{
bool createLicense(std::string url);
//std::string getLicense(std::string key);
bool authLicense(std::string key, std::string hwid);

//Functions wrappers
Napi::Boolean PostWrapper(const Napi::CallbackInfo &info);
Napi::String AuthWrapper(const Napi::CallbackInfo &info);

Napi::Object Init(Napi::Env env, Napi::Object exports);
}