// PaintGDI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PaintGDI.h"
#include "Global.h"
using namespace Paint32;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) return FALSE;
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, Global::szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINTGDI, Global::szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINTGDI));

	Global::hLayer = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), Global::hWndMain, WndLayer, 0);
	ShowWindow(Global::hLayer, nCmdShow);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (!IsDialogMessage(Global::hLayer, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	CoUninitialize();
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0; //CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINTGDI));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_PAINTGDI);
	wcex.lpszClassName = Global::szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.style = CS_DBLCLKS;
	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	Global::hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(Global::szWindowClass, Global::szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	Global::hWndMain = hWnd;

	Global::offsetHDC.x = 0;
	Global::offsetHDC.y = 0;

	Global::sizeHDC.cx = 640;
	Global::sizeHDC.cy = 480;

	Global::pointHDC.x = 100;
	Global::pointHDC.y = 100;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONDBLCLK, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
		HANDLE_MSG(hWnd, WM_NOTIFY, OnNotify);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_VSCROLL, OnVScroll);
		HANDLE_MSG(hWnd, WM_HSCROLL, OnHScroll);
		HANDLE_MSG(hWnd, WM_MOUSEWHEEL, OnMouseWheel);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	static COLORREF acrCustClr[16];
	CHOOSECOLOR colorSelect;
	ZeroMemory(&colorSelect, sizeof(CHOOSECOLOR));
	RECT rect;
	HWND handle;
	POINT p;


	switch (id)
	{
	case ID_MENU_MODEL_LINE:
		CheckMenu(ID_MENU_MODEL_LINE, SHAPE_LINE);
		break;
	case ID_MENU_MODEL_CIRCLE:
		CheckMenu(ID_MENU_MODEL_CIRCLE, SHAPE_CIRCLE);
		break;
	case ID_MENU_MODEL_POLYGON:
		CheckMenu(ID_MENU_MODEL_POLYGON, SHAPE_POLYGON);
		break;
	case ID_MENU_MODEL_RECTANGLE:
		CheckMenu(ID_MENU_MODEL_RECTANGLE, SHAPE_RECTANGLE);
		break;
	case ID_MENU_MODEL_RECTANGLE_FILL:
		CheckMenu(ID_MENU_MODEL_RECTANGLE_FILL, SHAPE_RECTANGLE_FILL);
		break;
	case ID_MENU_MODEL_CIRCLE_FILL:
		CheckMenu(ID_MENU_MODEL_CIRCLE_FILL, SHAPE_CIRCLE_FILL);
		break;
	case ID_TOOL_UNDO:
	{
		/*if (Global::historyLayer.size() >= 1){
			int layer = Global::historyLayer[Global::historyLayer.size() - 1];
			Global::Layers[layer]->RemoveShape();
			Global::historyLayer.pop_back();
			ReDrawMain();
			}*/
		MessageBox(hwnd, L"Chức năng đang phát triển do xung đột layer.", L"Thống báo", 0);
		break;
	}
	case ID_TOOL_LAYERS:
		ShowWindow(Global::hLayer, SW_SHOW);
		break;
	case IDM_ABOUT:
		DialogBox(Global::hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;
	case ID_SAVE_BITMAP:
	{
		OPENFILENAME fileOpen;
		WCHAR filename[MAX_PATH] = { '\0' };
		ZeroMemory(&fileOpen, sizeof(fileOpen));
		fileOpen.lStructSize = sizeof(OPENFILENAME);
		fileOpen.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		fileOpen.lpstrFilter = (LPCWSTR)L"Bitmap Files (*.bmp)\0*.bmp\0Bin Files (*.bin)\0*.bin\0";
		fileOpen.lpstrFile = filename;
		fileOpen.nMaxFile = MAX_PATH;
		fileOpen.lpstrTitle = L"Save As";
		fileOpen.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
		fileOpen.lpstrDefExt = (LPCWSTR)L"bmp";
		if (GetSaveFileName(&fileOpen) == TRUE){
			if (fileOpen.nFilterIndex == 1){
				std::wstring path(fileOpen.lpstrFile);
				char str[256];
				sprintf(str, "%ws", fileOpen.lpstrFile);
				SaveToBitMap(str);
			}
			else if (fileOpen.nFilterIndex == 2){
				std::wstring path(fileOpen.lpstrFile);
				char str[256];
				sprintf(str, "%ws", fileOpen.lpstrFile);
				writeToBinFile(str);
			}
		}
		break;
	}
	case ID_OPEN_BITMAP:
	{
		OPENFILENAME fileOpen;
		WCHAR filename[MAX_PATH] = { '\0' };
		WCHAR type[50] = { '\0' };
		ZeroMemory(&fileOpen, sizeof(fileOpen));
		fileOpen.lStructSize = sizeof(fileOpen);
		fileOpen.hwndOwner = NULL;
		fileOpen.lpstrFile = filename;
		//
		// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
		// use the contents of szFile to initialize itself.
		//
		fileOpen.lpstrFile[0] = '\0';
		fileOpen.nMaxFile = MAX_PATH;
		fileOpen.lpstrFilter = L"Bitmap Files (*.bmp)\0*.bmp\0Bin Files (*.bin)\0*.bin\0";
		fileOpen.nFilterIndex = 1;
		fileOpen.lpstrTitle = L"Open";
		fileOpen.lpstrFileTitle = NULL;
		fileOpen.nMaxFileTitle = 0;
		fileOpen.lpstrInitialDir = NULL;
		fileOpen.lpstrDefExt = type;
		fileOpen.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&fileOpen) == TRUE){
			if (fileOpen.nFilterIndex == 1){
				Global::hBoxLayer.AddItemListView();
				Global::Layers.push_back(new Layer());
				Global::Layers[Global::Layers.size() - 1]->SetBackGround(Global::hInst, fileOpen.lpstrFile);
				Global::SelectLayers = 0;
				ReDrawMain();
			}
			else if (fileOpen.nFilterIndex == 2){
				for (int i = 0; i < Global::Layers.size(); ++i){
					Global::Layers[i]->Release();
					delete Global::Layers[i];
				}
				Global::Layers.clear();
				std::wstring path(fileOpen.lpstrFile);
				char str[256];
				sprintf(str, "%ws", fileOpen.lpstrFile);
				readFromBinFile(str);
				Global::SelectLayers = 0;
				ReDrawMain();
			}
		}
	}
	break;
	case ID_FILE_NEW:{
		DialogBox(Global::hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, New);
		break;
	}
	case IDC_TOOLBAR_PENWIDTH: //C: Thay đổi độ rộng nét vẽ
		if (codeNotify == CBN_SELCHANGE)
		{
			Global::sizePaint = SendMessage(GetDlgItem(Global::ToolBar->GetHandle(), IDC_TOOLBAR_PENWIDTH),
				CB_GETCURSEL, 0, 0) + 1;

			if (Global::sizePaint >= 1)
			{
				SendMessage(GetDlgItem(Global::ToolBar->GetHandle(), IDC_TOOLBAR_PENSTYLE),
					CB_SETCURSEL, 0, 0);
				Global::typePaint = /*PS_SOLID*/ 0;
			}
		}
		break; //-------------------------------------------------

	case IDC_TOOLBAR_PENSTYLE: //C: Thay đổi kiểu nét vẽ
		if (codeNotify == CBN_SELCHANGE)
		{
			Global::typePaint = SendMessage(GetDlgItem(Global::ToolBar->GetHandle(), IDC_TOOLBAR_PENSTYLE),
				CB_GETCURSEL, 0, 0);

			if (Global::typePaint != /*PS_SOLID*/ 0)
			{
				SendMessage(GetDlgItem(Global::ToolBar->GetHandle(), IDC_TOOLBAR_PENWIDTH),
					CB_SETCURSEL, 0, 0);
				Global::sizePaint = 1;
			}
		}
		break; //-------------------------------------------------
	case ID_COLOR_CHOOSE:
		colorSelect.lStructSize = sizeof(CHOOSECOLOR);
		colorSelect.hwndOwner = hwnd;
		colorSelect.lpCustColors = (LPDWORD)acrCustClr;
		colorSelect.rgbResult = Global::curColor;
		colorSelect.Flags = CC_FULLOPEN | CC_RGBINIT;
		//C: Hiển thị hộp thoại chọn màu
		if (ChooseColor(&colorSelect))
			Global::curColor = colorSelect.rgbResult;
		break;
	case ID_COLOR_FILL:
		colorSelect.lStructSize = sizeof(CHOOSECOLOR);
		colorSelect.hwndOwner = hwnd;
		colorSelect.lpCustColors = (LPDWORD)acrCustClr;
		colorSelect.rgbResult = Global::curColorBG;
		colorSelect.Flags = CC_FULLOPEN | CC_RGBINIT;
		//C: Hiển thị hộp thoại chọn màu
		if (ChooseColor(&colorSelect))
			Global::curColorBG = colorSelect.rgbResult;
		break;
	case ID_SELECT:
		UncheckAllMenu();
		Global::CurShapeType = SHAPE_MOVE;
		Global::paintPolygon = FALSE;
		Global::DrawStarted = FALSE;
		ReDrawMain();
		break;
	case ID_SHAPE_POINT:
		UncheckAllMenu();
		Global::CurShapeType = SHAPE_POINT;
		Global::paintPolygon = FALSE;
		Global::DrawStarted = FALSE;
		ReDrawMain();
		break;
	case ID_SHAPE_MODEL:
		GetCursorPos(&p);
		handle = WindowFromPoint(p);
		if (Global::hMenuModel == NULL){
			Global::hMenuModel = CreatePopupMenu();

			InsertMenu(Global::hMenuModel, 0, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, ID_MENU_MODEL_LINE, L"Line");
			InsertMenu(Global::hMenuModel, 1, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, ID_MENU_MODEL_CIRCLE, L"Circle");
			InsertMenu(Global::hMenuModel, 2, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, ID_MENU_MODEL_RECTANGLE, L"Rectangle");
			InsertMenu(Global::hMenuModel, 3, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, ID_MENU_MODEL_POLYGON, L"Polygon");
			InsertMenu(Global::hMenuModel, 4, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, ID_MENU_MODEL_CIRCLE_FILL, L"Circle Fill");
			InsertMenu(Global::hMenuModel, 5, MF_BYPOSITION | MF_STRING | MF_UNCHECKED, ID_MENU_MODEL_RECTANGLE_FILL, L"Rectangle Fill");
		}
		TrackPopupMenu(Global::hMenuModel, TPM_TOPALIGN | TPM_LEFTALIGN, p.x, p.y, 0, hwnd, NULL);
		//g_bPolygon = FALSE;
		Global::DrawStarted = FALSE;
		break;
	case IDC_RESIZE_RIBBON:{
		Global::HeightRibbon = int(hwndCtl);
		RECT rc = { 0 };
		GetClientRect(Global::hWndMain, &rc);
		Global::scrollMain.UpadateScrollY(Global::hWndMain, Global::hInst, rc, Global::HeightRibbon);
		ReDrawMain();
		break; 
	}
	case IDC_EDIT_SIZE:{
		Global::sizePaint = int(hwndCtl);
		break;
	}		
	case IDC_EDIT_STYLE:{
		Global::typePaint = int(hwndCtl);
		break;
	}		
	case IDM_EXIT:
		DestroyWindow(hwnd);
		break;
		//default:
		//return DefWindowProc(hwnd, message, wParam, lParam);
	}
}


