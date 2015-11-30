#include "mw.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWindow;

	if (mainWindow.success) mainWindow.show();
	else return 1;

	return app.exec();
}
