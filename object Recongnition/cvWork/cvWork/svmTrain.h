#include <stdio.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <string>

//#include <dirent.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <omp.h>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include<opencv2/legacy/legacy.hpp>
using namespace cv;
using namespace std;
class MySVMTrainer {
public:
	MySVMTrainer(string featureDescriptor, int clusters, int imageSize);
	
private:
	string featureDescriptor;
	int clusters;
	int imageSize;
public:
	void trainSVM(map<string, Mat>& classes_training_data, int response_cols, int response_type);
	void getTrainSamples(Ptr<FeatureDetector>& detector, BOWImgDescriptorExtractor& bowide, map<string, Mat>& classes_training_data);
	void getBowSVM();
};