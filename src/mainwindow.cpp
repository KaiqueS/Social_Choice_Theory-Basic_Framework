#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Classes/program_logic.h"

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ){

<<<<<<< HEAD
	scene = new QGraphicsScene(this);

	ui->screen->setScene(scene);

	fps = new QTimer(this);

	controle = new QTimer(this);

	//Connect timer

	connect(fps,SIGNAL(timeout()),this, SLOT(update()));

	fps->start(20);


//	text = scene->addText("Teste", QFont("Arial", 20) );
//	text->setPos(150,-150);

}

MainWindow::~MainWindow(){
=======
	ui -> setupUi( this );

	scene = new QGraphicsScene( this );

	ui -> screen -> setScene( scene );

	fps = new QTimer( this );

	controle = new QTimer( this );

	//Connect timer
	connect( fps, SIGNAL( timeout( ) ), this, SLOT( update( ) ) );
	fps -> start( 20 );


	text = scene -> addText( "SocialChoiceTheory", QFont( "Arial", 20 ) );
//	text -> setPos( 150, -150 );
	text -> setFlag( QGraphicsItem::ItemIsMovable );
}

MainWindow::~MainWindow( ){
>>>>>>> 62dde527f5b0c715e69e2538f8189fac9e4c0b7e

	delete ui;
}

<<<<<<< HEAD
void MainWindow::on_set_dimension_button_clicked(){

	int row = ui->row_size_input->value();

	int column = ui->column_size_input->value();

	std::vector<SocialPrefNode<char>> graph = logic.run_project(row,column);
	scene->clear();
	logic.clean();
	logic.show_graph(graph, scene);
}

void MainWindow::update(){
	logic.update();
=======
void MainWindow::on_set_dimension_button_clicked( ){

	int row = ui -> row_size_input -> value( );
	int column = ui -> column_size_input -> value( );

	Program_Logic::run_project( row, column );
>>>>>>> 62dde527f5b0c715e69e2538f8189fac9e4c0b7e
}
