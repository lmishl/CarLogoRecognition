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
#include <filesystem>


using namespace std;
using namespace std::tr2::sys;

struct Logo
{
	string name;
	cv::CascadeClassifier classifier;
	Logo(string _name, cv::CascadeClassifier _classifier)
	{
		name = _name;
		classifier = _classifier;
	}
};


int main()
{

	//загружаем логотипы
	vector<Logo> logos;
	path pathToLogos = "C:\\Users\\NoteBook\\Dropbox\\Univer\\CarLogoRecognition\\CarLogoRecognition\\Logo"; 
	string cur, next;

	for(directory_iterator it(pathToLogos); it != directory_iterator(); ++it)
	{
		cur = pathToLogos.string() + "/" + it->path().string();
		cv::CascadeClassifier cascadeSymbol;
		cascadeSymbol.load(cur);
		logos.emplace_back(it->path().basename(),cascadeSymbol);
	}



	//Начинаем перебирать фотки
	path pathToPhotos = "C:\\CarModel\\хундай";// "C:\\curs\\Test"; 

	for(directory_iterator it(pathToPhotos); it != directory_iterator(); ++it)
	{
		cur = pathToPhotos.string() + "/" + it->path().string();
		std::cout << cur << "\n";

		cv::Mat src = cv::imread(cur, cv::IMREAD_COLOR); // Инициализация изображения
		cv::Mat gray;
		cvtColor(src, gray, cv::COLOR_BGR2GRAY); // Перевод в чёрно-белое

		for(auto& logo : logos)
		{
			std::vector<cv::Rect> symbols;
			logo.classifier.detectMultiScale(gray, symbols); // Поиск с помощью каскада
			for(auto& p : symbols)
			{
				cv::Point symbolBegin	= cv::Point(p.x, p.y);
				cv::Point symbolEnd		= cv::Point(p.x+p.width, p.y+p.height);

				std::cout << "X: " << p.x << " Y: " << p.y << " Width: " << p.width << " Height: " << p.height << std::endl;

				rectangle(src, symbolBegin, symbolEnd, cv::Scalar(0,255,0), 2);	
				cv::Point text = cv::Point(symbolBegin.x, symbolBegin.y -3);
				cv::putText(src, logo.name, text, CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255), 1,8, false);
			}
		}


		cv::imshow("Test", src);
		cv::waitKey(0);

	}

	return 0;
}