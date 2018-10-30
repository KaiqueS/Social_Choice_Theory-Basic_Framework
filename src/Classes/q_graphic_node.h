#ifndef Q_GRAPHIC_NODE_H
#define Q_GRAPHIC_NODE_H

#include <QGraphicsItem>
#include <Classes/socialprefnode.h>
#include <QVector2D>
#include <QtMath>

template<typename Prefs> class Q_Graphic_Node{

public:

	// Constructors & Destructor
	Q_Graphic_Node( );
	Q_Graphic_Node( int z, QPointF position, int size, double allNodes, QGraphicsScene* scene, SocialPrefNode<Prefs> SocialPrefNode );
	Q_Graphic_Node( const Q_Graphic_Node& copy_qgnode );

	~Q_Graphic_Node( );

	// Setters

	void setRectangle( QGraphicsRectItem* value );

	void setPosition( const QPointF& value );

	void setPos( QPointF position );

	void setMoveVector( QPointF move );

	// Getters
	QGraphicsItem* getRectangle( ){ return itemForm; }

	QPointF getPosition( ){ return position; }

	SocialPrefNode<Prefs> getSPNode( ){ return SPNode; }

	// Operators
	Q_Graphic_Node& operator=( const Q_Graphic_Node& copy_qgnode );

	// Helper Functions
	void insert_node( Q_Graphic_Node* node, QGraphicsScene* scene );

	void createGraphicItem( int z, QPointF position, int size, QGraphicsScene* scene, SocialPrefNode<Prefs> SocialPrefNode );

	void moveNode( );

	void calcMovement( );

	void update( );

private:

	std::vector<QGraphicsLineItem*> edges{ };
	std::vector<QGraphicsPolygonItem*> arrow{ };
	std::vector<Q_Graphic_Node*> next_node{ };

	QGraphicsItem* itemForm{ };
	QGraphicsTextItem* label_name{ };

	QPointF position{ };
	QPointF moveVector{ };

	SocialPrefNode<Prefs> SPNode{ };

	double strength{ };
	double quantNodes{ };
};

/* Constructors & Destructor */

template<typename Prefs> Q_Graphic_Node<Prefs>::Q_Graphic_Node( ){

	edges = { };
	arrow = { };
	next_node = { };

	itemForm = { };
	label_name = { };

	position = { };
	moveVector = { };

	SPNode = { };

	strength = { };
	quantNodes = { };
}
template<typename Prefs> Q_Graphic_Node<Prefs>::Q_Graphic_Node( int z, QPointF position, int size, double allNodes, QGraphicsScene* scene, SocialPrefNode<Prefs> SocialPrefNode ){

	SPNode = SocialPrefNode;

	createGraphicItem( z, position, size, scene, SocialPrefNode );

	moveVector = QPointF( 0, 0 );

	this -> quantNodes = allNodes;

	strength = 0;
}
template<typename Prefs> Q_Graphic_Node<Prefs>::Q_Graphic_Node( const Q_Graphic_Node& copy_qgnode ){

	edges = copy_qgnode.edges;
	arrow = copy_qgnode.arrow;
	next_node = copy_qgnode.next_node;

	itemForm = copy_qgnode.itemForm;
	label_name = copy_qgnode.label_name;

	position = copy_qgnode.position;
	moveVector = copy_qgnode.moveVector;

	SPNode = copy_qgnode.SPNode;

	strength = copy_qgnode.strength;
	quantNodes = copy_qgnode.quantNodes;
}

template<typename Prefs> Q_Graphic_Node<Prefs>::~Q_Graphic_Node( ){ std::cout << "Node " << SPNode.get_id( ) << " was destructed.\n\n"; }

/* Setters */

template<typename Prefs> void Q_Graphic_Node<Prefs>::setRectangle( QGraphicsRectItem* value ){ itemForm = value; }

template<typename Prefs> void Q_Graphic_Node<Prefs>::setPosition( const QPointF& value ){ position = value; }

template<typename Prefs> void Q_Graphic_Node<Prefs>::setPos( QPointF position ){

	label_name -> setPos( position.rx( ), position.ry( ) );

	itemForm -> setPos( label_name -> pos( ) );

	this -> position = QPointF( position.rx( ) + ( ( itemForm -> boundingRect( ).width( ) ) / 2 ),
								position.ry( ) + ( ( itemForm -> boundingRect( ).height( ) ) / 2 ) );
}

template<typename Prefs> void Q_Graphic_Node<Prefs>::setMoveVector( QPointF move ){ moveVector = move; }

/* Getters */

