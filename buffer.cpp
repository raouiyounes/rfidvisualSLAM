#include <iostream.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>
#include <math.h>
#include  "sterio_interpretation.cpp"
#include <eigen3/Eigen/Dense>
#include "Robot.h"
#include "RFID.h"
#include "Vision.h"
#include "Utilities.cpp"
#define pi 3.14


using namespace std;
static float numberOfParticle=100;

map<int,int > observation(VectorXd X);
bool isInSector(float x_center,float y_center,float angle_offset,float angle, float x,float y);



int main(){

VectorXd X(3);
map<int,int>  retour;
retour=observation(X);
X(0)=1.1;X(1)=2.1;X(2)=2.1;

ofstream myfile;
myfile.open("exemple.txt");
for(int i=0;i<81;i++)
myfile<< retour[i] ;
myfile.close();
return 0;


}


map<int,int > observation(VectorXd X){
        int i,j,l=0;

map<int, int > tags;


for(i=0;i<81;i++){

tags[i]=0;
}


float angle_offset1=0.12;
float angle1=pi/4;
float angle_offset2=0.14;
float angle2=pi/8;


Eigen::MatrixXd tag(82,2);
        
bool v;

for(i=0;i<9;i++)
for(i=0;i<180;i+=20)
                for(j=0;j<180;j+=20){
                        tag(l,0)=i;
                        tag(l,1)=j;
                        l++;
                }


l=0;
  
        for(i=0;i<180;i+=20)
                for(j=0;j<180;j+=20){
if((v=isInSector( tag(l,0), tag(l,1),angle_offset1,angle1, X(0),X(1)))==true){
l++;
tags[l]++;
}
}

return tags;
}





bool isInSector(float x_center,float y_center,float angle_offset,float angle, float x,float y){

VectorXd first_line(3),second_line(3);
first_line(0)=sin(angle_offset);
first_line(1)=-cos(angle_offset);
first_line(2)=-x_center*sin(angle_offset)+y_center*cos(angle_offset);
second_line(0)=sin(angle_offset+angle);
second_line(1)=-cos(angle_offset+angle);
second_line(2)=-x_center*sin(angle_offset+angle)+y_center*cos(angle_offset+angle);


if((x*first_line(0)+y*first_line(1)+first_line(2)<0)&&(x*second_line(0)+y*second_line(1)+second_line(2)<0));
else return false;


}