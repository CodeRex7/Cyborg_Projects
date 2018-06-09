#define  THRESHOLD 500
#define  S1     A4
#define  S2     A3
#define  S3     A2
#define  S4     A1
#define  S5     A0
#define  Left_Motor_high        8
#define  Left_Motor_low         9
#define  Right_Motor_high       12
#define  Right_Motor_low        13
#define  SPD_MOTOR_L            10
#define  SPD_MOTOR_R            11
int A[5],i;
String cmp_value;

//========================================================================================================
//========================================================================================================
//========================================================================================================

#include <stdlib.h>
#define gridX	8
#define gridY	5
#define EAST	0
#define NORTH	1
#define WEST	2
#define SOUTH	3
#define F	0
#define R	1
#define B	2
#define L	3

//=========================================================================================================
//global variables declaration
int no_path = 0;
int dx, dy;
int dir,v_dir;
int dist;                                                    //stores the value of the current cordinate in the weighted matrix
int count = 0;                                              //counter for output[]
int output[gridX*gridY];                                   //the array that the function returns
int temp_x, temp_y;
int c_x, c_y;
int ch,c, a=0, b=0;
int wgrid[gridX][gridY];
int input[3][2]={2,0,
                 2,2,
                 3,6
                };
int grid[gridX][gridY] = {
					       250,250,250,250,250,
                                               250,  1,  1,  1, 250,
                                               250,  1,  1,  1, 250,
                                               250,  1,  1,  1, 250,
                                               250,  1,  1,  1, 250,
                                               250,  1,  1,  1, 250,
                                               250,  1,  1,  1, 250,
                                               250,250,250,250,250
                                        };

//=======================================================================================

//Function prototypes
void find_path();
void var_init();
void create_weighted();
void show_weighted();
void execute_path();


void setup()
   {
    pinMode(Left_Motor_high,OUTPUT);
    pinMode(Left_Motor_low,OUTPUT);
    pinMode(Right_Motor_high,OUTPUT);
    pinMode(Right_Motor_low,OUTPUT);
    pinMode(SPD_MOTOR_L,OUTPUT);
    pinMode(SPD_MOTOR_R,OUTPUT);
    cmp_value="";
    Serial.begin(9600);
   
   }

void loop()
   {
     //Serial.println("hi NeMeSiS :D :D :D");
     readInput();
     setValues();
 memset(output, -1, sizeof(output));
	dir = NORTH;
	dx = 6;
	dy = 1;
		c_x = dx;
		c_y = dy;
		for(;a<3;a++)
                  {
                    dx=input[a][b++];
                    dy=input[a][b];
                    b=0;
                  
		c=dx;
		dx=6-dy;
		dy=c+1;
		if(grid[dx][dy] > 99)
		{
			no_path = 1;
			Serial.print("Not possible");
			stopM();
		}
		find_path();
		execute_path();
		dir=v_dir;
		Serial.print(dir);
		memset(output, -1, sizeof(output));
                Serial.print("Reached the destination");
                stopM();
}
   }


void readInput()
   {
     A[0]=analogRead(S1);
     A[1]=analogRead(S2);
     A[2]=analogRead(S3);
     A[3]=analogRead(S4);
     A[4]=analogRead(S5);
   }

void setValues()
   {
     cmp_value="";
     for(i=0;i<5;i++)
      {
        //Serial.print(A[i]);
        //Serial.print("\t");
       if(A[i]>THRESHOLD)
      cmp_value+="W";
     else
      cmp_value+="B"; 
      }
      //Serial.print(cmp_value);
      //Serial.print("\t");
   }

void processValues()   
   {
     if(cmp_value=="BBWBB" || cmp_value=="BWWWB")
         return;//Serial.println("bad function call");
   //    gofwd();
     else if(cmp_value=="BBWWW" || cmp_value=="BBBWW" || cmp_value=="BBBWB"|| cmp_value=="BBWWB")
       goright();
     else if(cmp_value=="WWWBB"|| cmp_value=="WWBBB" || cmp_value=="BWBBB"|| cmp_value=="BWWBB")
       goleft();
        }

void gofwd()
   {
     Serial.print("GOING forward\n");
     while(1)
     {
     digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,150);
     analogWrite(SPD_MOTOR_R,150);
     delay(100);
    // Serial.print("GOING forward\n");
      readInput();
     setValues();
     processValues();
     if(cmp_value=="BWWWW"||cmp_value=="WWWWW"||cmp_value=="WWWWB")
     {
        digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,0);
     analogWrite(SPD_MOTOR_R,0);
     
     Serial.print("reached checkpoint");
           break;
     }
     }
     Serial.println("out of fwd");
     delay(1000);
   }
   
void goback()
{
  do
     {
     digitalWrite(Left_Motor_high,LOW);
     digitalWrite(Left_Motor_low,HIGH);
     digitalWrite(Right_Motor_high,LOW);
     digitalWrite(Right_Motor_low,HIGH);
     analogWrite(SPD_MOTOR_L,150);
     analogWrite(SPD_MOTOR_R,150);
     delay(100);
     //Serial.print("GOING BACK\n");
      readInput();
     setValues();
     processValues();
     if(cmp_value=="WWWWW"||cmp_value=="BWWWW"||cmp_value=="WWWWB")
          {
        digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,0);
     analogWrite(SPD_MOTOR_R,0);
     delay(1000);
     Serial.print("reached checkpoint");
            break;
     }
     }while(1);
}

