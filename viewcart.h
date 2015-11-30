#ifndef VIEWCART_H
#define VIEWCART_H
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <string>
#include <sstream>
#include "mw.h"
#include "datastore.h"
class viewcart : public QWidget
{
	Q_OBJECT
public:
	viewcart(User* user, MainWindow* mw);
	~viewcart();
	void error();
private slots:
	void OK();
	void Discard();
	void Buy();
private:
	MainWindow* mw;
	User* user;
	QLabel* name;
	QLabel* total;
	QVBoxLayout* layout;
	QHBoxLayout* buttons;
	QListWidget* products;
	QPushButton* buy;
	QPushButton* discard;
	QPushButton* ok;
};
#endif