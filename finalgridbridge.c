/**************************************
*FLOOD FILL GREEDY ALGORITHM
*NEME$I$
*IITKGP-EMBETRONIX-KSHITIJ 2k16
*-------------------------------------------------------------------------------------
*Conventions:
*East-0, North-1 and so on.
*not visited = 0;
*visited = 1;
*block = 200;
*boundaries = 250;
*the diagonnally connected nodes = 100
*The MATRIX( 9X9 ) is set according to coordinate system where the origin is  grid[9][8] as (0,0)
								And grid[1][1] as (-7,8) and so on………
*the bot starts from origin grid[9][8] and initially heading north....

*****************************************/

#include <stdlib.h>
#define gridX	11
#define gridY	11
#define EAST	0
#define NORTH	1
#define WEST	2
#define SOUTH	3
#define F	0
#define R	1
#define B	2
#define L	3
#define D   4


//global variables declaration
int no_path = 0;
int dx, dy;
int dir,v_dir;
int dist; //stores the value of the current cordinate in the weighted matrix
int count = 0; //counter for output[]
int output[gridX*gridY]; //the array that the function returns
int temp_x, temp_y;
int c_x, c_y;
int dest_x,dest_y;
int wgrid[gridX][gridY];
int grid[gridX][gridY] = {
					                           250,250,250,250,250,250,250,250,250,250,250,
					                           250, 1 , 1 , 1 , 1 , 1 ,200, 1 , 1 , 1 ,250,
                                               250, 1 ,200, 1 , 1 , 1 , 1 ,200, 1 , 1 ,250,
                                               250, 1 , 1 , 1 ,200, 1 , 1 , 1 , 1 , 1 ,250,
                                               250,100,200, 1 , 1 , 1 ,200, 1 ,200, 1 ,250,
                                               250,200,100,200, 1, 200, 1 , 1 , 1 , 1 ,250,
                                               250, 1 ,200,200, 1 , 1 , 1 ,200, 1 , 1 ,250,
                                               250,200, 1 ,200, 1 ,200, 1 , 1 ,200,100,250,
                                               250, 1 ,100,200, 1 , 1 , 1 , 1 ,100,200,250,
                                               250, 1 ,200,100, 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250,250,250,250,250,250,250,250,250,250,250,
                                        };
//Function prototypes
void find_path();
void var_init();
void create_weighted();             //creates weighted matrix
void show_weighted();               //prints it
void execute_path();                //prints the final path of the bot
void shortest_path();               //for the normal grid follower
void bridge_path();                 //for the bridge part


void main()
{
	memset(output, -1, sizeof(output));
	dir = NORTH;
	int ch,i, j;
	dx = 9;                //to set the origin as i wished earlier
	dy = 8;                //to set the origin as i wished earlier
	do
	{
		c_x = dx;
		c_y = dy;
		printf("Enter the destination point: ");
		scanf("%d%d", &dx, &dy);
		dest_x=dx;              //just for displaying the final coordinate
		dest_y=dy;              //just for displaying the final coordinate
		dx=9-dest_y;            //to set the coordinates as i wished earlier
		dy=dest_x+8;            //to set the coordinates as i wished earlier
		if(grid[dx][dy] > 99)
		{
			no_path = 1;
			printf("Not possible");
			return;
		}                                   //as no path is available as the destination is an antinode
		find_path();
		execute_path();
		dir=v_dir;
		printf("THE BOT IS HEADED TOWARDS %d\n\n", dir);
		printf("Do U Want To Enter Next Destination Point? (1/0)");
		scanf("%d", &ch);
		getchar();
		printf("\n\n");
		memset(output, -1, sizeof(output));
	}while(ch!=0);

}



void find_path()
{
	create_weighted();
	var_init();
	show_weighted();
	shortest_path();
}



void var_init()
{
	//c_x = 0;
	//c_y = 0;
	temp_x = c_x;
	temp_y = c_y;
	dist = wgrid[c_x][c_y];
	count = 0;
	v_dir=dir;
}


void show_weighted()
{
	int i, j;
        for(i=0;i<gridX;i++)
        {
                for(j=0;j<gridY;j++)
                {
			printf("%d\t", wgrid[i][j]);
                }
		printf("\n");

        }


}


