#include "mw.h"
#include "viewcart.h"
using namespace std;
viewcart::viewcart(User* user, MainWindow* mw){
	this->mw = mw;
	this->user = user;
	setWindowTitle("View Cart");
	layout = new QVBoxLayout();
	stringstream sa;
	sa << user->getBalance();
	string ba;
	sa >> ba;
	string sname=user->getName();
	sname+="'s Cart\t\tBalance: $";
	sname+=ba;
	name = new QLabel(QString::fromStdString(sname));
	products = new QListWidget();
	layout->addWidget(name);
	double p=0;
	for (unsigned int i=0; i<user->cart_.size(); i++){
		string info = user->cart_[i]->getName();
		stringstream ss;
		p+=user->cart_[i]->getPrice();
		ss << user->cart_[i]->getPrice();
		string a;
		ss >> a;
		info+=" $";
		info+=a;
		products->addItem(QString::fromStdString(info));
	}
	stringstream ss;
	ss << p;
	string pri;
	ss >> pri;
	string tpri = "Total Price is $";
	tpri+=pri;
	total = new QLabel(QString::fromStdString(tpri));
	layout->addWidget(total);
	layout->addWidget(products);
	buttons = new QHBoxLayout();
	buy = new QPushButton("Check Out");
	discard = new QPushButton("Remove Item");
	ok = new QPushButton("OK");
	buttons->addWidget(buy);
	buttons->addWidget(discard);
	buttons->addWidget(ok);
	connect(ok, SIGNAL(clicked()), this, SLOT(OK()));
	connect(discard, SIGNAL(clicked()), this, SLOT(Discard()));
	connect(buy,SIGNAL(clicked()),this,SLOT(Buy()));
	layout->addLayout(buttons);
	layout->addStretch();
	setLayout(layout);
}
viewcart::~viewcart(){
	products->clear();
	delete name;
	delete total;
	delete layout;
	delete buttons;
	delete products;
	delete buy;
	delete discard;
	delete ok;
}
void viewcart::OK(){
	this->close();
}

void viewcart::Discard(){
	int row = products->currentRow();
	if (row==-1) error();
	else{
		user->cart_.erase(user->cart_.begin()+row);
		products->takeItem(row);
	}
	double p=0;
	for (unsigned int i=0; i<user->cart_.size(); i++){
		p+=user->cart_[i]->getPrice();
	}
	stringstream ss;
	ss << p;
	string pri;
	ss >> pri;
	string tpri = "Total Price is $";
	tpri+=pri;
	total->setText(QString::fromStdString(tpri));
	mw->reset();
}

void viewcart::Buy(){
	user->buy();
	products->clear();
	stringstream sa;
	sa << user->getBalance();
	string ba;
	sa >> ba;
	string sname=user->getName();
	sname+="'s Cart\t\tBalance: $";
	sname+=ba;
	name->setText(QString::fromStdString(sname));
	double p=0;
	for (unsigned int i=0; i<user->cart_.size(); i++){
		string info = user->cart_[i]->getName();
		stringstream ss;
		p+=user->cart_[i]->getPrice();
		ss << user->cart_[i]->getPrice();
		string a;
		ss >> a;
		info+=" $";
		info+=a;
		products->addItem(QString::fromStdString(info));
	}
	stringstream ss;
	ss << p;
	string pri;
	ss >> pri;
	string tpri = "Total Price is $";
	tpri+=pri;
	total->setText(QString::fromStdString(tpri));
	mw->reset();
}

void viewcart::error(){
	QMessageBox msgBox;
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Please select a product");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Ok) {
		msgBox.close();
	}
}