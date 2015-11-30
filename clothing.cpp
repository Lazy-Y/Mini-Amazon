#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include "util.h"
#include "clothing.h"
using namespace std;
Clothing::Clothing(const string category, const string name, double price,
                   int qty, const string brand, const string size):Product(category,name,price,qty) {
    brand_=brand;
    size_=size;
}
set<string> Clothing::keywords() const {
    //find keywords
    set<string> keys=parseStringToWords(name_);
    set<string> keys2=parseStringToWords(brand_);
    keys=setUnion(keys,keys2);
    return keys;
}
string Clothing::displayString() const {
    //display the data
    string info=name_+"\n"+"Brand: "+brand_+" Size: ";
    info+=size_;
    info+="\n";
    stringstream temp,temp1;
    temp << price_;
    string cur,cur1;
    temp >> cur;
    info+=cur;
    info+=" ";
    temp1 << qty_;
    temp1 >> cur1;
    info+=cur1;
    info+=" left";
    return info;
}
//bool isMatch(vector<string>& searchTerms) const;
void Clothing::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n";
    os << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}

const string Clothing::getA() const{
    return brand_;
}

const string Clothing::getB() const{
    return size_;
}