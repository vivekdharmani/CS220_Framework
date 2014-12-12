/*
 * lee.h
 *
 *  Created on: Nov 21, 2014
 */

#include<iostream>
#include<string>
#include "problem_object.h"
#include "point.h"
#include "path.h"




namespace Utilities{
    class Lees {
        private:
    	int width,height;		        	/*Width and height of problem object*/
    	std::vector<Point> source, dest;	/*Vector to store source and sink values*/
        std::vector<Blocker> blocks;		/*List of all the blockages in problem object*/
        std::vector<Path*> finalpath;		/*Final paths of all nets to be routed*/
        void LeesBasic();		        	/*Basic Lees Algorithm*/
        void Lees3bit();			        /*Lees Algorithm (3-bit)*/
       	void Lees2Bit();			        /*Lees Algorithm (2-bit)*/
        
        
        public:
        //Constructor-Desctructor
        Lees(ProblemObject* first_problem);  
    	~Lees(){
            
        };

	    //Function to call Lees from main.cc
        std::vector<Path*> runALgo(int choice);
   	

    };


}
