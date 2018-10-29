#ifndef Q_GRAPHIC_NODE_H
#define Q_GRAPHIC_NODE_H

#include <QGraphicsItem>
#include <Classes/socialprefnode.h>
#include <QVector2D>
#include <QtMath>


template<typename Prefs> class Q_Graphic_Node
{
public:

	~Q_Graphic_Node(){
		std::cout << "Node " << SPNode.get_id() << "was destructed.\n\n";
	}

	Q_Graphic_Node(int z, QPointF position, int size, QGraphicsScene *scene, SocialPrefNode<Prefs> SocialPrefNode){
		SPNode = SocialPrefNode;
		createGraphicItem(z, position, size, scene, SocialPrefNode);
	}

	QPointF getPosition(){
		return position;
	}

	void setPosition(const QPointF &value){
		position = value;
	}

	void setRectangle(QGraphicsRectItem *value){
		itemForm = value;
	}

	QGraphicsItem *getRectangle(){
		return itemForm;
	}

	void insert_node(Q_Graphic_Node* node, QGraphicsScene *scene){

		next_node.push_back(node);

		QVector2D vAuxMiddle = QVector2D(position.rx()+node->getPosition().rx(), position.ry()+node->getPosition().ry());
		QVector2D vAuxaDiff = QVector2D(position.rx()-node->getPosition().rx(), position.ry()-node->getPosition().ry());
		vAuxMiddle/=2;
		vAuxaDiff.normalize();
		vAuxaDiff*=10;
		double angle = 10;
		QPointF v1(vAuxaDiff.x()*cos(angle)-vAuxaDiff.y()*sin(angle),vAuxaDiff.y()*cos(angle)+vAuxaDiff.x()*sin(angle));
		QPointF v2(vAuxaDiff.x()*cos(-angle)-vAuxaDiff.y()*sin(-angle),vAuxaDiff.y()*cos(-angle)+vAuxaDiff.x()*sin(-angle));

		QPolygonF Triangle;
		Triangle.append(QPointF(vAuxMiddle.x(),vAuxMiddle.y()));
		Triangle.append(v1+QPointF(vAuxMiddle.x(),vAuxMiddle.y()));
		Triangle.append(v2+QPointF(vAuxMiddle.x(),vAuxMiddle.y()));

		// Add the triangle & line polygon to the scene

		QGraphicsPolygonItem* pTriangleItem = scene->addPolygon(Triangle);
		QGraphicsLineItem * pLineItem = scene->addLine(position.rx(), position.ry(), node->getPosition().rx(), node->getPosition().ry());
		pLineItem->setZValue(-3);
		pTriangleItem->setZValue(-3);
		edges.push_back( pLineItem );
		arrow.push_back( pTriangleItem );


	}

	void createGraphicItem(int z, QPointF position, int size, QGraphicsScene *scene, SocialPrefNode<Prefs> SocialPrefNode){

		QPen outlinePen(Qt::black);

		QBrush innerBrush(Qt::lightGray);

		outlinePen.setWidth(2);

		label_name = scene->addText(QString(SocialPrefNode.get_id()), QFont("Arial", size) );
		label_name->setZValue(z+2);
		label_name->setFlag(QGraphicsItem::ItemIsMovable);
		itemForm = scene->addRect(label_name->boundingRect(), outlinePen, innerBrush);
		itemForm->setZValue(z+1);
		setPos(position);
	}

	void moveNode(QPointF movement){
		setPos(label_name->pos()+movement);
		for(std::vector<int>::size_type i = 0; i < next_node.size( ); ++i ){
			QVector2D vAuxMiddle = QVector2D(position.rx()+next_node[i]->getPosition().rx(), position.ry()+next_node[i]->getPosition().ry());
			QVector2D vAuxaDiff = QVector2D(position.rx()-next_node[i]->getPosition().rx(), position.ry()-next_node[i]->getPosition().ry());
			vAuxMiddle/=2;
			vAuxaDiff.normalize();
			vAuxaDiff*=-10;
			double angle = 10;
			QPointF v1(vAuxaDiff.x()*cos(angle)-vAuxaDiff.y()*sin(angle),vAuxaDiff.y()*cos(angle)+vAuxaDiff.x()*sin(angle));
			QPointF v2(vAuxaDiff.x()*cos(-angle)-vAuxaDiff.y()*sin(-angle),vAuxaDiff.y()*cos(-angle)+vAuxaDiff.x()*sin(-angle));

			QPolygonF Triangle;
			Triangle.append(QPointF(vAuxMiddle.x(),vAuxMiddle.y()));
			Triangle.append(v1+QPointF(vAuxMiddle.x(),vAuxMiddle.y()));
			Triangle.append(v2+QPointF(vAuxMiddle.x(),vAuxMiddle.y()));
			QGraphicsScene * scene = arrow[i]->scene();
			// Add the triangle & line polygon to the scene
			QGraphicsPolygonItem* pTriangleItem = scene->addPolygon(Triangle);
			QGraphicsLineItem * pLineItem = scene->addLine(position.rx(), position.ry(), next_node[i]->getPosition().rx(), next_node[i]->getPosition().ry());
			delete arrow[i];
			arrow[i] = pTriangleItem;
			delete edges[i];
			edges[i] = pLineItem;
		}
	}

	void setPos(QPointF position){
		label_name->setPos(position.rx(),position.ry());
		itemForm->setPos(label_name->pos());
		this->position = QPointF(position.rx()+(itemForm->boundingRect().width())/2,position.ry()+(itemForm->boundingRect().height())/2);
	}

	QPointF calcMovement(){
		QPointF move1(0,0);
		QPointF move2(0,0);
		int sizeAux = next_node.size();
		for(Q_Graphic_Node* node: next_node){
			if(std::rand()%100>10){
				QVector2D distance(node->position-position);
				if(distance.length() > sizeAux*sizeAux*40)
					move1+=distance.normalized().toPointF()*(distance.length()*sizeAux)/5000*sizeAux;
				}
		}
		for(Q_Graphic_Node* node: next_node){
			if(std::rand()%100>10){

				QVector2D distance(node->position-position);
				if(distance.length() < sizeAux*30)
					move2-=distance.normalized().toPointF()/500*distance.length();
			}
		}
		if(QVector2D(move1+move2).length()>0.5)
			return (move1+move2);
		else
			return QPointF(0,0);
	}

	void update(){
		moveNode(calcMovement());
	}

	SocialPrefNode<Prefs> getSPNode(){
		return SPNode;
	}

private:

	QGraphicsItem *itemForm;
	std::vector<QGraphicsLineItem *> edges;
	std::vector<QGraphicsPolygonItem*> arrow;
	QPointF position;
	SocialPrefNode<Prefs> SPNode;
	QGraphicsTextItem* label_name;
	std::vector<Q_Graphic_Node*> next_node;
};



#endif // Q_GRAPHIC_NODE_H
