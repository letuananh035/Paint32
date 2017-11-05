#include "Layer.h"
#include "Exception.h"
namespace Paint32{
	bool Layer::Create(SIZE size){
		if (this->hDc != NULL){
			DeleteDC(this->hDc);
		}
		HDC hdc = GetDC(0);
		this->hDc = CreateCompatibleDC(hdc);
		this->hBmp = CreateCompatibleBitmap(hdc, size.cx, size.cy);
		SelectObject(this->hDc, this->hBmp);
		this->sizeHDC = size;
		if (this->hDc == NULL){
			throw Exception(L"Lỗi tạo handle với CreateCompatibleDC!");
			return false;
		}
		if (this->hBmp == NULL){
			throw Exception(L"Lỗi tạo handle với CreateCompatibleBitmap!");
			return false;
		}
		DeleteObject(this->hBmp);
		DeleteDC(hdc);
		return true;
	}

	void Layer::AddShape(Model::CShape* shape){
		this->Shapes.push_back(shape);
	}

	void Layer::RemoveShape(){
		if (this->Shapes.size() >= 1){
			delete this->Shapes[this->Shapes.size() - 1];
			this->Shapes.pop_back();
		}
	}

	void Layer::DrawToMain(HDC hDcMain, POINT point, bool Sel){
		int length = this->Shapes.size();
		RECT rc = { 0, 0,
			this->sizeHDC.cx, this->sizeHDC.cy
		};
		BitBlt(this->hDc, 0, 0, this->sizeHDC.cx, this->sizeHDC.cy, hDcMain, point.x - this->offset.x, point.y - this->offset.y, SRCCOPY);
		if (this->hDcBG != NULL){
			BitBlt(this->hDc, 0, 0, this->sizeHDC.cx, this->sizeHDC.cy, this->hDcBG, 0, 0, SRCCOPY);
		}
		//FillRect(this->hDc, &rc, (HBRUSH)::GetStockObject(WHITE_BRUSH));
		if (Sel == true){
			HPEN hPen = CreatePen(2, 1, RGB(0, 0, 0));
			SelectObject(this->hDc, hPen);
			SelectObject(this->hDc, GetStockObject(NULL_BRUSH)); //Trong suốt
			Rectangle(this->hDc, 0, 0, this->sizeHDC.cx, this->sizeHDC.cy);
			DeleteObject(hPen);
		}
		if (length > 0){
			for (int i = 0; i < length; ++i){
				this->Shapes[i]->ReDraw(this->hDc);
			}
		}
		if (!BitBlt(hDcMain, point.x - this->offset.x, point.y - this->offset.y, this->sizeHDC.cx, this->sizeHDC.cy, this->hDc, 0, 0, SRCCOPY)){
			throw Exception(L"Lỗi DrawToMain");
		}
	}

	void Layer::Release(){
		//DeleteObject(this->hBmp);
		if (this->hDcBG != NULL){
			DeleteDC(this->hDcBG);
		}
		if (this->hDc != NULL){
			DeleteDC(this->hDc);
		}
		for (int i = 0; i < this->Shapes.size(); i++){
			delete this->Shapes[i];
		}
		this->Shapes.clear();
	}

	HDC Layer::GetParentHDC(HWND hWnd){
		HDC resultHDC = NULL;
		HBITMAP hBitmap = NULL;
		RECT client;
		::GetClientRect(hWnd, &client);

		int width = client.right - client.left;
		int height = client.bottom - client.top;

		HDC hDc = ::GetDC(hWnd);

		resultHDC = ::CreateCompatibleDC(hDc);

		hBitmap = ::CreateCompatibleBitmap(hDc, width, height);

		::SelectObject(resultHDC, hBitmap);
		::DeleteObject(hBitmap);
		::DeleteDC(hDc);
		return resultHDC;
	}

	HDC Layer::CreateHDC(SIZE size){
		HDC resultHDC = NULL;
		HBITMAP hBitmap = NULL;

		HDC hDc = ::GetDC(NULL);

		resultHDC = ::CreateCompatibleDC(hDc);

		hBitmap = ::CreateCompatibleBitmap(hDc, size.cx, size.cy);

		::SelectObject(resultHDC, hBitmap);
		::DeleteObject(hBitmap);
		::DeleteDC(hDc);
		return resultHDC;
	}

