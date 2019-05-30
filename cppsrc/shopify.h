#ifndef _SHOPIFY_H_
#define _SHOPIFY_H_
#include <napi.h>
#include "monitor.h"
#include <cpr/cpr.h>



namespace Shopify{
  std::string cartProduct(std::string domain, std::string pid);

  Napi::String MonitorWrapper();
  Napi::String CartProduct(const Napi::CallbackInfo &info);
  Napi::String GetProdData(const Napi::CallbackInfo &info);
  Napi::String GetAllProducts(const Napi::CallbackInfo &info);
  Napi::String FindProductByTitle(const Napi::CallbackInfo &info);
  Napi::String FindProductByHandle(const Napi::CallbackInfo &info);

  Napi::Object Init(Napi::Env env, Napi::Object exports);
}

#endif // !_SHOPIFY_H_