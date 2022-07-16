#include "/Trabalho/Projetos/Cpp/Social_Choice/Include/borda_count.hpp"

// Assuming that alternatives on each Profile in PrefMatrix are sorted lexicographically
Profile SCT::Borda_Count::operator( )( Preferencematrix& matrix ){

	winnerset = *matrix.begin( );

	for( auto i = 0; i < winnerset.size( ); ++i ){

		winnerset[ i ].set_value( 0 );
	}

	// Since alternatives are sorted, for any Profile, they are all in the same position.
	// Then: sum column-wise
	for( auto i = 0; i < winnerset.size( ); ++i ){

		for( auto j = 0; j < matrix.size( ); ++j ){

			winnerset[ i ] += matrix[ j ][ i ];
			winnerset[ i ] += 1;
		}
	}

	return winnerset;
}

Options SCT::Borda_Count::operator( )( Options& left, Options& right, Preferencematrix& matrix ){

	return left;
}

void SCT::Borda_Count::score( Preferencematrix& matrix ){


}