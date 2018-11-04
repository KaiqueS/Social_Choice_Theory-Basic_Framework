#ifndef Q_GRAPHIC_NODE_H
#define Q_GRAPHIC_NODE_H

#include <QGraphicsItem>
#include <Classes/socialprefnode.h>
#include <QVector2D>
#include <QtMath>
#include <typeinfo>

template<typename Prefs> class Q_Graphic_Node{

public:

	// Constructors & Destructor
	Q_Graphic_Node( );
	Q_Graphic_Node( int z, QPointF& position, int size, double allNodes, QGraphicsScene*& scene, SocialPrefNode<Prefs>& SocialPrefNode );
	Q_Graphic_Node( const Q_Graphic_Node& copy_qgnode );

	~Q_Graphic_Node( );

	// Setters
	void setRectangle( QGraphicsRectItem*& value );
	void setPosition( const QPointF& value );
	void setPos( QPointF position );
	void setMoveVector( QPointF move );

	// Getters
	QGraphicsItem* getRectangle( ){ return itemForm; }

	QPointF getPosition( ){ return position; }

	SocialPrefNode<Prefs> getSPNode( ){ return SPNode; }

	int get_Steps( ){ return steps; }
	int get_Rank( ){ return rank; }

	// Operators
	Q_Graphic_Node& operator=( const Q_Graphic_Node& copy_qgnode );

	// Helper Functions
	void insert_node( Q_Graphic_Node* node, QGraphicsScene* scene );
	void createGraphicItem( int& z, QPointF& position, int& size, QGraphicsScene*& scene, SocialPrefNode<Prefs>& SocialPrefNode );
	void moveNode( );
	void calcMovement( std::vector<Q_Graphic_Node*>& graph );
	void walkGraph( std::vector<Q_Graphic_Node*>& last_node );
	void update( );
	void set_Rank( int rank );

	bool has_loop( std::vector<Q_Graphic_Node*>& last_node,  Q_Graphic_Node*& node);

private:

	std::vector<QGraphicsLineItem*> edges{ };
	std::vector<QGraphicsPolygonItem*> arrow{ };
	std::vector<Q_Graphic_Node*> next_node{ };

	QGraphicsItem* itemForm{ };
	QGraphicsTextItem* label_name{ };
	QGraphicsTextItem* label_Rank{ };

	QPointF position{ };
	QPointF moveVector{ };

	SocialPrefNode<Prefs> SPNode{ };

	double strength{ };
	double quantNodes{ };
	int steps{ };
	int rank{ };
};

/* Constructors & Destructor */

template<typename Prefs> Q_Graphic_Node<Prefs>::Q_Graphic_Node( ){

	edges = { };
	arrow = { };
	next_node = { };

	itemForm = { };
	label_name = { };
	label_Rank = { };

	position = { };
	moveVector = { };

	SPNode = { };

	strength = { };
	quantNodes = { };
	steps = { };
	rank = { };
}
template<typename Prefs> Q_Graphic_Node<Prefs>::Q_Graphic_Node( int z, QPointF& position, int size, double allNodes, QGraphicsScene*& scene, SocialPrefNode<Prefs>& SocialPrefNode ){

	SPNode = SocialPrefNode;

	createGraphicItem( z, position, size, scene, SocialPrefNode );

	moveVector = QPointF( 0, 0 );

	this -> quantNodes = allNodes;

	strength = ( ( quantNodes - next_node.size( ) - 1 ) / quantNodes );

	steps = 0;

	rank = 0;
}
template<typename Prefs> Q_Graphic_Node<Prefs>::Q_Graphic_Node( const Q_Graphic_Node& copy_qgnode ){

	edges = copy_qgnode.edges;
	arrow = copy_qgnode.arrow;
	next_node = copy_qgnode.next_node;

	itemForm = copy_qgnode.itemForm;
	label_name = copy_qgnode.label_name;
	label_Rank = copy_qgnode.label_Rank;

	position = copy_qgnode.position;
	moveVector = copy_qgnode.moveVector;

	SPNode = copy_qgnode.SPNode;

	strength = copy_qgnode.strength;
	quantNodes = copy_qgnode.quantNodes;
	steps = copy_qgnode.steps;
	rank = copy_qgnode.rank;
}

