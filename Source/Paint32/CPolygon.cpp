#include "CPolygon.h"


namespace Paint32{
	namespace Model{
		void CPolygon::SetDraw(COLORREF color, COLORREF colorbg,
			POINT lefttop, POINT rightbottom,
			int iPenStyle, int iPenWidth, bool bSetRop){
			if (this->AddLine == true){
				this->Lines.push_back(new CLine);
				this->AddLine = false;
			}
			this->Lines[this->Lines.size() - 1]->SetDraw(color, colorbg, lefttop, rightbottom,
				iPenStyle, iPenWidth);
		}
		void CPolygon::Draw(HDC hDc, COLORREF color, COLORREF colorbg, POINT lefttop,
				POINT rightbottom, int iPenStyle, int iPenWidth, bool bSetRop)
		{
			this->Lines.push_back(new CLine);
			this->Lines[this->Lines.size() - 1]->Draw(hDc, color, colorbg, lefttop, rightbottom,
				iPenStyle, iPenWidth);
		}

		void CPolygon::ReDraw(HDC hDc)
		{
			for (int i = 0; i < this->Lines.size(); ++i)
				this->Lines[i]->ReDraw(hDc);
		}

		CShape* CPolygon::CreateNewShape()
		{
			CShape* shape = new CPolygon;
			return shape;
		}

		bool operator==(const POINT& p1, const POINT& p2)
		{
			if ((p1.x == p2.x) && (p1.y == p2.y))
				return true;
			else
				return false;
		}

		POINT CPolygon::GetFirst()
		{
			return this->Lines[0]->GetLefttop();
		}

		POINT CPolygon::GetLast(){
			return this->Lines[this->Lines.size() - 1]->GetLefttop();
		}

		void CPolygon::write(ofstream *out){
			CShape::write(out);
			out->write((char *) &this->AddLine, sizeof(bool));
			int size = this->Lines.size();
			out->write((char *)&size, sizeof(int));
			for (int i = 0; i < this->Lines.size(); i++){
				this->Lines[i]->write(out);
			}
		}

		void  CPolygon::read(ifstream *in){
			CShape::read(in);
			in->read((char *)&this->AddLine, sizeof(bool));
			int size;
			in->read((char *)&size, sizeof(int));
			for (int i = 0; i < size; i++){
				Model::CLine* shape = new Model::CLine();
				shape->read(in);
				this->Lines.push_back(shape);
			}
		}

	}
}