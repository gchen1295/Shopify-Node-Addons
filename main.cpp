#include <napi.h>
#include "cppsrc/httptest.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return apifunctions::Init(env,exports);
}

NODE_API_MODULE(testaddon, InitAll)