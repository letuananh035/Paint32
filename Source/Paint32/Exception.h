#pragma once

#ifndef EXCEPTION_H
#define PAINT32 __declspec(dllexport)
#else
#define PAINT32 __declspec(dllimport)
#endif

#include <windows.h>
#include <iostream>
using namespace std;
namespace Paint32{
	class PAINT32 Exception
	{
	public:
		wstring data;
		Exception(wstring str);
		Exception(){ data = L""; }
		/*Hiển thị lỗi ra dialog*/
		void ShowMessage(HWND hWnd);
	};
}
