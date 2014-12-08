/* 
 * File:   hadlock.h
 * Author: Vivek
 *
 * Created on December 6, 2014, 8:08 AM
 */

#include<iostream>
#include<string>
#include "problem_object.h"



using namespace Utilities;
        

namespace Utilities{
    class Hadlock {
        private:
    	int width,height;
    	std::vector<Point> source, dest;
        std::vector<Blocker> blocks;
        
        public:
        std::vector< std::vector<Point> > paths;
        Hadlock(ProblemObject* first_problem);  
   
    	~Hadlock(){
            
        };

       	void runHadlock();

    };


}
