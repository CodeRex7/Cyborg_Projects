int thr=750;
int thr_b=750;

int traversed[9][7];              // traversed locations
int w[9][7];                          //weighted matrix
int S[9][7];                          //super matrix
int current_x=1;
int current_y=1;
int destination_y=2;
int destination_x=1;
int dir=4;
int shortest_path_count=0;
int cx,cy;
//=================================
int block_count=1;
int block_info[5][5];
int block_sort[5][5];
int block_final[5][5];
int position_blocked=0;
int replaced=0;
//============================================
int x0 = A8;
int x1 = A9;
int x2 = A10;
int x3 = A11;
int x4 = A12;

int base_b=50;
int kp_b=10;
int correction_b;
int error_b;
int b[7]={0,0,0,0,0};
int divisor_b;
//============================================

//=================================
#include <LiquidCrystal.h>
LiquidCrystal lcd(42, 44, 46, 48, 50, 52);

//=================================
#define trigger 30
#define echo 32
//=================================
//======================================
int lift[2]={23,25};
int grab[2]={27,29};
int lift_speed=7;
int grab_speed=6;
int grab_state=0;
//======================================
//=================================
int H0 = 39;
int H1 = 41;
int H2 = 43;
int H3 = 45;
int H4 = 47;
int H5 = 49;
int H6 = 51;
int H7 = 53;
double height=0;
int h[8]={0,0,0,0,0,0,0,0};

//=================================
int S0 = A6;
int S1 = A5;
int S2 = A4;
int S3 = A3;
int S4 = A2;
int S5 = A1;
int S6 = A0;
int motor_R [2]={35,37};
int motor_L [2]={31,33};
int speed_R =4;
int speed_L =5;
//==============================

float error=0;
float prev_error;
int correction;
float divisor;
float P;
int node=0;
int kp = 20;
int base = 140;
 
//===============================

int s[7]={0,0,0,0,0,0,0};

int path[30];

//=================================
void setup()
{
      for (int i =0;i<2;i++)
    {pinMode(motor_R[i],OUTPUT);}
    
     for (int i =0;i<2;i++)
    {pinMode(motor_L[i],OUTPUT);}
    
     pinMode(speed_L,OUTPUT);
     pinMode(speed_R,OUTPUT);
    
      pinMode (trigger,OUTPUT);
      pinMode (echo,INPUT);
          lcd.begin(16, 2);
          Serial.begin(9600);
          
          traversed[1][1]=1;
          
          
        for (int i =0;i<2;i++)
                    {pinMode(lift[i],OUTPUT);}
        for (int i =0;i<2;i++)
                   {pinMode(grab[i],OUTPUT);}
       pinMode(lift_speed,OUTPUT);
       pinMode(grab_speed,OUTPUT);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* for(int i=0;i<9;i++)
       {
         S[i][5]=200;
         traversed[i][5]=200;
          S[i][4]=200;
         traversed[i][4]=200;
       }
        for(int i=0;i<7;i++)
       {
         S[7][i]=200;
         traversed[7][i]=200;
          S[6][i]=200;
         traversed[6][i]=200;
       }
  */
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
follow_line();
}


void loop()
{
      while(block_count<=5)
        {    
           if (traversed[destination_x][destination_y]==1) generate_destination();
           
           
             shortest_path();
             execute_path_USS();
             
             
        }
             
      sorting();
      
     // all_blockage_remove();
      arrange();
      analogWrite(speed_L, 0); 
     analogWrite(speed_R,0 ); 
     

     delay(500000);

}
//==================================================

