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

class MainWindow : public QMainWindow{

	Q_OBJECT

public:

	explicit MainWindow( QWidget* parent = nullptr );

	~MainWindow();

private slots:
<<<<<<< HEAD
	void on_set_dimension_button_clicked();
	void update();
=======

	void on_set_dimension_button_clicked( );

>>>>>>> 62dde527f5b0c715e69e2538f8189fac9e4c0b7e
private:

	Ui::MainWindow *ui;
<<<<<<< HEAD
	Program_Logic<char> logic;
	QTimer *fps;
	QTimer *controle;
	QGraphicsScene *scene;
	QGraphicsEllipseItem *ellipse;
	QGraphicsRectItem *rectangle;
=======

	QTimer* fps;
	QTimer* controle;

	QGraphicsScene* scene;
	QGraphicsEllipseItem* ellipse;
	QGraphicsRectItem* rectangle;
	QGraphicsTextItem* text;
>>>>>>> 62dde527f5b0c715e69e2538f8189fac9e4c0b7e
};

#endif // MAINWINDOW_H
