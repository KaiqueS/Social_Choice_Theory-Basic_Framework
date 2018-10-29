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
		moveVector = QPointF(0,0);
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
		pLineItem->setZValue(-10);
		pTriangleItem->setZValue(-10);
		edges.push_back( pLineItem );
		arrow.push_back( pTriangleItem );


	}

	void createGraphicItem(int z, QPointF position, int size, QGraphicsScene *scene, SocialPrefNode<Prefs> SocialPrefNode){

		QPen outlinePen(Qt::black);

		QBrush innerBrush(Qt::lightGray);

		outlinePen.setWidth(2);

		label_name = scene->addText(QString(SocialPrefNode.get_id()), QFont("Arial", size) );
		label_name->setZValue(z+2);
		label_name-> setFlag( QGraphicsItem::ItemIsMovable );
		itemForm = scene->addRect(label_name->boundingRect(), outlinePen, innerBrush);
		itemForm->setZValue(z+1);
		setPos(position);
	}

	void moveNode(){
		setPos(label_name->pos()+moveVector);
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

	void calcMovement(){
		QPointF move1(0,0);
		QPointF move2(0,0);
		int sizeAux = next_node.size();
		for(Q_Graphic_Node* node: next_node){
			QVector2D distance(node->position-position);
			QPointF pointAux(0,0);
			if(distance.length() > 200*sizeAux)
				pointAux+=distance.normalized().toPointF()*(distance.length()*sizeAux)/500*sizeAux;
			if(QVector2D(pointAux).length()>8)
				pointAux = (QVector2D(pointAux).normalized()*8).toPointF();
			move2+=pointAux;
		}
		for(Q_Graphic_Node* node: next_node){
			QVector2D distance(node->position-position);
			QPointF pointAux(0,0);
			if(distance.length() < 100)
				pointAux-=distance.normalized().toPointF()/600*distance.length()*distance.length();
			if(QVector2D(pointAux).length()>8)
				pointAux = (QVector2D(pointAux).normalized()*8).toPointF();
			move2+=pointAux;

		}
		QVector2D vetor(move1+move2);
		if(vetor.length()>4)
			moveVector = (vetor.normalized()*2).toPointF();
		else if(vetor.length()>0.3)
			moveVector = vetor.toPointF();
		else
			moveVector = QPointF(0,0);
	}

	void update(){
		moveNode();
	}

	SocialPrefNode<Prefs> getSPNode(){
		return SPNode;
	}

	void setMoveVector(QPointF move){
		moveVector = move;
	}

private:

	QGraphicsItem *itemForm;
	std::vector<QGraphicsLineItem *> edges;
	std::vector<QGraphicsPolygonItem*> arrow;
	QPointF position;
	QPointF moveVector;
	SocialPrefNode<Prefs> SPNode;
	QGraphicsTextItem* label_name;
	std::vector<Q_Graphic_Node*> next_node;
};



#endif // Q_GRAPHIC_NODE_H
