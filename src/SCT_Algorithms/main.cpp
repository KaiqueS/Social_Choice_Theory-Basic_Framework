#include "mainwindow.h"
#include <QApplication>



/*		 Fix the case where x and y have the same amount of votes, but no indifference: if xval == yval, then increase
 *		 Start documenting - IN PROGRESS
 *		 TODO: enhance code -> ADD EXCEPTIONS!
 *		 TODO: Remove templates, use static typing
 */


int main(int argc, char *argv[] ){


	srand( time( NULL ) );
//	Start Widget
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();

}


