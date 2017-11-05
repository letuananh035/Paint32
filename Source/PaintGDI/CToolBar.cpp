#include "stdafx.h"
#include "CToolBar.h"
#include "resource.h"
#include <tchar.h>

CToolBar::CToolBar()
{
	m_hInst = NULL;
	m_hParent = NULL;
	m_hToolBar = NULL;
	m_nID = 0;
}

void CToolBar::Create(HWND parentWnd, long ID, HINSTANCE hParentInst,
	int nWidth, int nHeight, int x, int y, long lStyle)
{
	InitCommonControls();
	m_hInst = hParentInst;
	m_hParent = parentWnd;
	m_hToolBar = CreateWindow(TOOLBARCLASSNAME, NULL, lStyle, x, y, nWidth, nHeight,
		m_hParent, (HMENU)ID, m_hInst, NULL);
	m_nID = ID;
	SendMessage(m_hToolBar, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);

	SetButtonImages();
	AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 1, ID_SELECT, _T("SELECT"), 0);
	AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 0, ID_SHAPE_POINT, _T("PEN"), 1);
	AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 2, ID_SHAPE_MODEL, _T("MODEL"), 2);
	AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 3, ID_COLOR_CHOOSE, _T("COLOR"), 3);
	AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 4, ID_COLOR_FILL, _T("FILL"), 4);



	//AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 3, ID_SHAPE_RECTANGLE, _T("Rectangle"), 2);
	//AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 5, ID_SHAPE_POLYGON, _T("Polygon"), 3);
	//AddNonButtonControl(_T("BUTTON"), _T("Color..."), WS_CHILD |
	//	WS_VISIBLE, IDC_BTN_CHOOSECOLOR, 55, 55, 4, 4);

	HWND hcbb1 = AddNonButtonControl(_T("COMBOBOX"), _T("1"), WS_CHILD |
		WS_VISIBLE | WS_VSCROLL  | CBS_DROPDOWN , IDC_TOOLBAR_PENWIDTH, 50, 200, 5, 5);
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"1");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"2");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"3");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"4");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"5");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"6");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"7");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"8");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"9");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"10");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"11");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"12");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"13");
	SendMessage(hcbb1, CB_SETCURSEL, 0, 0);

	hcbb1 = AddNonButtonControl(_T("COMBOBOX"), _T("PS_SOLID"), WS_CHILD |
		WS_VISIBLE | CBS_DROPDOWN, IDC_TOOLBAR_PENSTYLE, 150, 200, 6, 6);
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"PS_SOLID");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"PS_DASH");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"PS_DOT");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"PS_DASHDOT");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"PS_DASHDOTDOT");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"PS_NULL");
	SendMessage(hcbb1, CB_ADDSTRING, 0, (LPARAM)L"PS_INSIDEFRAME");
	SendMessage(hcbb1, CB_SETCURSEL, 0, 0);


}
//Neu goi ham nay nhieu lan thi phai goi theo thu tu btnIndex tang dan
HWND CToolBar::AddNonButtonControl(LPTSTR className, LPTSTR caption, int styles,
	int ID, int width, int height, int btnIndex,
	int iCommand)
{
	TBBUTTON button;
	button.fsState = TBSTATE_ENABLED;
	button.fsStyle = BTNS_SEP;
	button.iBitmap = 1;
	button.idCommand = iCommand;
	BOOL kq = SendMessage(m_hToolBar, TB_INSERTBUTTON, btnIndex, (LPARAM)&button);

	TBBUTTONINFO info;
	info.cbSize = sizeof(TBBUTTONINFO);
	info.dwMask = TBIF_SIZE;
	info.cx = width + 10;
	SendMessage(m_hToolBar, TB_SETBUTTONINFO, iCommand, (LPARAM)&info);

	RECT rect;
	SendMessage(m_hToolBar, TB_GETITEMRECT, btnIndex, (LPARAM)&rect);

	//Neu height=0 thi chieu cao se duoc tinh bang bottom-top
	//Neu height<>0 thi chieu cao se la height 
	HWND hWnd = CreateWindow(className, caption, styles, rect.left + 5,
		rect.top, rect.right - rect.left - 5,
		height == 0 ? rect.bottom - rect.top : height,
		m_hToolBar, (HMENU)ID, m_hInst, 0);

	return hWnd;
}

BOOL CToolBar::AddButton(BYTE fsState, BYTE fsStyle, int iBitmap, int idCommand, LPTSTR iString, DWORD_PTR dwData)
{
	int iStr = SendMessage(m_hToolBar, TB_ADDSTRING, 0, (LPARAM)iString);
	TBBUTTON button[1];

	button[0].dwData = dwData;
	button[0].fsState = fsState;
	button[0].iBitmap = iBitmap;

	button[0].fsStyle = fsStyle;
	button[0].idCommand = idCommand;
	button[0].iString = iStr;

	return SendMessage(m_hToolBar, TB_ADDBUTTONS, 1, (LPARAM)&button);
}

void CToolBar::SetButtonImages()
{
	SendMessage(m_hToolBar, TB_SETBITMAPSIZE, 0, MAKELONG(32, 32));

	HIMAGELIST hIml = ImageList_Create(32, 32, ILC_MASK | ILC_COLOR32, 5, 0);
	HBITMAP hBmp = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	//C: Xóa đi màu đen
	ImageList_AddMasked(hIml, hBmp, RGB(255, 255, 255));
	ImageList_SetBkColor(hIml, CLR_NONE);

	SendMessage(m_hToolBar, TB_SETIMAGELIST, 0, (LPARAM)hIml);
}


HWND CToolBar::GetHandle()
{
	return m_hToolBar;
}