	void  Layer::SetBackGround(HINSTANCE hInst, LPWSTR path){
		HBITMAP hBitmap = (HBITMAP)LoadImage(hInst, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		this->hDcBG = CreateCompatibleDC(NULL);
		SelectObject(this->hDcBG, hBitmap);
		DeleteObject(hBitmap);
	}

	Model::CShape*& Layer::GetShape(int i){
		return this->Shapes[i];
	}

	void Layer::SetOffset(POINT offset){
		this->offset = offset;
	}

	void Layer::write(ofstream *out){ 
		out->write((char *)&this->hDcBG, sizeof(HDC));
		out->write((char *)&this->offset.x, sizeof(int));
		out->write((char *)&this->offset.y, sizeof(int));
		out->write((char *)&this->sizeHDC.cx, sizeof(int));
		out->write((char *)&this->sizeHDC.cy, sizeof(int));

		if (this->hDcBG != NULL){
			bool BG = true;
			out->write((char *)&BG, sizeof(bool));
			int BitsPerPixel = 24;
			long Width = this->sizeHDC.cx;
			long Height = this->sizeHDC.cy;

			BITMAPINFO Info;
			BITMAPFILEHEADER Header;
			memset(&Info, 0, sizeof(Info));
			memset(&Header, 0, sizeof(Header));
			Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			Info.bmiHeader.biWidth = Width;
			Info.bmiHeader.biHeight = Height;
			Info.bmiHeader.biPlanes = 1;
			Info.bmiHeader.biBitCount = BitsPerPixel;
			Info.bmiHeader.biCompression = BI_RGB;
			Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
			Header.bfType = 0x4D42;
			Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


			char* Pixels = NULL;
			HDC MemDC = CreateCompatibleDC(this->hDcBG);
			HBITMAP Section = CreateDIBSection(this->hDcBG, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
			DeleteObject(SelectObject(MemDC, Section));
			BitBlt(MemDC, 0, 0, Width, Height, this->hDcBG, 0, 0, SRCCOPY);
			DeleteDC(MemDC);
			int size = sizeof(Header);
			out->write((char*)&size, sizeof(int));
			out->write((char*)&Header, sizeof(Header));
			size = sizeof(Info.bmiHeader);
			out->write((char*)&size, sizeof(int));
			out->write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
			out->write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
			DeleteObject(Section);
		}
		else{
			bool BG = false;
			out->write((char *)&BG, sizeof(bool));
		}

		int size = this->Shapes.size();
		out->write((char *)&size, sizeof(int));
		for (int i = 0; i < this->Shapes.size(); ++i){
			string data = this->Shapes[i]->getType();
			if (data  == "Line"){
				int type = 0;
				out->write((char *)&type, sizeof(int));
				Model::CLine* shape = (Model::CLine*)this->Shapes[i];
				shape->write(out);
			}
			else if (data == "Rectangle"){
				int type = 1;
				out->write((char *)&type, sizeof(int));
				Model::CRectangle* shape = (Model::CRectangle*)this->Shapes[i];
				shape->write(out);
			}
			else if (data == "Circle"){
				int type = 2;
				out->write((char *)&type, sizeof(int));
				Model::CCircle* shape = (Model::CCircle*)this->Shapes[i];
				shape->write(out);
			}
			else if (data == "Polygon"){
				int type = 3;
				out->write((char *)&type, sizeof(int));
				Model::CPolygon* shape = (Model::CPolygon*)this->Shapes[i];
				shape->write(out);
			}
			else if (data == "RectangleFill"){
				int type = 4;
				out->write((char *)&type, sizeof(int));
				Model::CRectangleFill* shape = (Model::CRectangleFill*)this->Shapes[i];
				shape->write(out);
			}
			else if (data == "CircleFill"){
				int type = 5;
				out->write((char *)&type, sizeof(int));
				Model::CCircleFill* shape = (Model::CCircleFill*)this->Shapes[i];
				shape->write(out);
			}
		}
	}

	void Layer::read(ifstream *in){ 
		in->read((char *)&this->hDcBG, sizeof(HDC));
		in->read((char *)&this->offset.x, sizeof(int));
		in->read((char *)&this->offset.y, sizeof(int));
		in->read((char *)&this->sizeHDC.cx, sizeof(int));
		in->read((char *)&this->sizeHDC.cy, sizeof(int));


		bool BG;
		in->read((char *)&BG, sizeof(bool));
		if (BG == true){
			int BitsPerPixel = 24;
			long Width = this->sizeHDC.cx;
			long Height = this->sizeHDC.cy;

			BITMAPINFO Info;
			BITMAPFILEHEADER Header;
			char* Pixels = new char[(((BitsPerPixel * Width + 31) & ~31) / 8) * Height];
			memset(&Info, 0, sizeof(Info));
			memset(&Header, 0, sizeof(Header));
			int size;
			in->read((char*)&size, sizeof(int));
			in->read((char*)&Header, size);
			in->read((char*)&size, sizeof(int));
			in->read((char*)&Info.bmiHeader, size);
			in->read(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);

			this->hDcBG = ::CreateCompatibleDC(0);

			HBITMAP Section = CreateDIBSection(this->hDcBG, &Info, DIB_RGB_COLORS, (void**)Pixels, 0, 0);
			SetDIBits(NULL, Section, 0, Info.bmiHeader.biHeight, Pixels, &Info, DIB_RGB_COLORS);
			SelectObject(this->hDcBG, Section);
			DeleteObject(Section);
		}
		
		int size;
		in->read((char *)&size, sizeof(int));
		for (int i = 0; i < size; ++i){
			int type = 0;
			in->read((char *)&type, sizeof(int));
			if (type == 0){
				Model::CLine* shape = new Model::CLine();
				shape->read(in);
				this->Shapes.push_back((Model::CShape*)shape);
			}
			else if (type == 1){
				Model::CRectangle* shape = new Model::CRectangle();
				shape->read(in);
				this->Shapes.push_back((Model::CShape*)shape);
			}
			else if (type == 2){
				Model::CCircle* shape = new Model::CCircle();
				shape->read(in);
				this->Shapes.push_back((Model::CShape*)shape);
			}
			else if (type == 3){
				Model::CPolygon* shape = new Model::CPolygon();
				shape->read(in);
				this->Shapes.push_back((Model::CShape*)shape);
			}
			else if (type == 4){
				Model::CRectangleFill* shape = new Model::CRectangleFill();
				shape->read(in);
				this->Shapes.push_back((Model::CShape*)shape);
			}
			else if (type == 5){
				Model::CCircleFill* shape = new Model::CCircleFill();
				shape->read(in);
				this->Shapes.push_back((Model::CShape*)shape);
			}
		}
	}
}
