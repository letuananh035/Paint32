
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
			HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
			SelectObject(hDc, hPen);

			if (bSetRop == true)
				SetROP2(hDc, R2_MERGEPENNOT);
			//
			//Màu nền
			SelectObject(hDc, GetStockObject(NULL_BRUSH)); //Trong suốt
		/*	SetDCBrushColor(hDc, this->ColorBG);
			SelectObject(hDc, GetStockObject(DC_BRUSH));
*/
			if (!Ellipse(hDc, lefttop.x, lefttop.y,
				rightbottom.x, rightbottom.y)){
				throw Exception(L"Lỗi Ellipse");
			}
			DeleteObject(hPen);
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
			HPEN hPen = CreatePen(iPenStyle, iPenWidth, color);
			SelectObject(hDc, hPen);

			if (bSetRop == true)
				SetROP2(hDc, R2_MERGEPENNOT);
			//
			//Màu nền
			//SelectObject(hDc, GetStockObject(NULL_BRUSH)); //Trong suốt
			SetDCBrushColor(hDc, this->ColorBG);
			SelectObject(hDc, GetStockObject(DC_BRUSH));
			if (!Ellipse(hDc, lefttop.x, lefttop.y,
				rightbottom.x, rightbottom.y)){
				throw Exception(L"Lỗi Ellipse");
			}
			DeleteObject(hPen);
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
