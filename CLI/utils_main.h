/* 
 * File:   utils_main.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 1:33
 */

#ifndef UTILS_MAIN_H
#define	UTILS_MAIN_H

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

/* The file to write the scores file (temporal) */
std::string scoresFile = "temp.pss" ;
std::string scoresFileString = "The score cache file." ;


#endif	/* UTILS_MAIN_H */

