#pragma once


#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commctrl.h>
#include <winuser.h>
#include <Commdlg.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "comctl32.lib")

#include <WindowsX.h> //C: Dùng để ánh xạ các message vào các hàm xử lí tương ứng
//C: Sử dụng lớp mảng động vector
#include <vector>
using namespace std;

#include "resource.h"
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnMouseMove(HWND, int, int, UINT);
void OnLButtonUp(HWND, int, int, UINT);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnSize(HWND hwnd, UINT state, int cx, int cy);
void OnPaint(HWND);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);
void OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
void OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys);
void ReDrawMain();
void DrawBackGround();
void CheckMenu(int ID,int Type);
void UncheckAllMenu();
void SaveToBitMap(const char* path);
void writeToBinFile(const char* path);
void readFromBinFile(const char* path);
void AddItemListView();
UINT GetLVItemState(HWND hwnd, int i, UINT mask);
void GetLVItemText(HWND hwnd, int iItem, int iSubItem, LPWSTR pszText, int cchTextMax);
void SetLVItemText(HWND hwnd, int i, int iSubItem, LPWSTR pszText);
BOOL GetLVItem(HWND hListView, UINT mask, int iItem, int iSubItem,LPLVITEM pitem, UINT stateMask);
int GetHeaderItemCount(HWND hwndHD);
HWND GetLVHeaderControl(HWND hListView);
int GetLVColumnsCount(HWND hListView);
void SwapLVItems(HWND hListView, int iItem1, int iItem2);
//Move up the selected items
void MoveLVSelectedItemsUp(HWND hListView);
//Move down the selected items
void MoveLVSelectedItemsDown(HWND hListView);
bool HDCToFile(const char* FilePath, HDC Context, RECT Area, int BitsPerPixel = 24);

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	WndLayer(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	New(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
