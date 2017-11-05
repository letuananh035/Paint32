#pragma once

#ifndef SCROLL_H
#define PAINT32 __declspec(dllexport)
#else
#define PAINT32 __declspec(dllimport)
#endif

#include "Exception.h"
namespace Paint32{
	namespace UI{
		class PAINT32 Scroll
		{
		private:
			int scrollY;
			int scrollX;
		public:
			Scroll(){ this->scrollX = this->scrollY = 0; }
			/*Tạo ScrollX và ScrollY*/
			void CreateScroll(HWND hWnd);
			int getScrollX(){ return this->scrollX; }
			int getScrollY(){ return this->scrollY; }
			/*Di chuyển ScrollX*/
			void MoveScrollX(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/*Di chuyển ScrollY*/
			void MoveScrollY(HWND hWnd, WPARAM wParam, LPARAM lParam);
		};
	}
}


