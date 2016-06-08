/* 
 * File:   main.cpp
 * Author: nonwhite
 *
 * Created on 6 de diciembre de 2015, 10:32 AM
 */
#include <boost/program_options.hpp>

#include "parent_set_selection_main.h"
#include "structure_optimizer_main.h"

namespace po = boost::program_options ;

int main( int argc , char** argv ){
	po::options_description desc( getProgramDescription( argv[ 0 ] ) ) ;

	desc.add_options()
		( structureOptimizerTypeShortCut.c_str() , po::value<std::string>(&structureOptimizerType)->required()->default_value( structureOptimizerTypeDefault) , structureOptimizerTypeString.c_str() )
		( bnetFileShortCut.c_str() , po::value<std::string> (&bnetFile), bnetFileString.c_str() )
		( stepsToPerformShortCut.c_str() , po::value<int>(&stepsToPerform)->required()->default_value( stepsToPerformDefault ) , stepsToPerformString.c_str() )
		( datasetShortCut.c_str() , po::value<std::string> (&datasetFile), datasetFileString.c_str() )
		( scoresFileShortCut.c_str() , po::value<std::string> (&scoresFile)->required()->default_value( scoresFileDefault ) , scoresFileString.c_str() )
		( delimiterShortCut.c_str() , po::value<char> (&delimiter)->required()->default_value( delimiterDefault ), delimiterString.c_str() )
		( rMinShortCut.c_str() , po::value<int> (&rMin)->default_value( rMinDefault ), rMinString.c_str() )
		( maxParentsShortCut.c_str() , po::value<int> (&maxParents)->default_value( maxParentsDefault ) , maxParentsString.c_str() )
		( threadCountShortCut.c_str() , po::value<int> (&threadCount)->default_value( threadCountDefault ) , threadString.c_str() )
		( runningTimeShortCut.c_str() , po::value<int> (&runningTime)->default_value( runningTimeDefault ) , runningTimeString.c_str() )
		( hasHeaderShortCut.c_str() , hasHeaderString.c_str() )
		( pruneShortCut.c_str() , pruneString.c_str() )
		( deCamposPruningShortCut.c_str() , deCamposPruningString.c_str() )
		( selectionTypeShortCut.c_str() , po::value<std::string>(&selectionType)->default_value( selectionTypeDefault ) , parentselection::parentSetSelectionString.c_str() )
		( sfShortCut.c_str() , po::value<std::string>( &sf )->default_value( sfDefault ) , sfString.c_str() )
		( bestScoreCalculatorShortCut.c_str() , po::value<std::string > (&bestScoreCalculator)->default_value( bestScoreCalculatorDefault ) , bestscorecalculators::bestScoreCalculatorString.c_str() )
		( initializerShortCut.c_str() , po::value<std::string > (&initializerType)->default_value( initializerTypeDefault ) , initializers::initializerTypeString.c_str() )
		( numSolutionsShortCut.c_str() , po::value<int> (&numSolutions)->default_value( numSolutionsDefault ) , numSolutionsString.c_str() )
		( maxIterationsShortCut.c_str() , po::value<int> (&maxIterations)->default_value( maxIterationsDefault ) , maxIterationsString.c_str() )
		( "help,h" , "Show this help message." ) ;

	po::positional_options_description positionalOptions ;
//	positionalOptions.add( datasetShortCut.c_str() , 1 ) ;
	positionalOptions.add( bnetFileShortCut.c_str() , 1 ) ;

	po::variables_map vm ;
	po::store( po::command_line_parser( argc , argv )
				.options( desc )
				.positional( positionalOptions ).run() , vm ) ;

	if( vm.count( "help" ) || argc == 1 ){
		std::cout << desc ;
		return 0 ;
	}

	po::notify( vm ) ;

	hasHeader = vm.count( "hasHeader" ) ;
	prune = ( vm.count( "doNotPrune" ) == 0 ) ;
	enableDeCamposPruning = vm.count( "enableDeCamposPruning" ) ;

	if( threadCount < 1 ){
		threadCount = 1 ;
	}

	printf( " ============================== BN_LEARNING ============================== \n" ) ;
	datasetFile = ( stepsToPerform & PERFORM_SCORE_CALCULATION ? datasetFile : "NO SPECIFIED" ) ;
	printf( "Dataset file: '%s'\n" , datasetFile.c_str() ) ;
	printf( "Score file: '%s'\n" , scoresFile.c_str() ) ;
	printf( "Bnet file: '%s'\n" , bnetFile.c_str() ) ;

	if( stepsToPerform & PERFORM_SCORE_CALCULATION )
		calculateScore() ;
	if( stepsToPerform & PERFORM_STRUCTURE_LEARNING )
		structureLearning() ;
}