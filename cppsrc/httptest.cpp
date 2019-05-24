#include <cpr/cpr.h>
#include <napi.h>
#include <iostream>
#include "httptest.h"

#include <cstdint>
#include <iostream>
#include <vector>
//#include <bsoncxx/json.hpp>
//#include <bsoncxx/builder/stream/document.hpp>
//#include <mongocxx/client.hpp>
//#include <mongocxx/stdx.hpp>
//#include <mongocxx/uri.hpp>
//#include <mongocxx/instance.hpp>

//using bsoncxx::builder::stream::close_array;
//using bsoncxx::builder::stream::close_document;
//using bsoncxx::builder::stream::document;
//using bsoncxx::builder::stream::finalize;
//using bsoncxx::builder::stream::open_array;
//using bsoncxx::builder::stream::open_document;

std::string apifunctions::createLicense(){
  auto r = cpr::Post(cpr::Url{"https://api-shopify.incizzle.ca/admin/createLicense"}, cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},cpr::Payload{{}});
  return r.text;
}

std::string apifunctions::authLicense(std::string key, std::string hwid){
  auto r = cpr::Post(cpr::Url{"https://api-shopify.incizzle.ca/license/login"}, 
                      cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
                      cpr::Payload{ {"license", key },
                                    {"hwid", hwid } });
  std::cout << r.url << std::endl;
  std::cout << r.status_code << std::endl;
  return r.text;
}

std::string apifunctions::createTask(std::string website, std::string keywords, std::string size, int numTasks, int numCheckouts ){
  // Clean url her
  // Parse keywords here
  
  auto r = cpr::Post(cpr::Url{"https://api-shopify.incizzle.ca/task/create"},
                      cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
                      cpr::Payload{ {"website", website },
                                    {"keywords", keywords },
                                    {"size", size },
                                    {"numTasks", numTasks },
                                    {"numCheckouts", numCheckouts }});
  return r.text;
}

// ===== Function Wrappers =====
// PostWrapper(const Napi::CallbackInfo &info) => createLicense(url)
// AuthWrapper(const Napi::CallbackInfo &info) => authLicense(key, hwid)
// Init(Napi::Env env, Napi::Object exports) => createTask(website,keywords,size,numTasks,numCheckouts)

// = TODO =
// Add in type checking and missing argument calls


Napi::String apifunctions::PostWrapper(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();

  std::string s = apifunctions::createLicense();
  return Napi::String::New(env,s);
}

Napi::String apifunctions::AuthWrapper(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();
  if(info.Length() < 2 || !info[0].IsString() || !info[1].IsString()){
    throw Napi::Error::New(env, "Invalid Arguments!");
  }
  std::string k = info[0].ToString();
  std::string h = info[1].ToString();
  std::string cl = apifunctions::authLicense(k,h);
  return Napi::String::New(env,cl);
}

Napi::String apifunctions::NewTaskWrapper(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();
  if(info.Length() < 5 || !info[0].IsString() || !info[1].IsString() || !info[2].IsString() || !info[3].IsNumber() || !info[4].IsNumber()){
    throw Napi::Error::New(env, "Invalid Arguments!");
  }
  std::string w = info[0].ToString();
  std::string kw = info[1].ToString();
  std::string sz = info[2].ToString();
  int nt = info[3].ToNumber();
  int nc = info[4].ToNumber();

  std::string response = createTask(w , kw, sz, nt, nc);
  return Napi::String::New(env, response);
}

Napi::Object apifunctions::Init(Napi::Env env, Napi::Object exports){
  exports.Set("post", Napi::Function::New(env, apifunctions::PostWrapper));
  exports.Set("authLicense", Napi::Function::New(env, apifunctions::AuthWrapper));
  return exports;
}


