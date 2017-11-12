#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>
#include <string>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
using namespace std;
namespace Paint32{
	namespace Model{
		class CShape
		{
		protected:
			COLORREF Color;
			COLORREF ColorBG;
			int PenStyle;
			int PenWidth;
			bool SetRop;
			POINT LeftTop;
			POINT RightBottom;
		public:
			virtual void SetDraw(COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle, int iPenWidth, bool bSetRop = TRUE) = 0;
			virtual void Draw(HDC hDc, COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle, int iPenWidth, bool bSetRop = TRUE) = 0;
			virtual void ReDraw(HDC hDc) = 0;
			virtual CShape* CreateNewShape() = 0;
			virtual string getType() = 0;
			virtual void write(ofstream *out){
				out->write((char *) &this->Color, sizeof(COLORREF));
				out->write((char *)	&this->ColorBG, sizeof(COLORREF));
				out->write((char *) &this->PenStyle, sizeof(int));
				out->write((char *) &this->PenWidth, sizeof(int));
				out->write((char *) &this->SetRop, sizeof(bool));
				int data = this->LeftTop.x;
				out->write((char *)&data, sizeof(int));
				data = this->LeftTop.y;
				out->write((char *) &data, sizeof(int));
				data = this->RightBottom.x;
				out->write((char *) &data, sizeof(int));
				data = this->RightBottom.y;
				out->write((char *) &data, sizeof(int));

			}

			virtual void read(ifstream *in){
				in->read((char *)&this->Color, sizeof(COLORREF));
				in->read((char *)&this->ColorBG, sizeof(COLORREF));
				in->read((char *)&this->PenStyle, sizeof(int));
				in->read((char *)&this->PenWidth, sizeof(int));
				in->read((char *)&this->SetRop, sizeof(bool));
				int data;
				in->read((char *)&data, sizeof(int));
				this->LeftTop.x = data;
				in->read((char *)&data, sizeof(int));
				this->LeftTop.y = data;
				in->read((char *)&data, sizeof(int));
				this->RightBottom.x = data;
				in->read((char *)&data, sizeof(int));
				this->RightBottom.y = data;

			}
		};
	}
}

