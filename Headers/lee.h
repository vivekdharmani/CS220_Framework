/*
 * lee.h
 *  Created on: Nov 21, 2014
 */

#include<iostream>
#include<string>
#include "problem_object.h"
#include "point.h"

namespace Utilities{
    class Lees {
        private:
    	int width,height;
    	std::vector<Point> source, dest;
        std::vector<Blocker> blocks;
        
        public:
        std::vector< std::vector<Point> > paths;
        Lees(ProblemObject* first_problem);  
   
    	~Lees(){
            
        };

        void handle();
   	void LeesBasic();
        void Lees3bit();
       	void Lees2Bit();

    };


}
