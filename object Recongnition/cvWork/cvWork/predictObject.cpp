

#include "predictCommon.h"


int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "enter objectDetection.exe 识别对象名称.png" << endl;
		return 1;
	}

	MyObjectPredictor predictor;

	predictor.setDebug(false);

	Mat __img = imread(argv[1]);
	resize(__img, __img, Size(300, 300), 0, 0, CV_INTER_LINEAR);
	vector<string> max_class;
	int res=predictor.evaluateOneImage(__img, max_class);
	std::cout<<predictor.getObjectType(res);
	/*cout << max_class[0];
	if (max_class.size()>1) {
		cout << "," << max_class[1];
	}
	cout << endl;*/

	return 0;
}