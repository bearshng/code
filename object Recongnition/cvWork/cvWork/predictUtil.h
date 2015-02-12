#include <stdio.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

#include <dirent.h>
#ifndef _UNISTD_H
#define _UNISTD_H
#include <io.h>
#include <process.h>
#endif /* _UNISTD_H */
#include <sys/stat.h>
#include <sys/types.h>

#include <omp.h>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include<opencv2/legacy/legacy.hpp>
#include<memory>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class MyObjectPredictor {
public:	

	MyObjectPredictor(string featureDescriptor, int cluseter, int imageSize);
	int predictOneImage(Mat& __img, map<float, string> & out_classes);
	map<string, unique_ptr<CvSVM>>& getClassesClassifiers() { return classes_classifiers; }
	void setDebug(bool _b) { debug = _b;}
	void setFeatureDescriptor(string featureDescriptor) { this->featureDescriptor = featureDescriptor; }
	string getObjectType(int obj);
	//string predictObject(Mat image, map<float, string>  max_class);
	Mat getPointMat(Mat mat);
	float getRightRate(string test);
private:
	void initColors();
	void initSVMs(string featureDescriptor);
	void initVocabulary(string featureDescriptor);
	int imageSize;
	bool debug;
	int cluseter;
	string featureDescriptor;
	Ptr<FeatureDetector > detector;
	Ptr<BOWImgDescriptorExtractor > bowide;
	Ptr<DescriptorMatcher > matcher;
	Ptr<DescriptorExtractor > extractor;
	map<string, unique_ptr<CvSVM>> classes_classifiers;
	map<string,Scalar> classes_colors;
	Mat vocabulary;
	
	
};