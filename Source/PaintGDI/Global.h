﻿#pragma once
#include "stdafx.h"

#include "..\\Paint32\\CLine.h"
#include "..\\Paint32\\CCircle.h"
#include "..\\Paint32\\CPolygon.h"
#include "..\\Paint32\\CRectangle.h"
#include "..\\Paint32\\Layer.h"
#include "..\\Paint32\\Exception.h"
#include "..\\Paint32\\Scroll.h"
#include "..\\Paint32\\LayerView.h"
#pragma comment(lib, "..\\Debug\\Paint32.lib")


#include "CToolBar.h"
using namespace Paint32;
///Define
//Shape
#define SHAPE_MOVE				-1
#define SHAPE					0
#define SHAPE_LINE				1
#define SHAPE_CIRCLE			2
#define SHAPE_RECTANGLE			3
#define SHAPE_POLYGON			4
#define SHAPE_POINT				5
#define SHAPE_CIRCLE_FILL		6
#define SHAPE_RECTANGLE_FILL	7
//
#define MAX_LOADSTRING 100
#define HEIGHT_TOOLBAR 64
namespace Global
{
	HWND hWndMain = NULL;							// HWND Main
	HINSTANCE hInst = NULL;							// Handle Instance
	//vector <Model::CShape*> Shapes;					// Danh sách các shape đã vẽ
	int ShapeType = SHAPE;							// Loại shape: SHAPE, SHAPE_LINE, SHAPE_CIRCLE, SHAPE_RECTANGLE, SHAPE_POLYGON, SHAPE_CIRCLE_FILL, SHAPE_RECTANGLE_FILL
	POINT pointHDC;									// Point HDC
	POINT offsetHDC;								// Offset HDC
	SIZE sizeHDC;									// Size HDC
	TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
	TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
	POINT pointMousePress;							// vị trí của chuột khi click chuột
	POINT pointMouseMove;							// vị trí của chuột khi move chuột
	bool isMove = false;							// bool, Có thể di chuyển
	HDC bufferHDC = NULL;							// buffer tránh việc nhấp nháy ảnh
	//HWND hToolBar = NULL;							// handle tool bar
	UI::Scroll scrollMain;							// Thanh scroll
	CToolBar* ToolBar;								// Tool bar
	int CurShapeType = SHAPE;							// Type shape
	bool DrawStarted = false;						//	
	vector <Model::CShape*> ShapeModels;			//
	COLORREF curColor = RGB(0, 0, 0);				//
	COLORREF curColorBG = RGB(255, 255, 0);			//
	vector<Layer*> Layers;							//
	int SelectLayers;								//
	HWND hLayer = NULL;								//
	POINT offsetMove;								//
	HMENU hMenuModel;								//
	bool paintPolygon = false;						//
	UI::LayerView hBoxLayer;						//
	int sizePaint = 1;								//
	int typePaint = 0;								//
	vector<int> historyLayer;						//

}