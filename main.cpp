/* 
 * File:   main.cpp
 * Author: nonwhite
 *
 * Created on 6 de diciembre de 2015, 10:32 AM
 */

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS

#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdexcept>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include "record_file.h"
#include "bayesian_network.h"
#include "variable.h"
#include "bic_scoring_function.h"
#include "ad_node.h"
#include "ad_tree.h"
#include "scoring_function.h"
#include "score_calculator.h"
#include "score_cache.h"
#include "greedy_search.h"
#include "initializer.h"
#include "initializer_creator.h"
#include "best_score_calculator.h"
#include "best_score_creator.h"
#include "node.h"
#include "utils.h"

namespace po = boost::program_options ;

/**
 * The file containing the data.
 */
std::string inputFile ;

/**
 * The delimiter in each line.
 */
char delimiter = ',' ;

/**
 * The file to write the scores.
 */
std::string outputFile ;

/**
 * File specifying constraints on the scores.
 */
std::string constraintsFile ;

/**
 * The minimum number of records in the AD-tree.
 */
int rMin = 5 ;

/**
 * The scoring function to use.
 */
std::string sf = "BIC" ;

/**
 * A reference to the scoring function object.
 */
scoring::ScoringFunction *scoringFunction ;

/*
 * Method to select parent sets
 */
std::string selectionType = "sequential" ;

/**
 * The data structure to use to calculate best parent set scores.
 * "tree", "list", "bitwise"
 */
std::string bestScoreCalculator ;

/**
 * The type of initializer to use.
 */
std::string initializerType ;

/**
 * Number of solutions to be generated with initializer.
 */
int numSolutions = 1000 ;

/**
 * The ess to use for BDeu.
 */
float equivalentSampleSize = 1.0f ;

/**
 * A hard limit on the size of parent sets.
 */
int maxParents = -1 ;

/**
 * The number of threads to use.
 */
int threadCount = 1 ;

/**
 * The maximum amount of time to use for each variable.
 */
int runningTime = -1 ;

/**
 * Whether the data file has variable names in the first row.
 */
bool hasHeader = false ;

/**
 * Whether to prune the scores before printing
 */
bool prune = true ;

/**
 * Whether to use deCampos-style pruning.
 */
bool enableDeCamposPruning = false ;

/**
 * The network information.
 */
datastructures::BayesianNetwork network ;

/**
 * The constraints information
 */
scoring::Constraints * constraints ;

inline std::string getTime(){
    time_t now = time( 0 ) ;
    tm *gmtm = gmtime( &now ) ;
    std::string dt( asctime( gmtm ) ) ;
    boost::trim( dt ) ;
    return dt ;
}

void scoringThread( int thread ){
    scoring::ScoreCalculator scoreCalculator( scoringFunction , maxParents , network.size() , runningTime , constraints , selectionType ) ;

    for( int variable = 0 ; variable < network.size() ; variable++ ){
        if( variable % threadCount != thread ){
            continue ;
        }
        
        std::string varFilename = outputFile + "." + TO_STRING(variable);
        if( file_exists( varFilename ) ) continue ;

        printf("Thread: %d, Variable: %d, Time: %s\n", thread, variable, getTime().c_str());

        FloatMap sc ;
        init_map(sc) ;
        scoreCalculator.calculateScores(variable, sc);
        
        int size = sc.size();
        printf("Thread: %d, Variable: %d, Size before pruning: %d, Time: %s\n", thread, variable, size, getTime().c_str());

        if (prune) {
            scoreCalculator.prune(sc);
            int prunedSize = sc.size();
            printf("Thread: %d, Variable: %d, Size after pruning: %d, Time: %s\n", thread, variable, prunedSize, getTime().c_str());
        }

        FILE *varOut = fopen(varFilename.c_str(), "w");

        datastructures::Variable *var = network.get(variable);
        fprintf(varOut, "VAR %s\n", var->getName().c_str());
        fprintf(varOut, "META arity=%d\n", var->getCardinality());

        fprintf(varOut, "META values=");
        for (int i = 0; i < var->getCardinality(); i++) {
            fprintf(varOut, "%s ", var->getValue(i).c_str());
        }
        fprintf(varOut, "\n");


        for (auto score = sc.begin(); score != sc.end(); score++) {
            varset parentSet = (*score).first;
            float s = (*score).second;

            fprintf(varOut, "%f ", s);

            for (int p = 0; p < network.size(); p++) {
                if (VARSET_GET(parentSet, p)) {
                    fprintf(varOut, "%s ", network.get(p)->getName().c_str());
                }
            }

            fprintf(varOut, "\n");
        }

        fprintf(varOut, "\n");
        fclose(varOut);

        sc.clear();
    }
}