void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys){
	if (zDelta < 0){
		SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 30);
	}
	else{
		SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, -30);
	}
}

void OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos){
	LPARAM lParam = MAKELPARAM(code, pos);
	Global::scrollMain.MoveScrollX(hwnd, (WPARAM)lParam, (LPARAM)hwndCtl);
	Global::offsetHDC.x = -Global::scrollMain.getScrollX();
	ReDrawMain();
}
void OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos){
	LPARAM lParam = MAKELPARAM(code, pos);
	Global::scrollMain.MoveScrollY(hwnd, (WPARAM)lParam, (LPARAM)hwndCtl);
	Global::offsetHDC.y = -Global::scrollMain.getScrollY();
	ReDrawMain();
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK New(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:{
		HWND hwndOutput = GetDlgItem(hDlg, IDC_EDIT1);
		SetWindowText(hwndOutput, L"640");
		hwndOutput = GetDlgItem(hDlg, IDC_EDIT2);
		SetWindowText(hwndOutput, L"480");
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch ((int)(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDOK:{
			for (int i = 0; i < Global::Layers.size(); ++i){
				Global::Layers[i]->Release();
				delete Global::Layers[i];
			}
			Global::Layers.clear();
			//Global::historyLayer.clear();
			Global::SelectLayers = 0;
			Global::hBoxLayer.Clear();
			Global::hBoxLayer.AddItemListView();
			Global::Layers.push_back(new Layer());
			//Lấy size
			HWND hwndOutput = GetDlgItem(hDlg, IDC_EDIT1);
			int outLength = GetWindowTextLength(hwndOutput) + 1;
			TCHAR* text = new TCHAR[outLength + 1];
			GetWindowText(hwndOutput, text, outLength);
			Global::sizeHDC.cx = _ttoi(text);

			hwndOutput = GetDlgItem(hDlg, IDC_EDIT2);
			outLength = GetWindowTextLength(hwndOutput) + 1;
			text = new TCHAR[outLength + 1];
			GetWindowText(hwndOutput, text, outLength);
			Global::sizeHDC.cy = _ttoi(text);

			ReDrawMain();
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK WndLayer(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int id_sel = -1;
	switch (message)
	{
	case WM_INITDIALOG:
		Global::Layers.push_back(new Layer());
		Global::SelectLayers = 0;

		RECT rcClient;                       // The parent window's client area.
		GetClientRect(hDlg, &rcClient);

		Global::hBoxLayer = UI::LayerView();
		Global::hBoxLayer.Create(hDlg, Global::hInst, rcClient);
		return (INT_PTR)TRUE;
	case WM_NOTIFY:
	{
		NMHDR* notifyMess = (NMHDR*)lParam;
		switch (notifyMess->code){
		case NM_CLICK:{
			id_sel = ListView_GetSelectionMark(Global::hBoxLayer.getHandle());
			if (id_sel != -1){
				Global::SelectLayers = id_sel;
				ReDrawMain();
			}
			break;
		}
		}
		break;
	}
	case WM_COMMAND:
		switch ((int)(wParam))
		{
		case IDC_BUTTON1: // Thêm layer
			Global::Layers.push_back(new Layer());
			Global::hBoxLayer.AddItemListView();
			ReDrawMain();
			break;
		case IDC_BUTTON2: // Xóa layer
		{
			int iCount = Global::hBoxLayer.DeleteSelect();
			if (iCount != -1) Global::Layers.erase(Global::Layers.begin() + iCount);
			Global::SelectLayers = ListView_GetSelectionMark(Global::hBoxLayer.getHandle());
			ReDrawMain();
			break;
		}
		case IDC_BUTTON3:{ // Di chuyên lên layer
			int iIndex = Global::hBoxLayer.MoveLVSelectedItemsUp();
			if (iIndex != -1)
				iter_swap(Global::Layers.begin() + iIndex, Global::Layers.begin() + iIndex - 1);
			ReDrawMain();
			break;
		}
		case IDC_BUTTON4:{ // Di chuyển xuống layer
			int iIndex = Global::hBoxLayer.MoveLVSelectedItemsDown();
			if (iIndex != -1)
				iter_swap(Global::Layers.begin() + iIndex, Global::Layers.begin() + iIndex + 1);
			ReDrawMain();
			break;
		}
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		default:
			break;
		}
	}

	return (INT_PTR)FALSE;
}
void OnDestroy(HWND hwnd)
{
	for (int i = 0; i < Global::Layers.size(); ++i){
		Global::Layers[i]->Release();
		delete Global::Layers[i];
	}
	for (int i = 0; i < Global::ShapeModels.size(); ++i){
		delete Global::ShapeModels[i];
	}
	GdiplusShutdown(Global::gdiplusToken);
	DestroyFramework();
	PostQuitMessage(0);


}
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm){
	LPNMTOOLBAR lpnmToolBar = (LPNMTOOLBAR)pnm;
	return 0;
}

bool initSuccess;
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	RECT		client;
	::GetClientRect(hwnd, &client);
	double width = client.right - client.left;
	double height = client.bottom - client.top;

	//Global::ToolBar = new CToolBar;
	//Global::ToolBar->Create(hwnd, IDC_TOOLBAR, Global::hInst, 0, 0, 0, 0);
	//SendMessage(Global::ToolBar->GetHandle(), TB_AUTOSIZE, 0, (LPARAM)0);



	//C: Tạo ra các mẫu đối tượng cơ bản
	Global::ShapeModels.push_back(NULL);//Shape
	Global::ShapeModels.push_back(new Model::CLine);
	Global::ShapeModels.push_back(new Model::CCircle);
	Global::ShapeModels.push_back(new Model::CRectangle);
	Global::ShapeModels.push_back(new Model::CPolygon);
	Global::ShapeModels.push_back(new Model::CPolygon);
	Global::ShapeModels.push_back(new Model::CCircleFill);
	Global::ShapeModels.push_back(new Model::CRectangleFill);
	//Tạo scroll
	Global::scrollMain.CreateScroll(hwnd, Global::hInst);


	GdiplusStartup(&Global::gdiplusToken, &Global::gdiplusStartupInput, NULL);

	initSuccess = InitializeFramework(hwnd);

	if (!initSuccess) return -1;

	return TRUE;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC			hdc;
	RECT		client;
	//Get Size Screen
	::GetClientRect(hwnd, &client);
	double width = client.right - client.left;
	double height = client.bottom - client.top;

	hdc = BeginPaint(hwnd, &ps);
	if (Global::bufferHDC != NULL) DeleteDC(Global::bufferHDC);
	Global::bufferHDC = Layer::GetParentHDC(hwnd);

	try{
		for (int i = 0; i < Global::Layers.size(); ++i)
			Global::Layers[i]->Create(Global::sizeHDC);
	}
	catch (Exception e){
		e.ShowMessage(Global::hWndMain);
	}

	DrawBackGround();

	POINT pDraw;
	pDraw.x = Global::pointHDC.x + Global::offsetHDC.x;
	pDraw.y = Global::pointHDC.y + Global::offsetHDC.y;
	try{
		for (int i = 0; i < Global::Layers.size(); ++i){
			Global::Layers[i]->DrawToMain(Global::bufferHDC, pDraw, i == Global::SelectLayers);
		}
	}
	catch (Exception e){
		e.ShowMessage(hwnd);
	}


	if (!BitBlt(hdc, 0, Global::HeightRibbon, (int)width,
		(int)height, Global::bufferHDC, 0, 0, SRCCOPY)){
		MessageBox(hwnd, L"", L"", 0);
	}
	EndPaint(hwnd, &ps);
	ReleaseDC(hwnd, hdc);
}

void OnSize(HWND hwnd, UINT state, int cx, int cy){
	RECT rc = { 0 };
	GetClientRect(Global::hWndMain, &rc);
	Global::scrollMain.UpadateScrollY(Global::hWndMain, Global::hInst, rc, Global::HeightRibbon);
	ReDrawMain();
	//SendMessage(Global::ToolBar->GetHandle(), TB_AUTOSIZE, 0, (LPARAM)0);
}
bool isMoveMain = false;
POINT pointStart;
POINT offsetTemp;
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	int ctrlValue = ::GetAsyncKeyState(VK_CONTROL);

	if (ctrlValue){
		isMoveMain = true;
		pointStart.x = x;
		pointStart.y = y;
		offsetTemp = Global::pointHDC;
	}

	if (Global::DrawStarted == FALSE && Global::CurShapeType != SHAPE && Global::CurShapeType != SHAPE_MOVE){
		Model::CShape* shapeTest = Global::ShapeModels[Global::CurShapeType]->CreateNewShape();
		Global::Layers[Global::SelectLayers]->AddShape(shapeTest);
		//Global::historyLayer.push_back(Global::SelectLayers); // Thêm vào lịch sử
		Global::DrawStarted = TRUE;
		Global::pointMousePress.x = x - (Global::pointHDC.x + Global::offsetHDC.x) + Global::Layers[Global::SelectLayers]->GetOffset().x;
		Global::pointMousePress.y = y - (Global::pointHDC.y + Global::offsetHDC.y) - Global::HeightRibbon + Global::Layers[Global::SelectLayers]->GetOffset().y;

		Global::pointMouseMove.x = x - (Global::pointHDC.x + Global::offsetHDC.x) + Global::Layers[Global::SelectLayers]->GetOffset().x;
		Global::pointMouseMove.y = y - (Global::pointHDC.y + Global::offsetHDC.y) - Global::HeightRibbon + Global::Layers[Global::SelectLayers]->GetOffset().y;
		if (Global::CurShapeType == SHAPE_POLYGON){
			int iIndex = Global::Layers[Global::SelectLayers]->GetSize();
			Model::CPolygon* tshape = (Model::CPolygon*)Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1);
			tshape->SetAddLine();
			Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1)->SetDraw(Global::curColor, Global::curColorBG, Global::pointMousePress, Global::pointMouseMove,
				Global::typePaint, Global::sizePaint, FALSE);
		}
		if (Global::CurShapeType == SHAPE_POINT){
			int iIndex = Global::Layers[Global::SelectLayers]->GetSize();
			Model::CPolygon* tshape = (Model::CPolygon*)Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1);
			tshape->SetAddLine();
			Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1)->SetDraw(Global::curColor, Global::curColorBG, Global::pointMousePress, Global::pointMousePress,
				0, Global::sizePaint, FALSE);
		}
		if (Global::paintPolygon){
			Global::paintPolygon = false;
		}
	}


	if (Global::paintPolygon == true){
		if (fDoubleClick){
			int iIndex = Global::Layers[Global::SelectLayers]->GetSize();
			Model::CPolygon* tshape = (Model::CPolygon*)Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1);
			POINT start = tshape->GetLast();
			POINT end = tshape->GetFirst();
			Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1)->SetDraw(Global::curColor, Global::curColorBG, start, end,
				Global::typePaint, Global::sizePaint, FALSE);
			Global::paintPolygon = false;
			Global::DrawStarted = FALSE;
			ReDrawMain();
		}
	}
	if (Global::DrawStarted == FALSE && Global::CurShapeType == SHAPE_MOVE){
		Global::isMove = true;
		Global::pointMousePress.x = x;
		Global::pointMousePress.y = y;
		Global::offsetMove = Global::Layers[Global::SelectLayers]->GetOffset();
	}

}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	int ctrlValue = ::GetAsyncKeyState(VK_CONTROL);
	if (isMoveMain && ctrlValue){
		Global::pointHDC.y = offsetTemp.y + (y - pointStart.y);
		Global::pointHDC.x = offsetTemp.x + (x - pointStart.x);
		ReDrawMain();
	}
	else{
		POINT mouse;
		mouse.x = x - (Global::pointHDC.x + Global::offsetHDC.x);
		mouse.y = y - (Global::pointHDC.y + Global::offsetHDC.y) - Global::HeightRibbon;
		TCHAR mousePos[50];
		wsprintf(mousePos, _T("Paint32 (%d,%d)"), mouse.x, mouse.y);
		SetWindowText(Global::hWndMain, mousePos);

		if (Global::isMove){
			POINT a;
			a.x = Global::offsetMove.x - (x - Global::pointMousePress.x);
			a.y = Global::offsetMove.y - (y - Global::pointMousePress.y);
			Global::Layers[Global::SelectLayers]->SetOffset(a);
			ReDrawMain();
		}

		if (Global::DrawStarted == TRUE)
		{

			RECT		client;
			int iIndex = Global::Layers[Global::SelectLayers]->GetSize();
			if (Global::CurShapeType == SHAPE_POINT){
				int iIndex = Global::Layers[Global::SelectLayers]->GetSize();
				Model::CPolygon* tshape = (Model::CPolygon*)Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1);
				tshape->SetAddLine();
				Global::pointMousePress = Global::pointMouseMove;
				Global::pointMouseMove.x = mouse.x + Global::Layers[Global::SelectLayers]->GetOffset().x;
				Global::pointMouseMove.y = mouse.y + Global::Layers[Global::SelectLayers]->GetOffset().y;
				Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1)->SetDraw(Global::curColor, Global::curColorBG, Global::pointMousePress, Global::pointMouseMove,
					0, Global::sizePaint, FALSE);
			}
			else{
				Global::pointMouseMove.x = mouse.x + Global::Layers[Global::SelectLayers]->GetOffset().x;
				Global::pointMouseMove.y = mouse.y + Global::Layers[Global::SelectLayers]->GetOffset().y;
				if (Global::CurShapeType == SHAPE_CIRCLE || Global::CurShapeType == SHAPE_CIRCLE_FILL || Global::CurShapeType == SHAPE_RECTANGLE || Global::CurShapeType == SHAPE_RECTANGLE_FILL){
					int ctrlValue = ::GetAsyncKeyState(VK_SHIFT);
					if (ctrlValue){
						int width = abs(Global::pointMousePress.x - Global::pointMouseMove.x);
						if (Global::pointMouseMove.y > Global::pointMousePress.y){
							Global::pointMouseMove.y = Global::pointMousePress.y + width;
						}
						else{
							Global::pointMouseMove.y = Global::pointMousePress.y - width;
						}

					}
				}
				Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1)->SetDraw(Global::curColor, Global::curColorBG, Global::pointMousePress, Global::pointMouseMove,
					Global::typePaint, Global::sizePaint);
			}
			ReDrawMain();
		}
	}


}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	Global::isMove = false;
	isMoveMain = false;

	if (Global::DrawStarted == FALSE)
		return;

	int iIndex = Global::Layers[Global::SelectLayers]->GetSize();
	if (Global::CurShapeType == SHAPE_POLYGON){
		Model::CPolygon* tshape = (Model::CPolygon*)Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1);
		tshape->SetAddLine();
	}
	/*if (Global::CurShapeType != SHAPE_POINT){
		if (Global::CurShapeType == SHAPE_CIRCLE || Global::CurShapeType == SHAPE_CIRCLE_FILL || Global::CurShapeType == SHAPE_RECTANGLE || Global::CurShapeType == SHAPE_RECTANGLE_FILL){
		int ctrlValue = ::GetAsyncKeyState(VK_SHIFT);
		if (ctrlValue){
		int width = abs(Global::pointMousePress.x - Global::pointMouseMove.x);
		if (Global::pointMouseMove.y > Global::pointMousePress.y){
		Global::pointMouseMove.y = Global::pointMousePress.y + width;
		}
		else{
		Global::pointMouseMove.y = Global::pointMousePress.y - width;
		}

		}
		}
		Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1)->SetDraw(Global::curColor, Global::curColorBG, Global::pointMousePress, Global::pointMouseMove,
		Global::typePaint, Global::sizePaint, FALSE);
		}*/
	if (Global::CurShapeType != SHAPE_POLYGON){
		Global::DrawStarted = FALSE;
	}
	else
	{
		int iIndex = Global::Layers[Global::SelectLayers]->GetSize();
		Model::CPolygon* tshape = (Model::CPolygon*)Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1);
		tshape->SetAddLine();
		Global::pointMousePress.x = x - (Global::pointHDC.x + Global::offsetHDC.x) + Global::Layers[Global::SelectLayers]->GetOffset().x;
		Global::pointMousePress.y = y - (Global::pointHDC.y + Global::offsetHDC.y) - Global::HeightRibbon + Global::Layers[Global::SelectLayers]->GetOffset().y;
		Global::Layers[Global::SelectLayers]->GetShape(iIndex - 1)->SetDraw(Global::curColor, Global::curColorBG, Global::pointMousePress, Global::pointMouseMove,
			Global::typePaint, Global::sizePaint, FALSE);
		Global::paintPolygon = TRUE;

	}

	ReDrawMain();
}

