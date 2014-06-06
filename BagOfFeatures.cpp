/*
 * BagOfFeatures.cpp
 *
 *  Created on: 7 mai 2014
 *      Author: younes
 */

#include "BagOfFeatures.h"

#include <iostream>
#include <vector.h>
#include <cv.h>
#include<fstream>
#include <highgui.h>
#include <eigen3/Eigen/Dense>
#include<iostream>
#include <string>


#define NUMBEROFFEATURES 1000
#define DIMFEATURE 10
#define numberStatNN 45
using namespace std;
using namespace cv;



BagOfFeatures::BagOfFeatures() {
	// TODO Auto-generated constructor stub

}

BagOfFeatures::~BagOfFeatures() {
	// TODO Auto-generated destructor stub
}

vector<IplImage*> BagOfFeatures::load_image_db(){
       IplImage *im;
       vector<IplImage*> ims;
       int i;
       char buffer[20];
       for (i=1;i<16;i++)
       {
           sprintf(buffer,  "rooms/im%d.png",i);
           im=cvLoadImage(buffer,1);

           ims.push_back(im);

       }
       return ims;

   }




int BagOfFeatures::extract_BRISC(){
    vector<IplImage*> image_scenes=load_image_db();
    int i;
    CvMat *image1=0;
    ofstream outputFile("surf_db.txt");
    static CvScalar red_color[] ={0,0,255};
    IplImage* image;

    for(i=0;i<6;i++){
        image=image_scenes.at(i);
        image1 = cvCreateMat(image->height, image->width, CV_8UC1);
        cvCvtColor(image, image1, CV_BGR2GRAY);
        CvSURFParams params;
        //  cv::Mat GrayA =cv::imread(image1);
        //  cv::Mat GrayB =cv::imread(PimB);
        std::vector<cv::KeyPoint> keypointsA;
        cv::Mat descriptorsA;
        int Threshl=40;
        int Octaves=2;
        float PatternScales=1.0f;
        cv::BRISK  BRISKD(Threshl,Octaves,PatternScales);//initialize algoritm
        BRISKD.create("Feature2D.BRISK");
        BRISKD.detect(image1, keypointsA);
        BRISKD.compute(image1, keypointsA,descriptorsA);
        cv::Ptr<cv::FeatureDetector> detector = cv::Algorithm::create<cv::FeatureDetector>("Feature2D.BRISK");
        detector->detect(image1, keypointsA);
        cv::Ptr<cv::DescriptorExtractor> descriptorExtractor =cv::Algorithm::create<cv::DescriptorExtractor>("Feature2D.BRISK");
        descriptorExtractor->compute(image1, keypointsA, descriptorsA);

        for(int i=0;i<keypointsA.size();i++){
            outputFile<<keypointsA[i].pt.x<<" "<<keypointsA[i].pt.y<<" ";
            outputFile<<descriptorsA.row(i)<<endl;
        }

    }
    outputFile <<endl;


    return 0;
}
/*
std::map<int,vector<int> > BagOfFeatures::neuralNetworkLearning(map<int, vector<int> > features){
int  i=0;
int N=100;
int a=0;
int x=1;
int sortie_designee=1;
vector<double> e;
	vector<double> weights;
int feature_number=0;
	map<int,vector<int> > baseOfFact;
	float S=0;
	for(i=0;i<NUMBEROFFEATURES;i++)
		weights.at(i)=0.0;
while(feature_number!=NUMBEROFFEATURES)
	{
	for (i=0;i<N;i++)
		e.at(i)=0;
	for(i=0;i<DIMFEATURE;i++){
		a=a+(weights.at(i)*e.at(i));
		a=a-S;
if(a>0) x=1; else x=-1;
if(x!=sortie_designee){
	for(i=0;i<N;i++)
	weights.at(i)=weights.at(i)+e.at(i)*x;
}
}
return baseOfFact;
}
*/


int kmeanSS(map<int, vector<int> > features) {
vector<int> line;
int i,j;

Mat src = Mat::zeros(NUMBEROFFEATURES,DIMFEATURE, CV_8UC1);
for(i=0;i<NUMBEROFFEATURES;i++){
line=features[i];

for(j=0;j<DIMFEATURE;j++)
src(line);

}






    
    blur(src, src, Size(15,15));
    imshow("blurred", src);

    Mat p = Mat::zeros(src.cols*src.rows, 5, CV_32F);
    Mat bestLabels, centers, clustered;
    vector<Mat> bgr;
    cv::split(src, bgr);
    // i think there is a better way to split pixel bgr color
    for(int i=0; i<src.cols*src.rows; i++) {
        p.at<float>(i,0) = (i/src.cols) / src.rows;
        p.at<float>(i,1) = (i%src.cols) / src.cols;
        p.at<float>(i,2) = bgr[0].data[i] / 255.0;
        p.at<float>(i,3) = bgr[1].data[i] / 255.0;
        p.at<float>(i,4) = bgr[2].data[i] / 255.0;
    }

    int K = 8;
    cv::kmeans(p, K, bestLabels,
            TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
            3, KMEANS_PP_CENTERS, centers);

    int colors[K];
    for(int i=0; i<K; i++) {
        colors[i] = 255/(i+1);
    }
    // i think there is a better way to do this mayebe some Mat::reshape?
    clustered = Mat(src.rows, src.cols, CV_32F);
    for(int i=0; i<src.cols*src.rows; i++) {
        clustered.at<float>(i/src.cols, i%src.cols) = (float)(colors[bestLabels.at<int>(0,i)]);
//      cout << bestLabels.at<int>(0,i) << " " << 
//              colors[bestLabels.at<int>(0,i)] << " " << 
//              clustered.at<float>(i/src.cols, i%src.cols) << " " <<
//              endl;
    }

    clustered.convertTo(clustered, CV_8U);
    imshow("clustered", clustered);

    waitKey();
    return 0;
}




/*
vector<int> BagOfFeatures::histogramComputation(map<int vector<int> > words){
vector<int> hist;
	vector<int>  feature_quantized;
	vector<int> histograme;
	for(int i=0;i<DIMFEATURE;i++)
		feature_quantized.at(i)=0;
feature_quantized=words[0];

for(i=0;i<numberStatNN;i++){

}

}
*/
/*
vector<int> BagOfFeatures::sort(map<int,std::vector<int> dico){

int j;
int i;
for(i=0;i< NUMBEROFFEATURES; i++){
v1=v[i]
for(j=i+1;j<NUMBEROFFEATURES;j++){
if(v[j]>v1){
temp=v[j];
v[j]=v1;
v1=temp;
}
}
}
}

*/


int main(){



	return 0;



}