template<typename Prefs> Q_Graphic_Node<Prefs>::~Q_Graphic_Node( ){ std::cout << ">>Rank = " << steps << "  >>Node " << SPNode.get_id( ) << " was destructed.\n\n"; }

/* Setters */

template<typename Prefs> void Q_Graphic_Node<Prefs>::setRectangle( QGraphicsRectItem*& value ){ itemForm = value; }
template<typename Prefs> void Q_Graphic_Node<Prefs>::setPosition( const QPointF& value ){ position = value; }
template<typename Prefs> void Q_Graphic_Node<Prefs>::setPos( QPointF position ){

	label_name -> setPos( position.rx( ), position.ry( ) );

	itemForm -> setPos( label_name -> pos( ) );


	label_Rank -> setPos( position + QPointF( 0, label_name -> boundingRect().height() ) );

	this -> position = QPointF( position.rx( ) + ( ( itemForm -> boundingRect( ).width( ) ) / 2 ),
								position.ry( ) + ( ( itemForm -> boundingRect( ).height( ) ) / 2 ) );

}
template<typename Prefs> void Q_Graphic_Node<Prefs>::setMoveVector( QPointF move ){ moveVector = move; }

/* Getters */


/* Operators */

template<typename Prefs> Q_Graphic_Node<Prefs>& Q_Graphic_Node<Prefs>::operator=( const Q_Graphic_Node& copy_qgnode ){

	edges = copy_qgnode.edges;
	arrow = copy_qgnode.arrow;
	next_node = copy_qgnode.next_node;

	itemForm = copy_qgnode.itemForm;
	label_name = copy_qgnode.label_name;
	label_Rank = copy_qgnode.label_Rank;

	position = copy_qgnode.position;
	moveVector = copy_qgnode.moveVector;

	SPNode = copy_qgnode.SPNode;

	strength = copy_qgnode.strength;
	quantNodes = copy_qgnode.quantNodes;
	steps = copy_qgnode.steps;
	rank = copy_qgnode.rank;

	return *this;
}

/* Helper Functions */

