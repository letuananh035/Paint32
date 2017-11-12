
#include "CCircle.h"
#include "Exception.h"
namespace Paint32{
	namespace Model{

		void CCircle::SetDraw(COLORREF color, COLORREF colorbg,
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
		void CCircle::Draw(HDC hDc, COLORREF color, COLORREF colorbg,
			POINT lefttop, POINT rightbottom,
			int iPenStyle, int iPenWidth, bool bSetRop)
		{
			//Lưu các thuộc tính để vẽ lại
			this->ColorBG = colorbg;
			this->Color = color;
			this->LeftTop = lefttop;
			this->RightBottom = rightbottom;

			this->PenStyle = iPenStyle;
			this->PenWidth = iPenWidth;
			//HDC hdc = GetDC(hwnd);
			//HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
			//SelectObject(hDc, hPen);

			if (bSetRop == true)
				SetROP2(hDc, R2_MERGEPENNOT);
			//
			//Màu nền
			SelectObject(hDc, GetStockObject(NULL_BRUSH)); //Trong suốt
			/*SetDCBrushColor(hDc, this->ColorBG);
			SelectObject(hDc, GetStockObject(DC_BRUSH));
			*/
			/*if (!Ellipse(hDc, lefttop.x, lefttop.y,
				rightbottom.x, rightbottom.y)){
				throw Exception(L"Lỗi Ellipse");
			}*/
			::Color color_;
			color_.SetFromCOLORREF(color);
			Graphics* graphics = new Graphics(hDc);
			Pen* pen = new Pen(color_, iPenWidth);
			pen->SetDashStyle((DashStyle)iPenStyle);
			graphics->DrawEllipse(pen, lefttop.x, lefttop.y, rightbottom.x - lefttop.x, rightbottom.y - lefttop.y);
			delete pen;
			delete graphics;

			//HatchBrush* myHatchBrush = new HatchBrush(
			//	HatchStyleCross,
			//	Color(255, 0, 255, 0),
			//	Color(255, 0, 0, 255));
			//
			//graphics->FillRectangle(myHatchBrush, 100, 50, 100, 30);

			//// ! Seperation drawing & filling
			//graphics->DrawRectangle(pen, 100, 50, 100, 30);

			

			//DeleteObject(hPen);
		}

		void CCircle::ReDraw(HDC hDc)
		{
			this->Draw(hDc, this->Color,this->ColorBG, this->LeftTop, this->RightBottom,
				this->PenStyle, this->PenWidth, false);
		}

		CShape* CCircle::CreateNewShape()
		{
			CShape* shape = new CCircle;
			return shape;
		}

		// Circle Fill

		void CCircleFill::SetDraw(COLORREF color, COLORREF colorbg,
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
		void CCircleFill::Draw(HDC hDc, COLORREF color, COLORREF colorbg,
			POINT lefttop, POINT rightbottom,
			int iPenStyle, int iPenWidth, bool bSetRop)
		{
			//Lưu các thuộc tính để vẽ lại
			this->ColorBG = colorbg;
			this->Color = color;
			this->LeftTop = lefttop;
			this->RightBottom = rightbottom;

			this->PenStyle = iPenStyle;
			this->PenWidth = iPenWidth;
			//HDC hdc = GetDC(hwnd);
			//HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
			//SelectObject(hDc, hPen);

			if (bSetRop == true)
				SetROP2(hDc, R2_MERGEPENNOT);
			//
			//Màu nền
			//SelectObject(hDc, GetStockObject(NULL_BRUSH)); //Trong suốt
			/*SetDCBrushColor(hDc, this->ColorBG);
			SelectObject(hDc, GetStockObject(DC_BRUSH));
			if (!Ellipse(hDc, lefttop.x, lefttop.y,
				rightbottom.x, rightbottom.y)){
				throw Exception(L"Lỗi Ellipse");
			}
			DeleteObject(hPen);*/

			::Color color_;
			color_.SetFromCOLORREF(color);
			Graphics* graphics = new Graphics(hDc);
			//Pen* pen = new Pen(color_, iPenWidth);
			//pen->SetDashStyle((DashStyle)iPenStyle);
			SolidBrush *brush = new SolidBrush(color_);
			Rect rec = Rect(lefttop.x, lefttop.y, rightbottom.x - lefttop.x, rightbottom.y - lefttop.y);
			graphics->FillEllipse(brush, rec);
			delete brush;
			delete graphics;

		}

		void CCircleFill::ReDraw(HDC hDc)
		{
			this->Draw(hDc, this->Color, this->ColorBG, this->LeftTop, this->RightBottom,
				this->PenStyle, this->PenWidth, false);
		}

		CShape* CCircleFill::CreateNewShape()
		{
			CShape* shape = new CCircleFill;
			return shape;
		}
	}
}
