#pragma once

#ifndef LAYER_H
#define PAINT32 __declspec(dllexport)
#else
#define PAINT32 __declspec(dllimport)
#endif
#include <vector>
#include "CLine.h"
#include "CPolygon.h"
#include "CCircle.h"
#include "CRectangle.h"

namespace Paint32{
	class PAINT32 Layer
		{
		private:
			vector <Model::CShape*> Shapes;
			HDC hDc = NULL;
			HDC hDcBG = NULL;
			HBITMAP hBmp = NULL;
			SIZE sizeHDC;
			POINT offset;
		public:
			Layer(){
				this->offset.x = 0;
				this->offset.y = 0;
				this->sizeHDC.cx = 0;
				this->sizeHDC.cy = 0;
			}
			/*Tạo HDC cho layer*/
			bool Create(SIZE size);
			/*Thêm shape cho layer*/
			void AddShape(Model::CShape* shape);
			/*Xóa shape cho layer*/
			void RemoveShape();
			/*Vẽ HDC vào HDC main*/
			void DrawToMain(HDC hDcMain, POINT point, bool Sel);
			/*Xóa bộ nhớ*/
			void Release();
			
			/*GetSize*/
			int GetSize(){ return Shapes.size(); }
			/**/
			Model::CShape*& GetShape(int i);
			/**/
			static HDC GetParentHDC(HWND hWnd);

			static HDC CreateHDC(SIZE size);

			void SetOffset(POINT offset);

			POINT GetOffset() { return this->offset; }

			void read(ifstream *in);
			void write(ofstream *out);

			void SetBackGround(HINSTANCE hInst, LPWSTR path);
		};
}


