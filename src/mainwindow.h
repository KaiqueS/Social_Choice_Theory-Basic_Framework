#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <iostream>
#include "Classes/program_logic.h"

namespace Ui{

	class MainWindow;
}

// Use RAII
class MainWindow : public QMainWindow{

	Q_OBJECT

public:

	explicit MainWindow( QWidget* parent = nullptr );

	~MainWindow( );

private slots:

	void on_set_dimension_button_clicked( );
	void update( );

private:

	Ui::MainWindow *ui{ };

	Program_Logic<char> *logic{ };

	QTimer* fps{ };
	QTimer* controle{ };

	QGraphicsScene* scene{ };
	QGraphicsEllipseItem* ellipse{ };
	QGraphicsRectItem* rectangle{ };
};

#endif // MAINWINDOW_H
