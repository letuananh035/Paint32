
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

			::Color color_;
			color_.SetFromCOLORREF(color);
			Graphics* graphics = new Graphics(hDc);
			Pen* pen = new Pen(color_, iPenWidth);
			pen->SetDashStyle((DashStyle)iPenStyle);
			graphics->DrawEllipse(pen, lefttop.x, lefttop.y, rightbottom.x - lefttop.x, rightbottom.y - lefttop.y);
			delete pen;
			delete graphics;
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
			::Color color_;
			color_.SetFromCOLORREF(colorbg);
			Graphics* graphics = new Graphics(hDc);
			SolidBrush *brush = new SolidBrush(color_);
			Rect rec = Rect(lefttop.x, lefttop.y, rightbottom.x - lefttop.x, rightbottom.y - lefttop.y);
			graphics->FillEllipse(brush, rec);
			
			//Viền
			::Color color_bg;
			color_bg.SetFromCOLORREF(color);
			Graphics* graphics_bg = new Graphics(hDc);
			Pen* pen = new Pen(color_bg, iPenWidth);
			pen->SetDashStyle((DashStyle)iPenStyle);
			graphics_bg->DrawEllipse(pen, lefttop.x, lefttop.y, rightbottom.x - lefttop.x, rightbottom.y - lefttop.y);
			delete graphics_bg;
			delete pen;

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
