#include "LayerView.h"
#include <tchar.h>

namespace Paint32{
	namespace UI{

		void LayerView::Create(HWND hwnd, HINSTANCE hInst, RECT rcClient){
			LVCOLUMN lvCol;
			this->hWnd = CreateWindow(WC_LISTVIEW,
				L"",
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_NOCOLUMNHEADER | LVS_SHAREIMAGELISTS | WS_TABSTOP | LVS_REPORT | LVS_ICON | LVS_EDITLABELS | LVS_SHOWSELALWAYS,
				5, 5,
				rcClient.right - rcClient.left - 10,
				rcClient.bottom - rcClient.top - 40,
				hwnd,
				NULL,
				hInst,
				NULL);

			lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
			lvCol.fmt = LVCFMT_LEFT;

			lvCol.cx = rcClient.right - rcClient.left - 10;
			lvCol.pszText = _T("Layers");
			ListView_InsertColumn(this->hWnd, 0, &lvCol);

			this->AddItemListView();
		}

		void LayerView::Clear(){
			ListView_DeleteAllItems(this->hWnd);
		}

		HWND LayerView::getHandle(){
			return this->hWnd;
		}

		int LayerView::GetItemCount(){
			return ListView_GetItemCount(this->hWnd);
		}

		int LayerView::DeleteSelect(){
			int iCount = ListView_GetItemCount(this->hWnd);
			if (iCount == 1) return -1;
			int iIndex = ListView_GetSelectionMark(this->hWnd);
			if (iIndex != -1){
				ListView_DeleteItem(this->hWnd, iIndex);
				return iIndex;
			}
			else return -1;
		}

		void LayerView::AddItemListView(){
			int i = ListView_GetItemCount(this->hWnd);
			TCHAR mousePos[11];
			wsprintf(mousePos, _T("Layer %d"), i + 1);
			LVITEM item;
			item.mask = LVIF_TEXT;
			item.iSubItem = 0;
			item.pszText = mousePos;
			item.iItem = i;
			ListView_InsertItem(this->hWnd, &item);
		}

		UINT LayerView::GetLVItemState(int i, UINT mask)
		{
			return ListView_GetItemState(this->hWnd, i, mask);
		}

		void LayerView::GetLVItemText(int iItem, int iSubItem, LPWSTR pszText, int cchTextMax)
		{
			ListView_GetItemText(this->hWnd, iItem, iSubItem, pszText, cchTextMax);
		}

		void LayerView::SetLVItemText(int i, int iSubItem, LPWSTR pszText)
		{
			ListView_SetItemText(this->hWnd, i, iSubItem, pszText);
		}


		BOOL LayerView::GetLVItem(UINT mask, int iItem, int iSubItem,
			LPLVITEM pitem, UINT stateMask)
		{
			pitem->mask = mask;
			pitem->stateMask = stateMask;
			pitem->iItem = iItem;
			pitem->iSubItem = iSubItem;
			return ListView_GetItem(this->hWnd, pitem);
		}


		int LayerView::GetHeaderItemCount(HWND hHeader)
		{
			return Header_GetItemCount(hHeader);
		}

		HWND LayerView::GetLVHeaderControl()
		{
			return ListView_GetHeader(this->hWnd);
		}

		int LayerView::GetLVColumnsCount()
		{
			return (GetHeaderItemCount(GetLVHeaderControl()));
		}


		bool LayerView::SwapLVItems(int iItem1, int iItem2)
		{
			//I assume that 4K buffer is really enough for storing the content of a column
			const int LOCAL_BUFFER_SIZE = 20;
			LVITEM lvi1, lvi2;
			UINT uMask = LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT | LVIF_PARAM | LVIF_STATE;
			WCHAR szBuffer1[LOCAL_BUFFER_SIZE + 1], szBuffer2[LOCAL_BUFFER_SIZE + 1];
			lvi1.pszText = szBuffer1;
			lvi2.pszText = szBuffer2;
			lvi1.cchTextMax = sizeof(szBuffer1);
			lvi2.cchTextMax = sizeof(szBuffer2);

			BOOL bResult1 = GetLVItem(uMask, iItem1, 0, &lvi1, (UINT)-1);
			BOOL bResult2 = GetLVItem(uMask, iItem2, 0, &lvi2, (UINT)-1);
			if (bResult1 && bResult2)
			{
				//Đổi vị trí
				//iter_swap(Global::Layers.begin() + iItem1, Global::Layers.begin() + iItem2);
				lvi1.iItem = iItem2;
				lvi2.iItem = iItem1;
				lvi1.mask = uMask;
				lvi2.mask = uMask;
				lvi1.stateMask = (UINT)-1;
				lvi2.stateMask = (UINT)-1;
				//swap the items
				ListView_SetItem(this->hWnd, &lvi1);
				ListView_SetItem(this->hWnd, &lvi2);

				int iColCount = GetLVColumnsCount();
				//Loop for swapping each column in the items.
				for (int iIndex = 1; iIndex < iColCount; iIndex++)
				{
					szBuffer1[0] = '\0';
					szBuffer2[0] = '\0';
					GetLVItemText(iItem1, iIndex,
						szBuffer1, LOCAL_BUFFER_SIZE);
					GetLVItemText(iItem2, iIndex,
						szBuffer2, LOCAL_BUFFER_SIZE);
					SetLVItemText(iItem2, iIndex, szBuffer1);
					SetLVItemText(iItem1, iIndex, szBuffer2);
				}
				return true;
			}
			return false;
		}

		//Move up the selected items
		int LayerView::MoveLVSelectedItemsUp()
		{
			int iCount = ListView_GetItemCount(this->hWnd);

			for (int iIndex = 1; iIndex < iCount; iIndex++)
				if (GetLVItemState(iIndex, LVIS_SELECTED) != 0)
					if (SwapLVItems(iIndex, iIndex - 1)) return iIndex;
					else return -1;
			return -1;

		}

		//Move down the selected items
		int LayerView::MoveLVSelectedItemsDown()
		{
			int iCount = ListView_GetItemCount(this->hWnd);

			for (int iIndex = iCount - 1; iIndex >= 0; iIndex--)
				if (GetLVItemState(iIndex, LVIS_SELECTED) != 0)
					if (SwapLVItems(iIndex, iIndex + 1)) return iIndex; 
					else return -1;
			return -1;
		}

	}
}


