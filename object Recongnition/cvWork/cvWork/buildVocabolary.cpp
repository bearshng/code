/*
创建BOW
*/
#include "buildVocabolary.h"

MyVocabolaryBuilder::MyVocabolaryBuilder(string dir, string descriptor, int clusters, int imageSize) {
	this->dir = dir;
	this->descriptor = descriptor;
	this->clusters = clusters;
	this->imageSize = imageSize;
}
void MyVocabolaryBuilder::buildVocabolary(){
	string dir = this->dir, filepath;
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	dp = opendir(dir.c_str());
	vector<KeyPoint> keypoints;
	if (descriptor == "surf"){
		SurfFeatureDetector detector(400);
		Ptr<DescriptorExtractor > extractor(
			new OpponentColorDescriptorExtractor(
			Ptr<DescriptorExtractor>(new SurfDescriptorExtractor())
			)
			);

		Mat descriptors;
		Mat training_descriptors(1, extractor->descriptorSize(), extractor->descriptorType());
		Mat img;

		cout << "------- 创建词库 ---------\n";

		cout << "提取.." << endl;

		while (dirp = readdir(dp))
		{
			//	count++;
			filepath = dir + "/" + dirp->d_name;

			// If the file is a directory (or is in some way invalid) we'll skip it 
			if (stat(filepath.c_str(), &filestat)) continue;
			if (S_ISDIR(filestat.st_mode))         continue;

			img = imread(filepath);
			if (!img.data) {
				continue;
			}

			resize(img, img, Size(imageSize, imageSize), 0, 0, CV_INTER_LINEAR);
			detector.detect(img, keypoints);
			extractor->compute(img, keypoints, descriptors);
			training_descriptors.push_back(descriptors);
			cout << ".";
		}
		cout << endl;
		closedir(dp);

		cout << "总数: " << training_descriptors.rows << endl;

		FileStorage fs("surf_training_descriptors.yml", FileStorage::WRITE);
		fs << "training_descriptors" << training_descriptors;
		fs.release();

		BOWKMeansTrainer bowtrainer(clusters); //num clusters
		bowtrainer.add(training_descriptors);
		cout << "对词库进行聚类" << endl;
		Mat vocabulary = bowtrainer.cluster();
		stringstream ss;
		ss << clusters;
		string vocabularyFileName = "surf_vocabulary_" + ss.str();
		FileStorage fs1(vocabularyFileName + ".yml", FileStorage::WRITE);
		fs1 << "vocabulary" << vocabulary;
		fs1.release();

	}
	else if (descriptor == "sift"){

		SiftFeatureDetector detector(400);
		Ptr<DescriptorExtractor > extractor(
			new OpponentColorDescriptorExtractor(
			Ptr<DescriptorExtractor>(new SiftDescriptorExtractor())
			)
			);

		Mat descriptors;
		Mat training_descriptors(1, extractor->descriptorSize(), extractor->descriptorType());
		Mat img;

		cout << "------- 创建词库 ---------\n";

		cout << "提取.." << endl;

		while (dirp = readdir(dp))
		{
			//	count++;
			filepath = dir + "/" + dirp->d_name;

			// If the file is a directory (or is in some way invalid) we'll skip it 
			if (stat(filepath.c_str(), &filestat)) continue;
			if (S_ISDIR(filestat.st_mode))         continue;

			img = imread(filepath);
			if (!img.data) {
				continue;
			}

			resize(img, img, Size(imageSize, imageSize), 0, 0, CV_INTER_LINEAR);
			detector.detect(img, keypoints);
			extractor->compute(img, keypoints, descriptors);
			training_descriptors.push_back(descriptors);
			cout << ".";
		}
		cout << endl;
		closedir(dp);

		cout << "总数: " << training_descriptors.rows << endl;

		FileStorage fs("sift_training_descriptors.yml", FileStorage::WRITE);
		fs << "training_descriptors" << training_descriptors;
		fs.release();

		BOWKMeansTrainer bowtrainer(clusters); //num clusters
		bowtrainer.add(training_descriptors);
		cout << "对词库进行聚类" << endl;
		Mat vocabulary = bowtrainer.cluster();
		stringstream ss;
		ss << clusters;
		string vocabularyFileName = "sift_vocabulary_" + ss.str();
		FileStorage fs1(vocabularyFileName + ".yml", FileStorage::WRITE);
		fs1 << "vocabulary" << vocabulary;
		fs1.release();

	}




}

