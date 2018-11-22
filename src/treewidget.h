#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <iostream>
#include <QTreeWidget>

class TreeWidget
{
public:

	TreeWidget(QWidget* parent, int columns);

	~TreeWidget();

	QTreeWidgetItem * addTreeRoot(QString name, QString description);

	QTreeWidgetItem * addTreeChild(QTreeWidgetItem *parent, QString name, QString description);

	QTreeWidget* getTree() const;

private:

	QTreeWidget *tree;
};

#endif // TREEWIDGET_H
