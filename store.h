#ifndef STORE_H
#define STORE_H
#include <iostream>
#include "datastore.h"
#include "user.h"
#include <map>
#include <vector>
#include "db_parser.h"
using namespace std;
class store : public DataStore
{
public:
    store();
    ~store();
    void addReview(Review* r);
    void addProduct(Product* p);
    void addUser(User* u);
    vector<Product*> search(vector<string>& terms, int type);
    void dump(ostream& ofile);
    const vector<Product*>& viewProd() const;
    int a();
private:
    vector<Product*> data;
    map<string,set<Product*> > storage;
};
#endif