template<typename Prefs> void Q_Graphic_Node<Prefs>::insert_node( Q_Graphic_Node* node, QGraphicsScene* scene ){

	next_node.push_back( node );

	QVector2D vAuxMiddle = QVector2D( position.rx( ) + node -> getPosition( ).rx( ),
									  position.ry( ) + node -> getPosition( ).ry( ) );

	QVector2D vAuxaDiff = QVector2D( position.rx( ) - ( node -> getPosition( ).rx( ) ),
									 position.ry( ) - ( node -> getPosition( ).ry( ) ) );

	// Vector to middle of edge
	vAuxMiddle /= 2 ;

	// Vector to represents the edge direction
	vAuxaDiff.normalize( );
	vAuxaDiff *= 10;

	// Angle of arrow pointer
	double angle = 10;

	// Static casting vAuxaDiff x and y methods, removes implicit conversion
	qreal xvAuxDiff = static_cast<qreal>( vAuxaDiff.x( ) );
	qreal yvAuxDiff = static_cast<qreal>( vAuxaDiff.y( ) );

	QPointF v1( ( xvAuxDiff * cos( angle ) ) - ( yvAuxDiff * sin( angle ) ),
				( yvAuxDiff * cos( angle ) ) + ( xvAuxDiff * sin( angle ) ) );

	QPointF v2( ( xvAuxDiff * cos( -angle ) ) - ( yvAuxDiff * sin( -angle ) ),
				( yvAuxDiff * cos( -angle ) ) + ( xvAuxDiff * sin( -angle ) ) );

	QPolygonF Triangle{ };

	// Static casting vAuxMiddle x and y methods, removes implicit conversion
	qreal xvAuxMiddle = static_cast<qreal>( vAuxMiddle.x( ) );
	qreal yvAuxMiddle = static_cast<qreal>( vAuxMiddle.y( ) );

	Triangle.append( QPointF( xvAuxMiddle, yvAuxMiddle ) );
	Triangle.append( v1 + QPointF( xvAuxMiddle, yvAuxMiddle ) );
	Triangle.append( v2 + QPointF( xvAuxMiddle, yvAuxMiddle ) );

	// Add the triangle & line polygon to the scene
	QGraphicsPolygonItem* pTriangleItem = scene -> addPolygon( Triangle );

	QGraphicsLineItem* pLineItem = scene -> addLine( position.rx( ),
													 position.ry( ),
													 node -> getPosition( ).rx( ),
													 node -> getPosition( ).ry( ) );

	pLineItem -> setZValue( -1 );

	pTriangleItem -> setZValue( -1 );

	edges.push_back( pLineItem );

	arrow.push_back( pTriangleItem );

	strength = ( ( quantNodes - next_node.size( ) - 1 ) / quantNodes );

	QBrush innerBrush( QColor( 245 - ( 20 * strength ), 245 - ( 100 * strength ), 245 - ( 100 * strength ) ) );

	QPen outlinePen( Qt::black );

	outlinePen.setWidth( 2 );

	int zValue = itemForm -> zValue( );

	delete itemForm;

	itemForm = scene -> addRect( label_name -> boundingRect( ), outlinePen, innerBrush );

	itemForm -> setZValue( zValue );

	setPos( position );
}
template<typename Prefs> void Q_Graphic_Node<Prefs>::createGraphicItem( int& z, QPointF& position, int& size, QGraphicsScene*& scene, SocialPrefNode<Prefs>& SocialPrefNode ){

	QPen outlinePen( Qt::black );

	QBrush innerBrush( QColor( 255, 130, 130 ) );

	outlinePen.setWidth( 2 );

	label_name = scene -> addText( QString( SocialPrefNode.get_id( ) ), QFont( "Arial", size ) );

	label_name -> setZValue( z + 2 );
	label_name -> setFlag( QGraphicsItem::ItemIsMovable );

	itemForm = scene -> addRect( label_name -> boundingRect( ), outlinePen, innerBrush );

	itemForm -> setZValue( z + 1 );

	label_Rank = label_name -> scene() -> addText( QString::number( -1 ), QFont( "Arial", 10 ) );

	setPos( position );
}
template<typename Prefs> void Q_Graphic_Node<Prefs>::moveNode( ){

	setPos( label_name -> pos( ) + moveVector );

	for( std::vector<int>::size_type i = 0; i < next_node.size( ); ++i ){

		QVector2D vAuxMiddle = QVector2D( position.rx( ) + next_node[ i ] -> getPosition( ).rx( ),
										  position.ry( ) + next_node[ i ] -> getPosition( ).ry( ) );

		QVector2D vAuxaDiff = QVector2D( position.rx( ) - next_node[ i ] -> getPosition( ).rx( ),
										 position.ry( ) - next_node[ i ] -> getPosition( ).ry( ) );

		// MAGIC NUMBER
		vAuxMiddle /= 2;

		vAuxaDiff.normalize( );
		vAuxaDiff *= -10;

		// MAGIC NUMBER
		double angle = 10;

		// Static casting vAuxaDiff x and y methods, removes implicit conversion
		qreal xvAuxDiff = static_cast<qreal>( vAuxaDiff.x( ) );
		qreal yvAuxDiff = static_cast<qreal>( vAuxaDiff.y( ) );

		QPointF v1( ( xvAuxDiff * cos( angle ) ) - ( yvAuxDiff * sin( angle ) ),
					( yvAuxDiff * cos( angle ) ) + ( xvAuxDiff * sin( angle ) ) );

		QPointF v2( ( xvAuxDiff * cos( -angle ) ) - ( yvAuxDiff * sin( -angle ) ),
					( yvAuxDiff * cos( -angle ) ) + ( xvAuxDiff * sin( -angle ) ) );

		QPolygonF Triangle;

		// Static casting vAuxMiddle x and y methods, removes implicit conversion
		qreal xvAuxMiddle = static_cast<qreal>( vAuxMiddle.x( ) );
		qreal yvAuxMiddle = static_cast<qreal>( vAuxMiddle.y( ) );

		Triangle.append( QPointF( xvAuxMiddle, yvAuxMiddle ) );
		Triangle.append( v1 + QPointF( xvAuxMiddle, yvAuxMiddle ) );
		Triangle.append( v2 + QPointF( xvAuxMiddle, yvAuxMiddle ) );

		QGraphicsScene* scene = arrow[ i ] -> scene( );

		// Add the triangle & line polygon to the scene
		QGraphicsPolygonItem* pTriangleItem = scene -> addPolygon( Triangle );

		QGraphicsLineItem* pLineItem = scene -> addLine( position.rx( ),
														 position.ry( ),
														 next_node[ i ] -> getPosition( ).rx( ),
														 next_node[ i ] -> getPosition( ).ry( ) );

		delete arrow[ i ];

		arrow[ i ] = pTriangleItem;

		delete edges[ i ];

		edges[ i ] = pLineItem;
	}
}
template<typename Prefs> void Q_Graphic_Node<Prefs>::calcMovement( std::vector<Q_Graphic_Node*>& graph ){

	QPointF move1( 0, 0 );

	int sizeAux = graph.size( );

	qreal velMax = 3 / ( strength + 1 );
	qreal velMin = velMax / 10;

	double edgeMaxLength = 90 * sqrt( sizeAux );
	qreal edgeMinLength = 80;

	for( Q_Graphic_Node* node: graph ){

		if( node -> SPNode.get_id( ) != SPNode.get_id( ) ){

			QVector2D distance( ( node -> position ) - position );

			// Static casting QVector2D distance length into q real, removes implicit conversion on if statement belw
			qreal vecdistance = static_cast<qreal>( distance.length( ) );

			QVector2D moveAux( distance - ( distance.normalized( ) * edgeMaxLength ) );

			if( vecdistance > edgeMaxLength || vecdistance < edgeMinLength )

				move1 += moveAux.toPointF( );
		}
	}

	QVector2D vetor( move1 );

	// Static casting vetor length into qreal, removes implicit conversion on if statement below
	qreal vetorlen = static_cast<qreal>( vetor.length( ) );

	if( vetorlen > velMax )

		move1 = vetor.normalized( ).toPointF( ) * velMax;

	if( vetorlen < velMin )

		move1 = QPointF( 0, 0 );

	// Resistence
	moveVector *= 0.85;
	moveVector += move1;
}
template<typename Prefs> void Q_Graphic_Node<Prefs>::walkGraph( std::vector<Q_Graphic_Node<Prefs>*>& last_node ){

	for( Q_Graphic_Node<Prefs>* nextNode : next_node ){

		if( !has_loop( last_node, nextNode ) ){

			std::vector<Q_Graphic_Node<Prefs>*> lastAux = last_node;

			lastAux.push_back( this );

			nextNode -> walkGraph( lastAux );
		}
	}

	++steps;
}
template<typename Prefs> void Q_Graphic_Node<Prefs>::update( ){	moveNode( ); }
template<typename Prefs> void Q_Graphic_Node<Prefs>::set_Rank( int rank ){

	this -> rank = rank;

	delete label_Rank;

	QFont fonte( "Arial", 15 );

	fonte.setBold( true );

	label_Rank = label_name -> scene( ) -> addText( QString::number( rank ), fonte );

	label_Rank -> setDefaultTextColor( Qt::red );
	label_Rank -> setZValue( label_name -> zValue( ) );
	label_Rank -> setPos( label_Rank -> pos( ).rx( ), ( label_Rank -> boundingRect( ).height( ) + label_Rank -> pos( ).ry( ) ) );
}

template<typename Prefs> bool Q_Graphic_Node<Prefs>::has_loop( std::vector<Q_Graphic_Node<Prefs>*>& last_node, Q_Graphic_Node*& node ){

	for( Q_Graphic_Node<Prefs>* nodeAux : last_node )

		if( nodeAux == node )

			return true;

	return false;
}

#endif // Q_GRAPHIC_NODE_H
