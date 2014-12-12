/* 
 * File:   hadlock.h
 *
 * Created on December 6, 2014, 8:08 AM
 */

#include<iostream>
#include<string>
#include "problem_object.h"
#include "path.h"



using namespace Utilities;
        

namespace Utilities{
    class Hadlock {
        private:
    	int width,height;			/*Width and height of problem object*/
    	std::vector<Point> source, dest;	/*Vector to store source and sink values*/
        std::vector<Path*> finalpath;		/*Final paths of all nets to be routed*/
        std::vector<Blocker> blocks;		/*List of all the blockages in problem object*/
        
        public:
	//Constructor-Desctructor
        Hadlock(ProblemObject* first_problem);  
    	~Hadlock(){
        };

	//Hadlocks Algorithm
       	std::vector<Path*> runHadlock();

    };


}
