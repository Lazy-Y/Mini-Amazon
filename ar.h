#ifndef AR_H
#define AR_H
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <cstring>
#include <sstream>
#include "review.h"
#include "datastore.h"
using namespace std;
class ar : public QWidget
{
	Q_OBJECT
public:
	ar(string prodName, DataStore* ds);
	~ar();
	void error();
private slots:
	void OK();
	void Cancel();
private:
	DataStore* ds;
	QLabel* rate;
	QLabel* date;
	QLabel* comment;
	QLabel* a;
	QLabel* b;
	QVBoxLayout* layout;
	QHBoxLayout* btn;
	QHBoxLayout* dlayout;
	QComboBox* addRate;
	QLineEdit* year;
	QLineEdit* month;
	QLineEdit* day;
	QTextEdit* addComment;
	QPushButton* ok;
	QPushButton* cancel;
	string prodName;
	Review* r;
};
#endif