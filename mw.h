#ifndef MW_H
#define MW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QListWidget>
#include <QString>
#include <cstring>
#include <vector>
#include <QImage>
#include <QMessageBox>
#include <QButtonGroup>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "store.h"
#include "user.h"
#include "msort.h"
#include "review.h"
#include "ar.h"


class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
	void error(int i);
	void sort(vector<Product*>& p);
	struct Comparator1
	{
		bool operator()(const Product* x, const Product* y) const{
			string a,b;
			a=x->getName();
			b=y->getName();
			return (a<b);
		}
	};
	struct  Comparator2
	{
		Comparator2(DataStore* ds){
			this->ds = ds;
		}
		DataStore* ds;
		bool operator()(Product* x, Product* y){
	      	int nx,ny;
    	  	double rx,ry;
    	  	nx=0;
    	 	ny=0;
	      	rx=0;
	    	ry=0;
	    	const vector<Review*> r = ds->getReview();
    	  	for (unsigned int i=0; i<r.size(); i++){
      			if (x->getName() == r[i]->prodName){
          			nx++;
          			rx+=r[i]->rating;
        		}
        		if (y->getName() == r[i]->prodName){
          			ny++;
          			ry+=r[i]->rating;
        		}
        	}
	      	if (nx!=0) rx/=nx;
    	  	if (ny!=0) ry/=ny;
			return (rx>ry);
		}
	};
	struct Comparator3
	{
		bool operator()(const Review* x,const Review* y){return (x->date>y->date);}	
	};
	bool success;
	void reset();
	vector<string> Keys(stringstream& words);

private slots:
	void showQuit();
	void ViewCart();
	void Search();
	void displayReview();
	void AddReview();
	void add();
	void credit();
	void exit();

private:
	friend Comparator2;
	DataStore* ds;
	vector<Product*> hits;
	QPushButton* ac;
	QButtonGroup* group;
	QVBoxLayout* reviewsDisplayLayout;
	QVBoxLayout* productDisplayLayout;
	QVBoxLayout* userDisplayLayout;
	QVBoxLayout* control;
	QLineEdit* keywords;
	QHBoxLayout* overallLayout;
	QPushButton* addReview;
	QPushButton* addCart;
	QPushButton* viewCart;
	QPushButton* quit;
	QRadioButton* AND;
	QRadioButton* OR;
	QRadioButton* alpha;
	QRadioButton* rating;
	QButtonGroup* group1;
	QPushButton* search;
	QPushButton* q;
	QLabel* words;
	QListWidget* productListWidget;
	QListWidget* reviewsListWidget;
	QListWidget* userListWidget;
	QLabel* reviewsNameLabel;
	QLabel* productNameLabel;
	QLabel* userNameLabel;
};

#endif