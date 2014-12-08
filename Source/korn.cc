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
                        this->width = abcd->get_width();
	    		this->height = abcd->get_height();
	    		std::vector<Connection> conn = abcd->get_connections();
                        for( int i=0; i<conn.size(); i++)
                        {
                            this->source.push_back(conn[i].source);
                            this->dest.push_back(conn[i].sink);
                        }
                        this->blocks = abcd->get_blockers();  
};


void Utilities::Korn::runKorn(double overpull)
{
    int sx;
    int sy;
    int dx;
    int dy;
    bool enhan2=false;
    bool bfdone = false;
    int grid[height][width];
    double cost[height][width];
    std::vector<int> discovered_x;
    std::vector<int> discovered_y;
      
   std::cout <<"Running Korn's Algorithm\n";
   std::cout <<"Expand cells most recently added to wavefront?(y/n)\n";
   char in;
   std::cin >> in;
   if(in == 'y' || in == 'Y')
       enhan2 = true;
 //Start The Breadth First Search
    //Initializing the grid
for(int run = 0; run<source.size(); run++)    
{
    sx = source[run].x;
    sy = source[run].y;
    dx = dest[run].x;
    dy = dest[run].y;
    
    std::cout << "Net " <<run+1 <<" -\nSource: " <<sx <<" " <<sy <<std::endl;
    std::cout <<"Sink: " <<dx <<" " <<dy <<std::endl;
    for(int i=0; i<height; i++){
		for(int j=0; j<width; j++)
		{
			cost[i][j] = -1;
		}
	}
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++)
		{
			grid[i][j] = -2;
		}
	}
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
    
    for(int r=run+1; r<source.size(); r++)
    {
            grid[source[r].x][source[r].y] = -1;
            grid[dest[r].x][dest[r].y] = -1;
    }
      
    
        
     for(int r=0; r < paths.size(); r++)
    {
        for(int s=0; s<paths[r].size(); s++)
        {
           grid[paths[r][s].x][paths[r][s].y] = -1;
        }
    }
     
        grid[dx][dy] = -2;
        grid[sx][sy] = 0;
        cost[sx][sy] = overpull*(abs(dx-sx) + abs(dy-sy));
        if(sx==dx && sy==dy)
	{
            bfdone=true;
    	}
    
    	if(sx<0||sx>height-1||dx<0||dx>height-1||sy<0||sy>width-1||dy<0||dy>width-1)
	{
		std::cout <<"Source/Sink value out of grid\n";
		bfdone = true;
		grid[dx][dy] = 0;

	}
     
        std::cout<<"Cost at Source: "<<cost[sx][sy] <<"\n";
       
        
    //Expanding wavefront by checking 4 neighbors    
        int curx, cury;
        int pos;
        if(enhan2)
        {
            //Declaring and Initializing Wavefront to source    
            discovered_x.push_back(sx);
            discovered_y.push_back(sy);
            while(!bfdone)
            {
                    
                    curx = discovered_x[0];
                    cury = discovered_y[0];
                    discovered_x.erase(discovered_x.begin());
                    discovered_y.erase(discovered_y.begin());
                    
                    
                if((curx != height-1) && !bfdone)
                    {
                            if((grid[curx +1][cury]==-2)|| (grid[curx+1][cury] > grid[curx][cury]+1))
                            {
                                grid[curx +1][cury] = grid[curx][cury] +1;
                                cost[curx +1][cury] = grid[curx +1][cury] + overpull*(abs(dx-(curx+1)) + abs(dy-cury));
                                   pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx +1][cury]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx+1);
                                    discovered_y.insert(discovered_y.begin() +pos,cury);
                                
                            }	

                            if(curx+1==dx && cury==dy)
                                    bfdone=true;
                    }


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
        }
        else
        {
            discovered_x.push_back(sx);
            discovered_y.push_back(sy);
            std::vector<int> currallx, currally;
            double wavecost;

            while(!bfdone)
            {

                wavecost = cost[discovered_x[0]][discovered_y[0]];
                int turn=0;
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
                    
                 if((curx != height-1) && !bfdone)
                    {
                            if((grid[curx +1][cury]==-2)|| (grid[curx+1][cury] > grid[curx][cury]+1))
                            {
                                grid[curx +1][cury] = grid[curx][cury] +1;
                                cost[curx +1][cury] = grid[curx +1][cury] + overpull*(abs(dx-(curx+1)) + abs(dy-cury));
                                    pos=0;
                                    while((pos<discovered_x.size())&&(cost[discovered_x[pos]][discovered_y[pos]] <  cost[curx +1][cury]))
                                    {
                                        pos++;
                                    }
                                    discovered_x.insert(discovered_x.begin() +pos,curx+1);
                                    discovered_y.insert(discovered_y.begin() +pos,cury);
                                
                            }	

                            if(curx+1==dx && cury==dy)
                                    bfdone=true;
                    }


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
                
            }
        }
//Backtracking for results          
    int backtrack_x = dx;
    int backtrack_y = dy;
    std::vector<Point> route;
        
    Point poin; poin.x = dx; poin.y = dy;
    route.push_back(poin);
    while(grid[backtrack_x][backtrack_y]!=0)
    {
        if((grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1) && (backtrack_x !=0))
			{
				backtrack_x -= 1;
			}
			
        else if((grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1)&&(backtrack_y !=0))
        {
                backtrack_y -= 1;
        }

        else if((grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1) && (backtrack_x != height-1))
        {
                backtrack_x +=1;
        }

        else if((grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1)  && (backtrack_y != width-1))
        {
                backtrack_y += 1;
        }

        else
        {
                std::cout <<"something went wrong!!";
                std::cout <<std::endl;
        }
        Point poin; poin.x = backtrack_x; poin.y = backtrack_y;
    
        route.push_back(poin);
        
        
    }
   
    
    paths.push_back(route);
    bfdone = false;
    discovered_x.clear();
    discovered_y.clear();
    route.clear();
}
 
   /*
    std::cout <<"Printing final grid :" <<std::endl <<std::endl;
    
    for(int i=0; i<height; i++)
    {
		for(int j=0; j<width; j++)
		{
			grid[i][j] = 0;
		}
    }
    
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
    
    for(int r=0; r<paths.size() ; r++)
    {
        for(int s=0; s<paths[r].size(); s++)
        {
            grid[paths[r][s].x][paths[r][s].y] = r+1;
        }
    }
        
    for(int i=0; i<height; i++)
    {
		for(int j=0; j<width; j++)
		{
                    	std::cout <<grid[i][j] <<  "\t";
		}
                std::cout <<std::endl;
	}
    */
};