void create_weighted()
{
	int i, j;
	for(i=0;i<gridX;i++)
	{
		for(j=0;j<gridY;j++)
		{
			if(grid[i][j] < 150)
			{
				wgrid[i][j] = fabs(dx - i) + fabs(dy - j);
			}

			else
			{
				wgrid[i][j] = grid[i][j];
			}
		}
	}
}


void execute_path()
{
    int i;
for(i = 0;i<gridX*gridY;i++)
		{
			switch(output[i])
			{
				case 0:
					printf("F->");
					break;
				case 1:
					printf("R->");
					break;
				case 2:
					printf("B->");
					break;
				case 3:
					printf("L->");
					break;
                case 4:
                    printf("D->");
                    break;
			}
        }
        printf("REACHED DESTINATION(%d,%d)\n",dest_x,dest_y);
}


void shortest_path()
{
    while(dist!=0)
	{
	   if(v_dir == SOUTH)
	   {
		if(wgrid[temp_x+1][temp_y] < dist)
		{
			v_dir = SOUTH;
			output[count] = F;
			dist = wgrid[temp_x+1][temp_y];
			temp_x += 1;
			temp_y += 0;
		}

		else if(wgrid[temp_x][temp_y+1] < dist)
		{
			v_dir = EAST;
			output[count] = L;
			dist = wgrid[temp_x][temp_y+1];
			temp_x += 0;
			temp_y += 1;
		}

		else if(wgrid[temp_x][temp_y-1] < dist)
		{
			v_dir = WEST;
			output[count] = R;
			dist = wgrid[temp_x][temp_y-1];
			temp_x -= 0;
			temp_y -= 1;
		}
		else if(wgrid[temp_x-1][temp_y] < dist)
		{
			v_dir = NORTH;
			output[count] = B;
			dist = wgrid[temp_x-1][temp_y];
			temp_x -= 1;
			temp_y -= 0;
		}
		else
                bridge_path();
                count++;
	   }


	   else if(v_dir == EAST)
           {
                if(wgrid[temp_x][temp_y+1] < dist)
                {
                        v_dir = EAST;
                        output[count] = F;
                        dist = wgrid[temp_x][temp_y+1];
			temp_x += 0;
			temp_y += 1;
             	}

                else if(wgrid[temp_x+1][temp_y] < dist)
                {
                        v_dir = SOUTH;
                        output[count] = R;
                        dist = wgrid[temp_x+1][temp_y];
			temp_x += 1;
			temp_y += 0;
                }

                else if(wgrid[temp_x-1][temp_y] < dist)
                {
                        v_dir = NORTH;
                        output[count] = L;
                        dist = wgrid[temp_x-1][temp_y];
			temp_x -= 1;
			temp_y -= 0;
                }
                else if(wgrid[temp_x][temp_y-1] < dist)
                {
                        v_dir = WEST;
                        output[count] = B;
                        dist = wgrid[temp_x][temp_y-1];
			temp_x -= 0;
			temp_y -= 1;
                }
                else
                bridge_path();
                count++;
	   }

	   else if(v_dir == WEST)
           {

                if(wgrid[temp_x][temp_y-1] < dist)
                {
                        v_dir = WEST;
                        output[count] = F;
                        dist = wgrid[temp_x][temp_y-1];
			temp_x -= 0;
			temp_y -= 1;
                }

                else if(wgrid[temp_x+1][temp_y] < dist)
                {
                        v_dir = SOUTH;
                        output[count] = L;
                        dist = wgrid[temp_x+1][temp_y];
			temp_x += 1;
			temp_y += 0;
                }
                else if(wgrid[temp_x-1][temp_y] < dist)
                {
                        v_dir = NORTH;
                        output[count] = R;
                        dist = wgrid[temp_x-1][temp_y];
			temp_x -= 1;
			temp_y -= 0;
                }
                else if(wgrid[temp_x][temp_y+1] < dist)
                {
                        v_dir = EAST;
                        output[count] = B;
                        dist = wgrid[temp_x][temp_y+1];
			temp_x += 0;
			temp_y += 1;
                }

                else
                    bridge_path();
                    count++;
	   }

	   else if(v_dir == NORTH)
           {
                if(wgrid[temp_x-1][temp_y] < dist)
                {
                        v_dir = NORTH;
                        output[count] = F;
                        dist = wgrid[temp_x-1][temp_y];
			temp_x -= 1;
			temp_y -= 0;
                }

                else if(wgrid[temp_x][temp_y+1] < dist)
                {
                        v_dir = EAST;
                        output[count] = R;
                        dist = wgrid[temp_x][temp_y+1];
			temp_x += 0;
			temp_y += 1;
                }

                else if(wgrid[temp_x][temp_y-1] < dist)
                {
                        v_dir = WEST;
                        output[count] = L;
                        dist = wgrid[temp_x][temp_y-1];
			temp_x -= 0;
			temp_y -= 1;
                }
                else if(wgrid[temp_x+1][temp_y] < dist)
                {
                        v_dir = SOUTH;
                        output[count] = B;
                        dist = wgrid[temp_x+1][temp_y];
			temp_x += 1;
			temp_y += 0;
                }
                else
                bridge_path();
                count++;
	   }
	}
}


