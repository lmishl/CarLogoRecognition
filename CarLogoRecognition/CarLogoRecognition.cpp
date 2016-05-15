#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string.h>
#include<windows.h>
#include <filesystem>
//#pragma comment (lib, "shell32.lib ")

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
	//std::tr2::sys::path dir = "c:\\cascade\\гранта\\";
	//std::tr2::sys::directory_iterator  iter(dir);

	//path last, next; 
	//do
	//{
	//	std::cout << iter->path()<<endl;
	//	last = iter->path();
	//	next = (++iter)->path();
	//}while(last.string().compare(next.string()));

	//return 0;

	int findedCnt = 0;
	int allCnt = 0;
	

	//загружаем логотипы
	vector<Logo> logos;
	//относительный путь не работает(((  надо было делать на шарпе((
	path pathToLogos = "C:\\Users\\NoteBook\\Dropbox\\Univer\\CarLogoRecognition\\CarLogoRecognition\\Logo"; 
	directory_iterator  iterL(pathToLogos);
	string cur, next;
	int cnt = 0;
	do
	{
		cur = iterL->path().string();
		cv::CascadeClassifier cascadeSymbol(cur);
		logos.emplace_back(cur,cascadeSymbol);
		iterL++;

		//next = iterL->path().string();
		cnt++;

	}while(cnt<9);//cur.compare(next));
	

	//Начинаем перебирать фотки
	path pathToPhotos = "C:\\CarModel\\хонда";// "C:\\curs\\Test"; 
	directory_iterator  iterP(pathToPhotos);
	path curP;
	do
	{
		curP = iterP->path();
		cur = pathToPhotos.string() + "/" + iterP->path().string();
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
				findedCnt++;
			
				rectangle(src, symbolBegin, symbolEnd, cv::Scalar(0,255,0), 2);	
				cv::putText(src, logo.name, symbolBegin, CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255), 1,8, false);
			}
			

		}


		cv::imshow("Test", src);
				cv::waitKey(0);

		next = (++iterP)->path().string();
	}while(cur.compare(next));



	//string s = "c:\\cascade\\гранта\\";//"C:\\CarModel\\ниссан\\";//"C:\\curs\\False\\";"
	//

	//cv::CascadeClassifier cascadeSymbol; // Объявление каскада
	//bool cascadeSymbolLoad = cascadeSymbol.load("nissan.xml"); // Загрузка каскада

	//if(!cascadeSymbolLoad)
	//{
	//	std::cerr << "Cascade not load. Check your directory \"haarcascade_russian_plate_number_symbol.xml\"" << std::endl;
	//	return false;
	//}


	//	do{


	//		//std::cout << FindFileData.cFileName << "\n";
	//		try
	//		{
	//			cv::Mat src = cv::imread(s + FindFileData.cFileName, cv::IMREAD_COLOR); // Инициализация изображения

	//			cv::Mat gray;
	//			cvtColor(src, gray, cv::COLOR_BGR2GRAY); // Перевод в чёрно-белое
	//			


	//			std::vector<cv::Rect> symbols;
	//			cascadeSymbol.detectMultiScale(gray, symbols); // Поиск с помощью каскада
	//			allCnt++;
	//			for(auto& p : symbols)
	//			{
	//				cv::Point symbolBegin	= cv::Point(p.x, p.y);
	//				cv::Point symbolEnd		= cv::Point(p.x+p.width, p.y+p.height);

	//				std::cout << "X: " << p.x << " Y: " << p.y << " Width: " << p.width << " Height: " << p.height << std::endl;
	//				findedCnt++;

	//				rectangle(src, symbolBegin, symbolEnd, cv::Scalar(0,255,0), 2);	
	//			}


	//			/*cv::imshow("Test", src);
	//			cv::waitKey(0);*/
	//		}
	//		catch(exception e)
	//		{
	//			cout<<e.what();
	//			continue;
	//		}


	//	}
	//	//while (FindNextFile(hf,&FindFileData)!=0);
	//	//FindClose(hf);
	//	cout<<endl<<allCnt<<" from "<<findedCnt<<endl<<100.0 * findedCnt / allCnt;
	//	cv::waitKey(0);

	
	return 0;
}