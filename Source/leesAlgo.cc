#include<iostream>
#include<string>
#include <vector>
#include "../Headers/problem_object.h"
#include "../Headers/lee.h"
#include "../Headers/point.h"
#include "../Headers/pathsegment.h"
#include "../Headers/segmentgroup.h"
#include "../Headers/path.h"





Utilities::Lees::Lees(ProblemObject* abcd){

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


std::vector<Utilities::Path*> Utilities::Lees::runALgo(int choice){
   
  //Run the algorithm according to choice made by user
    switch(choice)
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
            std::cout <<"Select valid option...";
            break;
    }
    return finalpath;
}


void Utilities::Lees::LeesBasic() {
    std::cout <<"Running Lees Algorithm..\n";

    int sx;					/* Source x-coordinate */
    int sy;					/* Source y-coordinate */
    int dx;					/* Sink x-coordinate */
    int dy;					/* Sink y-coordinate */
    bool bfdone = false;			/* Breadth-first flag (true when BF is complete/done) */
    int grid[height][width];			/* Main Grid to route nets on */
    std::vector<int> discovered_x;		/* vectors to save the wavefront(discovered points/nodes) */
    std::vector<int> discovered_y;


 /**********************************    
 * Initializing/Resetting the grid*
 **********************************/

  for(int run = 0; run<source.size(); run++)   			/*Loop to run the algorithm to route all paths in input problem*/ 
  {

    //Getting source and sink
   	sx = source[run].x;
    	sy = source[run].y;
    	dx = dest[run].x;
    	dy = dest[run].y;
    
    	std::cout << "Net " <<run+1 <<" -\nSource: " <<sx <<" " <<sy <<std::endl;
    	std::cout <<"Sink: " <<dx <<" " <<dy <<std::endl;

  
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

    //Declaring and Initializing Wavefront to source    
	
        discovered_x.push_back(sx);
        discovered_y.push_back(sy);
     
        int curx, cury;			/*Current node of BF*/

/*********************    
 * Exploring the grid*
 *********************/

    //Run the BF till sink is found (bfdone set to true when sink is found)

        while(!bfdone)
        {
            curx = discovered_x[0];		/*Take the next point from discovered points*/
            cury = discovered_y[0];
            discovered_x.erase(discovered_x.begin());
            discovered_y.erase(discovered_y.begin());
            
	//Explore node below current node
            if((curx != height-1) && !bfdone)
		{
			if(grid[curx +1][cury]==-2)
			{
				grid[curx +1][cury] = grid[curx][cury] + 1 ;
				discovered_x.push_back(curx +1);
                                discovered_y.push_back(cury);
			}	
			
			if(curx+1==dx && cury==dy)			/*If sink is found, end the search*/
				bfdone=true;
		}
            

            //Explore node to the right of current node

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
		
	    //Explore node above current node		

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
		
	    //Explore node to left of current node
            
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

	//If sink is not found and there are no more nodes to explore, end search and return message
	    if(!bfdone && discovered_x.size()==0)
 	    {
		std::cout<<"All paths blocked - No route possible\n"<<std::flush;
		bfdone=true;
		grid[dx][dy] = 0;
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
       
    while(grid[backtrack_x][backtrack_y]!=0)				/*Backtrack till source is found*/
    {

//Check all four neighbours for a lower value

	if((backtrack_x != 0) && (grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1))
	{
		backtrack_x -= 1;
	}
			
        else if((backtrack_y != 0) && (grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1))
        {
		 backtrack_y -= 1;
        }

        else if((backtrack_x != height-1) && (grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1))
        {
		backtrack_x +=1;
        }

        else if((backtrack_y != width - 1) && (grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1))
        {
		backtrack_y += 1;
        }

        else
        {
                std::cout <<"something went wrong!!";
                std::cout <<std::endl;
        }
        
        Point poin; poin.x = backtrack_x; poin.y = backtrack_y;
    
        if(pivot_x == backtrack_x || pivot_y == backtrack_y)		/*If point in same direction, add to current segment*/
        {
            segment->set_sink(poin);
        }
        else						/*Otherwise add this segment to Path, reset pivot to sink of it*/
        {
           netpath->add_segment(segment);
            pivot_x = segment->get_sink().x;
            pivot_y = segment->get_sink().y;
            segment = new PathSegment(pivot_x, pivot_y, backtrack_x, backtrack_y);
        }
        
    }
    
    netpath->add_segment(segment);
    
    bfdone = false;
    discovered_x.clear();
    discovered_y.clear();
    finalpath.push_back(netpath);				/*Save the route in path vector, which will be returned to main*/
  }
 

};


void Utilities::Lees::Lees3bit(){ 
    std::cout <<"Running Lees Algorithm (3-bit)\n";
    int sx;					/* Source x-coordinate */
    int sy;					/* Source y-coordinate */
    int dx;					/* Sink x-coordinate */
    int dy;					/* Sink y-coordinate */
    bool bfdone = false;			/* Breadth-first flag (true when BF is complete/done) */
    int grid[height][width];			/* Main Grid to route nets on */
    std::vector<int> discovered_x;		/* vectors to save the wavefront(discovered points/nodes) */
    std::vector<int> discovered_y;
    

/**********************************    
 * Initializing/Resetting the grid*
 **********************************/

    for(int run = 0; run<source.size(); run++)    		/*Loop to run the algorithm to route all paths in input problem*/
    {

      //Getting source and sink
        sx = source[run].x;
        sy = source[run].y;
        dx = dest[run].x;
        dy = dest[run].y;
        
        std::cout << "Net " <<run+1 <<" -\nSource: " <<sx <<" " <<sy <<std::endl;
        std::cout <<"Sink: " <<dx <<" " <<dy <<std::endl;


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

     //Declaring and Initializing Wavefront to source    

            discovered_x.push_back(sx);
            discovered_y.push_back(sy);

            int curx, cury;		/*Current node of BF*/

/*********************    
 * Exploring the grid*
 *********************/       

     //Run the BF till sink is found (bfdone set to true when sink is found)

     while(!bfdone)
            {
                curx = discovered_x[0];		/*Take the next point from discovered points*/
                cury = discovered_y[0];
                discovered_x.erase(discovered_x.begin());
                discovered_y.erase(discovered_y.begin());
 
          //Explore node below current node
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


           //Explore node to the right of current node
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

                
	  //Explore node above current node
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


         //Explore node to left of current node
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

	//If sink is not found and there are no more nodes to explore, end search and return message

		if(!bfdone && discovered_x.size()==0)
		    {
			std::cout<<"All paths blocked - No route possible\n"<<std::flush;
			bfdone=true;
			grid[dx][dy] = 0;
		    }

            }


/***********************    
 *Backtracking for path*
 ***********************/      

        int backtrack_x = dx;			/*Starting backtrack at sink*/
        int backtrack_y = dy;
        int pivot_x = dx;			/*pivot to save pathsegments whenever path takes a turn*/
        int pivot_y = dy;
    
        PathSegment* segment = new PathSegment(dx,dy,dx,dy);
        Path* netpath = new Path();

//Backtrack till source is found

        while(grid[backtrack_x][backtrack_y]!=0)
        {
	   //Check all four neighbours for a lower value

            if(((grid[backtrack_x-1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1)||(grid[backtrack_x-1][backtrack_y]==3 && grid[backtrack_x][backtrack_y]==1))&&(backtrack_x != 0))
                            {
                                    backtrack_x -= 1;
                            }

            else if(((grid[backtrack_x][backtrack_y-1] == grid[backtrack_x][backtrack_y] - 1)||(grid[backtrack_x][backtrack_y-1]==3 && grid[backtrack_x][backtrack_y] ==1))&&(backtrack_y != 0))
            {
                    backtrack_y -= 1;
            }

            else if(((grid[backtrack_x+1][backtrack_y] == grid[backtrack_x][backtrack_y] - 1)||(grid[backtrack_x+1][backtrack_y]==3 && grid[backtrack_x][backtrack_y] ==1))&&(backtrack_x != height-1))
            {
                    backtrack_x +=1;
            }

            else if(((grid[backtrack_x][backtrack_y+1] == grid[backtrack_x][backtrack_y] - 1) ||(grid[backtrack_x][backtrack_y+1] ==3 && grid[backtrack_x][backtrack_y] ==1))&&(backtrack_y != width - 1))
            {
                    backtrack_y += 1;
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
            else			/*Otherwise add this segment to Path, reset pivot to sink of it*/
            {
               netpath->add_segment(segment);
                pivot_x = segment->get_sink().x;
                pivot_y = segment->get_sink().y;
                segment = new PathSegment(pivot_x, pivot_y, backtrack_x, backtrack_y);
            }
        }


       netpath->add_segment(segment);
    
       bfdone = false;
       discovered_x.clear();
       discovered_y.clear();
       finalpath.push_back(netpath);			/*Save the route in path vector, which will be returned to main*/
    }
   
};


void Utilities::Lees::Lees2Bit(){ 
    std::cout <<"Running Lees Algorithm (2-bit)\n";
     int sx;					/* Source x-coordinate */
    int sy;					/* Source y-coordinate */
    int dx;					/* Sink x-coordinate */
    int dy;					/* Sink y-coordinate */
    bool bfdone = false;			/* Breadth-first flag (true when BF is complete/done) */
    int grid[height][width];			/* Main Grid to route nets on */
    std::vector<int> discovered_x[2];		/* vectors to save the 2 wavefronts(discovered points/nodes) */
    std::vector<int> discovered_y[2];
    
    int prev = 22;				/*variable to store previous wave values to know current value*/
    int wavevalue=1;
    

/**********************************    
 * Initializing/Resetting the grid*
 **********************************/

for(int run = 0; run<source.size(); run++)    			/*Loop to run the algorithm to route all paths in input problem*/
{
   //Getting source and sink
      sx = source[run].x;
      sy = source[run].y;
      dx = dest[run].x;
      dy = dest[run].y;
      prev = 22;
      wavevalue=1;
    
      std::cout << "Net " <<run+1 <<" -\nSource: " <<sx <<" " <<sy <<std::endl;
      std::cout <<"Sink: " <<dx <<" " <<dy <<std::endl;
	

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
        
    //Declaring and Initializing Wavefront to source    
        
        discovered_x[0].push_back(sx);
        discovered_y[0].push_back(sy);
        
       int curx, cury;			/*Current node of BF*/
        int bfturn=0;			/*Level of BF search*/
        


/*********************    
 * Exploring the grid*
 *********************/

   //Run the BF till sink is found (bfdone set to true when sink is found)
    while(!bfdone)
        {
            while(!discovered_x[bfturn%2].empty())
            {
                curx = discovered_x[bfturn%2][0];		/*Take the next point from discovered points*/
                cury = discovered_y[bfturn%2][0];
                discovered_x[bfturn%2].erase(discovered_x[bfturn%2].begin());
                discovered_y[bfturn%2].erase(discovered_y[bfturn%2].begin());

	//Explore node below current node
                if((curx != height-1) && !bfdone)
                    {
                            if(grid[curx +1][cury]==-2)
                            {
                                    grid[curx +1][cury] = wavevalue;
                                    discovered_x[(bfturn+1)%2].push_back(curx +1);
                                    discovered_y[(bfturn+1)%2].push_back(cury);
                            }	

                            if(curx+1==dx && cury==dy)			/*If sink is found, end the search*/
                                    bfdone=true;
                    }

		
		//Explore node to the right of current node

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


	//Explore node above current node

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


	//Explore node to left of current node

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


//If sink is not found and there are no more nodes to explore, end search and return message

		if(!bfdone && discovered_x[0].size()==0 && discovered_x[1].size()==0)
		    {
			std::cout<<"All paths blocked - No route possible\n"<<std::flush;
			bfdone=true;
			grid[dx][dy] = 0;
		    }

            }
            
            bfturn++;
            
//Change the wavevalue after each level of BF
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


/***********************    
 *Backtracking for path*
 ***********************/

    int backtrack_x = dx;		/*Starting backtrack at sink*/
    int backtrack_y = dy;
    int pivot_x = dx;			/*pivot to save pathsegments whenever path takes a turn*/
    int pivot_y = dy;
    
    PathSegment* segment = new PathSegment(dx,dy,dx,dy);
    Path* netpath = new Path();


    //Backtrack till source is found

    while(grid[backtrack_x][backtrack_y]!=0)
    {
        if(prev ==12 || prev==22)
            wavevalue = 2;
        else if(prev ==11 || prev==21)
            wavevalue = 1;    
    


    //Check all four neighbours for previous wavevalue      
        if(((grid[backtrack_x-1][backtrack_y] == wavevalue)||(grid[backtrack_x-1][backtrack_y] == 0))&&(backtrack_x != 0))
			{
				backtrack_x -= 1;
			}
			
        else if(((grid[backtrack_x][backtrack_y-1] == wavevalue)||(grid[backtrack_x][backtrack_y-1] == 0))&&(backtrack_y != 0))
        {
                backtrack_y -= 1;
        }

        else if(((grid[backtrack_x+1][backtrack_y] == wavevalue)||(grid[backtrack_x+1][backtrack_y] == 0))&&(backtrack_x != height-1))
        {
                backtrack_x +=1;
        }

        else if(((grid[backtrack_x][backtrack_y+1] == wavevalue)||(grid[backtrack_x][backtrack_y+1] == 0))&&(backtrack_y != width - 1))
        {
                backtrack_y += 1;
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
       
//Change the wavevalue after each iteration
        if(prev == 11)
            prev = 21;
        else if(prev == 12)
            prev = 11;
        else if(prev == 21)
            prev = 22;
        else if(prev == 22)
            prev = 12;
    }
    
    
     netpath->add_segment(segment);
    bfdone = false;
    discovered_x[0].clear();
    discovered_y[0].clear();
    discovered_x[1].clear();
    discovered_y[1].clear();

    finalpath.push_back(netpath);			/*Save the route in path vector, which will be returned to main*/
}
 
  
};
