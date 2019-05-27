#ifndef _SHOPIFYWRAPPED_
#define _SHOPIFYWRAPPED_

#include <napi.h>

class Monitor : public Napi::ObjectWrap<Monitor> {
  public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports); // Initializer?
  Monitor(const Napi::CallbackInfo &info);

  private:
    static Napi::FunctionReference constructor;

    Napi::Boolean AddToCart(const Napi::CallbackInfo &info);
    Napi::Boolean CheckCart(const Napi::CallbackInfo &info);
};


#endif