/* 
 * File:   utils_main.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 1:33
 */

#ifndef UTILS_MAIN_H
#define	UTILS_MAIN_H

#include <boost/algorithm/string.hpp>

inline std::string getTime(){
	time_t now = time( 0 ) ;
	tm *gmtm = gmtime( &now ) ;
	std::string dt( asctime( gmtm ) ) ;
	boost::trim( dt ) ;
	return dt ;
}

/* The file containing the data */
std::string datasetFile ;
std::string datasetFileString = "The data set file. First positional argument." ;
std::string datasetShortCut = "dataset" ;

/* The file to write the scores file */
std::string scoresFileDefault = "temp.pss" ;
std::string scoresFile = scoresFileDefault ;
std::string scoresFileString = "The score cache file. It will be deleted after calculation if default value" ;
std::string scoresFileShortCut = "scorefile" ;

/* The file containing the Bayesian network specification */
std::string bnetFile ;
std::string bnetFileString = "The Bayesian network file. Second positional argument." ;
std::string bnetFileShortCut = "bnetfile" ;

/* Bitset parameter for activate steps */
int stepsToPerformDefault = 3 ;
int stepsToPerform = stepsToPerformDefault ;
std::string stepsToPerformString = "Bitset representing the steps to perform for Bayesian network structure learning" ;
std::string stepsToPerformShortCut = "steps" ;

/* Constants for steps performing */
int PERFORM_SCORE_CALCULATION = 1<<0 ;
int PERFORM_STRUCTURE_LEARNING = 1<<1 ;

#endif	/* UTILS_MAIN_H */

