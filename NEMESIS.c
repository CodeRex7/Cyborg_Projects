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
*****************************************/

#include <stdlib.h>
#define gridX	13
#define gridY	15
#define EAST	0
#define NORTH	1
#define WEST	2
#define SOUTH	3
#define F	0
#define R	1
#define B	2
#define L	3


//global variables declaration
int no_path = 0;
int dx, dy;
int dir,v_dir;
int dist; //stores the value of the current cordinate in the weighted matrix
int count = 0; //counter for output[]
int output[gridX*gridY]; //the array that the function returns
int temp_x, temp_y;
int c_x, c_y;
int wgrid[gridX][gridY];
int grid[gridX][gridY] = {
					                           250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,
					                           250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250, 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,250,
                                               250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,
                                        };
//Function prototypes
void find_path();
void var_init();
void create_weighted();
void show_weighted();


void main()
{
	memset(output, -1, sizeof(output));
	dir = NORTH;
	int ch,c, i, j;
	dx = 5;
	dy = 11;
	do
	{
		c_x = dx;
		c_y = dy;
		printf("Enter the destination point: ");
		scanf("%d%d", &dx, &dy);
		c=dx;
		dx=9-dy;
		dy=c+8;
		if(grid[dx][dy] > 99)
		{
			no_path = 1;
			printf("Not possible");
			return;
		}
		find_path();
		for(i = 0;i<gridX*gridY;i++)
		{
			switch(output[i])
			{
				case 0:
					printf("F\t");
					break;
				case 1:
					printf("R\t");
					break;
				case 2:
					printf("B\t");
					break;
				case 3:
					printf("L\t");
					break;
			}
		}
		dir=v_dir;
		printf("%d\n", dir);
		printf("do u want to Enter next destination point? (1/0)");
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
		{
			wgrid[temp_x][temp_y] += 2;
			var_init();
			continue;
		}
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

                else if(wgrid[temp_x-1][temp_y] < dist)
                {
                        v_dir = NORTH;
                        output[count] = L;
                        dist = wgrid[temp_x-1][temp_y];
			temp_x -= 1;
			temp_y -= 0;
                }
                else if(wgrid[temp_x+1][temp_y] < dist)
                {
                        v_dir = SOUTH;
                        output[count] = R;
                        dist = wgrid[temp_x+1][temp_y];
			temp_x += 1;
			temp_y += 0;
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
                {
                        wgrid[temp_x][temp_y] += 2;
                        var_init();
                        continue;
                }
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
                {
                        wgrid[temp_x][temp_y] += 2;
                        var_init();
                        continue;
                }
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
                else if(wgrid[temp_x][temp_y+1] < dist)
                {
                        v_dir = EAST;
                        output[count] = R;
                        dist = wgrid[temp_x][temp_y+1];
			temp_x += 0;
			temp_y += 1;
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
                {
                        wgrid[temp_x][temp_y] += 2;
                        var_init();
                        continue;
                }
                count++;
           }

	}
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
			if(grid[i][j] < 100)
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

