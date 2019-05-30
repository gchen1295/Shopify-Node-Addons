
#include "asyncMonitor.h"

class ProductFinderM1 : public Napi::AsyncWorker
{
public:
  ProductFinderM1(Napi::Function &callback, std::string domain, std::vector<std::string> keywords) : Napi::AsyncWorker(callback), domain(domain), keywords(keywords){};

  ~ProductFinderM1(){};

  void Execute() override
  {
    res = Monitor::findProductByTitle(domain, keywords);
  };

  void OnOK() override
  {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {env.Null(), Napi::String::New(env, res)});
  };

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();
    Callback().Call({e.Value(), env.Undefined()});
  }

private:
  std::string domain;
  std::vector<std::string> keywords;
  std::string res = "";
};

class ProductScraper : public Napi::AsyncWorker
{
public:
  ProductScraper(Napi::Function &callback, std::string domain) : Napi::AsyncWorker(callback), domain(domain){};

  ~ProductScraper(){};

  void Execute() override
  {
    res = Monitor::getAllProducts(domain);
  };

  void OnOK() override
  {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {env.Null(), Napi::String::New(env, res)});
  };

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();
    Callback().Call({e.Value(), env.Undefined()});
  }

private:
  std::string domain;
  std::string res = "";
};

class ProductFinderM2 : public Napi::AsyncWorker
{
public:
  ProductFinderM2(Napi::Function &callback, std::string domain, std::vector<std::string> keywords) : Napi::AsyncWorker(callback), domain(domain), keywords(keywords){};

  ~ProductFinderM2(){};

  void Execute() override
  {
    res = Monitor::findProductByHandle(domain, keywords);
  };

  void OnOK() override
  {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {env.Null(), Napi::String::New(env, res)});
  };

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();
    Callback().Call({e.Value(), env.Undefined()});
  }

private:
  std::string domain;
  std::vector<std::string> keywords;
  std::string res = "";
};

class InstockFinder : public Napi::AsyncWorker
{
public:
  InstockFinder(Napi::Function &callback, std::string domain, std::string id) : Napi::AsyncWorker(callback), domain(domain), id(id){};

  ~InstockFinder(){};

  void Execute() override
  {
    res = Monitor::instockSizes(domain, id);
  };

  void OnOK() override
  {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {env.Null(), Napi::String::New(env, res)});
  };

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();
    Callback().Call({e.Value(), env.Undefined()});
  }

private:
  std::string domain;
  std::string id;
  std::string res = "";
};

class OutStockFinder : public Napi::AsyncWorker
{
public:
  OutStockFinder(Napi::Function &callback, std::string domain, std::string id) : Napi::AsyncWorker(callback), domain(domain), id(id){};
  ;

  ~OutStockFinder(){};

  void Execute() override
  {
    res = Monitor::outofstockSizes(domain, id);
  };

  void OnOK() override
  {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {env.Null(), Napi::String::New(env, res)});
  };

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();
    Callback().Call({e.Value(), env.Undefined()});
  }

private:
  std::string domain;
  std::string id;
  std::string res = "";
};

class SizeFinder : public Napi::AsyncWorker
{
public:
  SizeFinder(Napi::Function &callback, std::string domain, std::string id) : Napi::AsyncWorker(callback), domain(domain), id(id){};
  ;

  ~SizeFinder(){};

  void Execute() override
  {
    res = Monitor::getSizes(domain, id);
  };

  void OnOK() override
  {
    Napi::Env env = Env();
    Callback().MakeCallback(Receiver().Value(), {env.Null(), Napi::String::New(env, res)});
  };

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();
    Callback().Call({e.Value(), env.Undefined()});
  }

private:
  std::string domain;
  std::string id;
  std::string res = "";
};

