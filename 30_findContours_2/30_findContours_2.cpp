// 30_findContours_2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<algorithm>
using namespace std;
using namespace cv;
int main()
{
	//��ȡ���ص�һ��ͼƬ����ͼ���ֵ������ͨ����,��Ӳ�ҵĸ��� �����״̬��!
	cv::Mat srcMat = imread("C:/Users/lenovo/Desktop/��ͼͼƬ/die_on_chip.png");
	//��ֵ��
	Mat g_src, labels, stats, centroids, open_src;
	threshold(srcMat, g_src, 120, 255, THRESH_BINARY);
	//��ͨ������
	std::vector<cv::Mat>g_src_part(g_src.channels());//������ͨ������Ŀ��ȵ�ͼ������
	cv::split(g_src, g_src_part);//�ֽ���ͨ������Ŀ��ȵ�ͼ������
								 //���ýṹԪ��+��̬����
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(7, 7), Point(-1, -1));
	morphologyEx(g_src_part[0], open_src, MORPH_OPEN, element, Point(-1, -1));
	//��ͨ����
	int num = cv::connectedComponentsWithStats(open_src, labels, stats, centroids);
	//����
	int i_num = num - 1;
	for (int i = 1; i <= i_num; i++)
	{
		cv::Rect rect;
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);
		if (rect.width > 20)
		{
			rectangle(srcMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);
		}
		else
		{
			num -= 1;
		}
	}
	imshow("src", srcMat);
	std::cout << "������" << num - 1 << std::endl;
	//�ȴ��û�����
	waitKey(0);
	return 0;
}

