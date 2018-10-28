#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Classes/program_logic.h"

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ){

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

	delete ui;
}

void MainWindow::on_set_dimension_button_clicked( ){

	int row = ui -> row_size_input -> value( );
	int column = ui -> column_size_input -> value( );

	Program_Logic::run_project( row, column );
}
