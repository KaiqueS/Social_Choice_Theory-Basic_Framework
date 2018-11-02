#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Classes/program_logic.h"

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ){

	ui -> setupUi( this );

	scene = new QGraphicsScene( this );

	ui -> screen -> setScene( scene );

	fps = new QTimer( this );

	controle = new QTimer( this );

	// Connect timer
	connect( fps, SIGNAL( timeout( ) ), this, SLOT( update( ) ) );

	fps -> start( 20 );
}

MainWindow::~MainWindow( ){

	delete ui;
}

void MainWindow::on_set_dimension_button_clicked( ){

	int row = ui -> row_size_input -> value( );
	int column = ui -> column_size_input -> value( );

	std::vector<SocialPrefNode<char>> graph = logic.run_project( row, column );

	scene -> clear( );

	logic.clean( );
	logic.show_graph( graph, scene );
	logic.rank();
}

void MainWindow::update( ){

	logic.update( ui -> isMagnetic -> isChecked( ) );
}