bool HDCToFile(const char* FilePath, HDC Context, RECT Area, int BitsPerPixel)
{
	long Width = Area.right - Area.left;
	long Height = Area.bottom - Area.top;

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
	HDC MemDC = CreateCompatibleDC(Context);
	HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
	DeleteObject(SelectObject(MemDC, Section));
	BitBlt(MemDC, 0, 0, Width, Height, Context, 0, 0, SRCCOPY);
	DeleteDC(MemDC);

	std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
	if (hFile.is_open())
	{
		hFile.write((char*)&Header, sizeof(Header));
		hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
		hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
		hFile.close();
		DeleteObject(Section);
		return true;
	}

	DeleteObject(Section);
	return false;
}

void ReDrawMain(){
	RECT		client;
	::GetClientRect(Global::hWndMain, &client);
	client.top = Global::HeightRibbon;
	client.bottom += Global::HeightRibbon;
	client.right -= 17;
	InvalidateRect(Global::hWndMain, &client, FALSE);
}

void DrawBackGround(){
	RECT		client;
	//Get Size Screen
	::GetClientRect(Global::hWndMain, &client);

	if (!FillRect(Global::bufferHDC, &client, (HBRUSH)::GetStockObject(GRAY_BRUSH))){
		MessageBox(Global::hWndMain, L"", L"", 0);
	}

	RECT		client1;
	client1.left = Global::pointHDC.x + Global::offsetHDC.x;
	client1.top = Global::pointHDC.y + Global::offsetHDC.y;
	client1.right = client1.left + Global::sizeHDC.cx;
	client1.bottom = client1.top + Global::sizeHDC.cy;

	FillRect(Global::bufferHDC, &client1, (HBRUSH)::GetStockObject(WHITE_BRUSH));
}

