#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include "book.h"
#include "util.h"
Book::Book(const string category, const string name, double price,
           int qty, const string author, const string ISBN):Product(category,name,price,qty) {
    author_=author;
    ISBN_=ISBN;
}
set<string> Book::keywords() const {
    //find keywords
    set<string> keys=parseStringToWords(name_);
    set<string> keys2=parseStringToWords(author_);
    keys=setUnion<string>(keys,keys2);
    keys2.clear();
    keys2.insert(ISBN_);
    keys=setUnion<string>(keys,keys2);
    return keys;
}
string Book::displayString() const {
    //display the data
    string info=name_+"\n"+"Author: "+author_+" ISBN: "+ISBN_+"\n";
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
void Book::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n";
    os << qty_ << "\n" << ISBN_ << "\n" << author_ << "\n";
}

const string Book::getA() const{
    return author_;
}

const string Book::getB() const{
    return ISBN_;
} 