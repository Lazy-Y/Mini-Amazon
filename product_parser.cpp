#include <iostream>
#include <sstream>
#include "product_parser.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
/** Add any other desired #includes below */


using namespace std;

static string &trim(string &s);

ProductParser::ProductParser(){}

ProductParser::~ProductParser()
{

}


Product* ProductParser::parse(string category,
                              istream& is,
                              bool& error,
                              string& errorMsg,
                              int& lineno)
{

    parseCommonProduct(is, error, errorMsg, lineno);
    if(error) return NULL;
    return parseSpecificProduct(category, is, error, errorMsg, lineno);
}

void ProductParser::parseCommonProduct(istream& is,
                                       bool& error,
                                       string& errorMsg,
                                       int& lineno)

{
    lineno++;
    string myline;
    getline(is, myline);
    myline = trim(myline);
    if(myline.size() == 0) {
        error = true;
        errorMsg = "Unable to find a product name";
        return;
    }
    prodName_ = myline;

    lineno++;
    getline(is, myline);
    if(is.fail()) {
        error = true;
        errorMsg = "Expected another line with the price";
        return;
    }
    stringstream ss1(myline);
    ss1 >> price_;
    if( ss1.fail() ) {
        error = true;
        errorMsg = "Unable to read price";
        return;
    }

    lineno++;
    getline(is, myline);
    if(is.fail()) {
        error = true;
        errorMsg = "Expected another line with the quantity";
        return;
    }
    stringstream ss2(myline);
    ss2 >> qty_;
    if( ss2.fail() ) {
        error = true;
        errorMsg = "Unable to read quantity";
    }
}

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
static inline string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}


ProductBookParser::ProductBookParser() : ProductParser(){}

Product* ProductBookParser::parseSpecificProduct(string category,
        istream& is,
        bool& error,
        string& errorMsg,
        int& lineno)
{
    lineno++;
    string myline;
    getline(is, myline);
    stringstream ss3(myline);
    ss3 >> isbn_;
    if(ss3.fail()) {
        error = true;
        errorMsg = "Unable to read ISBN";
    }

    lineno++;
    getline(is, author_);
    if(is.fail()) {
        error = true;
        errorMsg = "Unable to read author";
    }
#ifdef DEBUG
    cout << "Making product " << prodName_ << endl;
#endif
    if(error) {
        return NULL;
    }
    return makeProduct(prodName_,price_,qty_,author_,isbn_);

}

string ProductBookParser::categoryID()
{
    return "book";
}


/**
 * Your job to fill in the code to create a new book product
 * using the data members in this class and the parent ProductParser class
 */
Product* ProductBookParser::makeProduct(const string prodName_, double price_,
                      int qty_, const string author_, const string isbn_)
{
    Product* Item = new Book("book",prodName_,price_,qty_,author_,isbn_);
    return Item;
}




ProductClothingParser::ProductClothingParser():ProductParser(){}

Product* ProductClothingParser::parseSpecificProduct(string category,
        istream& is,
        bool& error,
        string& errorMsg,
        int& lineno)
{
    lineno++;
    string myline;
    getline(is, myline);
    stringstream ss3(myline);
    ss3 >> size_;
    if(ss3.fail()) {
        error = true;
        errorMsg = "Unable to read size";
    }

    lineno++;
    getline(is, brand_);
    if(is.fail()) {
        error = true;
        errorMsg = "Unable to read brand";
    }
#ifdef DEBUG
    cout << "Making product " << prodName_ << endl;
#endif
    if(error) {
        return NULL;
    }
    return makeProduct(prodName_, price_, qty_, brand_, size_);

}

string ProductClothingParser::categoryID()
{
    return "clothing";
}


/**
 * Your job to fill in the code to create a new clothing product
 * using the data members in this class and the parent ProductParser class
 */
Product* ProductClothingParser::makeProduct(const string prodName_, double price_,
                      int qty_, const string brand_, const string size_)
{
    Product* Item = new Clothing("clothing",prodName_,price_,qty_,brand_,size_);
    return Item;
}



ProductMovieParser::ProductMovieParser():ProductParser(){}


Product* ProductMovieParser::parseSpecificProduct(string category,
        istream& is,
        bool& error,
        string& errorMsg,
        int& lineno)
{
    lineno++;
    string myline;
    getline(is, myline);
    stringstream ss3(myline);
    ss3 >> genre_;
    if(ss3.fail()) {
        error = true;
        errorMsg = "Unable to read genre";
    }

    lineno++;
    getline(is, myline);
    stringstream ss4(myline);
    ss4 >> rating_;
    if(ss4.fail()) {
        error = true;
        errorMsg = "Unable to read rating";
    }
#ifdef DEBUG
    cout << "Making product " << prodName_ << endl;
#endif
    if(error) {
        return NULL;
    }
    return makeProduct(prodName_, price_, qty_, genre_, rating_);

}

string ProductMovieParser::categoryID()
{
    return "movie";
}


/**
 * Your job to fill in the code to create a new movie product
 * using the data members in this class and the parent ProductParser class
 */
Product* ProductMovieParser::makeProduct(const string prodName_, double price_,
                      int qty_, const string genre_, const string rating_)
{
    Product* Item = new Movie("movie",prodName_,price_,qty_,genre_,rating_);
    return Item;
}
