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
  std::string getAllCleaned(std::string domain);
  std::string findProductByTitle(std::string domain, std::vector<std::string> keywords);
  std::string findProductByHandle(std::string domain, std::vector<std::string> keywords);
  std::string searchProductByTitle(std::string products, std::vector<std::string> keywords); // No request made just takes in JSON 
  std::string searchProductByHandle(std::string products, std::vector<std::string> keywords); // No request made just takes in JSON
  std::string searchSizes(std::string product, std::string productID); // No request made just takes in JSON
  std::string searchOutofstockSizes(std::string product, std::string productID);// No request made just takes in JSON
  std::string searchInstockSizes(std::string product, std::string productID); // No request made just takes in JSON
  std::string getSizes(std::string domain, std::string productID);
  std::string outofstockSizes(std::string domain, std::string productID);
  std::string instockSizes(std::string domain, std::string productID);
  std::string getRestocked(std::string domain, std::string productID, std::vector<std::string> variants);
  void monitorProduct();
}