#include <cpr/cpr.h>
#include <napi.h>
#include <iostream>
#include "httptest.h"


std::string apifunctions::createLicense(std::string url){
  auto r = cpr::Post(cpr::Url{"https://api-shopify.incizzle.ca/admin/createLicense"}, cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},cpr::Payload{{}});

  return r.text;
}

std::string apifunctions::authLicense(std::string key, std::string hwid){
  auto r = cpr::Post(cpr::Url{"https://api-shopify.incizzle.ca/license/login"}, 
                      cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
                      cpr::Payload{ {"license", key },
                                    {"hwid", hwid } });
  //std::cout << key << std::endl << hwid << std::endl;
  std::cout << r.url << std::endl;
  std::cout << r.status_code << std::endl;
  return r.text;
}

Napi::String apifunctions::PostWrapper(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();
  std::string s = apifunctions::createLicense(info[0].ToString());
  return Napi::String::New(env,s);
}

Napi::String apifunctions::AuthWrapper(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();
  std::string k = info[0].ToString();
  std::string h = info[1].ToString();
  std::string cl = apifunctions::authLicense(k,h);
  return Napi::String::New(env,cl);
}

Napi::Object apifunctions::Init(Napi::Env env, Napi::Object exports){
  exports.Set("post", Napi::Function::New(env, apifunctions::PostWrapper));
  exports.Set("authLicense", Napi::Function::New(env, apifunctions::AuthWrapper));
  return exports;
}


