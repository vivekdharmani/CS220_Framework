/*
 * ruben.h
 *
 *  Created on: Nov 21, 2014
 */

#include<iostream>
#include<string>
#include "problem_object.h"
#include "point.h"



namespace Utilities{
    class Ruben {
        private:
    	int width,height;
    	std::vector<Point> source, dest;
        std::vector<Blocker> blocks;
        int manD(int x, int y);
        
        public:
        std::vector< std::vector<Point> > paths;
        Ruben(ProblemObject* first_problem);  
   
    	~Ruben(){
            
        };

       	void runRuben();

    };


}