void calculateScore(){
    printf("Parsing input file.\n");
    datastructures::RecordFile recordFile(inputFile, delimiter, hasHeader);
    recordFile.read();

    printf("Initializing data specifications.\n");
    network.initialize(recordFile);

    printf("Creating AD-tree.\n");
    scoring::ADTree *adTree = new scoring::ADTree(rMin);
    adTree->initialize(network, recordFile);
    adTree->createTree();

    boost::algorithm::to_lower(sf);

    if( maxParents > network.size() || maxParents < 1 ){
        maxParents = network.size() - 1 ;
    }

    if( sf.compare( "bic" ) == 0 ){
        int maxParentCount = log( 2 * recordFile.size() / log( recordFile.size() ) ) ;
        if( maxParentCount < maxParents ){
            maxParents = maxParentCount ;
        }
    }else if( sf.compare( "fnml" ) == 0 ){
    }else if( sf.compare( "bdeu" ) == 0 ){
    }else{
        throw std::runtime_error( "Invalid scoring function.  Options are: 'BIC', 'Fnml' or 'BDeu'." ) ;
    }

    constraints = NULL;
    if (constraintsFile.length() > 0) {
        constraints = scoring::parseConstraints(constraintsFile, network);
    }

    scoringFunction = NULL;

    std::vector<float> ilogi = scoring::LogLikelihoodCalculator::getLogCache(recordFile.size());
    scoring::LogLikelihoodCalculator *llc = new scoring::LogLikelihoodCalculator(adTree, network, ilogi);
    
    if (sf.compare("bic") == 0) {
        scoringFunction = new scoring::BICScoringFunction(network, recordFile, llc, constraints, enableDeCamposPruning);
    } else if (sf.compare("fnml") == 0) {
    } else if (sf.compare("bdeu") == 0) {
    }

    std::vector<boost::thread*> threads;
    for (int thread = 0; thread < threadCount; thread++) {
        boost::thread *workerThread = new boost::thread(scoringThread, thread);
        threads.push_back(workerThread);
    }

    for (auto it = threads.begin(); it != threads.end(); it++) {
        (*it)->join();
    }

    // concatenate all of the files together
    std::ofstream out(outputFile, std::ios_base::out | std::ios_base::binary);

    // first, the header information
    std::string header = "META pss_version = 0.1\nMETA input_file=" + inputFile + "\nMETA num_records=" + TO_STRING(recordFile.size()) + "\n";
    header += "META parent_limit=" + TO_STRING(maxParents) + "\nMETA score_type=" + sf + "\nMETA ess=" + TO_STRING(equivalentSampleSize) + "\n\n";
    out.write(header.c_str(), header.size());

    for (int variable = 0; variable < network.size(); variable++) {
        std::string varFilename = outputFile + "." + TO_STRING(variable);
        std::ofstream varFile(varFilename, std::ios_base::in | std::ios_base::binary);

        out << varFile.rdbuf();
        varFile.close();

        // and remove the variable file
        remove(varFilename.c_str());
    }

    out.close();
}

