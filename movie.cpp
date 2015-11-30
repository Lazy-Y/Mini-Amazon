#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include "util.h"
#include "movie.h"
using namespace std;
Movie::Movie(const string category, const string name, double price,
             int qty, const string genre, const string rating):Product(category,name,price,qty) {
    genre_=genre;
    rating_=rating;
}
set<string> Movie::keywords() const {
    //find keywords
    set<string> keys=parseStringToWords(name_);
    set<string> keys2=parseStringToWords(genre_);
    keys=setUnion(keys,keys2);
    return keys;
}
string Movie::displayString() const {
    //display the data
    string info=name_+"\n"+"Genre: "+genre_+" Rating: "+rating_+"\n";
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
void Movie::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n";
    os << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
}

const string Movie::getA() const{
    return genre_;
}

const string Movie::getB() const{
    return rating_;
}