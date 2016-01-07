#pragma once

#include <opencv2\core\core.hpp>

#define MAX_STRING 256

struct Info
{
	// Ảnh
	cv::Mat img;

	// Đường dẫn đến file ảnh
	char filePath[MAX_STRING];
};

// Hàm xử lý sự kiện chuột
// Con trỏ data trỏ tới biến kiểu struct Info
void onMouse(int eventID, int x, int y, int flags, void* data);

// Phép dãn ảnh src trên vùng (x1, y1) - (x2, y2)
void grayDilate(cv::Mat &src, int x1, int y1, int x2, int y2);

// Phép co ảnh src trên vùng (x1, y1) - (x2, y2)
void grayErode(cv::Mat &src, int x1, int y1, int x2, int y2);

// Lưu ảnh kết quả ra file
void saveResult(cv::Mat &res, const char* filePath);