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

#include "score_cache.h"
#include "greedy_search.h"
#include "initializer.h"
#include "initializer_creator.h"
#include "best_score_calculator.h"
#include "best_score_creator.h"
#include "node.h"
#include "utils.h"
#include "files.h"

namespace po = boost::program_options ;

/* The file containing the score cache */
std::string scoresFile ;
std::string scoresFileString = "The score cache file. First positional argument." ;

/* The file to write the scores */
//std::string bnetFile ;
//std::string bnetFileString = "The score file. Second positional argument." ;

/* The data structure to use to calculate best parent set scores */
std::string bestScoreCalculator ;

/* The type of initializer to use */
std::string initializerType ;

/* Number of solutions to be generated with initializer */
int numSolutions = 1 ;
std::string numSolutionsString = "Number of initial solutions to be generated." ;

/* Number of iterations for greedy search until stopping */
int maxIterations = 500 ;
std::string maxIterationsString = "Max number of iterations in greedy search." ;

/* The network information */
datastructures::BayesianNetwork network ;

inline std::string getTime(){
	time_t now = time( 0 ) ;
	tm *gmtm = gmtime( &now ) ;
	std::string dt( asctime( gmtm ) ) ;
	boost::trim( dt ) ;
	return dt ;
}

void greedySearch(){
	printf( "Scores file: '%s'\n" , scoresFile.c_str() ) ;
	//    printf("Net file: '%s'\n", netFile.c_str());
	printf( "Best score calculator: '%s'\n" , bestScoreCalculator.c_str() ) ;
	printf( "Initialization type: '%s'\n" , initializerType.c_str() ) ;

	printf( "Reading score cache.\n" ) ;
	scoring::ScoreCache cache ;
	cache.read( scoresFile ) ;

	printf( "Creating Best score calculators.\n" ) ;
	std::vector<bestscorecalculators::BestScoreCalculator*> bestScCalc = bestscorecalculators::create( bestScoreCalculator , cache ) ;

	printf( "Creating Initialization heuristic.\n" ) ;
	initializers::Initializer* initializer = initializers::create( initializerType , bestScCalc ) ;

	greedysearch::GreedySearch* algorithm = new greedysearch::GreedySearch( initializer , bestScCalc , maxIterations ) ;
	std::vector<greedysearch::Node*> solution = algorithm->search( numSolutions ) ;
}

int main( int argc , char** argv ){
	std::string description = std::string( "Compute the scores for a csv file.  Example usage: " ) + argv[ 0 ] + " iris.csv iris.pss" ;
	po::options_description desc( description ) ;

	desc.add_options()
		( "scoreFile" , po::value<std::string > (&scoresFile)->required(), scoresFileString.c_str() )
//		( "bnetFile" , po::value<std::string > (&bnetFile)->required(), bnetFile.c_str() )
		( "bestScore,b" , po::value<std::string > (&bestScoreCalculator)->default_value("list") , bestscorecalculators::bestScoreCalculatorString.c_str() )
		( "initializer,z" , po::value<std::string > (&initializerType)->default_value("random"), initializers::initializerTypeString.c_str() )
		( "numSolutions,n" , po::value<int> (&numSolutions)->default_value(1), numSolutionsString.c_str() )
		( "maxIterations,k" , po::value<int> (&maxIterations)->default_value(100), maxIterationsString.c_str() )
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