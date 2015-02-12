
#include <stdio.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include <dirent.h>
#ifndef _UNISTD_H
#define _UNISTD_H
#include <io.h>
#include <process.h>
#endif /* _UNISTD_H */
#include <sys/stat.h>
#include <sys/types.h>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <stdio.h>
#include <sstream>
using namespace cv;
using namespace std;
class MyVocabolaryBuilder {
public:
	MyVocabolaryBuilder(string dir, string descriptor, int clusters, int imageSize);
	void buildVocabolary();

	
private:
	string dir;
	string descriptor; 
	int clusters;
	int imageSize;


};