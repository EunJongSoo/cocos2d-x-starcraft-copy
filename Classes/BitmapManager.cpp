#include "BitmapManager.h"
#include <Windows.h>

BitmapManager::BitmapManager()
{
}

BitmapManager::~BitmapManager()
{
}


unsigned char* BitmapManager::load_bitmap(char* filename)
{
	BITMAPINFOHEADER bi;
	FILE* f = fopen(filename, "rb");
	
	// BITMAPFILEHEADER 파일 14바이트 만큼 이동
	fseek(f, 14, SEEK_SET);											
	// 나머지 정보 BITMAPINFOHEADER 40바이트 저장
	fread(&bi, sizeof(unsigned char), sizeof(BITMAPINFOHEADER), f);	

	// unsigned char info[54];
	// fread(info, sizeof(unsigned char), 54, f);	// read the 54-byte header
													// extract image height and width from header
	
	// 가로, 세로 크기에 직접 접근												
	// int width = *(int*)&info[18];
	// int height = *(int*)&info[22];
	
	// 가로, 세로 크기로 사이즈를 계산
	// int size = 3 * width * height;

	// 저장된 값을 바로 대입한다.
	// int width = bi.biWidth;
	// int height = bi.biHeight;

	// 헤더 파일 사이즈 54바이트를 더해준다.
	int size = bi.biSize + 54;

	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel

	// 위치 지시자를 처음으로 돌려보내서
	fseek(f, 0, SEEK_SET);
	// 헤더파일까지 모두 읽는다.
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	 // b,g,r 배치를 r,g,b로 변경
	/*for (int i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}*/
	return data;
}
//
//// c
//unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader) {
//	FILE *filePtr; //our file pointer
//	BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
//	unsigned char *bitmapImage;  //store image data
//	int imageIdx = 0;  //image index counter
//	unsigned char tempRGB;  //our swap variable
//
//							//open filename in read binary mode
//	filePtr = fopen(filename, "rb");
//	if (filePtr == NULL)
//		return NULL;
//
//	//read the bitmap file header
//	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
//
//	//verify that this is a bmp file by check bitmap id
//
//	if (bitmapFileHeader.bfType != 0x4D42)
//	{
//		fclose(filePtr);
//		return NULL;
//	}
//
//	//read the bitmap info header
//	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
//
//	//move file point to the begging of bitmap data
//	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
//
//	//allocate enough memory for the bitmap image data
//	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
//
//	//verify memory allocation
//	if (!bitmapImage)
//	{
//		free(bitmapImage);
//		fclose(filePtr);
//		return NULL;
//	}
//
//	//read in the bitmap image data
//
//	// 사이즈가 없어서 수정했음
//	//sizeof(unsigned long),
//
//	fread(bitmapImage, sizeof(unsigned long), bitmapInfoHeader->biSizeImage, filePtr);
//
//	//make sure bitmap image data was read
//	if (bitmapImage == NULL)
//	{
//		fclose(filePtr);
//		return NULL;
//	}
//
//	//swap the r and b values to get RGB (bitmap is BGR)
//	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
//	{
//		tempRGB = bitmapImage[imageIdx];
//		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
//		bitmapImage[imageIdx + 2] = tempRGB;
//	}
//
//	//close file and return bitmap iamge data
//	fclose(filePtr);
//	return bitmapImage;
//}
//
//
////c++
//#include <windows.h>
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//using namespace std;
//int main(void){
//   BITMAPFILEHEADER    bf;
//   BITMAPINFOHEADER    bi;
//
//   ifstream fin;
//   fin.open("a.bmp", ios_base::in | ios_base::binary); //a.bmp파일을 바이트로 읽어 들인다..
//   fin.read((char*)&bf, sizeof(BITMAPFILEHEADER)); // 사이즈..
//
//   FILE *fp = fopen("a.bmp", "rb");   
//
//   fread(&bf, sizeof(unsigned char), sizeof(BITMAPFILEHEADER), fp);// 사이중 헤더에 사이즈 14바이트..
//   fread(&bi, sizeof(unsigned char), sizeof(BITMAPINFOHEADER), fp);// 나머지 정보 40바이트 저장..
//   unsigned char* data = (unsigned char*)malloc(bi.biSizeImage);
//   fread(data, sizeof(unsigned char), bi.biSizeImage, fp);
//  
//   int r, g, b, mean;
//   for(int x=0; x<bi.biHeight; x++){
//       for(int y=0; y<bi.biWidth*3; y=y+3){
//          
//           //printf("%d\t", x *(bi.biWidth*3) + y);
//           //printf("%d\t", x *(bi.biWidth*3) + y+1);
//           //printf("%d\t", x *(bi.biWidth*3) + y+2);
//           b = data[x *(bi.biWidth*3) + y];// *(data+x *(bi.biWidth*3) + y);
//           g = data[x *(bi.biWidth*3) + y+1];
//           r = data[x *(bi.biWidth*3) + y+2];
//          
//           /*mean = (r+g+b)/3;
//
//           data[x *(bi.biWidth*3) + y] = mean;
//           data[x *(bi.biWidth*3) + y+1] = mean;
//           data[x *(bi.biWidth*3) + y+2] = mean;*/
//       }
//   }
//   /*printf("%d\n", bi.biWidth*3*bi.biHeight);
//   printf("%d\n", bi.biSizeImage);*/
//  
//   ////평균
//   //int mean;
//   //for(int i=0; i<bi.biSizeImage; i = i+3){
//   //    //data[i] = 255-data[i];
//   //    mean = (data[i] + data[i+1] + data[i+2])/3;
//   //    data[i] = mean;
//   //    data[i+1] = mean;
//   //    data[i+2] = mean;
//   //}
//
//   fclose(fp);
//  
//   // b.bmp파일에 다시 기록..
//   fp = fopen("b.bmp", "wb");
//   fwrite(&bf, sizeof(unsigned char), sizeof(BITMAPFILEHEADER), fp);
//   fwrite(&bi, sizeof(unsigned char), sizeof(BITMAPINFOHEADER), fp);
//   fwrite(data, sizeof(unsigned char), bi.biSizeImage, fp);
//   fclose(fp);
//  
//   free(data);
//   return 0;
//