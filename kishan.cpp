#include<iostream>
using namespace std;
int dx=3,dy=6;
int d[8][8];
int p[20];
int dir=4,f=1;

int a(int b)
{
     if(b<0) return -b;
     else    return b;
}

int main()
{

  for(int j=0;j<8;j++)   //initialize boundary antinodes for 3X4 grid
  {
    d[j][0]=200;
	d[0][j]=200;
	d[j][7]=200;
	d[7][j]=200;
   }

///////////////////////////////////////
//////  weighted matrix creation ///////
///////////////////////////////////////
 for(int j=0;j<8;j++)
 {
   for(int k=0;k<8;k++)
   {
      if(d[j][k]!=200)   {  d[j][k]=a(dx-j)+a(dy-k); }
       f=1;
     // antinodes initialisation
       if((j==1)&&(k==3)) {  cout<<200<<"\t ";  d[j][k]=200; f=0;}
     if((j==2)&&(k==3)) {  cout<<200<<"\t ";  d[j][k]=200; f=0;}
       if((j==3)&&(k==3)) {  cout<<200<<"\t ";  d[j][k]=200; f=0;}
       if(f)              {  cout<<d[j][k]<<"\t "; }
    }
    cout<<"\n";
 }



/////////////////////////////////////////
/////   shortest path       /////////////
////////////////////////////////////////

 int t=0,j=1,k=1;
 p[t]=1;

// while((j!=dx) && (k!=dy))
while(d[j][k]!=0)
 {
     if(dir==1)
    {
           if(d[j][k]==d[j][k+1]+1) { p[++t]=1; k++;}
      else if(d[j][k]==d[j+1][k]+1) { p[++t]=2; j++; dir=2;}
      else if(d[j][k]==d[j-1][k]+1) { p[++t]=4; j--; dir=4;}
	  else {
	         d[j][k]=d[j][k]+2;
			 t=0;
             j=1; k=1; dir=1;
            }

     }
    else if(dir==2)
    {
           if(d[j][k]==d[j+1][k]+1) { p[++t]=2; j++;}
      else if(d[j][k]==d[j][k+1]+1) { p[++t]=1; k++; dir=1;}
      else if(d[j][k]==d[j][k-1]+1) { p[++t]=3; k--; dir=3;}
	  else {
	         d[j][k]=d[j][k]+2;
			 t=0;
             j=1; k=1; dir=1;
            }

     }
     else if(dir==3)
    {
           if(d[j][k]==d[j][k-1]+1) { p[++t]=3; k--;}
      else if(d[j][k]==d[j+1][k]+1) { p[++t]=2; j++; dir=2;}
      else if(d[j][k]==d[j-1][k]+1) { p[++t]=4; j--; dir=4;}
	  else {
	         d[j][k]=d[j][k]+2;
			 t=0;
             j=1; k=1; dir=1;
            }

     }
     else if(dir==4)
    {
           if(d[j][k]==d[j-1][k]+1) { p[++t]=4; j--;}
      else if(d[j][k]==d[j][k+1]+1) { p[++t]=1; k++; dir=1;}
      else if(d[j][k]==d[j][k-1]+1) { p[++t]=3; k--; dir=3;}
	  else {
	         d[j][k]=d[j][k]+2;
			 t=0;
             j=1; k=1; dir=1;
            }
     }
 } //while end

 p[++t]=0;
  j=0;
  cout<<"\nPATH:  ";
  while(p[j]!=0)
  {
    cout<<p[j]<<" -> ";
    j++;
  }
  cout<<" REACHED ("<<dx<<","<<dy<<")";
cin>>j;}
