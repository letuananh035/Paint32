// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
#include "stdafx.h"
#include <UIRibbon.h>

#include "CommandHandler.h"
#include "RibbonIDs.h"
#include "RibbonFramework.h"
#include "resource.h"
extern HWND hWndApp;
// Static method to create an instance of the object.
HRESULT CCommandHandler::CreateInstance(IUICommandHandler **ppCommandHandler)
{
	if (!ppCommandHandler)
	{
		return E_POINTER;
	}

	*ppCommandHandler = NULL;

	HRESULT hr = S_OK;

	CCommandHandler* pCommandHandler = new CCommandHandler();
	if (pCommandHandler != NULL)
	{
		*ppCommandHandler = static_cast<IUICommandHandler *>(pCommandHandler);
	}
	else
	{
		hr = E_OUTOFMEMORY;
	}

	return hr;
}

// IUnknown method implementations.
STDMETHODIMP_(ULONG) CCommandHandler::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CCommandHandler::Release()
{
	LONG cRef = InterlockedDecrement(&m_cRef);
	if (cRef == 0)
	{
		delete this;
	}

	return cRef;
}

STDMETHODIMP CCommandHandler::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == __uuidof(IUnknown))
	{
		*ppv = static_cast<IUnknown*>(this);
	}
	else if (iid == __uuidof(IUICommandHandler))
	{
		*ppv = static_cast<IUICommandHandler*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

//
//  FUNCTION: UpdateProperty()
//
//  PURPOSE: Called by the Ribbon framework when a command property (PKEY) needs to be updated.
//
//  COMMENTS:
//
//    This function is used to provide new command property values, such as labels, icons, or
//    tooltip information, when requested by the Ribbon framework.  
//    
//    In this SimpleRibbon sample, the method is not implemented.  
//
STDMETHODIMP CCommandHandler::UpdateProperty(
	UINT nCmdID,
	REFPROPERTYKEY key,
	const PROPVARIANT* ppropvarCurrentValue,
	PROPVARIANT* ppropvarNewValue)
{
	UNREFERENCED_PARAMETER(nCmdID);
	UNREFERENCED_PARAMETER(key);
	UNREFERENCED_PARAMETER(ppropvarCurrentValue);
	UNREFERENCED_PARAMETER(ppropvarNewValue);
	HRESULT hr = E_FAIL;
	HWND handle = GetForegroundWindow();
	if (key == UI_PKEY_Minimized)
	{
		SendMessage(handle, WM_COMMAND, ID_TOOL_LAYERS, 0);
	}

	return E_NOTIMPL;
}

//
//  FUNCTION: Execute()
//
//  PURPOSE: Called by the Ribbon framework when a command is executed by the user.  For example, when
//           a button is pressed.
//
STDMETHODIMP CCommandHandler::Execute(
	UINT nCmdID,
	UI_EXECUTIONVERB verb,
	const PROPERTYKEY* key,
	const PROPVARIANT* ppropvarValue,
	IUISimplePropertySet* pCommandExecutionProperties)
{
	UNREFERENCED_PARAMETER(pCommandExecutionProperties);
	UNREFERENCED_PARAMETER(ppropvarValue);
	UNREFERENCED_PARAMETER(key);
	UNREFERENCED_PARAMETER(verb);
	UNREFERENCED_PARAMETER(nCmdID);
	//HWND handle = FindWindow(L"PaintGDI", L"PaintGDI");
	HWND handle = GetForegroundWindow();
	switch (nCmdID)
	{
	case ID_CMD_EXIT:
		SendMessage(handle, WM_DESTROY, 0, 0);
		break;
	case ID_CMD_NEW:
		SendMessage(handle, WM_COMMAND, ID_FILE_NEW, 0);
		break;
	case ID_CMD_OPEN:
		SendMessage(handle, WM_COMMAND, ID_OPEN_BITMAP, 0);
		break;
	case ID_CMD_SAVE:
		SendMessage(handle, WM_COMMAND, ID_SAVE_BITMAP, 0);
		break;
	case ID_CMD_COLOR:
		SendMessage(handle, WM_COMMAND, ID_COLOR_CHOOSE, 0);
		break;
	case ID_CMD_FILL:
		SendMessage(handle, WM_COMMAND, ID_COLOR_FILL, 0);
		break;
	case ID_CMD_SELECT:
		SendMessage(handle, WM_COMMAND, ID_SELECT, 0);
		break;
	case ID_CMD_PEN:
		SendMessage(handle, WM_COMMAND, ID_SHAPE_POINT, 0);
		break;
	case ID_CMD_MODEL:
		SendMessage(handle, WM_COMMAND, ID_SHAPE_MODEL, 0);
		break;
	case ID_CMD_LAYERS:
		SendMessage(handle, WM_COMMAND, ID_TOOL_LAYERS, 0);
		break;
	case ID_CMD_SIZE_1:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_SIZE, 1);
		break;
	case ID_CMD_SIZE_2:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_SIZE, 2);
		break;
	case ID_CMD_SIZE_3:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_SIZE, 3);
		break;
	case ID_CMD_SIZE_4:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_SIZE, 4);
		break;
	case ID_CMD_SIZE_5:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_SIZE, 5);
		break;
	case ID_CMD_SIZE_6:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_SIZE, 6);
		break;
	case ID_CMD_SIZE_7:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_SIZE, 7);
		break;
	case ID_CMD_STYLE_SOLID:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_STYLE, 0);
		break;
	case ID_CMD_STYLE_DASH:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_STYLE, 1);
		break;
	case ID_CMD_STYLE_DOT:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_STYLE, 2);
		break;
	case ID_CMD_STYLE_DASHDOT:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_STYLE, 3);
		break;
	case ID_CMD_STYLE_DASHDOTDOT:
		SendMessage(handle, WM_COMMAND, IDC_EDIT_STYLE, 4);
		break;
	default:
		break;
	}

	return S_OK;
}
