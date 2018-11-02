#include "mainwindow.h"
#include <QApplication>

/*		 Fix the case where x and y have the same amount of votes, but no indifference: if xval == yval, then increase ival
 *		 Start documenting - IN PROGRESS
 *		 TODO: enhance code -> ADD EXCEPTIONS!
 *		 TODO: Remove templates, use static typing
 *		 TODO: Fix GUI problem: sometimes graphs are incomplete, i.e., not all nodes are connected
 *		 TODO: Fix GUI problem: for some values of row/column, graphs are not formed at all
 *		 TODO: Fix GUI problem: arrows pointing to the wrong direction
 *		 TODO: Fix GUI problem: create bidirectional arrows between indifferent elements
 *		 TODO: Document program_logic.h and q_graphic_node.h
 */

int main(int argc, char* argv[ ] ){

	srand( time( NULL ) );

	//	Start Widget
	QApplication a( argc, argv );

	MainWindow w;

	w.show( );

	return a.exec( );

}


