#include <napi.h>
#include "shopify.h"
#include "monitor.h"

namespace ShopifyAsync
{
Napi::Value FindProductByTitleAsync(const Napi::CallbackInfo &info);
Napi::Value FindProductByHandleAsync(const Napi::CallbackInfo &info);
Napi::Value GetAllProductsAsync(const Napi::CallbackInfo &info);
Napi::Value InstockSizesAsync(const Napi::CallbackInfo &info);
Napi::Value OutSizesAsync(const Napi::CallbackInfo &info);
Napi::Value GetSizesAsync(const Napi::CallbackInfo &info);
Napi::Object Init(Napi::Env env, Napi::Object exports);
} // namespace ShopifyAsync

