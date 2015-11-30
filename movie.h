#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include "product.h"
using namespace std;
class Movie : public Product
{
public:
    Movie(const string category, const string name, double price,
          int qty, const string genre, const string rating);
    set<string> keywords() const;
    string displayString() const;
    //bool isMatch(vector<string>& searchTerms) const;
    void dump(ostream& os) const;
    const string getA() const;
    const string getB() const;
private:
    string genre_;
    string rating_;
};
#endif