#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	scene = new QGraphicsScene(this);
	ui->screen->setScene(scene);
	fps = new QTimer(this);
	controle = new QTimer(this);

	//Connect timer
	connect(fps,SIGNAL(timeout()),this, SLOT(update()));
	fps->start(20);


	text = scene->addText("Teste", QFont("Arial", 20) );
//	text->setPos(150,-150);
	text->setFlag(QGraphicsItem::ItemIsMovable);
}

MainWindow::~MainWindow()
{
	delete ui;
}
