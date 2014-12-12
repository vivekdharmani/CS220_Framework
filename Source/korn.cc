/*
 * korn.cc
 *
 *  Created on: Nov 21, 2014
 */

#include<iostream>
#include<string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include "../Headers/problem_object.h"
#include "../Headers/korn.h"


using namespace Utilities;

Utilities::Korn::Korn(ProblemObject* abcd)
{
			//Copy data from problem object passed from main.cc
                        this->width = abcd->get_width();
	    		this->height = abcd->get_height();
	    		std::vector<Connection> conn = abcd->get_connections();
                        for( int i=0; i<conn.size(); i++)		/*Copying all connections in source and sink vectors*/
                        {
                            this->source.push_back(conn[i].source);
                            this->dest.push_back(conn[i].sink);
                        }
                        this->blocks = abcd->get_blockers();  
};


std::vector<Path*> Utilities::Korn::runKorn(double overpull)
{
    int sx;					/* Source x-coordinate */
    int sy;					/* Source y-coordinate */
    int dx;					/* Sink x-coordinate */
    int dy;					/* Sink y-coordinate */
    bool enhan2=false;				/* Expand latest discovered node*/
    bool enhan1=false;				/* Min turns enhancement */
    bool bfdone = false;			/* Breadth-first flag (true when BF is complete/done) */
    int grid[height][width];			/* Main Grid to route nets on */
    double cost[height][width];			/* Table to save korn costs*/
    std::vector<int> discovered_x;		/* vectors to save the 2 wavefronts(discovered points/nodes) */
    std::vector<int> discovered_y;
      
   std::cout <<"Running Korn's Algorithm\n";

   std::cout <<"Expand cells most recently added to wavefront?(y/n)\n";
   char in;
   std::cin >> in;
   if(in == 'y' || in == 'Y')
       enhan2 = true;				/* flag set to indicate enhancement 2 (search along latest nodes) */

   std::cout <<"Minimize the number of turns in path?(y/n)\n";
   std::cin >> in;
   if(in == 'y' || in == 'Y')
       enhan1 = true;				/* flag set to indicate enhancement 1 (take min no. of turns) */



//Loop to run the algorithm to route all paths in input problem
for(int run = 0; run<source.size(); run++)    
{


/**********************************    
* Initializing/Resetting the grid*
**********************************/

//Getting source and sink
    sx = source[run].x;
    sy = source[run].y;
    dx = dest[run].x;
    dy = dest[run].y;
    
    std::cout << "Net " <<run+1 <<" -\nSource: " <<sx <<" " <<sy <<std::endl;
    std::cout <<"Sink: " <<dx <<" " <<dy <<std::endl;


//Initialising ruben costs to -1
    for(int i=0; i<height; i++){
		for(int j=0; j<width; j++)
		{
			cost[i][j] = -1;
		}
	}


//Initialising grid to -2 (-2 value indicates undiscovered nodes)
    for(int i=0; i<height; i++){
		for(int j=0; j<width; j++)
		{
			grid[i][j] = -2;
		}
	}


//Setting value of all blockages to -1 in grid
    for(int b=0; b<blocks.size(); b++)
    {
        for(int p=0; p<blocks[b].height; p++)
        {
            for(int q=0; q<blocks[b].width; q++)
            {
                grid[blocks[b].location.x + p][blocks[b].location.y + q] = -1;
            }
        }
    }
    

//Setting source-sink values of other nets as -1 (indicating blockages)
    for(int r=run+1; r<source.size(); r++)
    {
            grid[source[r].x][source[r].y] = -1;
            grid[dest[r].x][dest[r].y] = -1;
    }
      
    
    
//Adding previously routed paths as blockages  
    int so_x, so_y, si_x, si_y;
    for (int i = 0; i < finalpath.size();i++) {
        so_x = finalpath.at(i)->at(0)->get_source().x; so_y = finalpath.at(i)->at(0)->get_source().y;
		for (unsigned j = 0;j < finalpath.at(i)->size();j++) {
                
                    si_x = finalpath.at(i)->at(j)->get_sink().x; si_y = finalpath.at(i)->at(j)->get_sink().y;
                    
                    if(so_x==si_x)
                    {
                        if(so_y<si_y)
                        {
                            while(so_y!=si_y)
                            {
                                grid[so_x][so_y] = -1;
                                so_y++;
                            }
                        }
                        else
                        {
                            while(so_y!=si_y)
                            {
                                grid[so_x][so_y] = -1;
                                so_y--;
                            }
                        }
                    }
                    else
                    {
                        if(so_x<si_x)
                        {
                            while(so_x!=si_x)
                            {
                                grid[so_x][so_y] = -1;
                                so_x++;
                            }
                        }
                        else
                        {
                            while(so_x!=si_x)
                            {
                                grid[so_x][so_y] = -1;
                                so_x--;
                            }
                        }
                    }
                    
		}
        grid[so_x][so_y] = -1;
	}
    

        grid[dx][dy] = -2;
        grid[sx][sy] = 0;
        cost[sx][sy] = overpull*(abs(dx-sx) + abs(dy-sy));


        if(sx==dx && sy==dy)			/*Case - Source Sink values are same*/
	{
            bfdone=true;
    	}
    
    	if(sx<0||sx>height-1||dx<0||dx>height-1||sy<0||sy>width-1||dy<0||dy>width-1)	/*Case - Value of source/sink > grid size*/
	{
		std::cout <<"Source/Sink value out of grid\n";
		bfdone = true;
		grid[dx][dy] = 0;

	}
     
        std::cout<<"Cost at Source: "<<cost[sx][sy] <<"\n";
       
          
        
    //Declaring and Initializing Wavefront to source
	discovered_x.push_back(sx);
        discovered_y.push_back(sy);
        
	int curx, cury;			/*Current node of BF*/
        int pos;			/*position of a node in queue/stack(increasing order)*/


/*********************    
 * Exploring the grid*
 *********************/

//If enhancement 1, expand only 1 node from stack
        if(enhan2)
        {    
            while(!bfdone)
            {
                    curx = discovered_x[0];
                    cury = discovered_y[0];
                    discovered_x.erase(discovered_x.begin());
                    discovered_y.erase(discovered_y.begin());

		//Explore node below current node
                if((curx != height-1) && !bfdone)
                    {
                            if((grid[curx +1][cury]==-2)|| (grid[curx+1][cury] > grid[curx][cury]+1))
                            {
                                grid[curx +1][cury] = grid[curx][cury] +1;
                                cost[curx +1][cury] = grid[curx +1][cury] + overpull*(abs(dx-(curx+1)) + abs(dy-cury));
				   //insert node at proper position (according to korn value)
                                   pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx+1][cury]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx+1);
                                    discovered_y.insert(discovered_y.begin() +pos,cury);
                                
                            }	

                            if(curx+1==dx && cury==dy)			/*If sink is found, end the search*/
                                    bfdone=true;
                    }


		//Explore node to the right of current nod
                if((cury != width - 1)&&!bfdone)
                    {
                            if((grid[curx][cury+1]==-2)|| (grid[curx][cury+1] > grid[curx][cury]+1))
                            {
                                    grid[curx][cury+1] = grid[curx][cury] + 1;
                                    cost[curx][cury+1] = grid[curx][cury+1] + overpull*(abs(dx-curx) + abs(dy-(cury+1)));
                                  pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx][cury+1]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx);
                                    discovered_y.insert(discovered_y.begin() +pos,cury+1);
                                
                            }
                            if(curx==dx && cury+1==dy)
                                    bfdone=true;
                    }

		
		//Explore node above current node
                if((curx != 0)&&!bfdone)
                    {
                            if((grid[curx -1][cury]==-2)|| (grid[curx-1][cury] > grid[curx][cury]+1))
                            {
                                    grid[curx -1][cury] = grid[curx][cury] +1;
                                    cost[curx-1][cury] = grid[curx -1][cury] + overpull*(abs(dx-(curx-1)) + abs(dy-cury));
                                    
                                   pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx-1][cury]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx-1);
                                    discovered_y.insert(discovered_y.begin() +pos,cury);
                                
                            }
                            if(curx-1==dx && cury==dy)
                                    bfdone=true;
                    }


		//Explore node to left of current node
                if((cury != 0)&&!bfdone)
                    {
                            if((grid[curx][cury-1]==-2)|| (grid[curx][cury-1] > grid[curx][cury]+1))
                            {
                                    grid[curx][cury-1] = grid[curx][cury] +1;
                                    cost[curx][cury-1] = grid[curx][cury-1] + overpull*(abs(dx-curx) + abs(dy-(cury-1)));
                                  pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx][cury-1]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx);
                                    discovered_y.insert(discovered_y.begin() +pos,cury-1);
                               
                            }
                            if(curx==dx && cury-1==dy)
                                    bfdone=true;
                    }


		//If sink is not found and there are no more nodes to explore, end search and return message

		if(!bfdone && discovered_x.size()==0)
		    {
			std::cout<<"All paths blocked - No route possible\n"<<std::flush;
			bfdone=true;
			grid[dx][dy] = 0;
		    }
         
            }
        }
        else
        {
            std::vector<int> currallx, currally;	/*vector for all nodes of same korn cost*/
            double wavecost;				/*lowest korn value in queue*/

    //Run the BF till sink is found (bfdone set to true when sink is found)
            while(!bfdone)
            {

                wavecost = cost[discovered_x[0]][discovered_y[0]];
                int turn=0;		/*counting no. of same cost values*/

		//Copy all nodes to be explored(of same/lowest cost in array)
                while((turn<discovered_x.size())&&(cost[discovered_x[turn]][discovered_y[turn]] == wavecost))
                {
                    currallx.push_back(discovered_x[turn]);
                    currally.push_back(discovered_y[turn]);
                    turn++;
                }
                
                while(turn !=0)
                {
                    discovered_x.erase(discovered_x.begin());
                    discovered_y.erase(discovered_y.begin());
                    turn--;
                }   
               
		
                while(!currallx.empty())
                {
                    curx = currallx[0];
                    cury = currally[0];
                    currallx.erase(currallx.begin());
                    currally.erase(currally.begin());
                  
		 //Explore node below current node  
                 if((curx != height-1) && !bfdone)
                    {
                            if((grid[curx +1][cury]==-2)|| (grid[curx+1][cury] > grid[curx][cury]+1))
                            {
                                grid[curx +1][cury] = grid[curx][cury] +1;
                                cost[curx +1][cury] = grid[curx +1][cury] + overpull*(abs(dx-(curx+1)) + abs(dy-cury));
				    //insert node at proper position (according to korn value)
                                    pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx +1][cury]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx+1);
                                    discovered_y.insert(discovered_y.begin() +pos,cury);
                                
                            }	

                            if(curx+1==dx && cury==dy)			/*If sink is found, end the search*/
                                    bfdone=true;
                    }


		//Explore node to the right of current node
                if((cury != width - 1)&&!bfdone)
                    {
                            if((grid[curx][cury+1]==-2)|| (grid[curx][cury+1] > grid[curx][cury]+1))
                            {
                                    grid[curx][cury+1] = grid[curx][cury] + 1;
                                    cost[curx][cury+1] = grid[curx][cury+1] + overpull*(abs(dx-curx) + abs(dy-(cury+1)));
                                  pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx][cury+1]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx);
                                    discovered_y.insert(discovered_y.begin() +pos,cury+1);
                                
                            }
                            if(curx==dx && cury+1==dy)
                                    bfdone=true;
                    }


		//Explore node above current node
                if((curx != 0)&&!bfdone)
                    {
                            if((grid[curx -1][cury]==-2)|| (grid[curx-1][cury] > grid[curx][cury]+1))
                            {
                                    grid[curx -1][cury] = grid[curx][cury] +1;
                                    cost[curx-1][cury] = grid[curx -1][cury] + overpull*(abs(dx-(curx-1)) + abs(dy-cury));
                                    
                                   pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx-1][cury]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx-1);
                                    discovered_y.insert(discovered_y.begin() +pos,cury);
                                
                            }
                            if(curx-1==dx && cury==dy)
                                    bfdone=true;
                    }


		//Explore node to left of current node
                if((cury != 0)&&!bfdone)
                    {
                            if((grid[curx][cury-1]==-2)|| (grid[curx][cury-1] > grid[curx][cury]+1))
                            {
                                    grid[curx][cury-1] = grid[curx][cury] +1;
                                    cost[curx][cury-1] = grid[curx][cury-1] + overpull*(abs(dx-curx) + abs(dy-(cury-1)));
                                  pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx][cury-1]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx);
                                    discovered_y.insert(discovered_y.begin() +pos,cury-1);
                               
                            }
                            if(curx==dx && cury-1==dy)
                                    bfdone=true;
                    }    
                }
                

