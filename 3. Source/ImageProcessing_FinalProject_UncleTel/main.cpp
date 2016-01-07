#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "Funcs.h"

using namespace std;
using namespace cv;

int main()
{
	Info info;

	printf("Input file path: ");
	scanf("%s", info.filePath);
	//strcpy(info.filePath, "E:\\Pics\\3.jpg");
	info.img = imread(info.filePath, CV_LOAD_IMAGE_GRAYSCALE);

	// Không tìm thấy file hoặc file không phù hợp
	if (info.img.empty())
	{
		printf("\nInvalid file!\n\nExiting...\n");
		return 0;
	}

	printf("\nPicture loaded successfully!\n");
	printf("Use your mouse to select a rectangular area.\n");

	namedWindow(info.filePath);

	// Đặt một hàm xử lý sự kiện chuột cho cửa sổ
	setMouseCallback(info.filePath, onMouse, &info);
	
	imshow(info.filePath, info.img);
	waitKey(0);

	// Lưu kết quả ra file
	saveResult(info.img, info.filePath);
	printf("\nExiting...\n");
	return 0;
}