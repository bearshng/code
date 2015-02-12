#include "cvwork.h"
#include <QtWidgets/QApplication>
#include "buildVocabolary.h"
#include "svmTrain.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	cvWork w;
	w.show();
	return a.exec();
	//char filename[] = "surfCluster.txt"; // 此处写入文件名 
	//ofstream fout(filename);
	/*
		int cluster = 600;
		int imageSize = 400;
		string descriptor = "sift";
		MyVocabolaryBuilder builder("train", descriptor, cluster, imageSize);
		builder.buildVocabolary();
		MySVMTrainer svmTrainer(descriptor, cluster, imageSize);
		svmTrainer.getBowSVM();
	*/
	
}
