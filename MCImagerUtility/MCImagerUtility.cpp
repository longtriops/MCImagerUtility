#include <iostream>
#include <fstream>
#include <math.h>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include "CIEDE2000.h"

using namespace std;
namespace fs = std::filesystem;

using namespace cv;
using namespace CIEDE2000;

const int L = 0;
const int A = 1;
const int B = 2;

const string workdir = fs::current_path().string();

/*
vector<string> recordTextureFiles(string directory) {
	//move code to here/respective file 
}*/

int main(){
	//check if texture color file exists if not, do the processing for textures
	//otherwise, process image and output block form
	//get list of all texture files
	vector<std::string> alltextures;
	string texturedir = workdir + "/textures";

	for (const auto& entry : fs::directory_iterator(texturedir)) {
		alltextures.push_back(entry.path().filename().string());
	}

	ofstream avgColorFile;
	avgColorFile.open(workdir + "/colors.txt");

	//go through list of texture files and generate avg. color of each file
	for (int i = 0; i < alltextures.size(); i++) {
		Mat text = imread(texturedir + "/" + alltextures[i]);
		//if can't open image/not valid
		if (text.empty()) {
			cout << "Could not open image" << endl;
			cin.get();
			return -1;
		}

		cvtColor(text, text, COLOR_BGR2Lab);

		double textL = 0;
		double textA = 0;
		double textB = 0;
		for (int y = 0; y < text.rows; y++) {
			for (int x = 0; x < text.cols; x++) {
				Vec3b intensity = text.at<Vec3b>(y, x);
				textL += intensity.val[L];
				textA += intensity.val[A];
				textB += intensity.val[B];
			}
		}
		int totPixels = text.rows * text.cols;
		textL = textL / totPixels;
		textA = textA / totPixels;
		textB = textB / totPixels;
		
		//write this information to structure/file to save
		//LAB test = { textL, textA, textB };
		avgColorFile << alltextures[i];
		//converting from opencv value range to regular Lab
		avgColorFile << " " << textL/(255/100) << " " << textA-128 << " " << textB-128 << endl;
	}

	avgColorFile.close();

	//vector<vector<std::string>> labs(alltextures.size(), vector<;

	/*
	Mat image = imread(workdir + "/" + "gorilla.jpg");
	cvtColor(image, image, COLOR_BGR2Lab);

	//choose data structure for the texture labs!!
	
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Vec3b intensity = image.at<Vec3b>(i, j);
			double pixL = intensity.val[L];
			double pixA = intensity.val[A];
			double pixB = intensity.val[B];
			
		}
	}*/

	/*
	String afterConv = "After OPENCV cvtColor";
	namedWindow(afterConv);
	imshow(afterConv, imlab);
	waitKey(0);
	destroyWindow(afterConv);
	*/
	return 0;
}