
#include "CLine.h"
#include "Exception.h"
namespace Paint32{
	namespace Model{
		void CLine::SetDraw(COLORREF color, COLORREF colorbg,
			POINT lefttop, POINT rightbottom,
			int iPenStyle, int iPenWidth, bool bSetRop){
			this->ColorBG = colorbg;
			this->Color = color;
			this->LeftTop = lefttop;
			this->RightBottom = rightbottom;

			this->PenStyle = iPenStyle;
			this->PenWidth = iPenWidth;
			this->SetRop = bSetRop;
		}

		void CLine::Draw(HDC hDc, COLORREF color, COLORREF colorbg,
			POINT lefttop, POINT rightbottom,
			int iPenStyle, int iPenWidth, bool bSetRop)
		{
			//Lưu lại các thuộc tính để vẽ lại
			this->ColorBG = colorbg;
			this->Color = color;
			this->LeftTop = lefttop;
			this->RightBottom = rightbottom;

			this->PenStyle = iPenStyle;
			this->PenWidth = iPenWidth;

			//HDC hdc = GetDC(hwnd);

			if (bSetRop == true)
				SetROP2(hDc, R2_MERGEPENNOT);

			//HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
			//SelectObject(hDc, hPen);
			//if (!MoveToEx(hDc, lefttop.x, lefttop.y, NULL)){
			//	throw Exception(L"Lỗi MoveToEx");
			//	return;
			//}
			//if(!LineTo(hDc, rightbottom.x, rightbottom.y)){
			//	throw Exception(L"Lỗi LineTo");
			//	return;
			//}
			//DeleteObject(hPen);

			::Color color_;
			color_.SetFromCOLORREF(color);
			Graphics* graphics = new Graphics(hDc);
			Pen* pen = new Pen(color_, iPenWidth);
			pen->SetDashStyle((DashStyle)iPenStyle);
			graphics->DrawLine(pen, lefttop.x, lefttop.y, rightbottom.x, rightbottom.y);
			delete pen;
			delete graphics;

			//ReleaseDC(hwnd, hdc);
		}

		void CLine::ReDraw(HDC hDc)
		{
			this->Draw(hDc, this->Color,this->ColorBG, this->LeftTop, this->RightBottom,
				this->PenStyle, this->PenWidth, false);
		}

		CShape* CLine::CreateNewShape()
		{
			CShape* shape = new CLine;
			return shape;
		}

		POINT CLine::GetLefttop(){ 
			return this->LeftTop; 
		};
	}
}
