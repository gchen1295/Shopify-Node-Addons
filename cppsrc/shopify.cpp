#include <napi.h>
#include "shopify.h"
#include "cpr/cpr.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "rapidjson/rapidjson.h"
#include "rapidjson/pointer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

// ======= HELPER FUNCTIONS ============

void unique(std::vector<std::string> &keywords)
{
  std::vector<std::string>::iterator it;
  std::sort(keywords.begin(), keywords.end());
  it = std::unique(keywords.begin(), keywords.end());
  keywords.resize(std::distance(keywords.begin(), it));
}

void split(std::string sentence, std::string delimiter, std::vector<std::string> &words)
{
  size_t dpos = 0;
  std::string tmp;
  sentence += delimiter;
  while ((dpos = sentence.find(delimiter)) != std::string::npos)
  {
    tmp = sentence.substr(0, dpos);
    words.push_back(tmp);
    sentence.erase(0, dpos + delimiter.length());
  }
}

std::string Shopify::cartProduct(std::string domain, std::string pid)
{
  std::string url = "https://" + domain + "/cart/add.json";
  auto r1 = cpr::Post(cpr::Url{url},
                      cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}},
                      cpr::Payload{{"id", pid},
                                   {"quantity", "1"}});
  return r1.text;
};

std::string Shopify::getAllProducts(std::string domain)
{
  std::string url = "https://" + domain + "/products.json";
  auto r1 = cpr::Get(cpr::Url(url));
  rapidjson::Document doc;
  doc.Parse(r1.text.c_str());
  assert(doc["products"].IsArray());
  const rapidjson::Value &p = doc["products"];
  assert(p.IsArray());
  // static const char *kTypeNames[] =
  //     {"Null", "False", "True", "Object", "Array", "String", "Number"};

  // for(rapidjson::SizeType i = 0; i < p.Size(); i++){
  //   std::cout << p[i]["title"].GetString() << std::endl;
  //   std::cout << p[i]["handle"].GetString() << std::endl;
  // }
  return r1.text;
};

std::string Shopify::findProductByTitle(std::string domain, std::vector<std::string> keywords)
{
  ProductCollection pc = ProductCollection();
  int i = 0;
  std::vector<std::string>::iterator itr;
  std::vector<std::string> foundtitle;
  unique(keywords);
  std::string products = getAllProducts(domain);

  rapidjson::Document doc;
  doc.Parse(products.c_str());
  assert(doc["products"].IsArray());
  const rapidjson::Value &p = doc["products"];

  for (itr = keywords.begin(); itr != keywords.end(); ++itr)
  {
    for (rapidjson::SizeType i = 0; i < p.Size(); ++i)
    {
      std::string kw = *itr;
      std::string title = p[i]["title"].GetString();
      std::transform(kw.begin(), kw.end(), kw.begin(), ::tolower);
      std::transform(title.begin(), title.end(), title.begin(), ::tolower);

      if (title.find(kw) != std::string::npos)
      {
        //std::cout << "Found in title: " << title << std::endl;
        //std::cout << "Matched keyword: " << kw << std::endl;

        //BUILD OUR PRODUCT
        std::string id = std::to_string(p[i]["id"].GetInt64());
        std::string handle = p[i]["handle"].GetString();
        pc.createProduct(id, title, handle);

        // Loop through our variants
        const rapidjson::Value &var = doc["products"][i]["variants"];
        for (rapidjson::SizeType i = 0; i < var.Size(); i++)
        {
          std::string id2 = std::to_string(var[i]["id"].GetInt64());
          std::string vtitle = var[i]["title"].GetString();
          std::string sku = var[i]["sku"].GetString();
          std::string price = var[i]["price"].GetString();
          pc.addVariant(id, id2, vtitle, sku, price);
        }
        foundtitle.push_back(title);
      }
    }
  }
  //For each product in product title and product handle eliminate all that dont contain a kw
  unique(foundtitle);
  for (itr = keywords.begin(); itr != keywords.end(); ++itr)
  {
    std::string kw = *itr;
    std::vector<std::string>::iterator itr2;
    for (itr2 = foundtitle.begin(); itr2 != foundtitle.end(); ++itr2)
    {
      std::string title = *itr2;
      if (title.find(kw) == std::string::npos)
      {
        foundtitle.erase(itr2--);
      }
    }
  }
  std::string response = "";
  for (itr = foundtitle.begin(); itr != foundtitle.end(); ++itr)
  {
    Product *pt = pc.findProductByTitle(*itr);
    if (pt != nullptr)
    {
      pt->printFields();
      response += pt->getProduct();
      response += ",";
    }
  }
  if (response != "")
  {
    response.pop_back();
  }
  response = "[" + response + "]";
  return response;
  //BUILD PRODUCT OBJECT OR RETURN ARRAY OF PRODUCTS MATCHING?
  // For each product in our array create a json object
}