//=========================================
void turn_left()
{    int spd=80;
      int del=400;
      if (grab_state=1) {spd=120;del=600;}
     digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],0);
     digitalWrite(motor_L[0],1); 
     analogWrite(speed_L, 100); 
     analogWrite(speed_R,100); 
     delay(90);
     digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],1);
     digitalWrite(motor_L[0],0); 
     analogWrite(speed_L, spd); 
     analogWrite(speed_R,spd );
     delay(del);
    while(analogRead(S4)<thr)
        {
        digitalWrite(motor_R[1],0);
        digitalWrite(motor_R[0],1);
       digitalWrite(motor_L[1],1);
       digitalWrite(motor_L[0],0); 
       analogWrite(speed_L, 100); 
       analogWrite(speed_R,100 );
        }
       analogWrite(speed_L, 0); 
       analogWrite(speed_R,0 );
     
      delay(100);

     
}
//================================================
void turn_right()
{
       int spd=80;
       int del=400;
      if (grab_state=1) {spd=120;del=600;}
     digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],0);
     digitalWrite(motor_L[0],1); 
     analogWrite(speed_L, 100); 
     analogWrite(speed_R,100 ); 
     delay(90);
     digitalWrite(motor_R[1],1);
     digitalWrite(motor_R[0],0);
     digitalWrite(motor_L[1],0);
     digitalWrite(motor_L[0],1); 
     analogWrite(speed_L, spd); 
     analogWrite(speed_R,spd );
     delay(del);
    while(analogRead(S2)<thr)
        {
        digitalWrite(motor_R[0],0);
        digitalWrite(motor_R[1],1);
       digitalWrite(motor_L[0],1);
       digitalWrite(motor_L[1],0); 
       analogWrite(speed_L, 100); 
       analogWrite(speed_R,100 );
        }
       analogWrite(speed_L, 0); 
       analogWrite(speed_R,0 );


      delay(100);
    
}
//=========================================
int follow_line()
{
  while (1)
  {
s[0]=analogRead(S0);
s[1]=analogRead(S1);
s[2]=analogRead(S2);
s[3]=analogRead(S3);
s[4]=analogRead(S4);
s[5]=analogRead(S5);
s[6]=analogRead(S6);
  error=0;     
  divisor=0;
  
  for(int i =0;i<7;i++)
        {
          if (s[i]>thr)
                  {s[i]=1;}
                  else s[i]=0;
        }
        
     for(int i =0;i<7;i++)
      {
          if (s [i]==1)
                  {error=error+i+1; divisor++;}
        }
  
     error=error/divisor;
     error=error-4;
     
     correction =kp*error;

     digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],0);
     digitalWrite(motor_L[0],1);

    if (divisor==6)
         {
                 analogWrite(speed_L, 0); 
                 analogWrite(speed_R, 0); 
                 delay(10);
                 analogWrite(speed_L, 200); 
                 analogWrite(speed_R, 200); 
                  delay(200);
             return (1);
                
         }
     else{
     
           if (correction>base){correction=base;}
                 analogWrite(speed_L, base+correction); 
                 analogWrite(speed_R, base-correction); 
     }
     
     }
}
//=================================================================================
void execute_path()
{
 int j,k,t,temp;
 t=0;
	for (int n =0;n<10;n++)
	{
		if (dir==1)
			{
					if (path[n]==1) {			                  		  }
				else if (path[n]==2) {turn_right(); 		        dir=2;         }
				else if (path[n]==4) {turn_left(); 		        dir=4;         }
				else if (path[n]==3) {turn_left();turn_left();	dir=3;         }
			}
         else if (dir==2)
			{
					if (path[n]==2) {				                          }
				else if (path[n]==3) {turn_right(); 		        dir=3;         }
				else if (path[n]==1) {turn_left(); 	                dir=1;         }
				else if (path[n]==4) {turn_left();turn_left();       dir=4;         }
			}
         else if (dir==3)
			{
					if (path[n]==3) {				                          }
				else if (path[n]==4) {turn_right(); 		        dir=4;         }
				else if (path[n]==2) {turn_left()	;                       dir=2;         }
				else if (path[n]==1) {turn_left();turn_left();	dir=1;         }
			}
	 else if (dir==4)
			{
  				       if (path[n]==4) {				                                  }
				else if (path[n]==1) {turn_right(); 	               dir=1;          }
				else if (path[n]==3) {turn_left();                      dir=3;           }
				else if (path[n]==2) {turn_left();turn_left();      dir=2;          }
			}
                if (path[n]==0) 
                {
                 break;
                }
                

                            temp=follow_line();
                                      if (dir==1)  {current_x=current_x+1;}
                             else  if (dir==2)  {current_y=current_y-1;}
                             else  if (dir==3)  {current_x=current_x-1;}
                             else  if (dir==4)  {current_y=current_y+1;}      
//                               Serial.print(current_x); Serial.print("   ");  Serial.println(current_y);

                        
   }
}
//===============================================================================
void generate_destination()
{
      int curr_x=cx;
      int curr_y=cy;
      int flag=1;
//     if (traversed[destination_x][destination_y]==1)
//     {

        while (flag ==1)
                {
                    if(curr_x%2==1)
                                {
                                  if (curr_y<5)
                                          {  destination_y=curr_y+1;      destination_x=curr_x; }
                                  else
                                          {   destination_x=curr_x+1;      destination_y=curr_y;}
                                 }
                     else
                            {
                                if(curr_y==1)
                                          { destination_x=curr_x+1;     destination_y=curr_y;}
                                 else
                                          {  destination_y=curr_y-1;    destination_x=curr_x; }
                            } 
                                  if (traversed[destination_x][destination_y]>=1)
                                                  {curr_x = destination_x;  curr_y = destination_y;}
                    else flag=0;
  
              }  
//     }
//     lcd.setCursor(0,1);
//     lcd.print(destination_x); lcd.setCursor(4,1); lcd.print(destination_y);
}

