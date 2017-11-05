#pragma once

#ifndef LAYERVIEW_H
#define PAINT32 __declspec(dllexport)
#else
#define PAINT32 __declspec(dllimport)
#endif
#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include "Exception.h"
namespace Paint32{
	namespace UI{
		class PAINT32 LayerView
		{
		private:
			HWND hWnd;
		public:
			void Create(HWND hwnd, HINSTANCE hInst, RECT rcClient);
			HWND getHandle();
			void AddItemListView();
			UINT GetLVItemState(int i, UINT mask);
			void GetLVItemText(int iItem, int iSubItem, LPWSTR pszText, int cchTextMax);
			void SetLVItemText(int i, int iSubItem, LPWSTR pszText);
			BOOL GetLVItem(UINT mask, int iItem, int iSubItem, LPLVITEM pitem, UINT stateMask);
			int GetHeaderItemCount(HWND hHeader);
			HWND GetLVHeaderControl();
			int GetLVColumnsCount();
			bool SwapLVItems(int iItem1, int iItem2);
			int MoveLVSelectedItemsUp();
			int MoveLVSelectedItemsDown();
			void Clear();
			int GetItemCount();
			int DeleteSelect();
		};
	}
}