void goleft()

   {
     digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,60);
     analogWrite(SPD_MOTOR_R,130);
     delay(50);
     Serial.print("GOING left\n");
   }  


void goright()
   {
     digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,130);
     analogWrite(SPD_MOTOR_R,60);
     delay(50);
     Serial.print("GOING right\n");
   }


   void stopM()
   {
     digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,0);
     analogWrite(SPD_MOTOR_R,0);
     delay(10000);
     Serial.print("blinking\n");
   }
     
     void gosharpright()
     {
       digitalWrite(Left_Motor_high,HIGH);
       digitalWrite(Left_Motor_low,LOW);
       digitalWrite(Right_Motor_high,HIGH);
       digitalWrite(Right_Motor_low,LOW);
       analogWrite(SPD_MOTOR_L,150);
       analogWrite(SPD_MOTOR_R,150);
       delay(60);
       Serial.print("GOING SHARP right\n");
       while(1)
       {
         digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,LOW);
     digitalWrite(Right_Motor_low,HIGH);
     analogWrite(SPD_MOTOR_L,120);
     analogWrite(SPD_MOTOR_R,100);
     delay(50);
     readInput();
     setValues();
     //Serial.print("GOING SHARP RIGHT\n");
      digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,0);
     analogWrite(SPD_MOTOR_R,0);
     delay(50);
     if(cmp_value=="BWWWB"||cmp_value=="BBWBB")
           break;
       }
      allign();
      gofwd();
      Serial.println("Why am i here???/ ?/ .svacn");
     }
     
     void gosharpleft()
     {
       digitalWrite(Left_Motor_high,HIGH);
       digitalWrite(Left_Motor_low,LOW);
       digitalWrite(Right_Motor_high,HIGH);
       digitalWrite(Right_Motor_low,LOW);
       analogWrite(SPD_MOTOR_L,150);
       analogWrite(SPD_MOTOR_R,150);
       delay(60);
       Serial.print("GOING SHARP LEFT\n");
       do
       {
         digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     digitalWrite(Left_Motor_high,LOW);
     digitalWrite(Left_Motor_low,HIGH);
     analogWrite(SPD_MOTOR_L,120);
     analogWrite(SPD_MOTOR_R,100);
      delay(50);
     readInput();
     setValues();
    // Serial.print("GOING SHARP LEFT\n");
     digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,0);
     analogWrite(SPD_MOTOR_R,0);
     delay(50);
     if(cmp_value=="BWWWB" || cmp_value=="BBWBB")
           break;
       }while (1);
       allign();
       gofwd();
     }
     
     void allign()
     {
       readInput();
       setValues();
       if(cmp_value=="BBWBB" || cmp_value=="BWWWB" || cmp_value=="WWWWW")
       {
         digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,75);
     analogWrite(SPD_MOTOR_R,75);
     delay(50);
       }
     else if(cmp_value=="BBWWW" || cmp_value=="BBBWW" || cmp_value=="BBBWB"|| cmp_value=="BBWWB"||cmp_value=="BWWWW")
       {
         digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,75);
     analogWrite(SPD_MOTOR_R,50);
     delay(50);
       }
     else if(cmp_value=="WWWBB"|| cmp_value=="WWBBB" || cmp_value=="BWBBB"|| cmp_value=="BWWBB"|| cmp_value=="WWWWB")
       {
         digitalWrite(Left_Motor_high,HIGH);
     digitalWrite(Left_Motor_low,LOW);
     digitalWrite(Right_Motor_high,HIGH);
     digitalWrite(Right_Motor_low,LOW);
     analogWrite(SPD_MOTOR_L,50);
     analogWrite(SPD_MOTOR_R,75);
     delay(50);
       }
       
     }
    
//===============================================================
//===============================================================

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
			v_dir = SOUTH;
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
                        v_dir = EAST;
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
                        v_dir = WEST;
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
                else if(wgrid[temp_x+1][temp_y] < dist)
                {
                        v_dir = NORTH;
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
//==================================================
//==================================================

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
//========================================================
//========================================================

void show_weighted()
{
	int i, j;
        for(i=0;i<gridX;i++)
        {
                for(j=0;j<gridY;j++)
                {
			Serial.print("\t");
                        Serial.print(wgrid[i][j]);
                }
		Serial.print("\n");

        }


}
//=======================================================
//=======================================================

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
//========================================================
//========================================================
     
     void execute_path()
{
    int i;
    for(i = 0;i<gridX*gridY;i++)
    Serial.println(output[i]);
for(i = 0;i<gridX*gridY;i++)
		{
 
			switch(output[i])
			{
  
				case 0:
                                          Serial.print("F\t");
                                          gofwd();
                                          Serial.print("out of fwd again");
					  break;
                                          
				case 1:
					Serial.print("R\t");  
                                         gosharpright();
                                         Serial.print("out of sright");
					break;
				case 2:
					Serial.print("B\t");
                                        goback();
					break;
				case 3:
					Serial.print("L\t");
                                        goleft();
					break;
			}
        }
}