//========================================================================

int check_next_node()
{
  int ar[10];
       analogWrite(speed_L, 0); 
       analogWrite(speed_R,0 );
   int temp;
   float distance,duration;
   for(int n=0;n<10;n++)
{
  digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(trigger,LOW);

  duration=pulseIn(echo,HIGH);
  distance =duration/29.1;
  distance=distance/2;
//  lcd.clear(); 
//   lcd.print(distance);
  
   //===============
   digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(trigger,LOW);
  duration=pulseIn(echo,HIGH);
  //==================
ar[n]=distance;
}   

for(int i=0;i<10;i++)
     {   int p=0;
             for(int j=i;j<10;j++)
             {
                     if(ar[i]>ar[j])
                    {
                                    p=ar[i];
                                    ar[i]=ar[j];
                                     ar[j]=p;
                      }
                      }
                    }
       distance=ar[5];

  if(distance<25 ) {
                              //  Serial.println("block found");
                                return 1; 
                            }
             else return 0;
              
 
}

//============================================

//=================================================================================
void execute_path_USS()
{
 int j,k,t,temp, block;
cx=current_x;
cy=current_y;
	for (int n =0;n<30;n++)
	{
          block=0;
		if (dir==1)
			{
					if (path[n]==1) {			                  		  }
				else if (path[n]==2) {turn_right(); 		        dir=2;         }
				else if (path[n]==4) {turn_left(); 		        dir=4;         }
				else if (path[n]==3) {turn_left();turn_left();	dir=3;         }
			}
         else if (dir==2)
			{
					if (path[n]==2) {				                          }
				else if (path[n]==3) {turn_right(); 		        dir=3;         }
				else if (path[n]==1) {turn_left(); 	                dir=1;         }
				else if (path[n]==4) {turn_left();turn_left();       dir=4;         }
			}
         else if (dir==3)
			{
					if (path[n]==3) {				                          }
				else if (path[n]==4) {turn_right(); 		        dir=4;         }
				else if (path[n]==2) {turn_left()	;                       dir=2;         }
				else if (path[n]==1) {turn_left();turn_left();	dir=1;         }
			}
	 else if (dir==4)
			{
  				       if (path[n]==4) {				                                   }
				else if (path[n]==1) {turn_right(); 	               dir=1;           }
				else if (path[n]==3) {turn_left();                       dir=3;           }
				else if (path[n]==2) {turn_left();turn_left();      dir=2;           }
			}
         if (path[n]==0) 
                {
                      break;
                }
        block=check_next_node();
         if (block==0)                                                             // no block
                          {
                            temp=follow_line();
                                      if (dir==1)  {current_x=current_x+1;cx=cx+1;}
                             else  if (dir==2)  {current_y=current_y-1;cy=cy-1;}
                             else  if (dir==3)  {current_x=current_x-1;cx=cx-1;}
                             else  if (dir==4)  {current_y=current_y+1;cy=cy+1;}      
                                  traversed[current_x][current_y]=1;
                       //        Serial.print(current_x); Serial.print("   ");  Serial.println(current_y);
                          }
                           else {                                         //    Serial.print("block found at: ");                 // block detected
                                              if (dir==1)   {traversed[current_x+1][current_y]=1;   S[current_x+1][current_y]=200;  Serial.print(current_x+1); Serial.print("   ");  Serial.println(current_y); measure_height();cx=cx+1;}
                                     else  if (dir==2)    {traversed[current_x][current_y-1]=1;    S[current_x][current_y-1]=200;  Serial.print(current_x); Serial.print("   ");  Serial.println(current_y-1);  measure_height();cy=cy-1;}
                                     else  if (dir==3)    {traversed[current_x-1][current_y]=1;    S[current_x-1][current_y]=200;  Serial.print(current_x-1); Serial.print("   ");  Serial.println(current_y);  measure_height();cx=cx-1;}
                                     else  if (dir==4)    {traversed[current_x][current_y+1]=1;   S[current_x][current_y+1]=200;  Serial.print(current_x); Serial.print("   ");  Serial.println(current_y+1); measure_height();cy=cy+1;}
                                        break;   
                                   }
    }
}
//===============================================================================
int mod(int a)
{
     if(a<0) return -a;
     else    return a;
}
//===============================================================================
void weighted()
{
	for(int n=0;n<9;n++)
	{
		for(int m=0;m<7;m++)
			{w[n][m]=S[n][m];}
	}

//boundary //
for(int j=0;j<7;j++)
      {   w[0][j]=200;        w[8][j]=200;   }
for(int ho=0;ho<9;ho++)
      {  w[ho][0]=200;     w[ho][6]=200;}
//      w[2][2]=200;
 //     w[3][4]=200;
//     w[1][3]=200;  traversed[1][3]=1;

 // weights //
for(int j=0;j<9;j++)
        {
                           for(int k=0;k<7;k++)
                        { if(w[j][k]!=200)   {  w[j][k]=mod(destination_x-j)+mod(destination_y-k); }}
        }
}
//==================================================================================

