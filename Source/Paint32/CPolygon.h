#pragma once

#ifndef CPOLYGON_H
#define PAINT32 __declspec(dllexport)
#else
#define PAINT32 __declspec(dllimport)
#endif

#include <vector>
using namespace std;

#include "CShape.h"
#include "CLine.h"
namespace Paint32{
	namespace Model{
		class PAINT32 CPolygon : public CShape
		{
		private:
			vector<CLine*> Lines; //C: Đa giác gồm nhiều đường ghép lại
			bool AddLine = false;
		public:
			virtual void SetDraw(COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle = PS_SOLID, int iPenWidth = 1, bool bSetRop = TRUE);
			void Draw(HDC hDc, COLORREF color, COLORREF colorbg,
				POINT lefttop, POINT rightbottom,
				int iPenStyle = PS_SOLID, int iPenWidth = 1, bool bSetRop = true);

			void ReDraw(HDC hDc);
			CShape* CreateNewShape();
			POINT GetFirst();
			POINT GetLast();
			void SetAddLine(){ this->AddLine = true; }
			~CPolygon(){
				for (int i = 0; i < Lines.size(); ++i){
					delete Lines[i];
				}
				Lines.clear();
			}
			void write(ofstream *out);
			void read(ifstream *in);

			string getType(){ return "Polygon"; }
		};
		bool operator==(const POINT& p1, const POINT& p2);
	}
}


