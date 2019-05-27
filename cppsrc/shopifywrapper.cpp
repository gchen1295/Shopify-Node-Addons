#include "shopifywrapped.h"

Napi::FunctionReference Monitor::constructor;

Napi::Object Monitor::Init(Napi::Env env, Napi::Object exports){
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Monitor",{
    InstanceMethod("addToCart", &Monitor::AddToCart),
    InstanceMethod("checkCart", &Monitor::CheckCart)
  });
}