#include "rapidjson/rapidjson.h"
#include "rapidjson/pointer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "product.h"
#include "cpr/cpr.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace Monitor{
  std::string getAllProducts(std::string domain);
  std::string findProductByTitle(std::string domain, std::vector<std::string> keywords);
  std::string findProductByHandle(std::string domain, std::vector<std::string> keywords);
  std::string getSizes(std::string domain, std::string productID);
  std::string outofstockSizes(std::string domain, std::string productID);
  std::string instockSizes(std::string domain, std::string productID);
  void monitorProduct();
}