void shortest_path()
{ shortest_path_count=0;
        weighted();
     /*   	for(int n=0;n<7;n++)
	{
		for(int m=0;m<9;m++)
			{cout<<w[m][n]<<"\t";
            }
            cout<<"\n";
	}*/

	int t=0,j=current_x,k=current_y;
	int v_dir=dir;


	while(w[j][k]!=0&&shortest_path_count<60)
 	{
        shortest_path_count++;
     	if(v_dir==1)
		    {
	    	       if(  w[j][k]==w[j+1][k]+1)         { path[t]=1;       j++;                         t++;}
		      else if(  w[j][k]==w[j][k-1]+1)         { path[t]=2;       k--;         v_dir=2;        t++;}
		      else if(  w[j][k]==w[j][k+1]+1)         { path[t]=4;       k++;         v_dir=4;        t++;}
		      else if(  w[j][k]==w[j-1][k]+1)         { path[t]=3;       j--;         v_dir=3;        t++;}
		      
		      else {
			                 w[j][k]=w[j][k]+2;
				             	 t=0;
	        	           j=current_x;           k=current_y;         v_dir=dir;
	       		      }

    		       }
 	   else if(v_dir==2)
	    	      {
    	    	            if(    w[j][k]==w[j][k-1]+1)         { path[t]=2;       k--;                        t++;}
  	         	    else if(     w[j][k]==w[j+1][k]+1)         { path[t]=1;       j++;        v_dir=1;        t++;}
		              else if(     w[j][k]==w[j-1][k]+1)         { path[t]=3;       j--;        v_dir=3;        t++;}
	                else if(     w[j][k]==w[j][k+1]+1)         { path[t]=4;       k++;        v_dir=4;        t++;}
                  else   {
			                           w[j][k]=w[j][k]+2;
				                         t=0;
	            	                 j=current_x;       k=current_y;        v_dir=dir;
	                      }
	   		}
	     else if(v_dir==3)
	  	      {
	        	     if(    w[j][k]==w[j-1][k]+1)        { path[t]=3;     j--;                       t++;}
	    	    else if(    w[j][k]==w[j][k-1]+1)        { path[t]=2;     k--;         v_dir=2;      t++;}
    		    else if(    w[j][k]==w[j][k+1]+1)        { path[t]=4;     k++;         v_dir=4;      t++;}
    		    else if(    w[j][k]==w[j+1][k]+1)        { path[t]=1;     j++;         v_dir=1;      t++;}
                     else {
	    	    	                  w[j][k]=w[j][k]+2;
				                        t=0;
	    	                        j=current_x;       k=current_y;       v_dir=dir;
    	    	                }

  	   		}
    	else if(v_dir==4)
 	 		{
			             if(   w[j][k]==w[j][k+1]+1)         { path[t]=4;       k++;                       t++;}
		          else if(   w[j][k]==w[j+1][k]+1)         { path[t]=1;       j++;         v_dir=1;      t++;}
	            else if(   w[j][k]==w[j-1][k]+1)         { path[t]=3;       j--;         v_dir=3;      t++;}
	            else if(    w[j][k]==w[j][k-1]+1)        { path[t]=2;       k--;         v_dir=2;      t++;}
	            else {
	    	                           w[j][k]=w[j][k]+2;
					                         t=0;
    	                          	 j=current_x;         k=current_y;         v_dir=dir;
        	 	   }
    		          }
 
 	}
 if(shortest_path_count==60)
 traversed[destination_x][destination_y]=1;
 	path[t]=0;


//                                           for (int h; path[h]!=0;h++)
//                                                     {
//                                                              // lcd.print(path[h]);lcd.print(">");
//                                                               Serial.print(path[h]);
//
//                                                     }Serial.println();

}
//============================================================================
boolean all_traversed()
{
	for(int i=1;i<=7;i++)
	{
		for(int j=1;j<=5;j++)
		{
			if(traversed[i][j]==0)
             return true;
              
		}
	}
return false;	
}
//================================================================================
//==============================================================================
//==============================================================================
void three_cm_proximity()
{
    while (proximity()>3)
    {
      s[0]=analogRead(S0);
s[1]=analogRead(S1);
s[2]=analogRead(S2);
s[3]=analogRead(S3);
s[4]=analogRead(S4);
s[5]=analogRead(S5);
s[6]=analogRead(S6);
  error=0;     
  divisor=0;
  
  for(int i =0;i<7;i++)
        {
          if (s[i]>thr)
                  {s[i]=1;}
                  else s[i]=0;
        }
        
     for(int i =0;i<7;i++)
      {
          if (s [i]==1)
                  {error=error+i+1; divisor++;}
        }
  
     error=error/divisor;
     error=error-4;
     
     correction =kp*error;

     digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],0);
     digitalWrite(motor_L[0],1);

        
     if (correction>50){correction=50;}
                 analogWrite(speed_L, 50+correction); 
                 analogWrite(speed_R, 50-correction); 
     }
    
                 analogWrite(speed_L, 50); 
                 analogWrite(speed_R, 50); 
                 delay (150);
}

