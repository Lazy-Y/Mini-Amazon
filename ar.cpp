#include "ar.h"
using namespace std;
ar::ar(string prodName, DataStore* ds){
	this->ds=ds;
	string title="Add Review to ";
	this->prodName = prodName;
	title+=prodName;
	setWindowTitle(QString::fromStdString(title));
	layout = new QVBoxLayout();
	rate = new QLabel("Rating");
	date = new QLabel("Date");
	comment = new QLabel("comment");
	addRate = new QComboBox();
	addRate->addItem(QWidget::tr("5"));
	addRate->addItem(QWidget::tr("4"));
	addRate->addItem(QWidget::tr("3"));
	addRate->addItem(QWidget::tr("2"));
	addRate->addItem(QWidget::tr("1"));
	dlayout = new QHBoxLayout();
	a = new QLabel("-");
	b = new QLabel("-");
	year = new QLineEdit("YYYY");
	month = new QLineEdit("MM");
	day = new QLineEdit("DD");
	dlayout->addWidget(year);
	dlayout->addWidget(a);
	dlayout->addWidget(month);
	dlayout->addWidget(b);
	dlayout->addWidget(day);
	addComment = new QTextEdit("write comments here");
	cancel = new QPushButton("Cancel");
	ok = new QPushButton("Done");
	btn = new QHBoxLayout();
	btn->addWidget(cancel);
	btn->addWidget(ok);
	layout->addWidget(rate);
	layout->addWidget(addRate);
	layout->addWidget(date);
	layout->addLayout(dlayout);
	layout->addWidget(comment);
	layout->addWidget(addComment);
	layout->addLayout(btn);
	connect(ok, SIGNAL(clicked()), this, SLOT(OK()));
	connect(cancel, SIGNAL(clicked()), this, SLOT(Cancel()));
	setLayout(layout);
}

ar::~ar(){
	delete rate;
	delete date;
	delete comment;
	delete a;
	delete b;
	delete layout;
	delete dlayout;
	delete addRate;
	delete year;
	delete month;
	delete day;
	delete addComment;
	delete ok;
	delete cancel;
	delete btn;
}

void ar::OK(){
	int rating = 5 - addRate->currentIndex();
	string setDate; 
	string y = year->text().toStdString();
	string m = month->text().toStdString();
	string d = day->text().toStdString();
	string yu("2016");
	string yl("1899");
	string ml("00");
	string mu("13");
	string du("32");
	string dl("00");
	if (((y<yu and y>yl) and (d>dl and d<du)) and (m<mu and m>ml)) {
		setDate+=y;
		setDate+="-";
		setDate+=m;
		setDate+="-";
		setDate+=d;
		string Comment = addComment->toPlainText().toStdString();
		r = new Review(prodName,rating,setDate,Comment);
		ds->reviews.push_back(r);
		this->close();
	}
	else error();
}

void ar::Cancel(){
	this->close();
}

void ar::error(){
	QMessageBox msgBox;
	msgBox.setWindowTitle("Warning");
	msgBox.setText("Invalid Date\nValid Year: from 1900 ~ 2015\nValid Month: from 01 ~ 12\nValid Date: from 01 ~ 31");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Ok) {
		msgBox.close();
	}
}