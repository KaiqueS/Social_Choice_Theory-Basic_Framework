#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <iostream>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_set_dimension_button_clicked();

private:
	Ui::MainWindow *ui;

	QTimer *fps;
	QTimer *controle;
	QGraphicsScene *scene;
	QGraphicsEllipseItem *ellipse;
	QGraphicsRectItem *rectangle;
	QGraphicsTextItem *text;
};

#endif // MAINWINDOW_H
