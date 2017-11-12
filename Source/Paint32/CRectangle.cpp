
#include "CRectangle.h"
#include "Exception.h"
namespace Paint32{
	namespace Model{

		void CRectangle::SetDraw(COLORREF color, COLORREF colorbg,
			POINT lefttop, POINT rightbottom,
			int iPenStyle, int iPenWidth, bool bSetRop){
			this->Color = color;
			this->ColorBG = colorbg;
			this->LeftTop = lefttop;
			this->RightBottom = rightbottom;

			this->PenStyle = iPenStyle;
			this->PenWidth = iPenWidth;
			this->SetRop = bSetRop;
		}
		void CRectangle::Draw(HDC hDc, COLORREF color, COLORREF colorbg,
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
			HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
			SelectObject(hDc, hPen);

			if (bSetRop == true)
				SetROP2(hDc, R2_MERGEPENNOT);
			//Màu nền
		/*	SetDCBrushColor(hDc, this->ColorBG);
			SelectObject(hDc, GetStockObject(DC_BRUSH)); */
			SelectObject(hDc, GetStockObject(NULL_BRUSH)); //Trong suốt
			//Vẽ
			/*if (!Rectangle(hDc, lefttop.x, lefttop.y,
				rightbottom.x, rightbottom.y)){
				throw Exception(L"Lỗi Rectangle");
			}*/
			/*Rectangle(hDc, lefttop.x, lefttop.y,
				rightbottom.x, rightbottom.y);*/
			::Color color_;
			color_.SetFromCOLORREF(color);
			Graphics* graphics = new Graphics(hDc);
			Pen* pen = new Pen(color_, iPenWidth);
			pen->SetDashStyle((DashStyle)iPenStyle);
			graphics->DrawRectangle(pen, lefttop.x, lefttop.y, rightbottom.x - lefttop.x, rightbottom.y - lefttop.y);
			delete pen;
			delete graphics;
			//DeleteObject(hPen);
			//ReleaseDC(hwnd, hdc);
		}

		void CRectangle::ReDraw(HDC hDc)
		{
			this->Draw(hDc, this->Color,this->ColorBG, this->LeftTop, this->RightBottom,
				this->PenStyle, this->PenWidth, false);
		}

		CShape* CRectangle::CreateNewShape()
		{
			CShape* shape = new CRectangle;
			return shape;
		}
		//CRectangleFill

		void CRectangleFill::SetDraw(COLORREF color, COLORREF colorbg,
			POINT lefttop, POINT rightbottom,
			int iPenStyle, int iPenWidth, bool bSetRop){
			this->Color = color;
			this->ColorBG = colorbg;
			this->LeftTop = lefttop;
			this->RightBottom = rightbottom;

			this->PenStyle = iPenStyle;
			this->PenWidth = iPenWidth;
			this->SetRop = bSetRop;
		}


		void CRectangleFill::Draw(HDC hDc, COLORREF color, COLORREF colorbg,
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
			HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
			SelectObject(hDc, hPen);

			if (bSetRop == true)
				SetROP2(hDc, R2_MERGEPENNOT);
			//Màu nền
			//SetDCBrushColor(hDc, this->ColorBG);
			//SelectObject(hDc, GetStockObject(DC_BRUSH)); 
			//SelectObject(hDc, GetStockObject(NULL_BRUSH)); //Trong suốt
			//Vẽ
			/*if (!Rectangle(hDc, lefttop.x, lefttop.y,
				rightbottom.x, rightbottom.y)){
				throw Exception(L"Lỗi Rectangle");
			}*/
			/*Rectangle(hDc, lefttop.x, lefttop.y,
			rightbottom.x, rightbottom.y);*/
			::Color color_;
			color_.SetFromCOLORREF(color);
			Graphics* graphics = new Graphics(hDc);
			//Pen* pen = new Pen(color_, iPenWidth);
			//pen->SetDashStyle((DashStyle)iPenStyle);
			SolidBrush *brush = new SolidBrush(color_);
			Rect rec = Rect(lefttop.x, lefttop.y, rightbottom.x - lefttop.x, rightbottom.y - lefttop.y);
			graphics->FillRectangle(brush, rec);
			delete brush;
			delete graphics;
			//DeleteObject(hPen);
			//ReleaseDC(hwnd, hdc);
		}

		void CRectangleFill::ReDraw(HDC hDc)
		{
			this->Draw(hDc, this->Color, this->ColorBG, this->LeftTop, this->RightBottom,
				this->PenStyle, this->PenWidth, false);
		}

		CShape* CRectangleFill::CreateNewShape()
		{
			CShape* shape = new CRectangleFill;
			return shape;
		}
	}
}
