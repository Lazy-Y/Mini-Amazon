#ifndef MSORT_H
#define MSORT_H
#include <iostream>
#include <vector>
#include <string>
#include "product.h"
using namespace std;
struct Comparator
{
	bool operator()(const string& x, const string& y) const{return (x<y);}
	bool operator()(const string* x, const string* y) const{return (*x<*y);}
};

template <class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp, int low, int high){
	if (low < high){
		int mid = (low + high)/2;
		mergeSort(myArray,comp,low,mid);
		mergeSort(myArray,comp,mid+1,high);
		vector<T> v1,v2;
		for (int i=low; i<=mid; i++){
			v1.push_back(myArray[i]);
		}
		for (int i=mid+1; i<=high; i++){
			v2.push_back(myArray[i]);
		}
		for (int i=high; i>=low; i--){
			if (v1.empty()) {
				myArray[i]=v2[v2.size()-1];
				v2.pop_back();
			}
			else if (v2.empty()) {
				myArray[i]=v1[v1.size()-1];
				v1.pop_back();
			}
			else{
				if (comp(v1[v1.size()-1],v2[v2.size()-1])){
					myArray[i]=v2[v2.size()-1];
					v2.pop_back();
				}
				else {
					myArray[i]=v1[v1.size()-1];
					v1.pop_back();
				}
			}
		}
	}
}
#endif