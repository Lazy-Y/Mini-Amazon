#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include "product.h"
using namespace std;
class Book : public Product
{
public:
    Book(const string category, const string name, double price,
         int qty, const string author, const string ISBN);
    set<string> keywords() const;
    string displayString() const;
    //bool isMatch(vector<string>& searchTerms) const;
    void dump(ostream& os) const;
    const string getA() const;
    const string getB() const;
private:
    string author_;
    string ISBN_;
};


#endif