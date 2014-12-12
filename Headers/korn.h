/* 
 * File:   korn.h
 *
 * Created on December 5, 2014, 2:40 AM
 */

#include<iostream>
#include<string>
#include "problem_object.h"
#include "point.h"
#include "path.h"



using namespace Utilities;
        

namespace Utilities{
    class Korn {
        private:
    	int width,height;			/*Width and height of problem object*/
    	std::vector<Path*> finalpath;		/*Final paths of all nets to be routed*/
        std::vector<Point> source, dest;	/*Vector to store source and sink values*/
        std::vector<Blocker> blocks;		/*List of all the blockages in problem object*/
        
        public:
        //Constructor-Desctructor
        Korn(ProblemObject* first_problem);  
   
    	~Korn(){
            
        };

	//Korns Algorithm
       	std::vector<Path*> runKorn(double overpull);

    };


}
