/* 
 * File:   korn.h
 *
 * Created on December 5, 2014, 2:40 AM
 */

#include<iostream>
#include<string>
#include "problem_object.h"



using namespace Utilities;
        

namespace Utilities{
    class Korn {
        private:
    	int width,height;
    	std::vector<Point> source, dest;
        std::vector<Blocker> blocks;
        
        public:
        std::vector< std::vector<Point> > paths;
        Korn(ProblemObject* first_problem);  
   
    	~Korn(){
            
        };

       	void runKorn(double overpull);

    };


}