//==============================================================================
int proximity()
{
     int temp;
   float distance,duration;
   
  digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(trigger,LOW);

  duration=pulseIn(echo,HIGH);
  distance =duration/29.1;
  distance=distance/2;
 // Serial.println(distance);
 // Serial2.println(distance);

return distance;
  
  
  
}
//==============================================================================

void measure_height()
{
// go forward 
// measure height 
// update posoition of that block with height in the block matrix
// incriment block count
// come back 
{
//  int initial=proximity();
      int block_number_disp;

  
  three_cm_proximity();
  height=0;double prev_height;
  
 for(int i=0;i<100;i++)
 {
                h[0]=digitalRead(H0);
                h[1]=digitalRead(H1);
                h[2]=digitalRead(H2);
                h[3]=digitalRead(H3);
                h[4]=digitalRead(H4);
                h[5]=digitalRead(H5);
                h[6]=digitalRead(H6);
                h[7]=digitalRead(H7);
                if (h[0]==1)    height=10;
                if (h[1]==1)    height=20;
                if (h[2]==1)    height=30;
                if (h[3]==1)    height=40;
                if (h[4]==1)    height=50;
                if (h[5]==1)    height=60;
                if (h[6]==1)    height=70;
                if (h[7]==1)    height=80;
                
                prev_height=height+prev_height ;
              
 }
 prev_height=prev_height/100;
 
 block_info[block_count-1][0]=prev_height;
 
                                              if (dir==1)   {block_info[block_count-1][1]=current_x+1;  block_info[block_count-1][2]=current_y;          }
                                     else  if (dir==2)    {block_info[block_count-1][1]=current_x;      block_info[block_count-1][2]= current_y-1;     }
                                     else  if (dir==3)    {block_info[block_count-1][1]=current_x-1;   block_info[block_count-1][2]=current_y;         }
                                     else  if (dir==4)    {block_info[block_count-1][1]=current_x;      block_info[block_count-1][2]= current_y+1;    }
                                     
                                     block_count++;
//    Serial.println(prev_height ); 
//    Serial2.println(prev_height ); 
    lcd.setCursor(0,1);
    if (prev_height<30)block_number_disp=1;
    if (prev_height==30)block_number_disp=2;
    if (prev_height==50 || prev_height==60 )block_number_disp=3;
    if (prev_height==70)block_number_disp=4;
    if (prev_height==80)block_number_disp=5;

    lcd.print(block_number_disp);    
      while (1)    
    {
          back_lfr();
          s[0]=analogRead(S0);
          s[6]=analogRead(S6);
          if (s[6]>thr  ||  s[0]>thr) break;
    }       
    
                
      
     digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],0);
     digitalWrite(motor_L[0],1);

                 analogWrite(speed_L, 0); 
                 analogWrite(speed_R, 0); 
                 delay(100);
                 analogWrite(speed_L, 200); 
                 analogWrite(speed_R, 200); 
                  delay(200); 

  }
}

