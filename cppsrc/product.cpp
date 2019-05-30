#include "product.h"

void Product::addVariant(std::string id, std::string title, std::string sku, std::string price, std::string available)
{
  Variant *v = new Variant(id, title, sku, price, available);
  variants.emplace(id, v);
}

void Product::removeVariant(std::string id)
{
  auto f = variants.find(id);
  if (f != variants.end())
  {
    delete f->second;
    variants.erase(f);
  }
}

Product::Product(std::string id, std::string title, std::string handle)
{
  this->id = id;
  this->title = title;
  this->handle = handle;
}
Product::~Product()
{
  for (auto &vr : this->variants)
  {
    delete vr.second;
  }
}

std::string Product::getVariants()
{
  std::string vstr = "";
  for (auto &var : this->variants)
  {
    std::string vid = var.second->getID();
    std::string vtitle = var.second->getTitle();
    std::string vsku = var.second->getSKU();
    std::string vprice = var.second->getPrice();
    //std::string vavailable = var.second->getAvailable();
    vid.erase(std::remove(vid.begin(), vid.end(), '"'), vid.end());
    vtitle.erase(std::remove(vtitle.begin(), vtitle.end(), '"'), vtitle.end());
    vsku.erase(std::remove(vsku.begin(), vsku.end(), '"'), vsku.end());
    vprice.erase(std::remove(vprice.begin(), vprice.end(), '"'), vprice.end());
    vstr += "{";
    vstr += "\"id\":\"" + var.second->getID() + "\",";
    vstr += "\"title\":\"" + var.second->getTitle() + "\",";
    vstr += "\"sku\":\"" + var.second->getSKU() + "\",";
    vstr += "\"price\":\"" + var.second->getPrice() + "\",";
    vstr += "\"available\":\"" + var.second->getAvailable() + "\"";
    vstr += "},";
  }
  vstr.pop_back();
  return vstr;
}

void Product::printFields()
{
  std::cout << "========= CONTENTS =========\n\n";
  std::cout << "{\n";
  std::cout << "\"id\":\"" + id + "\",\n";
  std::cout << "\"title\":\"" + title + "\",\n";
  std::cout << "\"handle\":\"" + handle + "\",\n";
  std::cout << "\"variants\":[";
  std::cout << getVariants() << '\n';
  std::cout << "]}\n";
}

std::string Product::getProduct()
{
  id.erase(std::remove(id.begin(), id.end(), '"'), id.end());
  title.erase(std::remove(title.begin(), title.end(), '"'), title.end());
  handle.erase(std::remove(handle.begin(), handle.end(), '"'), handle.end());
  std::string jsn = "{";
  jsn += "\"id\":\"" + id + "\",";
  jsn += "\"title\":\"" + title + "\",";
  jsn += "\"handle\":\"" + handle + "\",";
  jsn += "\"variants\":[";
  jsn += getVariants();
  jsn += "]}";
  return jsn;
}

std::string Product::getID()
{
  return this->id;
}

std::string Product::getTitle()
{
  return this->title;
}

std::string Product::getHandle()
{
  return this->handle;
}

// ================= VARIANTS ===========================

Variant::Variant(std::string id, std::string title, std::string sku, std::string price, std::string available)
{
  this->id = id;
  this->title = title;
  this->sku = sku;
  this->price = price;
  this->available = available;
}

std::string Variant::getID()
{
  return this->id;
}
std::string Variant::getTitle()
{
  return this->title;
}
std::string Variant::getSKU()
{
  return this->sku;
}
std::string Variant::getPrice()
{
  return this->price;
}
std::string Variant::getAvailable()
{
  return this->available;
}
bool Variant::isAvailable()
{
  if (this->available == "true")
  {
    return true;
  }
  else
  {
    return false;
  }
}

// ================= PRODUCTS COLLECTION ===========================

void ProductCollection::createProduct(std::string id, std::string title, std::string handle)
{
  //Creates our product and inserts into map with id as identifier
  Product *p = new Product(id, title, handle);
  products.emplace(id, p);
}

void ProductCollection::addVariant(std::string productID, std::string id, std::string title, std::string sku, std::string price, std::string available)
{
  products[productID]->addVariant(id, title, sku, price, available);
}

void ProductCollection::removeProduct(std::string id)
{
  products.erase(id);
}

void ProductCollection::printAll()
{
  for (auto &f : products)
  {
    f.second->printFields();
  }
}

Product *ProductCollection::findProductByID(std::string id)
{
  auto f = products.find(id);
  if (f != products.end())
  {
    return f->second;
  }
  else
  {
    return nullptr;
  }
}

Product *ProductCollection::findProductByTitle(std::string name)
{
  for (auto &f : products)
  {
    if (f.second->getTitle() == name)
    {
      return f.second;
    }
  }
  return nullptr;
}
Product *ProductCollection::findProductByHandle(std::string name)
{
  for (auto &f : products)
  {
    if (f.second->getHandle() == name)
    {
      return f.second;
    }
  }
  return nullptr;
}