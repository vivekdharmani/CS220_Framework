
#include "../Headers/grid.h"
#include "../Headers/problem_object.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

int main(int argc,char* argv[]) {

	// DO NOT CHANGE THIS SECTION OF CODE
	if(argc < 2) { cout << "Usage: ./grid_router <test_file>" << endl; }
	Utilities::ProblemObject* first_problem = new Utilities::ProblemObject(std::string(argv[1]));
	// EDIT FROM HERE DOWN

	//Create your problem map object (in our example, we use a simple grid, you should create your own)
//	Utilities::Grid g(first_problem->get_width(), first_problem->get_height());

	/*
	Note: we do not take into account the connections or blockers that exist in the Project Object
	You should be accouting for these in your problem map objects (you should not be using Grid). You
	should be using both the Node and Edge classes as the background for whatever problem map object
	you create.
	*/

	/*
	Run your algorithm after creating your problem map object. You should be returning from your algorithm 
	either a Path or a Netlist

	Path: a series of straight line segments, with a single source and a single sink
	Netlist: a series of stright line segments, with a single source and more than one sink
	*/

	//Note, we create random paths just as an example of how to create paths, netlists are created similarly
/*	vector<Path*> paths;
	srand(time(NULL));
	int number_paths = first_problem->get_connections().size();
	cout << "Creating " << number_paths << " paths...";
	for (int i = 0;i < number_paths;i++) {
		Path* new_path = new Path();
		int x = rand() % first_problem->get_width();
		int y = rand() % first_problem->get_height();
		int path_length = 1+rand()%10;
		for (unsigned j = 0;j < path_length;j++) {
			bool direction = rand()%2;
			Point head(x,y);
			direction?x+=1:y+=1;
			Point tail(x,y);
			PathSegment* new_segment = new PathSegment(head,tail);
			new_path->add_segment(new_segment);
		}
		paths.push_back(new_path);
	}
	cout << "Completed." << endl;
*/

 int algo;
    std::cout << "Select an Algorithm to use: " <<std::endl;
    std::cout << "1. Lees Algorithm" <<std::endl;
    std::cout << "2. Ruben's Algorithm" <<std::endl;
    std::cin >> algo;
    std::vector< std::vector<Point> > paths;
    
    switch(algo)
    {
        case 1:
        {
		std::cout <<"in";
            Utilities::Lees leeobj(first_problem);		
		std::cout <<"done";
            leeobj.handle();
            paths = leeobj.paths;
        }
        break;
        case 2:
        {
            Utilities::Ruben ruben(first_problem);
            ruben.runRuben();
            paths = ruben.paths;
        }
        break;
        default:
            std::cout <<"Select valid option..";
            break;
    }
	//Print the paths/netlists that you have return from your algorithm
	int r=0; r < paths.size() ; r++)
    {
        std::cout << "Net " << r+1 <<": ";
        for(int s=0; s<paths[r].size(); s++)
        {
           std::cout<< "( " <<paths[r][s].x << " , " <<paths[r][s].y <<" )";
        }
        std::cout<<std::endl;
    }
    
	
/*	
	for (unsigned i = 0;i < paths.size();i++) {
		cout << "\tPath " << i+1 << " of " << paths.size() << ": (" 
			 << paths.at(i)->at(0)->get_source().x << "," << paths.at(i)->at(0)->get_source().y << ") ";
		for (unsigned j = 0;j < paths.at(i)->size();j++) {
			cout << "(" << paths.at(i)->at(j)->get_sink().x << "," << paths.at(i)->at(j)->get_sink().y << ") ";
		}
		cout << endl;
		Path* temp = paths.at(i);
		delete temp;
	}
	paths.clear();
*/
	delete first_problem;

	return 0;
}