void CheckMenu(int ID, int Type){
	UncheckAllMenu();
	int state = GetMenuState(Global::hMenuModel, ID, MF_BYCOMMAND);
	if (state == MF_CHECKED){
		CheckMenuItem(Global::hMenuModel, ID, MF_UNCHECKED);
		Global::CurShapeType = SHAPE;
		Global::DrawStarted = FALSE;
	}
	else{
		CheckMenuItem(Global::hMenuModel, ID, MF_CHECKED);
		Global::CurShapeType = Type;
		Global::DrawStarted = FALSE;
	}
}

void UncheckAllMenu(){
	int state = GetMenuState(Global::hMenuModel, ID_MENU_MODEL_LINE, MF_BYCOMMAND);
	if (state == MF_CHECKED){
		CheckMenuItem(Global::hMenuModel, ID_MENU_MODEL_LINE, MF_UNCHECKED);
		Global::CurShapeType = SHAPE;
		Global::DrawStarted = FALSE;
	}

	state = GetMenuState(Global::hMenuModel, ID_MENU_MODEL_CIRCLE, MF_BYCOMMAND);
	if (state == MF_CHECKED){
		CheckMenuItem(Global::hMenuModel, ID_MENU_MODEL_CIRCLE, MF_UNCHECKED);
		Global::CurShapeType = SHAPE;
		Global::DrawStarted = FALSE;
	}

	state = GetMenuState(Global::hMenuModel, ID_MENU_MODEL_RECTANGLE, MF_BYCOMMAND);
	if (state == MF_CHECKED){
		CheckMenuItem(Global::hMenuModel, ID_MENU_MODEL_RECTANGLE, MF_UNCHECKED);
		Global::CurShapeType = SHAPE;
		Global::DrawStarted = FALSE;
	}

	state = GetMenuState(Global::hMenuModel, ID_MENU_MODEL_POLYGON, MF_BYCOMMAND);
	if (state == MF_CHECKED){
		CheckMenuItem(Global::hMenuModel, ID_MENU_MODEL_POLYGON, MF_UNCHECKED);
		Global::CurShapeType = SHAPE;
		Global::DrawStarted = FALSE;
	}

	state = GetMenuState(Global::hMenuModel, ID_MENU_MODEL_RECTANGLE_FILL, MF_BYCOMMAND);
	if (state == MF_CHECKED){
		CheckMenuItem(Global::hMenuModel, ID_MENU_MODEL_RECTANGLE_FILL, MF_UNCHECKED);
		Global::CurShapeType = SHAPE;
		Global::DrawStarted = FALSE;
	}

	state = GetMenuState(Global::hMenuModel, ID_MENU_MODEL_CIRCLE_FILL, MF_BYCOMMAND);
	if (state == MF_CHECKED){
		CheckMenuItem(Global::hMenuModel, ID_MENU_MODEL_CIRCLE_FILL, MF_UNCHECKED);
		Global::CurShapeType = SHAPE;
		Global::DrawStarted = FALSE;
	}
}

