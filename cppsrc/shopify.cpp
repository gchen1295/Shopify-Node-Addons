#include "shopify.h"

std::string Shopify::cartProduct(std::string domain, std::string pid)
{
  std::string url = "https://" + domain + "/cart/add.json";
  auto r1 = cpr::Post(cpr::Url{url},
                      cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
                      cpr::Payload{{"id", pid},
                                   {"quantity", "1"}});
  return r1.text;
};

//Function Wrappers
//
//
//

Napi::String Shopify::CartProduct(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!info[0].IsString() || info.Length() < 1 || !info[1].IsString())
  {
    Napi::Error::New(env, "Must be of type string!").ThrowAsJavaScriptException();
  }
  std::string param1 = info[0].ToString();
  std::string param2 = info[1].ToString();
  std::string s = Shopify::cartProduct(param1, param2);
  return Napi::String::New(env, s);
};

Napi::String Shopify::GetAllProducts(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!info[0].IsString() || info.Length() < 1)
    Napi::Error::New(env, "Must be of type string!").ThrowAsJavaScriptException();
  std::string param1 = info[0].ToString();
  std::string s = Monitor::getAllProducts(param1);
  return Napi::String::New(env, s);
};

Napi::String Shopify::FindProductByTitle(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 2)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Must be a string!").ThrowAsJavaScriptException();
  }
  if (!info[1].IsArray())
  {
    Napi::Error::New(env, "Keywords must be an array!").ThrowAsJavaScriptException();
  }
  std::string param1 = info[0].ToString();
  std::vector<std::string> param2;
  Napi::Array arr = Napi::Array::Array(env, info[1]);
  for (size_t i = 0; i < arr.Length(); ++i)
  {
    Napi::Value val = arr.Get(i);
    // ++ ASSERT => val is string
    std::string keyword = val.ToString();
    param2.push_back(keyword);
  }
  std::string s = Monitor::findProductByTitle(param1, param2);
  return Napi::String::New(env, s);
};

Napi::String Shopify::FindProductByHandle(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 2)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
  }
  if (!info[1].IsArray())
  {
    Napi::Error::New(env, "Keywords must be an array!").ThrowAsJavaScriptException();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Site must be a string!").ThrowAsJavaScriptException();
  }
  std::string param1 = info[0].ToString();
  std::vector<std::string> param2;
  Napi::Array arr = Napi::Array::Array(env, info[1]);
  for (size_t i = 0; i < arr.Length(); ++i)
  {
    Napi::Value val = arr.Get(i);
    // ++ ASSERT => val is string
    std::string keyword = val.ToString();
    param2.push_back(keyword);
  }
  std::string s = Monitor::findProductByHandle(param1, param2);
  return Napi::String::New(env, s);
};

Napi::Object Shopify::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("cartProduct", Napi::Function::New(env, Shopify::CartProduct));
  //exports.Set("getProductData", Napi::Function::New(env, Shopify::GetProdData));
  exports.Set("getAllProductsSync", Napi::Function::New(env, Shopify::GetAllProducts));
  exports.Set("findByTitleSync", Napi::Function::New(env, Shopify::FindProductByTitle));
  exports.Set("findByHandleSync", Napi::Function::New(env, Shopify::FindProductByHandle));
  return exports;
}

