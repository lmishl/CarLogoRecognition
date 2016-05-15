#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <algorithm>
#include <iostream>
#include <math.h>
#include<windows.h>
#pragma comment (lib, "shell32.lib ")

using namespace std;




int main()
{
	int q=0;
	int w=0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	string s = "c:\\cascade\\������\\";//"C:\\CarModel\\������\\";//"C:\\curs\\False\\";"
	string first = s + "*";
	hf=FindFirstFile(first.c_str(), &FindFileData);
	if (hf!=INVALID_HANDLE_VALUE)
	{
		cv::CascadeClassifier cascadeSymbol; // ���������� �������
		bool cascadeSymbolLoad = cascadeSymbol.load("nissan.xml"); // �������� �������

		if(!cascadeSymbolLoad)
		{
			std::cerr << "Cascade not load. Check your directory \"haarcascade_russian_plate_number_symbol.xml\"" << std::endl;
			return false;
		}


		do{
			if(FindFileData.cFileName[0] == '.')
				continue;

			std::cout << FindFileData.cFileName << "\n";
			try
			{
				cv::Mat src = cv::imread(s + FindFileData.cFileName, cv::IMREAD_COLOR); // ������������� �����������

				cv::Mat gray;
				cvtColor(src, gray, cv::COLOR_BGR2GRAY); // ������� � �����-�����
				


				std::vector<cv::Rect> symbols;
				cascadeSymbol.detectMultiScale(gray, symbols); // ����� � ������� �������
				w++;
				for(auto& p : symbols)
				{
					cv::Point symbolBegin	= cv::Point(p.x, p.y);
					cv::Point symbolEnd		= cv::Point(p.x+p.width, p.y+p.height);

					std::cout << "X: " << p.x << " Y: " << p.y << " Width: " << p.width << " Height: " << p.height << std::endl;
					q++;

					rectangle(src, symbolBegin, symbolEnd, cv::Scalar(0,255,0), 2);	
				}


				/*cv::imshow("Test", src);
				cv::waitKey(0);*/
			}
			catch(exception e)
			{
				cout<<e.what();
				continue;
			}


		}
		while (FindNextFile(hf,&FindFileData)!=0);
		FindClose(hf);
		cout<<w<<endl<<q<<endl<<100.0 * q / w;
		cv::waitKey(0);

	}
	return 0;
}