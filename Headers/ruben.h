/*
 * ruben.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Vivek
 */

#include<iostream>
#include<string>
#include "problem_object.h"
#include "path.h"



using namespace Utilities;
        

namespace Utilities{
    class Ruben {
        private:
    	int width,height;			/*Width and height of problem object*/
    	std::vector<Point> source, dest;	/*Vector to store source and sink values*/
        std::vector<Blocker> blocks;		/*List of all the blockages in problem object*/
        std::vector<Path*> finalpath;		/*Final paths of all nets to be routed*/
        
        public:
	//Constructor-Desctructor
        Ruben(ProblemObject* first_problem);  
    	~Ruben(){  
        
        };

	//Rubens Algorithm
       	std::vector<Path*> runRuben();

    };


}
