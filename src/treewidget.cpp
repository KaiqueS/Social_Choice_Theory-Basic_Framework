#include "treewidget.h"


TreeWidget::TreeWidget(QWidget* parent, int columns){

	tree = new QTreeWidget( parent );

	tree->setColumnCount(columns);

	tree->show();

}

TreeWidget::~TreeWidget()
{
	delete tree;
}

QTreeWidgetItem * TreeWidget::addTreeRoot(QString name, QString description){

	QTreeWidgetItem *treeItem = new QTreeWidgetItem( tree );
	treeItem->setText(0, description);
	treeItem->setText(1, name);
	return treeItem;
}

QTreeWidgetItem * TreeWidget::addTreeChild(QTreeWidgetItem *parent, QString name, QString description){

	QTreeWidgetItem *treeItem = new QTreeWidgetItem();

	treeItem->setText(0, description);
	treeItem->setText(1, name);

	parent->addChild(treeItem);
	return treeItem;
}

QTreeWidget* TreeWidget::getTree() const
{
	return tree;
}
