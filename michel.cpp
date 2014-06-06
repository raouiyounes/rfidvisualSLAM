
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <eigen3/Eigen/Dense>
#include <math.h>
#include <exception>
#define ROWS 35
#define COLS 65



#define NUMBEROFFEATURES 1000
#define DIMFEATURE 10
#define numberStatNN 45
using namespace Eigen;
using namespace std;


MatrixXd carte(ROWS,COLS); 

MatrixXd brisc(int i){

const int BUFFSIZE=400;
map<int, vector<int> > carte;
char buff[BUFFSIZE];
char buff_appearance[3];
MatrixXd array(ROWS,COLS);
ifstream ifs("Brisc_db.txt");
stringstream ss;
int aide;
string s;
int k;
int c;
for(int row=0;row<ROWS-1;row++) {
ifs.getline(buff,BUFFSIZE);
ss<<buff;
for(int col=0;col<COLS-2;col++){
getline( ss,s,',');
array(row,col)=atoi(s.c_str());
//cout<<array(row,col);
//cin>>c;
ss<<"";
}
}
return array;
}

int indice[ROWS];
int min(float d[4]);


int* kmeanCluster(){

int c,i,j,k;
float distance;
int indice[ROWS];
int center[4][COLS];
int s[ROWS];
float s_biased[ROWS];
float d[4]={0.0,0.0,0.0,0.0};
i=0;

for(int i=0;i<ROWS-1;i++)
s[i]=0;
indice[0]=0;

for(i=0;i<COLS-1;i++){
	center[0][i]=carte(0,i);
	center[1][i]=carte(2,i);
	center[2][i]=carte(6,i);
	center[3][i]=carte(9,i);
}

for(j=0;j<COLS-1;j++){
	for(i=0;i<ROWS-1;i++)
		{
		d[0]=d[1]=d[2]=d[3]=0.0;
		for(j=0;j<COLS-1;j++){
			d[0]=d[0]+sqrt(pow((center[0][j]-carte(i,j)),2));
			d[1]=d[1]+sqrt(pow((center[1][j]-carte(i,j)),2));
			d[2]=d[2]+sqrt(pow((center[2][j]-carte(i,j)),2));
			d[3]=d[3]+sqrt(pow((center[3][j]-carte(i,j)),2));
}
indice[i]=min(d);
}
return indice;
}
}


int min(float d[4]){
int i,min_i;
float min;
i=1;
min=d[0];
min_i=0;
while(i!=4)
{
if(min>d[i]){
	min=d[i];
    min_i=i;
  }
    i++;
}
return min_i;
}






