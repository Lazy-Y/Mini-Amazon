#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include <QMessageBox>
#include <QLabel>
#include "product.h"
using namespace std;
/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, int age, double balance, int type);
    virtual ~User();

    int getAge() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    void addItem(Product* p);
    void viewCart();
    void buy();
    void error(int i,vector<Product*> buyed);
    double getBalance();
    void add(int add);
    void success(vector<Product*> buyed);
    vector<Product*> cart_;

private:
    std::string name_;
    int age_;
    double balance_;
    int type_;
};
#endif
