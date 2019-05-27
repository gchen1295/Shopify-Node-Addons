#include <napi.h>

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