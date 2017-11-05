
#include "Exception.h"
namespace Paint32{
	Exception::Exception(wstring str){
		this->data = str;
	}

	void Exception::ShowMessage(HWND hWnd){
		MessageBox(hWnd, this->data.c_str(), L"Error", MB_OK);
	}
}