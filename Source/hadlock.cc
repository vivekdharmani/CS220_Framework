/*
 * hadlock.cc
 *
 *  Created on: Nov 21, 2014
 *
 */

#include<iostream>
#include<string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include "../Headers/problem_object.h"
#include "../Headers/hadlock.h"


using namespace Utilities;

Utilities::Hadlock::Hadlock(ProblemObject* abcd)
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


void Utilities::Hadlock::runHadlock()
{
    int sx;
    int sy;
    int dx;
    int dy;
    bool enhan2=false;
    bool bfdone = false;
    bool inputerr = false;
    int grid[height][width];
    std::vector<int> discovered_x[2];
    std::vector<int> discovered_y[2];
      
   std::cout <<"Running Hadlock's Algorithm\n";
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
        if(sx==dx && sy==dy)
	{
            bfdone=true;
    	}
    
    	if(sx<0||sx>height-1||dx<0||dx>height-1||sy<0||sy>width-1||dy<0||dy>width-1)
	{
		std::cout <<"Source/Sink value out of grid\n";
		bfdone = true;
		inputerr = true;
		grid[dx][dy] = 0;

	}        
        
    //Declaring and Initializing Wavefront to source    
        
        discovered_x[0].push_back(sx);
        discovered_y[0].push_back(sy);
        
    //Expanding wavefront by checking 4 neighbors    
        int curx, cury;
        int bfturn=0;
        
        
        while(!bfdone)
        {
            while(!discovered_x[bfturn%2].empty())
            {
                if(enhan2)
                {
                    curx = discovered_x[bfturn%2][discovered_x[bfturn%2].size()-1];
                    cury = discovered_y[bfturn%2][discovered_x[bfturn%2].size()-1];
                    discovered_x[bfturn%2].pop_back();
                    discovered_y[bfturn%2].pop_back();
                }
                else
                {
                    curx = discovered_x[bfturn%2][0];
                    cury = discovered_y[bfturn%2][0];
                    discovered_x[bfturn%2].erase(discovered_x[bfturn%2].begin());
                    discovered_y[bfturn%2].erase(discovered_y[bfturn%2].begin());
                }
                if((curx != height-1) && !bfdone)
                    {
                            if((grid[curx +1][cury]==-2)|| (grid[curx+1][cury] > grid[curx][cury]))
                            {
                                if(curx<dx)
                                {
                                    grid[curx +1][cury] = grid[curx][cury];
                                    discovered_x[bfturn%2].push_back(curx +1);
                                    discovered_y[bfturn%2].push_back(cury);
                                }
                                else
                                {
                                    grid[curx +1][cury] = grid[curx][cury] +1;
                                    discovered_x[(bfturn+1)%2].push_back(curx +1);
                                    discovered_y[(bfturn+1)%2].push_back(cury);
                                }
                            }	

                            if(curx+1==dx && cury==dy)
                                    bfdone=true;
                    }


                if((cury != width - 1)&&!bfdone)
                    {
                            if((grid[curx][cury+1]==-2)|| (grid[curx][cury+1] > grid[curx][cury]))
                            {
                                if(cury<dy)
                                {
                                    grid[curx][cury +1] = grid[curx][cury];
                                    discovered_x[bfturn%2].push_back(curx);
                                    discovered_y[bfturn%2].push_back(cury+1);
                                }
                                else
                                {
                                    grid[curx][cury+1] = grid[curx][cury] +1;
                                    discovered_x[(bfturn+1)%2].push_back(curx);
                                    discovered_y[(bfturn+1)%2].push_back(cury+1);
                                }
                                    
                            }
                            if(curx==dx && cury+1==dy)
                                    bfdone=true;
                    }


                if((curx != 0)&&!bfdone)
                    {
                            if((grid[curx -1][cury]==-2)|| (grid[curx-1][cury] > grid[curx][cury]))
                            {
                                if(curx>dx)
                                {
                                    grid[curx -1][cury] = grid[curx][cury];
                                    discovered_x[bfturn%2].push_back(curx -1);
                                    discovered_y[bfturn%2].push_back(cury);
                                }
                                else
                                {
                                    grid[curx-1][cury] = grid[curx][cury] +1;
                                    discovered_x[(bfturn+1)%2].push_back(curx-1);
                                    discovered_y[(bfturn+1)%2].push_back(cury);
                                }
                                   
                            }
                            if(curx-1==dx && cury==dy)
                                    bfdone=true;
                    }

                if((cury != 0)&&!bfdone)
                    {
                            if((grid[curx][cury-1]==-2)|| (grid[curx][cury-1] > grid[curx][cury]))
                            {
                                if(cury>dy)
                                {
                                    grid[curx][cury -1] = grid[curx][cury];
                                    discovered_x[bfturn%2].push_back(curx);
                                    discovered_y[bfturn%2].push_back(cury-1);
                                }
                                else
                                {
                                    grid[curx][cury-1] = grid[curx][cury] +1;
                                    discovered_x[(bfturn+1)%2].push_back(curx);
                                    discovered_y[(bfturn+1)%2].push_back(cury-1);
                                }
                            }
                            if(curx==dx && cury-1==dy)
                                    bfdone=true;
                    }
            }
            
            bfturn++;
            
        }


//Backtracking for results  
    int backtrack_x = dx;
    int backtrack_y = dy;
    std::vector<Point> route;
    //up-1; right-2; down-3; left-4;
    char lastpoint;
    Point poin; poin.x = dx; poin.y = dy;
    route.push_back(poin);
	
    if(inputerr)
	{
		backtrack_x = sx;
    		backtrack_y = sy;
	}

    while(!(backtrack_x ==sx && backtrack_y ==sy))
    {
        if(grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1 && grid[backtrack_x-1][backtrack_y]>=0 && backtrack_x != 0)
        {
                backtrack_x -= 1;
                lastpoint = 'd';
        }
			
        else if(grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1 && grid[backtrack_x][backtrack_y-1]>=0 && backtrack_y != 0)
        {
                backtrack_y -= 1;
                lastpoint = 'r';
                
        }

        else if(grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1 && grid[backtrack_x+1][backtrack_y]>=0 && backtrack_x != height-1)
        {
                backtrack_x += 1;
                lastpoint = 'u';
        }

        else if(grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1 && grid[backtrack_x][backtrack_y+1]>=0 && backtrack_y != width - 1)
        {
                backtrack_y += 1;
                lastpoint = 'l';
        }

    //Round 2
        
        else if(backtrack_x-1>=sx && grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] && lastpoint != 'u' && backtrack_x != 0)
        {
                backtrack_x -= 1;
                lastpoint = 'd';
        }
			
        else if(backtrack_y-1>=sy && grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] && lastpoint != 'l' && backtrack_y != 0)
        {
                backtrack_y -= 1;
                lastpoint = 'r';
        }

        else if(backtrack_x+1<=sx && grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] && lastpoint != 'd' && backtrack_x != height-1)
        {
                backtrack_x +=1;
                lastpoint = 'u';
        }

        else if(backtrack_y+1<=sy && grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] && lastpoint != 'r' && backtrack_y != width - 1)
        {
                backtrack_y += 1;
                lastpoint = 'l';
        }

        //Round 3
        
        else if(grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] && lastpoint != 'u' && backtrack_x != 0)
        {
                backtrack_x -= 1;
                lastpoint = 'd';
        }
			
        else if(grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] && lastpoint != 'l' && backtrack_y != 0)
        {
                backtrack_y -= 1;
                lastpoint = 'r';
        }

        else if(grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] && lastpoint != 'd' && backtrack_x != height-1)
        {
                backtrack_x += 1;
                lastpoint = 'u';
        }

        else if(grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] && lastpoint != 'r' && backtrack_y != width - 1)
        {
                backtrack_y += 1;
                lastpoint = 'l';
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
    discovered_x[0].clear();
    discovered_y[0].clear();
    discovered_x[1].clear();
    discovered_y[1].clear();
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


