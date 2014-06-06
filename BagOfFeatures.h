/*
 * BagOfFeatures.h
 *
 *  Created on: 7 mai 2014
 *      Author: younes
 */

#include <eigen3/Eigen/Dense>
#include <cv.h>
#include <highgui.h>
#include <string>
#include <iostream>
using namespace Eigen;
#define NUMBEROFFEATURES 1000
#define DIMFEATURE 10
#define numberStatNN 45
using namespace std;
#ifndef BAGOFFEATURES_H_
#define BAGOFFEATURES_H_


class BagOfFeatures
{

	BagOfFeatures();
		virtual ~BagOfFeatures();
		int extract_BRISC();
		std::map<int,vector<int> > neuralFieldLearning();
	//	vector<int> histogramComputation(map<int vector<int> > words);
		vector<int> sort(map<int,std::vector<int> >dico);
	vector<IplImage*>	load_image_db();
};



#endif /* BAGOFFEATURES_H_ */
