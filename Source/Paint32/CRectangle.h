#pragma once

#ifndef CRECTANGLE_H
#define PAINT32 __declspec(dllexport)
#else
#define PAINT32 __declspec(dllimport)
#endif

#include "CShape.h"
namespace Paint32{
	namespace Model{
		class PAINT32 CRectangle : public CShape
		{
		public:
			virtual void SetDraw(COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle = PS_SOLID, int iPenWidth = 1, bool bSetRop = TRUE);
			void Draw(HDC hDc, COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle = PS_SOLID, int iPenWidth = 1, bool bSetRop = true);

			void ReDraw(HDC hDc);
			CShape* CreateNewShape();

			string getType(){ return "Rectangle"; }
		};


		class PAINT32 CRectangleFill : public CShape
		{
		public:
			virtual void SetDraw(COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle = PS_SOLID, int iPenWidth = 1, bool bSetRop = TRUE);
			void Draw(HDC hDc, COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle = PS_SOLID, int iPenWidth = 1, bool bSetRop = true);

			void ReDraw(HDC hDc);
			CShape* CreateNewShape();

			string getType(){ return "Rectangle"; }
		};
	}
}


