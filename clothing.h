#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include "product.h"
using namespace std;
class Clothing : public Product
{
public:
    Clothing(const string category, const string name, double price,
             int qty, const string brand, const string size);
    set<string> keywords() const;
    string displayString() const;
    //bool isMatch(vector<string>& searchTerms) const;
    void dump(ostream& os) const;
    const string getA() const;
    const string getB() const;
private:
    string brand_;
    string size_;
};


#endif