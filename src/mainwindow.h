#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <iostream>
#include <QTreeWidget>
#include <QFileDialog>
#include <QBuffer>
#include <iostream>
#include <fstream>
#include "Classes/program_logic.h"

namespace Ui{

	class MainWindow;
}

// Use RAII
class MainWindow : public QMainWindow{

	Q_OBJECT

public:

	Program_Logic<char> *logic{ };
	explicit MainWindow( QWidget* parent = nullptr );

	~MainWindow( );



private slots:

	void on_set_dimension_button_clicked( );
	void update( );

	void on_actionSave_triggered();

	void on_actionLoad_triggered();

	void on_actionimport_triggered();

	void on_actionExport_triggered();

private:




	Ui::MainWindow *ui{ };


	QTimer* fps{ };
	QTimer* controle{ };

	QGraphicsScene* scene{ };
	QGraphicsEllipseItem* ellipse{ };
	QGraphicsRectItem* rectangle{ };
};

#endif // MAINWINDOW_H