// TODO: Resolve issues
template<typename Prefs> void Q_Graphic_Node<Prefs>::insert_node( Q_Graphic_Node* node, QGraphicsScene* scene ){

	next_node.push_back( node );

	QVector2D vAuxMiddle = QVector2D( position.rx( ) + node -> getPosition( ).rx( ),
									  position.ry( ) + node -> getPosition( ).ry( ) );

	QVector2D vAuxaDiff = QVector2D( position.rx( ) - ( node -> getPosition( ).rx( ) ),
									 position.ry( ) - ( node -> getPosition( ).ry( ) ) );

	// MAGIC NUMBER
	vAuxMiddle /= 2 ;

	vAuxaDiff.normalize( );
	vAuxaDiff *= 10;

	// MAGIC NUMBER
	double angle = 10;

	QPointF v1( vAuxaDiff.x( )*cos( angle ) - ( vAuxaDiff.y( )*sin( angle ) ),
				vAuxaDiff.y( )*cos( angle ) + ( vAuxaDiff.x( )*sin( angle ) ) );

	QPointF v2( vAuxaDiff.x( )*cos( -angle ) - ( vAuxaDiff.y( )*sin( -angle ) ),
				vAuxaDiff.y( )*cos( -angle ) + ( vAuxaDiff.x( )*sin( -angle ) ) );

	QPolygonF Triangle;

	Triangle.append( QPointF( vAuxMiddle.x( ), vAuxMiddle.y( ) ) );
	Triangle.append( v1+ QPointF( vAuxMiddle.x( ), vAuxMiddle.y( ) ) );
	Triangle.append( v2+ QPointF( vAuxMiddle.x( ), vAuxMiddle.y( ) ) );

	// Add the triangle & line polygon to the scene
	QGraphicsPolygonItem* pTriangleItem = scene -> addPolygon( Triangle );

	QGraphicsLineItem* pLineItem = scene -> addLine( position.rx( ),
													 position.ry( ),
													 node -> getPosition( ).rx( ),
													 node -> getPosition( ).ry( ) );

	pLineItem -> setZValue( -10 );

	pTriangleItem -> setZValue( -10 );

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

	std::cout<< "Strength = "<< strength << "\n";

}

template<typename Prefs> void Q_Graphic_Node<Prefs>::createGraphicItem( int z, QPointF position, int size, QGraphicsScene* scene, SocialPrefNode<Prefs> SocialPrefNode ){

	QPen outlinePen( Qt::black );

	QBrush innerBrush( QColor( 255, 130, 130 ) );

	outlinePen.setWidth( 2 );

	label_name = scene -> addText( QString( SocialPrefNode.get_id( ) ), QFont( "Arial", size ) );

	label_name -> setZValue( z + 2 );
	label_name -> setFlag( QGraphicsItem::ItemIsMovable );

	itemForm = scene -> addRect( label_name -> boundingRect( ), outlinePen, innerBrush );

	itemForm -> setZValue( z + 1 );

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

		// MAGIC NUMBER
		vAuxaDiff *= -10;

		// MAGIC NUMBER
		double angle = 10;

		QPointF v1( ( vAuxaDiff.x( ) * cos( angle ) ) - ( vAuxaDiff.y( ) * sin( angle ) ),
					( vAuxaDiff.y( ) * cos( angle ) ) + ( vAuxaDiff.x( ) * sin( angle ) ) );

		QPointF v2( ( vAuxaDiff.x( ) * cos( -angle ) ) - ( vAuxaDiff.y( ) * sin( -angle ) ),
					( vAuxaDiff.y( ) * cos( -angle ) ) + ( vAuxaDiff.x( ) * sin( -angle ) ) );

		QPolygonF Triangle;

		Triangle.append( QPointF( vAuxMiddle.x( ), vAuxMiddle.y( ) ) );
		Triangle.append( v1 + QPointF( vAuxMiddle.x( ), vAuxMiddle.y( ) ) );
		Triangle.append( v2 + QPointF( vAuxMiddle.x( ), vAuxMiddle.y( ) ) );

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

template<typename Prefs> void Q_Graphic_Node<Prefs>::calcMovement( ){

	QPointF move1( 0, 0 );
	QPointF move2( 0, 0 );

	int sizeAux = next_node.size( );

	for( Q_Graphic_Node* node: next_node ){

		QVector2D distance( ( node -> position ) - position );

		QPointF pointAux( 0, 0 );

		if( distance.length( ) > ( 200 * sizeAux ) )

			pointAux += distance.normalized( ).toPointF( ) * ( ( distance.length( ) * sizeAux ) / ( 500 * sizeAux ) );

		if( QVector2D( pointAux ).length( ) > 8 )

			pointAux = ( QVector2D( pointAux ).normalized( ) * 8 ).toPointF( );

		move2 += pointAux;
	}

	for( Q_Graphic_Node* node: next_node ){

		QVector2D distance( ( node -> position ) - position );

		QPointF pointAux( 0, 0 );

		if( distance.length( ) < 100 )

			pointAux -= distance.normalized( ).toPointF( ) / ( 600 * distance.length( ) * distance.length( ) );

		if( QVector2D( pointAux ).length( ) > 8 )

			pointAux = ( QVector2D( pointAux ).normalized( ) * 8 ).toPointF( );

		move2 += pointAux;
	}

	QVector2D vetor( move1 + move2 );

	// MAGIC NUMBER
	if( vetor.length( ) > 4 )

		moveVector = ( vetor.normalized( ) * 2 ).toPointF( );

	// MAGIC NUMBER
	else if( vetor.length( ) > 0.3 )

		moveVector = vetor.toPointF( );

	else

		moveVector = QPointF( 0, 0 );
}

template<typename Prefs> void Q_Graphic_Node<Prefs>::update( ){ moveNode( ); }

/* Operators */

template<typename Prefs> Q_Graphic_Node<Prefs>& Q_Graphic_Node<Prefs>::operator=( const Q_Graphic_Node& copy_qgnode ){

	edges = copy_qgnode.edges;
	arrow = copy_qgnode.arrow;
	next_node = copy_qgnode.next_node;

	itemForm = copy_qgnode.itemForm;
	label_name = copy_qgnode.label_name;

	position = copy_qgnode.position;
	moveVector = copy_qgnode.moveVector;

	SPNode = copy_qgnode.SPNode;

	strength = copy_qgnode.strength;
	quantNodes = copy_qgnode.quantNodes;

	return *this;
}

/* Helper Functions */

#endif // Q_GRAPHIC_NODE_H
