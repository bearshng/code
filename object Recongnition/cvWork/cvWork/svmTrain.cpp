#include<svmTrain.h>
MySVMTrainer::MySVMTrainer(string featureDescriptor, int clusters, int imageSize){
	this->featureDescriptor = featureDescriptor;
	this->clusters = clusters;
	this->imageSize = imageSize;


}
void MySVMTrainer::trainSVM(map<string, Mat>& classes_training_data, int response_cols, int response_type) {
	vector<string> classes_names;
	for (map<string, Mat>::iterator it = classes_training_data.begin(); it != classes_training_data.end(); ++it) {
		classes_names.push_back((*it).first);
	}
	for (int i = 0; i < classes_names.size(); i++) {
		string class_ = classes_names[i];
		std::cout << "ѵ����" << class_ << "����" << std::endl;
		Mat samples(0, response_cols, response_type);
		Mat labels(0, 1, CV_32FC1);

		//copy class samples and label
		cout << "��� " << classes_training_data[class_].rows << " ������" << endl;
		samples.push_back(classes_training_data[class_]);
		Mat class_label = Mat::ones(classes_training_data[class_].rows, 1, CV_32FC1);
		labels.push_back(class_label);

		//copy rest samples and label
		for (map<string, Mat>::iterator it1 = classes_training_data.begin(); it1 != classes_training_data.end(); ++it1) {
			string not_class_ = (*it1).first;
			if (not_class_.compare(class_) == 0) continue;
			samples.push_back(classes_training_data[not_class_]);
			class_label = Mat::zeros(classes_training_data[not_class_].rows, 1, CV_32FC1);
			labels.push_back(class_label);
		}

		cout << "ѵ��.." << endl;
		Mat samples_32f; samples.convertTo(samples_32f, CV_32F);
		if (samples.rows == 0) continue;
		CvSVM classifier;
		//CvParamGrid Cgrid(0.1, 10000, sqrt(10.0f));
		classifier.train(samples_32f, labels);

		{
			stringstream ss;
			ss << featureDescriptor << "_SVM_classifier_";

			ss << class_ << ".yml";
			cout << "�����ļ�.." << endl;
			classifier.save(ss.str().c_str());
		}
	}
}
void MySVMTrainer::getTrainSamples(Ptr<FeatureDetector>& detector, BOWImgDescriptorExtractor& bowide, map<string, Mat>& classes_training_data){
	cout << "�鿴ѵ������" << endl;
	Ptr<ifstream> ifs(new ifstream("train.txt"));
	int total_samples = 0;
	vector<string> classes_names;
	char buf[1024]; int count = 0;
	vector<string> lines;
	while (!ifs->eof()) {// && count++ < 30) {
		ifs->getline(buf, 1024);
		if (ifs->fail()){
			break;
		}
		lines.push_back(buf);
	}
	for (int i = 0; i < lines.size(); i++) {
		vector<KeyPoint> keypoints;
		Mat response_hist;
		Mat img;
		string filepath;
		string line(lines[i]);
		istringstream iss(line);
		iss >> filepath;
		string class_; iss >> class_;

		if (class_.size() == 0) continue;
		class_ = "class_" + class_;
		img = imread(filepath);
		resize(img, img, Size(imageSize, imageSize), 0, 0, CV_INTER_LINEAR);
		//imshow("", img);
		//waitKey(0);
		detector->detect(img, keypoints);
		bowide.compute(img, keypoints, response_hist);
		cout << "."; cout.flush();
		if (classes_training_data.count(class_) == 0) { //not yet created...
			classes_training_data[class_].create(0, response_hist.cols, response_hist.type());
			classes_names.push_back(class_);
		}
		classes_training_data[class_].push_back(response_hist);
		total_samples++;
		//		waitKey(0);
	}
	cout << endl;

	cout << "�����ļ�.." << endl;
	{
		string fileName = featureDescriptor + "_" + "training_samples";
		FileStorage fs(fileName+".yml", FileStorage::WRITE);
		for (map<string, Mat>::iterator it = classes_training_data.begin(); it != classes_training_data.end(); ++it) {
			fs << (*it).first << (*it).second;
		}
	}
}

void  MySVMTrainer::getBowSVM(){

	cout << "-------- ѵ��BOWSVM -----------" << endl;
	cout << "��ȡ�ֵ���Ϣ" << endl;
	Mat vocabulary;
	stringstream ss;
	ss << clusters;
	string vocabularyFileName = featureDescriptor + "_vocabulary_" + ss.str();
	FileStorage fs(vocabularyFileName + ".yml", FileStorage::READ);
	fs["vocabulary"] >> vocabulary;
	fs.release();
	if (featureDescriptor == "surf"){
		Ptr<FeatureDetector > detector(new SurfFeatureDetector()); //detector
		//Ptr<DescriptorExtractor > extractor(new SurfDescriptorExtractor());//  extractor;
		Ptr<DescriptorExtractor > extractor(
			new OpponentColorDescriptorExtractor(
			Ptr<DescriptorExtractor>(new SurfFeatureDetector())
			)
			);
		Ptr<DescriptorMatcher > matcher(new BruteForceMatcher<L2<float> >());
		BOWImgDescriptorExtractor bowide(extractor, matcher);
		bowide.setVocabulary(vocabulary);

		//setup training data for classifiers
		map<string, Mat> classes_training_data; classes_training_data.clear();

		cout << "��ȡѵ������.." << endl;
		getTrainSamples(detector, bowide, classes_training_data);

		cout << "�ܹ��� " << classes_training_data.size() << " ��." << endl;
		for (map<string, Mat>::iterator it = classes_training_data.begin(); it != classes_training_data.end(); ++it) {
			cout << " ��� " << (*it).first << " �� " << (*it).second.rows << " ������" << endl;
		}

		cout << "ѵ�� SVMs\n";
		trainSVM(classes_training_data, bowide.descriptorSize(), bowide.descriptorType());
	}
	else if (featureDescriptor == "sift")
	{
		Ptr<FeatureDetector > detector(new SiftFeatureDetector()); //detector
		//Ptr<DescriptorExtractor > extractor(new SurfDescriptorExtractor());//  extractor;
		Ptr<DescriptorExtractor > extractor(
			new OpponentColorDescriptorExtractor(
			Ptr<DescriptorExtractor>(new SiftFeatureDetector())
			)
			);
		Ptr<DescriptorMatcher > matcher(new BruteForceMatcher<L2<float> >());
		BOWImgDescriptorExtractor bowide(extractor, matcher);
		bowide.setVocabulary(vocabulary);

		//setup training data for classifiers
		map<string, Mat> classes_training_data; classes_training_data.clear();

		cout << "��ȡѵ������.." << endl;
		getTrainSamples(detector, bowide, classes_training_data);

		cout << "�ܹ��� " << classes_training_data.size() << " ��." << endl;
		for (map<string, Mat>::iterator it = classes_training_data.begin(); it != classes_training_data.end(); ++it) {
			cout << " ��� " << (*it).first << " �� " << (*it).second.rows << " ������" << endl;
		}

		cout << "ѵ�� SVMs\n";
		trainSVM(classes_training_data, bowide.descriptorSize(), bowide.descriptorType());
	}

}
