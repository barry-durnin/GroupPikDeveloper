/*****************************************************************************
Client entry point

Authored by Barry Durnin.
******************************************************************************/

#include "gdp.h"
#include <QtWidgets/QApplication>

/**************************************************************************************************************
Entry point on windows
Trigger the GDP Main widget
**************************************************************************************************************/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GDP w;
	w.show();
	return a.exec();
}
