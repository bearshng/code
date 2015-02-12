
#include <iostream>
#include <string>
#include <io.h>
#include <dirent.h>
#include <fstream>
//#ifndef _UNISTD_H
//#include <unistd.h>
//#define _UNISTD_H
//#include <io.h>
//#include <process.h>
//#endif /* _UNISTD_H */
#include <sys/stat.h>
#include <sys/types.h>
#include <opencv2/opencv.hpp>
#include <windows.h>  
using namespace std;
using namespace cv;
void getFiles(string path, vector<string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;

	if ((hFile = _findfirst(p.assign(path).append("*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//	如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

}


int char_to_class(char c) {
	switch (c) {
	case 'b':
		return 1;
		break;
	case 'c':
		return 2;
		break;
	
	case 'd':
		return 3;
		break;
	case 'f':
	
		return 4;
		break;
	case 'h':
	
		return 5;
		break;
	case 'k':
	
		return 6;
		break;
	case 'l':

		return 7;
		break;
	case 't':
	
		return 8;
		break;
	case 'w':
	
		return 9;
		break;
	case 'u':
	
		return 10;
		break;
	
	}
}

int main(int argc, char** argv){
	if (argc < 3){
		std::cout << "enter objectClassification.exe dataSet outputFileName.txt ";
		getchar();
		exit(0);
	}
	string fileName;
	char * filePath = argv[1];
	vector<string> files;
	////获取该路径下的所有文件
	getFiles(filePath, files);
	ofstream ofs(argv[2], fstream::out);
	int size = files.size();
	
	for (int i = 0; i < size; i++)
	{

		fileName = files[i].c_str();
		int x = fileName.rfind('\\');
		int y = fileName.rfind('/');
		x = max(y,x);
		char c = fileName[x+1];
		std::cout << x<<c << std::endl;
		int sampleClass=char_to_class(c);
		std::cout << fileName << "\t" << sampleClass << "\n";
		ofs << fileName<<"\t"<<sampleClass<<"\n";

	}
	ofs<<flush; ofs.close();

}
