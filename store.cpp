#include "store.h"
#include <iostream>
#include "user.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "product.h"
#include "util.h"
#include "review.h"
#include <vector>
#include <set>
#include <map>
#include <fstream>
using namespace std;
store::store() {
}
store::~store(){
    //delet all data
    for (unsigned int i=0; i<data.size(); i++){
        delete data[i];
    }
    for (unsigned int i=0; i<users.size(); i++){
        delete users[i];
    }
    for (unsigned int i=0; i<reviews.size(); i++){
        delete reviews[i];
    }
}
void store::addProduct(Product* p) {
    data.push_back(p);
    bool x=0;
    //find keys and the matched object then store the keys and objects in the map
    set<string> keys=p->keywords();
    for (set<string>::iterator it=keys.begin(); it!=keys.end(); it++){
        for (map<string,set<Product*> >::iterator its=storage.begin(); its!=storage.end(); its++) {
            if (its->first!=*it) x=1;
        }
        if (x) {
            storage[*it].insert(p);
        }
        else {
            set<Product*> prod;
            prod.insert(p);
            storage[*it]=prod;
        }
    }
}
void store::addUser(User* u) {
    users.push_back(u);
}
vector<Product*> store::search(vector<string>& terms, int type) {
    set<Product*> result;
    vector<Product*> final;
    result=storage[terms[0]];
    //find the product one by one
    if (type==0) {
        for (unsigned int i = 0; i<terms.size(); i++) {
            result=setIntersection<Product*>(result,storage[terms[i]]);
        }
    }
    else if (type==1) {
        for (unsigned int i = 0; i < terms.size(); ++i){
            result=setUnion<Product*>(result,storage[terms[i]]);
        }
    }
    for (set<Product*>::iterator it2=result.begin(); it2!=result.end(); it2++) {
        final.push_back(*it2);
    }
    return final;
}
void store::dump(ostream& ofile) {
    //write into the file
    ofile << "<products>" << endl;
    for (unsigned int i=0; i<data.size(); i++) {
        data[i]->dump(ofile);
    }
    ofile << "</products>" << endl << "<users>" << endl;
    for (unsigned int i=0; i<users.size(); i++) {
        users[i]->dump(ofile);
    }
    ofile << "</users>" << endl << "<reviews>" << endl;
    for (unsigned int i=0; i<reviews.size(); i++) {
        reviews[i]->dump(ofile);
    }
    ofile << "</reviews>" << endl;
}
const vector<Product*>& store::viewProd() const{
    return data;
}
void store::addReview(Review* r){
    reviews.push_back(r);
}