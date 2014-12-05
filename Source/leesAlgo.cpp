/*
 * LeesAlgo.cpp
 *
 *  Created on: Nov 21, 2014
 */
#include<iostream>
#include<string>
#include <vector>
#include "../Headers/problem_object.h"
#include "../Headers/lee.h"
#include "../Headers/point.h"




Utilities::Lees::Lees(ProblemObject* abcd){
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


void Utilities::Lees::handle(){
     int opt;
    std::cout << "Select an Option: " <<std::endl;
    std::cout << "1. Basic Lees Algorithm" <<std::endl;
    std::cout << "2. Lees Algorithm (3-bit)" <<std::endl;
    std::cout << "3. Lees Algorithm (2-bit)" <<std::endl;
    std::cin >> opt;
    std::vector< std::vector<Point> > paths;
   
    
    switch(opt)
    {
        case 1:
            LeesBasic();
            break;
        case 2:
            Lees3bit();
            break;
        case 3:
            Lees2Bit();
            break;
        default:
            std::cout <<"Select valid option..";
            break;
    }
}


void Utilities::Lees::LeesBasic() {
    std::cout <<"Running Lees Algorithm\n";
    int sx;
    int sy;
    int dx;
    int dy;
    bool bfdone = false;
    int grid[height][width];
    std::vector<int> discovered_x;
    std::vector<int> discovered_y;
    
 //Start The Breadth First Search
    //Initializing the grid
for(int run = 0; run<source.size(); run++)    
{
    sx = source[run].x;
    sy = source[run].y;
    dx = dest[run].x;
    dy = dest[run].y;
    if(sx==dx && sy==dy)
    {
        bfdone=true;
    }
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
        
        
    //Declaring and Initializing Wavefront to source    
	
        
        discovered_x.push_back(sx);
        discovered_y.push_back(sy);
     
    //Expanding wavefront by checking 4 neighbors    
        int curx, cury;
        while(!bfdone)
        {
            curx = discovered_x[0];
            cury = discovered_y[0];
            discovered_x.erase(discovered_x.begin());
            discovered_y.erase(discovered_y.begin());
            
            if((curx != height-1) && !bfdone)
		{
			if(grid[curx +1][cury]==-2)
			{
				grid[curx +1][cury] = grid[curx][cury] + 1 ;
				discovered_x.push_back(curx +1);
                                discovered_y.push_back(cury);
			}	
			
			if(curx+1==dx && cury==dy)
				bfdone=true;
		}
            
            
            if((cury != width - 1)&&!bfdone)
		{
			if(grid[curx][cury+1]==-2)
			{
				grid[curx][cury+1] = grid[curx][cury] +1;
				discovered_x.push_back(curx);
                                discovered_y.push_back(cury+1);
			}
			if(curx==dx && cury+1==dy)
				bfdone=true;
		}
		
		
            if((curx != 0)&&!bfdone)
		{
			if(grid[curx -1][cury]==-2)
			{
				grid[curx -1][cury] = grid[curx][cury] +1;
				discovered_x.push_back(curx -1);
                                discovered_y.push_back(cury);
			}
			if(curx-1==dx && cury==dy)
				bfdone=true;
		}
		
            if((cury != 0)&&!bfdone)
		{
			if(grid[curx][cury-1]==-2)
			{
				grid[curx][cury-1] = grid[curx][cury] + 1;
				discovered_x.push_back(curx);
                                discovered_y.push_back(cury-1);
			}
			if(curx==dx && cury-1==dy)
				bfdone=true;
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
        if(grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1)
			{
				backtrack_x -= 1;
			}
			
        else if(grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1)
        {
                backtrack_y -= 1;
        }

        else if(grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1)
        {
                backtrack_x +=1;
        }

        else if(grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1)
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


void Utilities::Lees::Lees3bit(){
    std::cout <<"Running Lees Algorithm (3-bit)\n";
    int sx;
    int sy;
    int dx;
    int dy;
    bool bfdone = false;
    int grid[height][width];
    std::vector<int> discovered_x;
    std::vector<int> discovered_y;
    
 //Start The Breadth First Search
    //Initializing the grid
    for(int run = 0; run<source.size(); run++)    
    {
        sx = source[run].x;
        sy = source[run].y;
        dx = dest[run].x;
        dy = dest[run].y;
        if(sx==dx && sy==dy)
            bfdone=true;
        
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

        //Declaring and Initializing Wavefront to source    


            discovered_x.push_back(sx);
            discovered_y.push_back(sy);

        //Expanding wavefront by checking 4 neighbors    
            int curx, cury;
            while(!bfdone)
            {
                curx = discovered_x[0];
                cury = discovered_y[0];
                discovered_x.erase(discovered_x.begin());
                discovered_y.erase(discovered_y.begin());

                if((curx != height-1) && !bfdone)
                    {
                            if(grid[curx +1][cury]==-2)
                            {
                                if(grid[curx][cury] == 3)
                                {
                                    grid[curx +1][cury] = 1 ;
                                    discovered_x.push_back(curx +1);
                                    discovered_y.push_back(cury);
                                }
                                else
                                {
                                    grid[curx +1][cury] = grid[curx][cury] + 1 ;
                                    discovered_x.push_back(curx +1);
                                    discovered_y.push_back(cury);
                                }
                            }	

                            if(curx+1==dx && cury==dy)
                                    bfdone=true;
                    }


                if((cury != width - 1)&&!bfdone)
                    {
                            if(grid[curx][cury+1]==-2)
                            {
                                if(grid[curx][cury] == 3)
                                {
                                    grid[curx][cury+1] = 1;
                                    discovered_x.push_back(curx);
                                    discovered_y.push_back(cury+1);
                                }
                                else
                                {
                                    grid[curx][cury+1] = grid[curx][cury] +1;
                                    discovered_x.push_back(curx);
                                    discovered_y.push_back(cury+1);
                                }
                            }
                            if(curx==dx && cury+1==dy)
                                    bfdone=true;
                    }


                if((curx != 0)&&!bfdone)
                    {
                            if(grid[curx -1][cury]==-2)
                            {
                                if(grid[curx][cury] == 3)
                                {
                                    grid[curx -1][cury] = 1;
                                    discovered_x.push_back(curx -1);
                                    discovered_y.push_back(cury);
                                }
                                else
                                {
                                    grid[curx -1][cury] = grid[curx][cury] +1;
                                    discovered_x.push_back(curx -1);
                                    discovered_y.push_back(cury);
                                }
                            }
                            if(curx-1==dx && cury==dy)
                                    bfdone=true;
                    }

                if((cury != 0)&&!bfdone)
                    {
                            if(grid[curx][cury-1]==-2)
                            {
                                if(grid[curx][cury] == 3)
                                {
                                    grid[curx][cury-1] = 1;
                                    discovered_x.push_back(curx);
                                    discovered_y.push_back(cury-1);
                                }
                                else
                                {
                                    grid[curx][cury-1] = grid[curx][cury] + 1;
                                    discovered_x.push_back(curx);
                                    discovered_y.push_back(cury-1);
                                }
                            }
                            if(curx==dx && cury-1==dy)
                                    bfdone=true;
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
            if((grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1)||(grid[backtrack_x-1][backtrack_y]==3 && grid[backtrack_x][backtrack_y]==1))
                            {
                                    backtrack_x -= 1;
                            }

            else if((grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1)||(grid[backtrack_x][backtrack_y-1]==3 && grid[backtrack_x][backtrack_y] ==1))
            {
                    backtrack_y -= 1;
            }

            else if((grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1)||(grid[backtrack_x+1][backtrack_y]==3 && grid[backtrack_x][backtrack_y] ==1))
            {
                    backtrack_x +=1;
            }

            else if((grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1) ||(grid[backtrack_x][backtrack_y+1] ==3 && grid[backtrack_x][backtrack_y] ==1))
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
   
};


void Utilities::Lees::Lees2Bit(){
    std::cout <<"Running Lees Algorithm (2-bit)\n";
    int sx;
    int sy;
    int dx;
    int dy;
    bool bfdone = false;
    int grid[height][width];
    std::vector<int> discovered_x[2];
    std::vector<int> discovered_y[2];
    
    int prev = 22;
    int wavevalue=1;
    
 //Start The Breadth First Search
    //Initializing the grid
for(int run = 0; run<source.size(); run++)    
{
    sx = source[run].x;
    sy = source[run].y;
    dx = dest[run].x;
    dy = dest[run].y;
    if(sx==dx && sy==dy)
        bfdone=true;
    prev = 22;
    wavevalue=1;
    
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
                curx = discovered_x[bfturn%2][0];
                cury = discovered_y[bfturn%2][0];
                discovered_x[bfturn%2].erase(discovered_x[bfturn%2].begin());
                discovered_y[bfturn%2].erase(discovered_y[bfturn%2].begin());
                if((curx != height-1) && !bfdone)
                    {
                            if(grid[curx +1][cury]==-2)
                            {
                                    grid[curx +1][cury] = wavevalue;
                                    discovered_x[(bfturn+1)%2].push_back(curx +1);
                                    discovered_y[(bfturn+1)%2].push_back(cury);
                            }	

                            if(curx+1==dx && cury==dy)
                                    bfdone=true;
                    }


                if((cury != width - 1)&&!bfdone)
                    {
                            if(grid[curx][cury+1]==-2)
                            {
                                    grid[curx][cury+1] = wavevalue;
                                    discovered_x[(bfturn+1)%2].push_back(curx);
                                    discovered_y[(bfturn+1)%2].push_back(cury+1);
                            }
                            if(curx==dx && cury+1==dy)
                                    bfdone=true;
                    }


                if((curx != 0)&&!bfdone)
                    {
                            if(grid[curx -1][cury]==-2)
                            {
                                    grid[curx -1][cury] = wavevalue;
                                    discovered_x[(bfturn+1)%2].push_back(curx -1);
                                    discovered_y[(bfturn+1)%2].push_back(cury);
                            }
                            if(curx-1==dx && cury==dy)
                                    bfdone=true;
                    }

                if((cury != 0)&&!bfdone)
                    {
                            if(grid[curx][cury-1]==-2)
                            {
                                    grid[curx][cury-1] = wavevalue;
                                    discovered_x[(bfturn+1)%2].push_back(curx);
                                    discovered_y[(bfturn+1)%2].push_back(cury-1);
                            }
                            if(curx==dx && cury-1==dy)
                                    bfdone=true;
                    }
            }
            
            bfturn++;
            
            if(!bfdone)
            {
                if(prev == 11)
                {
                    prev = 12;
                    wavevalue = 2;
                }
                else if(prev == 12)
                {
                    prev = 22;
                    wavevalue = 1;
                }
                else if(prev == 22)
                {
                    prev = 21;
                    wavevalue = 1;
                }
                else if(prev == 21)
                {
                    prev = 11;
                    wavevalue = 2;
                }
                else
                    std::cout<<"Error in wavevalue";
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
        if(prev ==12 || prev==22)
            wavevalue = 2;
        else if(prev ==11 || prev==21)
            wavevalue = 1;    
    
        
        if((grid[backtrack_x-1][backtrack_y] == wavevalue)||(grid[backtrack_x-1][backtrack_y] == 0))
			{
				backtrack_x -= 1;
			}
			
        else if((grid[backtrack_x][backtrack_y-1] == wavevalue)||(grid[backtrack_x][backtrack_y-1] == 0))
        {
                backtrack_y -= 1;
        }

        else if((grid[backtrack_x+1][backtrack_y] == wavevalue)||(grid[backtrack_x+1][backtrack_y] == 0))
        {
                backtrack_x +=1;
        }

        else if((grid[backtrack_x][backtrack_y+1] == wavevalue)||(grid[backtrack_x][backtrack_y+1] == 0))
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
       
        if(prev == 11)
            prev = 21;
        else if(prev == 12)
            prev = 11;
        else if(prev == 21)
            prev = 22;
        else if(prev == 22)
            prev = 12;
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
