#include "Funcs.h"
#include <Windows.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

void onMouse(int eventID, int x, int y, int flags, void* data)
{
	static int x1, x2, y1, y2;

	Info* pInfo = (Info*)data;
	Mat tmp;
	cvtColor(pInfo->img, tmp, CV_GRAY2BGR);

	switch (eventID)
	{
	case EVENT_LBUTTONDOWN:
		x1 = x2 = x;
		y1 = y2 = y;
		break;

	case EVENT_LBUTTONUP:
		x2 = min(pInfo->img.cols - 1, max(0, x)), y2 = min(pInfo->img.rows - 1, max(0, y));
		if (x2 != x1 && y2 != y1)
		{
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			// Thông báo vùng chọn lên console
			printf("\nSelection area: (%d,%d) - (%d,%d).\nProcessing...", x1, y1, x2, y2);

			// Xử lý vùng được chọn
			grayErode(pInfo->img, x1, y1, x2, y2);
			grayErode(pInfo->img, x1, y1, x2, y2);
			grayDilate(pInfo->img, x1, y1, x2, y2);
			grayDilate(pInfo->img, x1, y1, x2, y2);

			// Thông báo kết thúc
			printf(" Done!\n");
		}

		imshow(pInfo->filePath, pInfo->img);
		break;

	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON)
		{
			x2 = min(pInfo->img.cols, max(0, x)), y2 = min(pInfo->img.rows, max(0, y));
			if (x2 != x1 && y2 != y1)
			{
				rectangle(tmp, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 2);
				imshow(pInfo->filePath, tmp);
			}
			else
				imshow(pInfo->filePath, pInfo->img);
		}
		break;
	}
}

void grayDilate(Mat &src, int x1, int y1, int x2, int y2)
{
	Mat res = src.clone();

	for (int x = x1; x <= x2; ++x)
	for (int y = y1; y <= y2; ++y)
	{
		int tmp = 0;
		int xx1 = max(0, x - 1), xx2 = min(src.cols - 1, x + 1);
		int yy1 = max(0, y - 1), yy2 = min(src.rows - 1, y + 1);

		for (int i = xx1; i <= xx2; ++i)
		for (int j = yy1; j <= yy2; ++j)
			tmp = max(tmp, src.at<uchar>(j, i));

		res.at<uchar>(y, x) = tmp;
	}

	res.copyTo(src);
}

void grayErode(Mat &src, int x1, int y1, int x2, int y2)
{
	Mat res = src.clone();

	for (int x = x1; x <= x2; ++x)
	for (int y = y1; y <= y2; ++y)
	{
		int tmp = 255;
		int xx1 = max(0, x - 1), xx2 = min(src.cols - 1, x + 1);
		int yy1 = max(0, y - 1), yy2 = min(src.rows - 1, y + 1);

		for (int i = xx1; i <= xx2; ++i)
		for (int j = yy1; j <= yy2; ++j)
			tmp = min(tmp, src.at<uchar>(j, i));

		res.at<uchar>(y, x) = tmp;
	}

	res.copyTo(src);
}

void saveResult(Mat &res, const char* filePath)
{
	printf("\n");
	char outFilePath[MAX_STRING];
	char cmd[MAX_STRING];
	strcpy(outFilePath, filePath);
	char* tmp = (char*)filePath + strlen(filePath) - 1;
	while (*tmp != '\\' && *tmp != '/' && tmp != filePath)
		--tmp;
	if (*tmp == '\\' || *tmp == '/')
		++tmp;
	outFilePath[tmp - filePath] = '\0';

	sprintf(outFilePath, "%sresult/", outFilePath);
	sprintf(cmd, "mkdir \"%s\"", outFilePath);
	system(cmd);
	
	sprintf(outFilePath, "%s%s", outFilePath, tmp);
	imwrite(outFilePath, res);

	printf("Result saved to %s.\n", outFilePath);
}