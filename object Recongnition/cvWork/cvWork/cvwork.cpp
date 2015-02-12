#include "cvwork.h"
#include <QMessageBox>
#include<QFileDialog>
#include<Qstring>
#include<QImage>
#include<QPixmap>

cvWork::cvWork(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Qt::WindowFlags flags = 0;
	//flags |= Qt::WindowMinimizeButtonHint;
	setWindowFlags(flags); // 设置禁止最大化
	setFixedSize(721, 529); // 禁止改变窗口大小。
	ui.siftBtn->setVisible(false);
	ui.surfBtn->setVisible(false);
	
}

cvWork::~cvWork()
{

}
void cvWork::on_surfBtn_clicked()
{
	string res=predict("surf");
	QMessageBox::about(this, tr("Informaition"), tr(res.c_str()));

}
void cvWork::on_siftBtn_clicked()
{
	string res = predict("sift");
	QMessageBox::about(this, tr("Informaition"), tr(res.c_str()));
}
void cvWork::on_actionOpen_triggered()
{
	// Qstring fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*);;mp3file(*.mp3)"));

	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF)"),
		0);
	if (filename.isEmpty())
	{
		QMessageBox::about(this, tr("Information"), tr("Can not open file!"));
	}
	else
	{
		QImage *img2 = new QImage;
		//QMessageBox::about(this, tr("提示信息"), tr(filename.toStdString().c_str()));
		this->setImagePath(filename.toStdString());
		std::cout << filename.toStdString();
		if (!(img2->load(filename))) //加载图像
		{
			QMessageBox::information(this,
				tr("Fail to open file"),
				tr("Fail to open file!"));
			return;
		}
		QImage * imgScaled = new QImage;
			*imgScaled = img2->scaled(400,
			400,
			Qt::KeepAspectRatio);
		ui.imageLabel->setPixmap(QPixmap::fromImage(*imgScaled)); //显示图像
		ui.siftBtn->setVisible(true);
		ui.surfBtn->setVisible(true);
		
	}
}

string cvWork::predict(string descriptor){
	Mat image = imread(this->imagePath);
	MyObjectPredictor predictor(descriptor,600,400);
	Mat point=predictor.getPointMat(image);
	map<float,string> max_class;
	int res1 = predictor.predictOneImage(image, max_class);
	string res = predictor.getObjectType(res1);
	map<float, string>::iterator it;
	int count = 0;
	string ss= "\btop five objects possible:\n";
	for (it = max_class.begin(); count != 5; ++it){

		ss = ss+"\t"+ it->second+"\n";
		count++;
	}

	ui.topLabel->setText(tr(ss.c_str()));
	cv::cvtColor(point, point, CV_BGR2RGB);
	QImage *qimg = new QImage((const  unsigned char*)point.data, // uchar* data
		point.cols, point.rows, // width height
		point.step, //bytesPerLine
		QImage::Format_RGB888); //format
	QImage * imgScaled = new QImage;
	*imgScaled = qimg->scaled(400,
		400,
		Qt::KeepAspectRatio);
	ui.imageLabel->setPixmap(QPixmap::fromImage(*imgScaled)); //显示图像
	return res;
}
void cvWork::setImagePath(string path){
	this->imagePath = path;
}