void greedySearch(){
    printf( "Dataset: '%s'\n" , outputFile.c_str() ) ;
//    printf("Net file: '%s'\n", netFile.c_str());
    printf( "Best score calculator: '%s'\n" , bestScoreCalculator.c_str() ) ;
    printf( "Initialization type: '%s'\n" , initializerType.c_str() ) ;

    printf( "Reading score cache.\n" ) ;
    scoring::ScoreCache cache ;
    cache.read( outputFile ) ;
    int variableCount = cache.getVariableCount() ;
    float gg = 0. ;
    VARSET_NEW( empty , variableCount ) ;
    VARSET_CLEAR_ALL( empty ) ;
    for(int i = 0 ; i < variableCount ; i++) gg += cache.getScore( i , empty ) ;
    printf("EMPTY NET = %.6f\n" , gg ) ;
    
    printf( "Creating Best score calculators.\n" ) ;
    std::vector<bestscorecalculators::BestScoreCalculator*> bestScCalc = bestscorecalculators::create( bestScoreCalculator , cache ) ;

    printf( "Creating Initialization heuristic.\n" ) ;
    initializers::Initializer* initializer = initializers::create( initializerType , bestScCalc ) ;
    
    greedysearch::GreedySearch* algorithm = new greedysearch::GreedySearch( initializer , bestScCalc ) ;
//    std::vector<greedysearch::Node*> solution = algorithm->search() ;
    std::vector<greedysearch::Node*> solution = algorithm->search( numSolutions ) ;
}

int main( int argc , char** argv ){
    boost::timer::auto_cpu_timer t;

    std::string description = std::string("Compute the scores for a csv file.  Example usage: ") + argv[0] + " iris.csv iris.pss" ;
    po::options_description desc(description) ;

    desc.add_options()
            ("input", po::value<std::string > (&inputFile)->required(), "The input file. First positional argument.")
            ("output", po::value<std::string > (&outputFile)->required(), "The output file. Second positional argument.")
            ("delimiter,d", po::value<char> (&delimiter)->required()->default_value(','), "The delimiter of the input file.")
            ("rMin,m", po::value<int> (&rMin)->default_value(5), "The minimum number of records in the AD-tree nodes.")
            ("maxParents,p", po::value<int> (&maxParents)->default_value(0), "The maximum number of parents for any variable. A value less than 1 means no limit.")
            ("threads,t", po::value<int> (&threadCount)->default_value(1), "The number of separate threads to use for score calculations.")
            ("time,r", po::value<int> (&runningTime)->default_value(-1), "The maximum amount of time to use for each variable. A value less than 1 means no limit.")
            ("hasHeader,s", "Add this flag if the first line of the input file gives the variable names.")
            ("doNotPrune,o", "Add this flag if the scores should NOT be pruned at the end of the search.")
            ("bestScore,b", po::value<std::string > (&bestScoreCalculator)->default_value( "list") , bestscorecalculators::bestScoreCalculatorString.c_str())
            ("initializer,z", po::value<std::string > (&initializerType)->default_value("random"), initializers::initializerTypeString.c_str())
            ("numSolutions,n", po::value<int> (&numSolutions)->default_value(1000), "Num of solutions to be generated.")
            ("parentSelectionType,q",po::value<std::string>(&selectionType)->default_value("sequential"),"Method to select parent sets ('Sequential', 'Greedy' or 'Independence')." )
            ("help,h", "Show this help message.")
            ;

    po::positional_options_description positionalOptions;
    positionalOptions.add("input", 1);
    positionalOptions.add("output", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc)
            .positional(positionalOptions).run(),
            vm);

    if (vm.count("help") || argc == 1) {
        std::cout << desc;
        return 0;
    }

    po::notify(vm);

    hasHeader = vm.count("hasHeader");
    prune = (vm.count("doNotPrune") == 0);
    enableDeCamposPruning = true; // TODO: Test without this setted in false
//    enableDeCamposPruning = vm.count("enableDeCamposPruning");

    if (threadCount < 1) {
        threadCount = 1;
    }

    printf("URLearning, Score Calculator\n");
    printf("Input file: '%s'\n", inputFile.c_str());
    printf("Output file: '%s'\n", outputFile.c_str());
    printf("Delimiter: '%c'\n", delimiter);
    printf("r_min: '%d'\n", rMin);
    printf("Scoring function: '%s'\n", sf.c_str());
    printf("ESS: '%f'\n", equivalentSampleSize);
    printf("Maximum parents: '%d'\n", maxParents);
    printf("Threads: '%d'\n", threadCount);
    printf("Running time (per variable): '%d'\n", runningTime);
    printf("Has header: '%s'\n", (hasHeader ? "true" : "false"));
    printf("Enable end-of-scoring pruning: '%s'\n", (prune ? "true" : "False"));

    srand( time( NULL ) ) ;
    if( !file_exists( outputFile ) )
        calculateScore() ;
 
    greedySearch() ;
}