void SaveToBitMap(const char* path){
	HDC hdc;
	SIZE size;
	RECT client1;

	client1.left = 0;
	client1.top = 0;
	client1.right = client1.left + Global::sizeHDC.cx;
	client1.bottom = client1.top + Global::sizeHDC.cy;

	if (Global::bufferHDC != NULL) DeleteDC(Global::bufferHDC);
	Global::bufferHDC = Layer::CreateHDC(Global::sizeHDC);
	FillRect(Global::bufferHDC, &client1, (HBRUSH)::GetStockObject(WHITE_BRUSH));
	POINT pDraw;
	pDraw.x = 0;
	pDraw.y = 0;
	try{
		for (int i = 0; i < Global::Layers.size(); ++i){
			Global::Layers[i]->DrawToMain(Global::bufferHDC, pDraw, false);
		}
	}
	catch (Exception e){
		e.ShowMessage(Global::hWndMain);
	}
	HDCToFile(path, Global::bufferHDC, client1);
}

void writeToBinFile(const char* path)
{
	ofstream ofs(path, ios_base::out | ios_base::binary);
	int size = Global::Layers.size();
	if (ofs)
	{
		ofs.write((char *)(&size), sizeof(size));
		for (int i = 0; i < size; ++i){
			Global::Layers[i]->write(&ofs);
		}
		ofs.close();
		//ofs.write(reinterpret_cast<const char*>(&Global::Layers), sizeof(Global::Layers[0]) * size);
	}
}

void readFromBinFile(const char* path)
{
	ifstream ifs(path, ios_base::in | ios_base::binary);
	int size;
	if (ifs)
	{
		// Read the size
		ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
		ListView_DeleteAllItems(Global::hBoxLayer.getHandle());
		for (int i = 0; i < size; ++i){
			Layer* layer = new Layer();
			layer->read(&ifs);
			Global::Layers.push_back(layer);
			Global::hBoxLayer.AddItemListView();
		}

		ifs.close();
		// Read all the data
		//ifs.read(reinterpret_cast<char*>(&Global::Layers[0]), sizeof(Layer) * size);
	}
}