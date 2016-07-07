/* 
 * File:   StructureOptimizer.cpp
 * Author: nonwhite
 * 
 * Created on 7 de julio de 2016, 15:18
 */

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "utils.h"
#include "structure_optimizer.h"

void structureoptimizer::StructureOptimizer::setParameters( std::string parametersFile ){
	setDefaultParameters() ;
	std::map<std::string,std::string> params = readParametersFile( parametersFile ) ;
	setFileParameters( params ) ;
}

std::map<std::string,std::string> structureoptimizer::StructureOptimizer::readParametersFile( std::string parametersFile ){
	std::map<std::string,std::string> params ;
	if( parametersFile.size() == 0 ){
		printf( "Not parameter file. Default values setted\n" ) ;
		return params ;
	}
	
	std::ifstream in( parametersFile.c_str() ) ;
	// make sure we found the file
	if( !in.is_open() ){
		printf( "Could not open the parameter file.\n" ) ;
		return params ;
	}

	std::string line ;
	std::string delimiter = "=" ;

	while( !in.eof() ){
		std::getline( in , line ) ;

		// skip empty lines and comments
		if( line.size() == 0 || line.compare( 0 , 1 , "#" ) == 0 ){
			continue ;
		}

		// make sure this is a meta line
		if( line.find( delimiter ) == std::string::npos ){
			throw std::runtime_error( "Error while parsing parameter information. Expected '=' symbol.  Line: '" + line + "'" ) ;
		}

		boost::trim( line ) ;
		std::vector<std::string> tokens ;
		boost::split( tokens , line , boost::is_any_of( delimiter.c_str() ) , boost::token_compress_on ) ;

		if( tokens.size() != 2 ){
			throw std::runtime_error( "Error while parsing parameter information. Too many tokens. Line: '" + line + "'" ) ;
		}

		boost::trim( tokens[ 0 ] ) ;
		boost::trim( tokens[ 1 ] ) ;
		params[ tokens[ 0 ] ] = tokens[ 1 ] ;
	}
	in.close() ;
	return params ;
}