Napi::Value ShopifyAsync::FindProductByTitleAsync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() < 3)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[1].IsArray())
  {
    Napi::Error::New(env, "Keywords must be an array!").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Must provide a string.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[2].IsFunction())
  {
    Napi::Error::New(env, "Must provide a callback function.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  std::string param1 = info[0].ToString();
  std::vector<std::string> param2;
  Napi::Function callback = info[2].As<Napi::Function>();
  Napi::Array arr = Napi::Array::Array(env, info[1]);
  for (size_t i = 0; i < arr.Length(); ++i)
  {
    Napi::Value val = arr.Get(i);
    // ++ ASSERT => val is string
    std::string keyword = val.ToString();
    param2.push_back(keyword);
  }
  ProductFinderM1 *mw = new ProductFinderM1(callback, param1, param2);
  mw->Queue();
  return info.Env().Undefined();
}

Napi::Value ShopifyAsync::FindProductByHandleAsync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 3)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[1].IsArray())
  {
    Napi::Error::New(env, "Keywords must be an array!").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Must be a string.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[2].IsFunction())
  {
    Napi::Error::New(env, "Must provide a callback function.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  std::string param1 = info[0].ToString();
  std::vector<std::string> param2;
  Napi::Function callback = info[2].As<Napi::Function>();
  Napi::Array arr = Napi::Array::Array(env, info[1]);
  for (size_t i = 0; i < arr.Length(); ++i)
  {
    Napi::Value val = arr.Get(i);
    // ++ ASSERT => val is string
    std::string keyword = val.ToString();
    param2.push_back(keyword);
  }
  ProductFinderM2 *mw = new ProductFinderM2(callback, param1, param2);
  mw->Queue();
  return info.Env().Undefined();
}

Napi::Value ShopifyAsync::GetAllProductsAsync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 2)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Must be a string.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[1].IsFunction())
  {
    Napi::Error::New(env, "Must provide a callback function.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  std::string param1 = info[0].ToString();
  Napi::Function callback = info[1].As<Napi::Function>();

  ProductScraper *psw = new ProductScraper(callback, param1);
  psw->Queue();
  return info.Env().Undefined();
}

Napi::Value ShopifyAsync::GetSizesAsync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 3)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[1].IsString())
  {
    Napi::Error::New(env, "Invalid argument").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Must be a string.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[2].IsFunction())
  {
    Napi::Error::New(env, "Must provide a callback function.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  std::string param2 = info[1].ToString();
  std::string param1 = info[0].ToString();
  Napi::Function callback = info[2].As<Napi::Function>();
  SizeFinder *psw = new SizeFinder(callback, param1, param2);
  psw->Queue();
  return info.Env().Undefined();
}

Napi::Value ShopifyAsync::OutSizesAsync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 3)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[1].IsString())
  {
    Napi::Error::New(env, "Invalid argument").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Must be a string.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[2].IsFunction())
  {
    Napi::Error::New(env, "Must provide a callback function.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  std::string param2 = info[1].ToString();
  std::string param1 = info[0].ToString();
  Napi::Function callback = info[2].As<Napi::Function>();

  OutStockFinder *psw = new OutStockFinder(callback, param1, param2);
  psw->Queue();
  return info.Env().Undefined();
}

Napi::Value ShopifyAsync::InstockSizesAsync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 3)
  {
    Napi::Error::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[1].IsString())
  {
    Napi::Error::New(env, "Invalid argument").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[0].IsString())
  {
    Napi::Error::New(env, "Must be a string.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  if (!info[2].IsFunction())
  {
    Napi::Error::New(env, "Must provide a callback function.").ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  std::string param2 = info[1].ToString();
  std::string param1 = info[0].ToString();
  Napi::Function callback = info[2].As<Napi::Function>();

  InstockFinder *psw = new InstockFinder(callback, param1, param2);
  psw->Queue();
  return info.Env().Undefined();
}

Napi::Object ShopifyAsync::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("findByTitle", Napi::Function::New(env, ShopifyAsync::FindProductByTitleAsync));
  exports.Set("findByHandle", Napi::Function::New(env, ShopifyAsync::FindProductByHandleAsync));
  exports.Set("getAllProducts", Napi::Function::New(env, ShopifyAsync::GetAllProductsAsync));
  exports.Set("getSizes", Napi::Function::New(env, ShopifyAsync::GetSizesAsync));
  exports.Set("outstockSizes", Napi::Function::New(env, ShopifyAsync::OutSizesAsync));
  exports.Set("instockSizes", Napi::Function::New(env, ShopifyAsync::InstockSizesAsync));
  return exports;
};