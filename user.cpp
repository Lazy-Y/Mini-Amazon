#include "user.h"
using namespace std;

User::User() : name_("unknown"), age_(0), balance_(0.0), type_(1)
{

}
User::User(std::string name, int age, double balance, int type) :
    name_(name), age_(age), balance_(balance), type_(type)
{

}

User::~User()
{

}


int User::getAge() const
{
    return age_;
}

std::string User::getName() const
{
    return name_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " " << age_ << " " << balance_ << " " << type_ << endl;
}

void User::addItem(Product* p){
	cart_.push_back(p);
}

void User::viewCart(){
	for (unsigned int i=0; i<cart_.size(); i++){
		cout << i+1 << " " << cart_[i]->getName() << endl;
	}
}

void User::buy(){
	//buy the product, calculate the balance and qty
	if (cart_.size()==0) return;
	vector<Product*> buyed;
	for (unsigned int i=cart_.size()-1; i+1>0; i--){
		double price=cart_[i]->buy();
		if (price==-1) {
			error(2,buyed);
			return;
		}
		else if (balance_<cart_[i]->getPrice()){
			error(1,buyed);
			return;
		}
		else {
			buyed.push_back(cart_[i]);
			balance_-=price;
			cart_[i]->subtractQty(1);
			cart_.erase(cart_.begin()+i);
		}
		if (i==0) break;
	}
	success(buyed);
}

void User::success(vector<Product*> buyed){
	QMessageBox msgBox;
	string name;
	if (buyed.size()>0){
		name+="Successfully buyed: \n";
		for (unsigned int i=0; i<buyed.size(); i++){
			name+="\"";
			name+=cart_[i]->getName();
			name+="\"\n";
		}
		name+="\n";
	}
	else {
		name+="You buyed nothing";
	}
	msgBox.setText(QString::fromStdString(name));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.show();
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Ok) {
		msgBox.close();
	}
}

void User::error(int i, vector<Product*> buyed){
	QMessageBox msgBox;
	msgBox.setWindowTitle("Warning");
	string name;
	if (buyed.size()>0){
		name+="Successfully buyed: \n";
		for (unsigned int i=0; i<buyed.size(); i++){
			name+="\"";
			name+=cart_[i]->getName();
			name+="\"\n";
		}
		name+="\n";
	}
	string words = "\"";
	words += cart_[cart_.size()-1]->getName();
	words += "\"";
	if (i==1){
		string a = "No enough credits to buy ";
		a+=words;
		name+=a;
	}
	else if (i==2){
		words += " is not in stock";
		name+=words;
	}
	msgBox.setText(QString::fromStdString(name));
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	msgBox.show();
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Ok) {
		msgBox.close();
	}
}

double User::getBalance(){
	return balance_;
}

void User::add(int add){
	balance_+=add;
}