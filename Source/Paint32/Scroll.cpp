#include "Scroll.h"


namespace Paint32{
	namespace UI{


		void Scroll::CreateScroll(HWND hWnd, HINSTANCE hIns){
			RECT rc = { 0 };
			GetClientRect(hWnd, &rc);

			 hWndVertScroll = CreateWindow(L"SCROLLBAR",
				(LPWSTR)NULL,
				WS_CHILD | WS_VISIBLE | SBS_VERT | SBS_RIGHTALIGN,
				rc.left, rc.top + 147, rc.right, (rc.bottom - 147),
				hWnd,
				NULL,
				hIns,
				FALSE);
			SCROLLINFO vScroll = { 0 };
			vScroll.cbSize = sizeof(SCROLLINFO);
			vScroll.fMask = SIF_ALL;
			vScroll.nMin = 0;
			vScroll.nMax = 30 * 50 + 21;
			vScroll.nPage = (rc.bottom - rc.top);
			vScroll.nPos = 0;
			vScroll.nTrackPos = 0;
			//SetScrollInfo(hWnd, SBS_VERT | SBS_TOPALIGN, &vScroll, true);
			//SetScrollRange(hWndVertScroll, SB_CTL, 0, 30 * 50 + 21, FALSE);
			SetScrollInfo(hWndVertScroll, SB_CTL, &vScroll, TRUE);

			SCROLLINFO hScroll = { 0 };
			hScroll.cbSize = sizeof(SCROLLINFO);
			hScroll.fMask = SIF_ALL;
			hScroll.nMin = 0;
			hScroll.nMax = 30 * 50 + 21;
			hScroll.nPage = (rc.right - rc.left);
			hScroll.nPos = 0 ;
			hScroll.nTrackPos = 0;
			SetScrollInfo(hWnd, SB_HORZ, &hScroll, true);
		}
		void  Scroll::UpadateScrollY(HWND hWnd, HINSTANCE hIns,RECT rc ,int Top){
			if (hWnd != NULL){
				int height = (rc.right - rc.left) - 17;
				SetWindowPos(hWndVertScroll, NULL, rc.left + height, rc.top + Top, 17, (rc.bottom - Top), FALSE);
			}
		}


		void Scroll::MoveScrollY(HWND hWnd, WPARAM wParam, LPARAM lParam){
			auto action = LOWORD(wParam);
			HWND hScroll = (HWND)lParam;
			int pos = -1;

			if (action == SB_THUMBPOSITION || action == SB_THUMBTRACK) {
				pos = HIWORD(wParam);
			}
			else if (action == SB_LINEDOWN) {
				pos = this->scrollY + 30;
			}
			else if (action == SB_LINEUP) {
				pos = this->scrollY - 30;
			}
			if (pos == -1)
				return;

			SCROLLINFO si = { 0 };
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			si.nPos = pos;
			si.nTrackPos = 0;
			SetScrollInfo(hWndVertScroll, SB_CTL, &si, true);
			GetScrollInfo(hWndVertScroll, SB_CTL, &si);
			pos = si.nPos;
			this->scrollY = pos;
		}

		void Scroll::MoveScrollX(HWND hWnd, WPARAM wParam, LPARAM lParam){
			auto action = LOWORD(wParam);
			HWND hScroll = (HWND)lParam;
			int pos = -1;

			if (action == SB_THUMBPOSITION || action == SB_THUMBTRACK) {
				pos = HIWORD(wParam);
			}
			else if (action == SB_LINEDOWN) {
				pos = this->scrollX + 30;
			}
			else if (action == SB_LINEUP) {
				pos = this->scrollX - 30;
			}
			if (pos == -1)
				return;

			WCHAR buf[20];
			SCROLLINFO si = { 0 };
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_POS;
			si.nPos = pos;
			si.nTrackPos = 0;
			SetScrollInfo(hWnd, SB_HORZ, &si, true);
			GetScrollInfo(hWnd, SB_HORZ, &si);
			pos = si.nPos;
			this->scrollX = pos;
		}
	}
}

