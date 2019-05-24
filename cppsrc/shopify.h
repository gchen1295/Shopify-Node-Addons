#include <napi.h>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

namespace Shopify{
  Napi::String Shopify::PostWrapper(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();
    std::string s = Shopify::createLicense(info[0].ToString());
    return Napi::String::New(env,s);
  }
}
