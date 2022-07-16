#ifndef BORDA_COUNT_HPP
#define BORDA_COUNT_HPP

#pragma once

#include "/Trabalho/Projetos/Cpp/Social_Choice/Include/procedure.hpp"

namespace SCT{


class Borda_Count : public Procedure{

	public:

		Borda_Count( ){ }
		~Borda_Count( ){ winnerset.clear( ); }

		virtual Profile operator( )( Preferencematrix& matrix ) override;

		virtual Options operator( )( Options& left, Options& right, Preferencematrix& matrix ) override;

		virtual void score( Preferencematrix& matrix ) override;

	private:
	
		Profile winnerset{ };
	};

}


#endif // BORDA_COUNT