//================================================================================
//==============================================================================
//==============================================================================

void grab_block(int dx,int dy)
{      
      lcd.setCursor(0,0);
    lcd.print("  grab block at  " );
    lcd.setCursor(0,1);
    lcd.print(dx);lcd.print("   " );lcd.print(dy);
      S[dx][dy]=0;
      destination_x=dx;   destination_y=dy;
      shortest_path();
      execute_path_grab();
}
//==========================================================================
void execute_path_grab()
{
 int j,k,t,temp, block;

	for (int n =0;n<30;n++)
	{
          block=0;
		if (dir==1)
			{
					if (path[n]==1) {			                  		  }
				else if (path[n]==2) {turn_right(); 		        dir=2;         }
				else if (path[n]==4) {turn_left(); 		        dir=4;         }
				else if (path[n]==3) {about_turn();            	dir=3;         }
			}
         else if (dir==2)
			{
					if (path[n]==2) {				                          }
				else if (path[n]==3) {turn_right(); 		        dir=3;         }
				else if (path[n]==1) {turn_left(); 	                dir=1;         }
				else if (path[n]==4) {about_turn();                   dir=4;         }
			}
         else if (dir==3)
			{
					if (path[n]==3) {				                          }
				else if (path[n]==4) {turn_right(); 		        dir=4;         }
				else if (path[n]==2) {turn_left()	;                       dir=2;         }
				else if (path[n]==1) {about_turn();             	dir=1;         }
			}
	 else if (dir==4)
			{
  				       if (path[n]==4) {				                                   }
				else if (path[n]==1) {turn_right(); 	               dir=1;           }
				else if (path[n]==3) {turn_left();                       dir=3;           }
				else if (path[n]==2) {about_turn();                  dir=2;           }
			}
         if (path[n]==0) 
                {
                      break;
                }
        block=check_next_node();
         if (block==0)                                                             // no block
                          {
                            temp=follow_line();
                                      if (dir==1)  {current_x=current_x+1;}
                             else  if (dir==2)  {current_y=current_y-1;}
                             else  if (dir==3)  {current_x=current_x-1;}
                             else  if (dir==4)  {current_y=current_y+1;}      
                         //         traversed[current_x][current_y]=1;
                               //Serial.print(current_x); Serial.print("   ");  Serial.println(current_y);
                          }
                           else {                                            // Serial.print("block found at: ");                 // block detected
                                              if (dir==1)   {    grabbing();    current_x=current_x+1;   current_y=current_y;       }
                                     else  if (dir==2)    {    grabbing();    current_x=current_x;       current_y=current_y-1;   }
                                     else  if (dir==3)    {    grabbing();    current_x=current_x-1;    current_y=current_y;      }
                                     else  if (dir==4)    {    grabbing();    current_x=current_x;       current_y=current_y+1;  }
                                                break;   
                                   }
    }
}

//==================================================================
void grabbing()
{
          three_cm_proximity();
                 analogWrite(speed_L, 0); 
                 analogWrite(speed_R, 0); 
         
           ///// grab /////
     digitalWrite(grab[1],0);
     digitalWrite(grab[0],1); 
     analogWrite(grab_speed,110 ); 
     delay(1200);
     analogWrite(grab_speed,70 ); 
     
     
      /////  LIFT   //////
     digitalWrite(lift[1],1);
     digitalWrite(lift[0],0);
     analogWrite(lift_speed, 250); 
     delay(1700);
     analogWrite(lift_speed, 0); 
    int temp=follow_line();
    
    grab_state=1;
          
}

