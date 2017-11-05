#pragma once

#ifndef CLINE_H
#define PAINT32 __declspec(dllexport)
#else
#define PAINT32 __declspec(dllimport)
#endif

#include "CShape.h"

namespace Paint32{
	namespace Model{
		class PAINT32 CLine : public CShape
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
			POINT GetLefttop();

			string getType(){ return "Line"; }
		};
	}
}


