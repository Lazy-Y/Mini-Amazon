#ifndef PRODUCT_PARSER_H
#define PRODUCT_PARSER_H
#include <string>
#include <iostream>
#include "product.h"

class ProductParser
{
public:
    ProductParser();

    virtual ~ProductParser();


    Product* parse(std::string category,
                   std::istream& is,
                   bool& error,
                   std::string& errorMsg,
                   int& lineno);

    void parseCommonProduct(std::istream& is,
                            bool& error,
                            std::string& errorMsg,
                            int& lineno);

    virtual Product* parseSpecificProduct(std::string category,
                                          std::istream& is,
                                          bool& error,
                                          std::string& errorMsg,
                                          int& lineno) = 0;

    virtual std::string categoryID() = 0;

protected:
    virtual Product* makeProduct(const std::string name, double price,
                      int qty, const std::string a, const std::string b) = 0;

    std::string prodName_;
    double price_;
    int qty_;

};


class ProductBookParser : public ProductParser
{
public:
    ProductBookParser();
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);

    std::string categoryID();

protected:
    Product* makeProduct(const std::string name, double price,
                      int qty, const std::string author, const std::string isbn);

private:
    std::string isbn_;
    std::string author_;
};


class ProductClothingParser : public ProductParser
{
public:
    ProductClothingParser();
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);

    std::string categoryID();

protected:
    Product* makeProduct(const std::string name, double price,
                      int qty, const std::string size, const std::string brnad);

private:
    std::string size_;
    std::string brand_;
};


class ProductMovieParser : public ProductParser
{
public:
    ProductMovieParser();
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);

    std::string categoryID();

protected:
    Product* makeProduct(const std::string name, double price,
                      int qty, const std::string genre, const std::string rating);

private:
    std::string genre_;
    std::string rating_;
};

#endif
