#ifndef CVWORK_H
#define CVWORK_H
#include <QTextCodec>
#include <QtWidgets/QMainWindow>
#include "ui_cvwork.h"
#include <string>
#include "predictUtil.h"

using  namespace std;
class cvWork : public QMainWindow
{
	Q_OBJECT

public:
	cvWork(QWidget *parent = 0);
	~cvWork();
	string predict(string descriptor);
	void setImagePath(string path);
private slots:
	void on_surfBtn_clicked();
	void on_siftBtn_clicked();
	void on_actionOpen_triggered();

private:
	Ui::cvWorkClass ui;
	string imagePath;
	QImage * imgScaled;
	
};

#endif // CVWORK_H