//==============================================================================
//==============================================================================
//==============================================================================
void release_block(int dx, int dy)
{
    destination_x=dx;    destination_y=dy;
    shortest_path();
    execute_path();
    lcd.setCursor(0,0);
    lcd.print("  drop block at " );
    lcd.setCursor(0,1);
    lcd.print(dx);lcd.print("   " );lcd.print(dy);
    ////   back  /////
                                              analogWrite(speed_L, 70); 
                                              analogWrite(speed_R, 67); 
                                              digitalWrite(motor_R[1],1);
                                             digitalWrite(motor_R[0],0);
                                             digitalWrite(motor_L[1],1);
                                             digitalWrite(motor_L[0],0);
                                             delay(1100);
     ///// DROP ////     
     digitalWrite(lift[1],0);
     digitalWrite(lift[0],1);
     analogWrite(lift_speed, 250); 
     delay(1700);
          analogWrite(lift_speed, 0); 
     
    ///// RELEASE ////
     digitalWrite(grab[1],1);
     digitalWrite(grab[0],0); 
     analogWrite(grab_speed,100 ); 
     delay(1200);  
          analogWrite(grab_speed,0 ); 
          
          grab_state=0;
          
   //// setting block location  //////
   S[dx][dy]=200;
   
   //// back to prev node///
     while (1)    
    {
          back_lfr();
          s[0]=analogRead(S0);
          s[6]=analogRead(S6);
          if (s[6]>thr  ||  s[0]>thr) break;
    }
 
                                      if (dir==1)  {current_x=current_x-1;}
                             else  if (dir==2)  {current_y=current_y+1;}
                             else  if (dir==3)  {current_x=current_x+1;}
                             else  if (dir==4)  {current_y=current_y-1;} 
                                  
                  digitalWrite(motor_R[1],0);
                  digitalWrite(motor_R[0],1);
                  digitalWrite(motor_L[1],0);
                  digitalWrite(motor_L[0],1);

                 analogWrite(speed_L, 0); 
                 analogWrite(speed_R, 0); 
                 delay(200);
                 analogWrite(speed_L, 200); 
                 analogWrite(speed_R, 200); 
                  delay(100); 
   
  
}

//==============================================================================
////=============================================================================
void transpose()
{
int block_trans[5][5];
 for(int i=0;i<5;i++)
     {  
             for(int j=0;j<5;j++)
             {
                     block_trans[i][j]=block_info[i][j];
             }
     
     }  
               for(int i=0;i<5;i++)
     {  
             for(int j=0;j<5;j++)
             {
                     block_info[i][j]=block_trans[j][i];
             }
     
  }   }
///==============================================================================
void sorting()
{
     transpose();
        for(int i=0;i<5;i++)
     {  
             for(int j=0;j<5;j++)
             {
                     block_sort[i][j]=block_info[i][j];
             }
     }     
     for(int i=0;i<5;i++)
     {   int p=0;
             for(int j=i;j<5;j++)
             {
                     if(block_sort[0][i]>block_sort[0][j])
                     { for(int l=0;l<3;l++)
                     {
                                    p=block_sort[l][i];
                                    block_sort[l][i]=block_sort[l][j];
                                     block_sort[l][j]=p;
                      }
                      }
               }
       }
       for(int i=0;i<5;i++)
            {
                    block_sort[3][i]=0;
            }
             for(int i=0;i<5;i++)
     {
             block_final[0][i]=block_sort[0][i];
      }     
       for(int i=0;i<5;i++)
     {       
     block_final[1][i]=2+i;
     block_final[2][i]=3;
     
     }
     compare();
}