void bridge_path()
{
			/*wgrid[temp_x][temp_y] += 2;
			var_init();
			continue;*/
			if(grid[temp_x][temp_y]==100)
            {
                if(grid[temp_x+1][temp_y+1]==100)
                {
                    if(wgrid[temp_x+1][temp_y+1]<=wgrid[temp_x][temp_y])
                    {
                        if(v_dir== NORTH || v_dir== SOUTH)
                            v_dir= EAST;
                        else
                            v_dir= SOUTH;
                        output[count]= D;
                        wgrid[temp_x][temp_y]+=2;
                        dist=wgrid[temp_x+1][temp_y+1];
                        temp_x+=1;
                        temp_y+=1;
                        count++;
                        shortest_path();
                    }
                    else
                    {
                        wgrid[temp_x][temp_y]+=3;
                        var_init();
                        shortest_path();
                    }
                }
                else if(grid[temp_x-1][temp_y-1]==100)
                {
                    if(wgrid[temp_x-1][temp_y-1]<=wgrid[temp_x][temp_y])
                    {
                        if(v_dir== NORTH || v_dir== SOUTH)
                            v_dir= WEST;
                        else
                            v_dir= NORTH;
                        output[count]= D;
                        wgrid[temp_x][temp_y]+=2;
                        dist=wgrid[temp_x-1][temp_y-1];
                        temp_x-=1;
                        temp_y-=1;
                        count++;
                        shortest_path();
                    }
                    else
                    {
                        wgrid[temp_x][temp_y]+=3;
                        var_init();
                        shortest_path();
                    }
                }
                else if(grid[temp_x-1][temp_y+1]==100)
                {
                    if(wgrid[temp_x-1][temp_y+1]<=wgrid[temp_x][temp_y])
                    {
                        if(v_dir== NORTH || v_dir== SOUTH)
                            v_dir= EAST;
                        else
                            v_dir= NORTH;
                        output[count]= D;
                        wgrid[temp_x][temp_y]+=2;
                        dist=wgrid[temp_x-1][temp_y+1];
                        temp_x-=1;
                        temp_y+=1;
                        count++;
                        shortest_path();
                    }
                    else
                    {
                        wgrid[temp_x][temp_y]+=3;
                        var_init();
                        shortest_path();
                    }
                }
               else if(grid[temp_x+1][temp_y-1]==100)
                {
                    if(wgrid[temp_x+1][temp_y-1]<=wgrid[temp_x][temp_y])
                    {
                        if(v_dir== NORTH || v_dir== SOUTH)
                            v_dir= WEST;
                        else
                            v_dir= SOUTH;
                        output[count]= D;
                        wgrid[temp_x][temp_y]+=2;
                        dist=wgrid[temp_x+1][temp_y-1];
                        temp_x+=1;
                        temp_y-=1;
                        count++;
                        shortest_path();
                    }
                    else
                    {
                        wgrid[temp_x][temp_y]+=3;
                        var_init();
                        shortest_path();
                    }
                }
            }
            else
            {
                wgrid[temp_x][temp_y]+=3;
                var_init();
                shortest_path();
            }
}



