#include <napi.h>
#include "cppsrc/httptest.h"
#include "cppsrc/shopify.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  Shopify::Init(env,exports);
  return apifunctions::Init(env,exports);
}

NODE_API_MODULE(botmodules, InitAll)