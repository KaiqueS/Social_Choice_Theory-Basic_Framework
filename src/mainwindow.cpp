#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Classes/program_logic.h"

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ){

	logic = new Program_Logic<char>();

	ui -> setupUi( this );

	scene = new QGraphicsScene( this );

	ui -> screen -> setScene( scene );

	ui->actionLoad->setToolTip(tr("Load contacts from a file"));

	ui->actionSave->setToolTip(tr("Save contacts to a file"));

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

	delete logic;

	logic = new Program_Logic<char>();

	int row = ui -> row_size_input -> value( );

	int column = ui -> column_size_input -> value( );

	std::vector<SocialPrefNode<char>> graph = logic->run_project( row, column );

	scene -> clear( );

	logic -> show_graph( graph, scene );

	logic -> rank();

}

void MainWindow::update( ){

	logic->update( ui -> isMagnetic -> isChecked( ) );
}

void MainWindow::on_actionSave_triggered()
{

	QString filename = QFileDialog::getSaveFileName(this,
	tr("Save Address Book"), "",
	tr("Address Book (*.csv);;All Files (*)"));
	QFile file(filename);

	if(!file.open(QIODevice::WriteOnly))
	{
		std::cout << "Could not open " << QString(filename).toStdString() << std::flush;
		return;
	}

	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_5_1);



	std::vector<Agent<char>> listofagents = logic->get_list_of_agents();
	int sizeList = listofagents.size();
	out << sizeList;
	for(Agent<char> agent: listofagents){
		out << QString::fromStdString(agent.get_id());
		std::vector<Options<char>> preferences = agent.get_preferences();
		int sizePref = preferences.size();
		out << sizePref;
		for(Options<char> pref: preferences){
			out << pref.get_alternatives();
			out << pref.get_value();
		}
	}



	file.flush();
	file.close();
}

void MainWindow::on_actionLoad_triggered()
{

	delete logic;

	logic = new Program_Logic<char>();


	QString filename = QFileDialog::getOpenFileName(this,
	tr("Open Address Book"), "",
	tr("Address Book (*.csv);;All Files (*)"));

	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly))
	{
		std::cout << "Could not open " << QString(filename).toStdString() << std::flush;
		return;
	}

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_5_1);


	std::vector<Agent<char>> listofagents;
	int sizeList;
	in >> sizeList;

	for(int i = 0; i<sizeList; i++){

		QString id;
		in >> id;

		std::vector<Options<char>> preferences;
		int sizePref;
		in >> sizePref;
		for(int i=0; i<sizePref; i++){
			int alt;
			int val;
			in >> alt;
			in >> val;
			char al = alt;
			Options<char> opt(al, val);
			preferences.push_back(opt);
		}
		listofagents.push_back(Agent<char> ( preferences, QString(id).toStdString()));
	}

	std::vector<SocialPrefNode<char>> graph = logic->run_project(listofagents);
	logic->setListofagents(listofagents);
	file.close();


	scene -> clear( );

	logic -> show_graph( graph, scene );

	logic -> rank();
}
