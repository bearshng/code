
#include "predictUtil.h"

MyObjectPredictor::MyObjectPredictor(string featureDescriptor, int cluseter, int imageSize){
	debug = true;
	this->imageSize = imageSize;
	this->cluseter = cluseter;
	//initColors();
	initSVMs(featureDescriptor);
	initVocabulary(featureDescriptor);
	if (featureDescriptor == "surf")
	{
		Ptr<FeatureDetector > _detector(new SurfFeatureDetector());
		Ptr<DescriptorMatcher > _matcher(new BruteForceMatcher<L2<float> >());
		Ptr<DescriptorExtractor > _extractor(new OpponentColorDescriptorExtractor(Ptr<DescriptorExtractor>(new SurfDescriptorExtractor())));
		matcher = _matcher;
		detector = _detector;
		extractor = _extractor;
	}
	else if (featureDescriptor == "sift")
	{
		Ptr<FeatureDetector > _detector(new SiftFeatureDetector());
		Ptr<DescriptorMatcher > _matcher(new BruteForceMatcher<L2<float> >());
		Ptr<DescriptorExtractor > _extractor(new OpponentColorDescriptorExtractor(Ptr<DescriptorExtractor>(new SiftDescriptorExtractor())));
		matcher = _matcher;
		detector = _detector;
		extractor = _extractor;
	}
	

	bowide = Ptr<BOWImgDescriptorExtractor>(new BOWImgDescriptorExtractor(extractor,matcher));
	bowide->setVocabulary(vocabulary);
}


void MyObjectPredictor::initSVMs(string featureDescriptor) {
	string dir, filepath;
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	
	if(debug) cout << "加载SVM分类器" << endl;
	dir = ".";
	dp = opendir( dir.c_str() );
	
	while ((dirp = readdir( dp )))
    {
		filepath = dir + "/" + dirp->d_name;
		if (stat( filepath.c_str(), &filestat )) continue;
		if (S_ISDIR( filestat.st_mode ))         continue;
		if (filepath.find(featureDescriptor + "_" + "SVM_classifier") != string::npos)
		{
			string class_ = filepath.substr(filepath.rfind('_')+1,filepath.rfind('.')-filepath.rfind('_')-1);
			if (debug) cout << "load " << filepath << ", class: " << class_ << endl;
			classes_classifiers.insert(make_pair(class_, unique_ptr<CvSVM>(new CvSVM())));
			classes_classifiers[class_]->load(filepath.c_str());
		}
	}
	closedir(dp);
}

void MyObjectPredictor::initVocabulary(string featureDescriptor) {
	if (debug) cout << "read vocabulary form file"<<endl;
	stringstream ss;
	ss << cluseter;
	string vocabularyFileName = featureDescriptor+"_vocabulary_" + ss.str();
	std::cout << vocabularyFileName;
	FileStorage fs(vocabularyFileName + ".yml", FileStorage::READ);
	fs["vocabulary"] >> vocabulary;
	fs.release();	
}	

int MyObjectPredictor::predictOneImage(Mat& __img, map<float, string> & out_classes) {
	resize(__img, __img, Size(imageSize, imageSize), 0, 0, CV_INTER_LINEAR);
	Mat response_hist;
	vector<KeyPoint> keypoints;
	detector->detect(__img, keypoints);
	bowide->compute(__img, keypoints, response_hist);
	out_classes.clear();
	float minf = FLT_MAX; string minclass;

	for (map<string, unique_ptr<CvSVM>>::iterator it = classes_classifiers.begin(); it != classes_classifiers.end(); ++it) {
		//std::cout << (*it).first << std::endl;
		float res = (*it).second->predict(response_hist, true);
		//std::cout << res<< std::endl;
		string str1 = (*it).first;
		double temp1 = atof(str1.c_str());
		int temp2 = int(temp1);
		out_classes.insert(pair<float, string>(res, getObjectType(temp2)));
		if (res > 1.0) continue;
		if (res < minf) {
			minf = res;
			minclass = (*it).first;
		}
	}
	double obj = atof(minclass.c_str());

	return int(obj);
			
			
}

string MyObjectPredictor::getObjectType(int obj) {
	switch (obj) {
	case 1:
		return "brain";
		break;
	case 2:
		return "chair";
		break;

	case 3:
		return "dog";
		break;
	case 4:

		return "elephant";
		break;
	case 5:

		return "face";
		break;
	case 6:

		return "headphone";
		break;
	case 7:

		return "kangaroo";
		break;
	case 8:

		return "tick";
		break;
	case 9:

		return "umbrellar";
		break;
	case 10:

		return "wrench";
		break;

	}
}

Mat MyObjectPredictor::getPointMat(Mat mat){
	//resize(mat, mat, Size(imageSize, imageSize), 0, 0, CV_INTER_LINEAR);
	vector<KeyPoint> keypoints;
	detector->detect(mat, keypoints);
	Mat out; 
	drawKeypoints(mat, keypoints, out, Scalar::all(-1), 0);
	return out;
}
float MyObjectPredictor::getRightRate(string test){
	ifstream ifs(test);
	char buf[1024];
	vector<string> lines;
	
	while (!ifs.eof()) {// && count++ < 30) {
		ifs.getline(buf, 1024);
		if (ifs.fail()){
			break;
		}
		lines.push_back(buf);
	}
	int totalNum = lines.size();
	int rightNum = 0;
	map<string, map<string, int> > confusionMatrix;
	confusionMatrix.clear();

	for (int i = 0; i < totalNum; i++) {
		string line(lines[i]);
		istringstream iss(line);
		string filepath;
		iss >> filepath;
		int class_; iss >> class_;
		Mat image = imread(filepath);
		resize(image, image, Size(imageSize, imageSize), 0, 0, CV_INTER_LINEAR);
		map<float, string> max_class;
		int res = predictOneImage(image, max_class);
		rightNum = class_ == res ? rightNum + 1 : rightNum;
		string orginal =getObjectType(class_);
		string result = getObjectType(res);
		std::cout << "orginal\t" << orginal << "\tresult\t" << result << "\n";
		confusionMatrix[orginal][result]++;
	}
	std::cout << "准确率" << (float)rightNum / totalNum << std::endl;
	return (float)rightNum / totalNum;
}
