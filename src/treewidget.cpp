#include "treewidget.h"

TreeWidget::TreeWidget( QWidget* parent, QStringList columnNames ){

	tree = new QTreeWidget( parent );

	tree->setHeaderLabels(columnNames);

    tree -> show( );

}

TreeWidget::TreeWidget(QWidget* parent, int column)
{
	tree = new QTreeWidget( parent );

	tree->setColumnCount(column);

	tree -> show( );
}

TreeWidget::~TreeWidget( ){

    delete tree;
}

QTreeWidgetItem* TreeWidget::addTreeRoot( QString name, QString description ){

    QTreeWidgetItem* treeItem = new QTreeWidgetItem( tree );

	treeItem -> setText( 0, name );
	treeItem -> setText( 1, description );

    return treeItem;
}

QTreeWidgetItem* TreeWidget::addTreeChild( QTreeWidgetItem* parent, QString name, QString description ){

    QTreeWidgetItem* treeItem = new QTreeWidgetItem( );

	treeItem -> setText( 0, name );
	treeItem -> setText( 1, description );

    parent -> addChild( treeItem );

	return treeItem;
}

QTreeWidget* TreeWidget::getTree( ) const{

    return tree;
}