std::string Shopify::findProductByHandle(std::string domain, std::vector<std::string> keywords)
{
  int i = 0;
  ProductCollection pc = ProductCollection();
  std::vector<std::string>::iterator itr;
  std::vector<std::string> foundhandle;
  unique(keywords);
  std::string products = getAllProducts(domain);

  rapidjson::Document doc;
  doc.Parse(products.c_str());
  assert(doc["products"].IsArray());
  const rapidjson::Value &p = doc["products"];
  // === FIND ===
  for (itr = keywords.begin(); itr != keywords.end(); ++itr)
  {
    for (rapidjson::SizeType i = 0; i < p.Size(); ++i)
    {
      std::string kw = *itr;
      std::string handle = p[i]["handle"].GetString();
      std::string title = p[i]["title"].GetString();
      std::string id = std::to_string(p[i]["id"].GetInt64());
      std::transform(kw.begin(), kw.end(), kw.begin(), ::tolower);
      std::transform(handle.begin(), handle.end(), handle.begin(), ::tolower);
      if (handle.find(kw) != std::string::npos)
      {
        //BUILD OUR PRODUCT
        std::string id = p[i]["title"].GetString();
        std::string handle = p[i]["handle"].GetString();
        pc.createProduct(id, title, handle);

        // Loop through our variants
        const rapidjson::Value &var = doc["products"][i]["variants"];
        for (rapidjson::SizeType i = 0; i < var.Size(); i++)
        {
          std::string id2 = std::to_string(var[i]["id"].GetInt64());
          std::string vtitle = var[i]["title"].GetString();
          std::string sku = var[i]["sku"].GetString();
          std::string price = var[i]["price"].GetString();
          pc.addVariant(id, id2, vtitle, sku, price);
        }
        foundhandle.push_back(handle);
      }
    }
  }
  //For each product in product title and product handle eliminate all that dont contain a kw   === FILTER ===
  std::string response = "";
  for (itr = foundhandle.begin(); itr != foundhandle.end(); ++itr)
  {
    Product *pt = pc.findProductByHandle(*itr);
    if (pt != nullptr)
    {
      pt->printFields();
      response += pt->getProduct();
      response += ",";
    }
  }
  if (response != "")
  {
    response.pop_back();
  }
  response = "[" + response + "]";
  return response;
  //BUILD OUR PRODUCT OBJECT HERE
}

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
}

Napi::String Shopify::GetAllProducts(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!info[0].IsString() || info.Length() < 1)
    Napi::Error::New(env, "Must be of type string!").ThrowAsJavaScriptException();
  std::string param1 = info[0].ToString();
  std::string s = Shopify::getAllProducts(param1);
  return Napi::String::New(env, s);
}

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
  std::string s = Shopify::findProductByTitle(param1, param2);
  return Napi::String::New(env, s);
}

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
  std::string s = Shopify::findProductByHandle(param1, param2);
  return Napi::String::New(env, s);
}

Napi::Object Shopify::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("cartProduct", Napi::Function::New(env, Shopify::CartProduct));
  //exports.Set("getProductData", Napi::Function::New(env, Shopify::GetProdData));
  exports.Set("getAllProducts", Napi::Function::New(env, Shopify::GetAllProducts));
  exports.Set("findProductM1", Napi::Function::New(env, Shopify::FindProductByTitle));
  exports.Set("findProductM2", Napi::Function::New(env, Shopify::FindProductByHandle));
  return exports;
}