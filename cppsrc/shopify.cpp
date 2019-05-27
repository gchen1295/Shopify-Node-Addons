#include <napi.h>
#include "shopify.h"
#include "cpr/cpr.h"
#include <iostream>
#include <string>
#include "rapidjson/rapidjson.h"
#include "rapidjson/pointer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

std::string Shopify::cartProduct(std::string domain, std::string pid){
  std::string url = "https://" + domain + "/cart/add.json";
  auto r1 = cpr::Post(cpr::Url{url}, 
    cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
    cpr::Payload{{"id", pid},
                  {"quantity", "1"}});
  //rapidjson::Document doc;
  //doc.Parse(r1.text.c_str());
  //if(doc["quantity"] == 1){
  //  std::cout <<  doc["key"].GetString() << std::endl;
  //}
  return r1.text;
};

void monitorProduct(){

};

std::string Shopify::getAllProducts(std::string domain){
  std::string url = "https://" + domain + "/products.json";
  auto r1 = cpr::Get(cpr::Url(url));
  return r1.text;
};


//Function Wrappers
// 
//
//

Napi::String Shopify::CartProduct(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();
  if(!info[0].IsString() || info.Length() < 1 || !info[1].IsString()){
    throw Napi::Error::New(env, "Must be of type string!");
   }
  std::string param1 = info[0].ToString();
  std::string param2 = info[1].ToString();
  std::string s = Shopify::cartProduct(param1, param2);
  return Napi::String::New(env,s);
}

Napi::String Shopify::GetAllProducts(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();
  if(!info[0].IsString() || info.Length() < 1) throw Napi::Error::New(env, "Must be of type string!");
  std::string param1 = info[0].ToString();
  std::string s = Shopify::getAllProducts(param1);
  return Napi::String::New(env,s);
}

Napi::Object Shopify::Init(Napi::Env env, Napi::Object exports){
  exports.Set("cartProduct", Napi::Function::New(env, Shopify::CartProduct));
  //exports.Set("getProductData", Napi::Function::New(env, Shopify::GetProdData));
  exports.Set("getAllProducts", Napi::Function::New(env, Shopify::GetAllProducts));
  return exports;
}