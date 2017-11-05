#include "Scroll.h"


namespace Paint32{
	namespace UI{
		void Scroll::CreateScroll(HWND hWnd){
			RECT rc = { 0 };
			GetClientRect(hWnd, &rc);

			SCROLLINFO vScroll = { 0 };
			vScroll.cbSize = sizeof(SCROLLINFO);
			vScroll.fMask = SIF_ALL;
			vScroll.nMin = 0;
			vScroll.nMax = 30 * 50 + 21;
			vScroll.nPage = (rc.right - rc.left);
			vScroll.nPos = 0;
			vScroll.nTrackPos = 0;
			SetScrollInfo(hWnd, SB_VERT, &vScroll, true);
			//SetScrollPos(hWnd, SB_VERT, 120, true);

			SCROLLINFO hScroll = { 0 };
			hScroll.cbSize = sizeof(SCROLLINFO);
			hScroll.fMask = SIF_ALL;
			hScroll.nMin = 0;
			hScroll.nMax = 30 * 50 + 21;
			hScroll.nPage = (rc.bottom - rc.top);  
			hScroll.nPos = 0 ;
			hScroll.nTrackPos = 0;
			SetScrollInfo(hWnd, SB_HORZ, &hScroll, true);
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
			SetScrollInfo(hWnd, SB_VERT, &si, true);
			GetScrollInfo(hWnd, SB_VERT, &si);
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

