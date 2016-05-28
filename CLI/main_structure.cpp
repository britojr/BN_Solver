/* 
 * File:   main.cpp
 * Author: nonwhite
 *
 * Created on 6 de diciembre de 2015, 10:32 AM
 */
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdexcept>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include "structure_optimizer_main.h"

namespace po = boost::program_options ;

int main( int argc , char** argv ){
	std::string description = std::string( "Compute the scores for a csv file.  Example usage: " ) + argv[ 0 ] + " iris.csv iris.pss" ;
	po::options_description desc( description ) ;

	desc.add_options()
		( "scoreFile" , po::value<std::string > (&scoresFile)->required(), scoresFileString.c_str() )
//		( "bnetFile" , po::value<std::string > (&bnetFile)->required(), bnetFile.c_str() )
		( "bestScore,b" , po::value<std::string > (&bestScoreCalculator)->default_value( bestScoreCalculatorDefault ) , bestscorecalculators::bestScoreCalculatorString.c_str() )
		( "initializer,z" , po::value<std::string > (&initializerType)->default_value( initializerTypeDefault ), initializers::initializerTypeString.c_str() )
		( "numSolutions,n" , po::value<int> (&numSolutions)->default_value( numSolutionsDefault ), numSolutionsString.c_str() )
		( "maxIterations,k" , po::value<int> (&maxIterations)->default_value( maxIterationsDefault ), maxIterationsString.c_str() )
		( "help,h" , "Show this help message." ) ;

	po::positional_options_description positionalOptions ;
	positionalOptions.add( "scoreFile" , 1 ) ;
//	positionalOptions.add( "bnetFile" , 1 ) ;

	po::variables_map vm ;
	po::store( po::command_line_parser( argc , argv )
				.options( desc )
				.positional( positionalOptions ).run() , vm ) ;

	if( vm.count( "help" ) || argc == 1 ){
		std::cout << desc ;
		return 0 ;
	}

	po::notify( vm ) ;

	printf( "URLearning, Structure optimizer\n" ) ;
	printf( "Score file: '%s'\n" , scoresFile.c_str() ) ;
//	printf( "Bnet file: '%s'\n" , outputFile.c_str() ) ;
	printf( "Initializer: '%s'\n" , initializerType.c_str() ) ;
	printf( "Number of init. solutions: %d\n" , numSolutions ) ;
	printf( "Max iterations: %d\n" , maxIterations ) ;

	greedySearch() ;
}