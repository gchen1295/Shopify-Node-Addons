#include <napi.h>
#include <cpr/cpr.h>
#include "product.h"

namespace Shopify{
  std::string cartProduct(std::string domain, std::string pid);
  std::string getProductData();
  std::string getAllProducts(std::string domain);
  std::string findProductByTitle(std::string domain, std::vector<std::string> keywords);
  std::string findProductByHandle(std::string domain, std::vector<std::string> keywords);
  void monitorProduct();

  Napi::String MonitorWrapper();
  Napi::String CartProduct(const Napi::CallbackInfo &info);
  Napi::String GetProdData(const Napi::CallbackInfo &info);
  Napi::String GetAllProducts(const Napi::CallbackInfo &info);
  Napi::String FindProductByTitle(const Napi::CallbackInfo &info);
  Napi::String FindProductByHandle(const Napi::CallbackInfo &info);

  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