//If sink is not found and there are no more nodes to explore, end search and return message
		if(!bfdone && discovered_x.size()==0)
		    {
			std::cout<<"All paths blocked - No route possible\n"<<std::flush;
			bfdone=true;
			grid[dx][dy] = 0;
		    }
            }
        }


/***********************    
 *Backtracking for path*
 ***********************/      
    int backtrack_x = dx;		/*Starting backtrack at sink*/
    int backtrack_y = dy;
    int pivot_x = dx;			/*pivot to save pathsegments whenever path takes a turn*/
    int pivot_y = dy;
    
    PathSegment* segment = new PathSegment(dx,dy,dx,dy);
    Path* netpath = new Path();


    //Backtrack till source is found using lee values
    while(grid[backtrack_x][backtrack_y]!=0)
    {

	//Check all four neighbours for lower value
		
        if((grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1) && (backtrack_x !=0))
	{
		backtrack_x -= 1;
		//If enhancement 1, try to keep going in one direction
		if(enhan1)
		   {
			while((backtrack_x != 0 )&&(grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1))
			{
			    backtrack_x -= 1;
			}
		   }
	}
			
        else if((grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1)&&(backtrack_y !=0))
        {
                backtrack_y -= 1;
		if(enhan1)
		   {
			while((grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1)&&(backtrack_y !=0))
			{
			    backtrack_y -= 1;
			}
		   }
        }

        else if((grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1) && (backtrack_x != height-1))
        {
                backtrack_x +=1;
		if(enhan1)
		   {
			while((grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1) && (backtrack_x != height-1))
			{
			    backtrack_x +=1;
			}
		   }
        }

        else if((grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1)  && (backtrack_y != width-1))
        {
                backtrack_y += 1;
		if(enhan1)
		   {
			while((grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1)  && (backtrack_y != width-1))
			{
			    backtrack_y += 1;
			}
		   }
        }

        else
        {
                std::cout <<"something went wrong!!";
                std::cout <<std::endl;
        }
        
        
        Point poin; poin.x = backtrack_x; poin.y = backtrack_y;
    
	//If point in same direction, add to current segment
        if(pivot_x == backtrack_x || pivot_y == backtrack_y)
        {
            segment->set_sink(poin);
        }
	//Otherwise add this segment to Path, reset pivot to sink of it
        else
        {
           netpath->add_segment(segment);
            pivot_x = segment->get_sink().x;
            pivot_y = segment->get_sink().y;
            segment = new PathSegment(pivot_x, pivot_y, backtrack_x, backtrack_y);
        }
        
        
    }
    
    netpath->add_segment(segment);
    
//Reset all values
    bfdone = false;
    discovered_x.clear();
    discovered_y.clear();
    finalpath.push_back(netpath);
}
	
   
      return finalpath;				/*Save the route in path vector, which will be returned to main*/

};