//===========================================================================
void compare()             //needs to be modified with cases
{
      for(int i=0;i<5;i++)
     {  
             for(int j=0;j<5;j++)
             {
                     if(block_sort[1][i]==block_final[1][j]&&block_sort[2][i]==block_final[2][j])
                     position_blocked++;
             }
     }  
 }
 
 //==========================================================================
 bool check_blockage(int n)
{  
                    if(block_final[0][n]==block_sort[0][n]&&block_final[1][n]==block_sort[1][n]&&block_final[2][n]==block_sort[2][n])
                    {
                         if(block_sort[3][n]==0)                                                                                                            
                         replaced++;
                         block_sort[3][n]=1;
                           
                    }
                    
     int c=0;
     for(int i=0;i<5;i++)
     {
             if(block_final[1][n]==block_sort[1][i]&&block_final[2][n]==block_sort[2][i]&&block_sort[3][i]==0)
             c++;
             else 
             if (block_sort[3][n]==1)
             c++;
     }
     if(c==0)
     return false;
     else
     return true;
}  
//=========================================================================
 void arrange()
 {
   int n=0;
 
     while(replaced<5)
     {          all_blockage_remove();
       
   if( check_blockage(n))
      {
          n++;
          }
          else
       {        lcd.print("n= " );lcd.print(n);
                grab_block(block_sort[1][n],block_sort[2][n]);
               release_block(block_final[1][n],block_final[2][n]);
               block_sort[3][n]=1;
               n++;
               replaced++;      
               
               }
               if(n==5)
               n=0;
       }
} 
            //=====================================================
boolean all_blocked()
 {    int c=0 ,m=0;
      for(int i=0;i<5;i++)
      {if(block_sort[3][i]==1)
            c++;
              for(int j=0;j<5;j++)
              {
                   if(block_final[1][i]==block_sort[1][j]&&block_final[2][i]==block_sort[2][j]&&block_sort[3][j]==0)
                    {       c++;
                           if(block_final[0][i]!=block_sort[0][j])
                         m++;
                         else
                        { 
                             block_sort[3][j]=1;
                             replaced++;
                         }
                     }
              }
       }
         if(c==5&&m!=0)                       
         return true;
         else 
         return false;
}
//====================================================================
void all_blockage_remove()
{int m=0;
   if(all_blocked())
     {
       for(int i=0;i<5;i++)
       {
               if(block_sort[3][i]==0)
               {
                 grab_block(block_sort[1][i],block_sort[2][i]);
                 if(dir==4)
                 m=block_sort[2][i]+1;
                 if(dir==2)
                  m=block_sort[2][i]-1;
                 release_block(block_sort[1][i],m);

                   block_sort[2][i]=m;
                  break;
                  }
       }
                 
                 }   
}

//====================================================================
//====================================================================
void about_turn()
{
digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],0);
     digitalWrite(motor_L[0],1); 
     analogWrite(speed_L, 100); 
     analogWrite(speed_R,100 ); 
     delay(100);
     
      analogWrite(speed_L, 0); 
     analogWrite(speed_R,0 ); 
     delay(100);
     
     digitalWrite(motor_R[1],0);
     digitalWrite(motor_R[0],1);
     digitalWrite(motor_L[1],1);
     digitalWrite(motor_L[0],0); 
     analogWrite(speed_L, 125); 
     analogWrite(speed_R,125 );
     delay(1200);
    while(analogRead(S3)<thr)
        {
        digitalWrite(motor_R[1],0);
        digitalWrite(motor_R[0],1);
       digitalWrite(motor_L[1],1);
       digitalWrite(motor_L[0],0); 
       analogWrite(speed_L, 125); 
       analogWrite(speed_R,125 );
        }
           analogWrite(speed_L, 0); 
           analogWrite(speed_R,0 );
           delay(50);
}
//======================================================

void back_lfr()
{

b[0]=analogRead(x0);
b[1]=analogRead(x1);
b[2]=analogRead(x2);
b[3]=analogRead(x3);
b[4]=analogRead(x4);


  error_b=0;     
  divisor_b=0;
  
  for(int i =0;i<5;i++)
        {
          if (b[i]>thr_b)
                  {b[i]=1;}
                  else b[i]=0;
        }
        
     for(int i =0;i<5;i++)
        {
          if (b [i]==1)
                  {error_b=error_b+i+1; divisor_b++;}
        }
  
     error_b=error_b/divisor_b;
     error_b=error_b-3;
     
     correction_b =kp_b*error_b;
     
     digitalWrite(motor_R[1],1);
     digitalWrite(motor_R[0],0);
     digitalWrite(motor_L[1],1);
     digitalWrite(motor_L[0],0);
     
     
     
     if (correction_b>base_b){correction_b=base_b;}
                 analogWrite(speed_L, base_b-correction_b); 
                 analogWrite(speed_R, base_b+correction_b); 
       
 
}



