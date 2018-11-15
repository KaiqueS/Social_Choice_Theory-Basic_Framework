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
	tr("Address Book (*.sctb);;All Files (*)"));
	QFile file(filename);

	if(!file.open(QIODevice::WriteOnly))
	{
		std::cout << "Could not open " << filename.toStdString() << std::flush;
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
	tr("Address Book (*.sctb);;All Files (*)"));

	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly))
	{
		std::cout << "Could not open " << filename.toStdString() << std::flush;
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
			Options<char> opt((char)alt, val);
			preferences.push_back(opt);
		}
		listofagents.push_back(Agent<char> ( preferences, id.toStdString()));
	}

	std::vector<SocialPrefNode<char>> graph = logic->run_project(listofagents);
	logic->setListofagents(listofagents);
	file.close();


	scene -> clear( );

	logic -> show_graph( graph, scene );

	logic -> rank();
}

void MainWindow::on_actionimport_triggered(){

	delete logic;

	logic = new Program_Logic<char>();

	QString filename = QFileDialog::getOpenFileName(this,
	tr("Open Address Book"), "",
	tr("Address Book (*.csv);;All Files (*)"));

	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly))
	{
		std::cout << "Could not open " << filename.toStdString() << std::flush;
		return;
	}

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_5_1);


	std::vector<Agent<char>> listofagents;
	QString entrada;
	int bufferSize = 100;
	char buffer[bufferSize];
	while(!in.atEnd()){
		int size;
		size = in.readRawData(buffer,bufferSize);
		std::cout << buffer << "  <= " << size << "\n" << std::flush;
		if(size<bufferSize)
			for(int i=size;i<bufferSize;i++)
				buffer[i] = 0;
		entrada += QString(buffer);
	}
	std::cout <<  ">>  \n" << entrada.toStdString() << "\n" << std::flush;

	QStringList listStringNode = entrada.split(QString("\n"));
	QStringList listStringHeader = listStringNode.at(0).split(QString(";"));

	std::vector<Options<char>> preferences;
	for(int i = 1; i<listStringNode.size()-1 ; i++){

		QString stringNode = listStringNode.at(i);
		QStringList listStringOpts = stringNode.split(QString(";"));
		QString id = listStringOpts.at(0);

		std::cout << "\t____idAgent = " << id.toStdString() << "\n" << std::flush;
		std::vector<Options<char>> preferences;
		for(int j = 1; j<listStringOpts.size() ; j++){
			char id = '_';
			if(j<listStringHeader.size())
			 id = listStringHeader.at(j).toStdString()[0];
			int val = listStringOpts.at(j).toInt();
			std::cout << "\t\t____opt = " << id << "  -- val = " << val << "\n" << std::flush;


			Options<char> opt(id, val);
			preferences.push_back(opt);
		}

		listofagents.push_back(Agent<char> ( preferences, id.toStdString()));
	}

	std::vector<SocialPrefNode<char>> graph = logic->run_project(listofagents);
	logic->setListofagents(listofagents);

	file.close();

	scene -> clear( );

	logic -> show_graph( graph, scene );

	logic -> rank();

}

void MainWindow::on_actionExport_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this,
	tr("Save Address Book"), "",
	tr("Address Book (*.csv);;All Files (*)"));
	QFile file(filename);

	if(!file.open(QIODevice::WriteOnly))
	{
		std::cout << "Could not open " << filename.toStdString() << std::flush;
		return;
	}
	file.close();
	std::ofstream myfile;
	myfile.open (filename.toStdString());

	std::vector<Agent<char>> listofagents;
	std::string saida("");
	std::vector<Agent<char>> listAgent = logic->get_list_of_agents();
	saida += "id";
	std::vector<Options<char>> preferencesaux;
	for(Options<char> opt : listAgent.at(0).get_preferences()){
		saida += ";";
		saida += opt.get_alternatives();
	}
	for(Agent<char> agent : listAgent){
		saida += "\n";
		std::string str = agent.get_id();
		saida += str;
		for(Options<char> opt : agent.get_preferences()){
			saida += ";";
			saida += QString::number(opt.get_value()).toStdString();
		}
	}

	myfile << saida <<"\n";


	std::cout << "saida :\n" << saida << std::flush;
	myfile.close();

}
