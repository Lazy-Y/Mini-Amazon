#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const string category, const string name, double price, int qty) {
    name_=name;
    price_=price;
    qty_=qty;
    category_=category;
}

Product::~Product()
{

}


double Product::getPrice() const
{
    return price_;
}

const string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

double Product::buy(){
  if (qty_==0) return -1;
  return price_;
}

string Product::getCate() const{
  return category_;
}
/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(vector<string>& searchTerms) const
{
    return false;
}

void Product::dump(ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}
