#include <windows.h>
#include "resource.h"
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;//인스턴스 핸들
LPCTSTR lpszClass = TEXT("팩맨");
HWND hWndMain;
int i, y, x, p = 17, m = 0, q = 18, mp = 0, g1x, g1y;
int x1 = 1, x2 = 10, x3 = 9, x4 = 10, x5 = 11, y1 = 1, y2 = 8, y3 = 10, y4 = 10, y5 = 10;
int g1 = 1, g2 = 1, g3 = 1, g4 = 1;
int point = 0, bp = 0, life = 100;
TCHAR a[100];
TCHAR b[100];
char ar[18][22] = {

  "2666666666!6666666661",
  "5         5         5",
  "5 21 2661 5 2661 21 5",
  "5 43 4663 9 4663 43 5",
  "5                   5",
  "5 261 0 76!68 0 261 5",
  "5 463 5   5   5 463 5",
  "5     #68 9 76$     5",
  "468 0 5       5 0 763",
  "    5 9 26661 9 5    ",
  "268 9   5^^^5   9 761",
  "5     0 46663 0     5",
  "5 761 5       5 268 5",
  "5   5 9 76!68 9 5   5",
  "#61 5     9     5 26$",
  "5 9 9 768   768 9 9 5",
  "5         0         5",
  "4666666666@6666666663"

};

//비트맵 리소스 핸들(배경 및 아이콘)
HBITMAP background[30];

//비트맵 이미지의 필요 없는 배경을 없애 주는 함수
void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask);

//비트맵을 윈도우상에 그려주는 함수
void DrawBitmap(HDC hdc);

//윈도우메인 부분
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	//윈도우 클래스 등록
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	//메뉴 등록 부분
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	//윈도우 생성
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		0, 0, 1024, 768,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	//메시지 루프
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

// 윈도우 메시지 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	//	RECT crt;
	//	srand(time(NULL));

	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		//SetRect(&crt,0,0,1024,768);
		//AdjustWindowRect(&crt,WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE);

		//SetWindowPos(hWnd,NULL,0,0,crt.right-crt.left,crt.bottom-crt.top,SWP_NOMOVE|SWP_NOZORDER);

		//비트맵 리소스들을 Backgroud[]배열에 등록
		background[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));//배경 리소스
		background[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		background[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		background[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		background[5] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		background[6] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
		background[7] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
		background[8] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
		background[9] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
		background[10] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
		background[11] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP11));
		background[12] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		background[13] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP13));
		background[14] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP14));
		background[15] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP15));
		background[16] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP16));
		background[17] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
		background[18] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP18));
		background[19] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19));
		background[20] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
		background[21] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP21));
		background[22] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP22));
		background[23] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP23));
		background[24] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP24));
		background[25] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP25));
		background[26] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP26));
		background[27] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP27));

		return 0;

	case WM_TIMER:
		switch (wParam) {

		case 1:
			x1 = x1 + 1;
			if (ar[y1][x1] == '1' || ar[y1][x1] == '2' || ar[y1][x1] == '3' ||
				ar[y1][x1] == '4' || ar[y1][x1] == '5' || ar[y1][x1] == '6' ||
				ar[y1][x1] == '7' || ar[y1][x1] == '8' || ar[y1][x1] == '9' ||
				ar[y1][x1] == '0' || ar[y1][x1] == '!' || ar[y1][x1] == '@' ||
				ar[y1][x1] == '#' || ar[y1][x1] == '$') {
				x1--; KillTimer(hWnd, 1);
				KillTimer(hWnd, 5);
			} //벽
			break;

		case 2:
			x1 = x1 - 1;
			if (ar[y1][x1] == '1' || ar[y1][x1] == '2' || ar[y1][x1] == '3' ||
				ar[y1][x1] == '4' || ar[y1][x1] == '5' || ar[y1][x1] == '6' ||
				ar[y1][x1] == '7' || ar[y1][x1] == '8' || ar[y1][x1] == '9' ||
				ar[y1][x1] == '0' || ar[y1][x1] == '!' || ar[y1][x1] == '@' ||
				ar[y1][x1] == '#' || ar[y1][x1] == '$') {
				x1++; KillTimer(hWnd, 2);
				KillTimer(hWnd, 5);
			} //벽
			break;

		case 3:
			y1 = y1 - 1;
			if (ar[y1][x1] == '1' || ar[y1][x1] == '2' || ar[y1][x1] == '3' ||
				ar[y1][x1] == '4' || ar[y1][x1] == '5' || ar[y1][x1] == '6' ||
				ar[y1][x1] == '7' || ar[y1][x1] == '8' || ar[y1][x1] == '9' ||
				ar[y1][x1] == '0' || ar[y1][x1] == '!' || ar[y1][x1] == '@' ||
				ar[y1][x1] == '#' || ar[y1][x1] == '$') {
				y1++; KillTimer(hWnd, 3);
				KillTimer(hWnd, 5);
			} //벽 
			break;

		case 4:
			y1 = y1 + 1;
			if (ar[y1][x1] == '1' || ar[y1][x1] == '2' || ar[y1][x1] == '3' ||
				ar[y1][x1] == '4' || ar[y1][x1] == '5' || ar[y1][x1] == '6' ||
				ar[y1][x1] == '7' || ar[y1][x1] == '8' || ar[y1][x1] == '9' ||
				ar[y1][x1] == '0' || ar[y1][x1] == '!' || ar[y1][x1] == '@' ||
				ar[y1][x1] == '#' || ar[y1][x1] == '$') {
				y1--;  KillTimer(hWnd, 4);
				KillTimer(hWnd, 5);
			} //벽 
			break;

		case 5:
			p = p + q;
			if (p >= 23) p = mp + q;
			break;

		case 6:    //유령1
			if (x2 > x1) {
				x2--;
				if (ar[y2][x2] == '1' || ar[y2][x2] == '2' || ar[y2][x2] == '3' ||
					ar[y2][x2] == '4' || ar[y2][x2] == '5' || ar[y2][x2] == '6' ||
					ar[y2][x2] == '7' || ar[y2][x2] == '8' || ar[y2][x2] == '9' ||
					ar[y2][x2] == '0' || ar[y2][x2] == '!' || ar[y2][x2] == '@' ||
					ar[y2][x2] == '#' || ar[y2][x2] == '$') x2++;
			}

			if (x2 < x1) {
				x2++;
				if (ar[y2][x2] == '1' || ar[y2][x2] == '2' || ar[y2][x2] == '3' ||
					ar[y2][x2] == '4' || ar[y2][x2] == '5' || ar[y2][x2] == '6' ||
					ar[y2][x2] == '7' || ar[y2][x2] == '8' || ar[y2][x2] == '9' ||
					ar[y2][x2] == '0' || ar[y2][x2] == '!' || ar[y2][x2] == '@' ||
					ar[y2][x2] == '#' || ar[y2][x2] == '$') x2--;
			}

			if (y2 > y1) {
				y2--;
				if (ar[y2][x2] == '1' || ar[y2][x2] == '2' || ar[y2][x2] == '3' ||
					ar[y2][x2] == '4' || ar[y2][x2] == '5' || ar[y2][x2] == '6' ||
					ar[y2][x2] == '7' || ar[y2][x2] == '8' || ar[y2][x2] == '9' ||
					ar[y2][x2] == '0' || ar[y2][x2] == '!' || ar[y2][x2] == '@' ||
					ar[y2][x2] == '#' || ar[y2][x2] == '$') y2++;
			}

			if (y2 < y1) {
				y2++;
				if (ar[y2][x2] == '1' || ar[y2][x2] == '2' || ar[y2][x2] == '3' ||
					ar[y2][x2] == '4' || ar[y2][x2] == '5' || ar[y2][x2] == '6' ||
					ar[y2][x2] == '7' || ar[y2][x2] == '8' || ar[y2][x2] == '9' ||
					ar[y2][x2] == '0' || ar[y2][x2] == '!' || ar[y2][x2] == '@' ||
					ar[y2][x2] == '#' || ar[y2][x2] == '$') y2--;
			}

			break;

		case 7:    //유령2
			if (x3 > x1) {
				x3--;
				if (ar[y3][x3] == '1' || ar[y3][x3] == '2' || ar[y3][x3] == '3' ||
					ar[y3][x3] == '4' || ar[y3][x3] == '5' || ar[y3][x3] == '6' ||
					ar[y3][x3] == '7' || ar[y3][x3] == '8' || ar[y3][x3] == '9' ||
					ar[y3][x3] == '0' || ar[y3][x3] == '!' || ar[y3][x3] == '@' ||
					ar[y3][x3] == '#' || ar[y3][x3] == '$') x3++;
			}
			if (x3 < x1) {
				x3++;
				if (ar[y3][x3] == '1' || ar[y3][x3] == '2' || ar[y3][x3] == '3' ||
					ar[y3][x3] == '4' || ar[y3][x3] == '5' || ar[y3][x3] == '6' ||
					ar[y3][x3] == '7' || ar[y3][x3] == '8' || ar[y3][x3] == '9' ||
					ar[y3][x3] == '0' || ar[y3][x3] == '!' || ar[y3][x3] == '@' ||
					ar[y3][x3] == '#' || ar[y3][x3] == '$') x3--;
			}
			if (y3 > y1) {
				y3--;
				if (ar[y3][x3] == '1' || ar[y3][x3] == '2' || ar[y3][x3] == '3' ||
					ar[y3][x3] == '4' || ar[y3][x3] == '5' || ar[y3][x3] == '6' ||
					ar[y3][x3] == '7' || ar[y3][x3] == '8' || ar[y3][x3] == '9' ||
					ar[y3][x3] == '0' || ar[y3][x3] == '!' || ar[y3][x3] == '@' ||
					ar[y3][x3] == '#' || ar[y3][x3] == '$') y3++;
			}
			if (y3 < y1) {
				y3++;
				if (ar[y3][x3] == '1' || ar[y3][x3] == '2' || ar[y3][x3] == '3' ||
					ar[y3][x3] == '4' || ar[y3][x3] == '5' || ar[y3][x3] == '6' ||
					ar[y3][x3] == '7' || ar[y3][x3] == '8' || ar[y3][x3] == '9' ||
					ar[y3][x3] == '0' || ar[y3][x3] == '!' || ar[y3][x3] == '@' ||
					ar[y3][x3] == '#' || ar[y3][x3] == '$') y3--;
			}

			break;

		case 8:    //유령3
			if (x4 > x1) {
				x4--;
				if (ar[y4][x4] == '1' || ar[y4][x4] == '2' || ar[y4][x4] == '3' ||
					ar[y4][x4] == '4' || ar[y4][x4] == '5' || ar[y4][x4] == '6' ||
					ar[y4][x4] == '7' || ar[y4][x4] == '8' || ar[y4][x4] == '9' ||
					ar[y4][x4] == '0' || ar[y4][x4] == '!' || ar[y4][x4] == '@' ||
					ar[y4][x4] == '#' || ar[y4][x4] == '$') x4++;
			}
			if (x4 < x1) {
				x4++;
				if (ar[y4][x4] == '1' || ar[y4][x4] == '2' || ar[y4][x4] == '3' ||
					ar[y4][x4] == '4' || ar[y4][x4] == '5' || ar[y4][x4] == '6' ||
					ar[y4][x4] == '7' || ar[y4][x4] == '8' || ar[y4][x4] == '9' ||
					ar[y4][x4] == '0' || ar[y4][x4] == '!' || ar[y4][x4] == '@' ||
					ar[y4][x4] == '#' || ar[y4][x4] == '$') x4--;
			}
			if (y4 > y1) {
				y4--;
				if (ar[y4][x4] == '1' || ar[y4][x4] == '2' || ar[y4][x4] == '3' ||
					ar[y4][x4] == '4' || ar[y4][x4] == '5' || ar[y4][x4] == '6' ||
					ar[y4][x4] == '7' || ar[y4][x4] == '8' || ar[y4][x4] == '9' ||
					ar[y4][x4] == '0' || ar[y4][x4] == '!' || ar[y4][x4] == '@' ||
					ar[y4][x4] == '#' || ar[y4][x4] == '$') y4++;
			}
			if (y4 < y1) {
				y4++;
				if (ar[y4][x4] == '1' || ar[y4][x4] == '2' || ar[y4][x4] == '3' ||
					ar[y4][x4] == '4' || ar[y4][x4] == '5' || ar[y4][x4] == '6' ||
					ar[y4][x4] == '7' || ar[y4][x4] == '8' || ar[y4][x4] == '9' ||
					ar[y4][x4] == '0' || ar[y4][x4] == '!' || ar[y4][x4] == '@' ||
					ar[y4][x4] == '#' || ar[y4][x4] == '$') y4--;
			}

			break;

		case 9:    //유령4
			if (x5 > x1) {
				x5--;
				if (ar[y5][x5] == '1' || ar[y5][x5] == '2' || ar[y5][x5] == '3' ||
					ar[y5][x5] == '4' || ar[y5][x5] == '5' || ar[y5][x5] == '6' ||
					ar[y5][x5] == '7' || ar[y5][x5] == '8' || ar[y5][x5] == '9' ||
					ar[y5][x5] == '0' || ar[y5][x5] == '!' || ar[y5][x5] == '@' ||
					ar[y5][x5] == '#' || ar[y5][x5] == '$') x5++;
			}
			if (x5 < x1) {
				x5++;
				if (ar[y5][x5] == '1' || ar[y5][x5] == '2' || ar[y5][x5] == '3' ||
					ar[y5][x5] == '4' || ar[y5][x5] == '5' || ar[y5][x5] == '6' ||
					ar[y5][x5] == '7' || ar[y5][x5] == '8' || ar[y5][x5] == '9' ||
					ar[y5][x5] == '0' || ar[y5][x5] == '!' || ar[y5][x5] == '@' ||
					ar[y5][x5] == '#' || ar[y5][x5] == '$') x5--;
			}
			if (y5 > y1) {
				y5--;
				if (ar[y5][x5] == '1' || ar[y5][x5] == '2' || ar[y5][x5] == '3' ||
					ar[y5][x5] == '4' || ar[y5][x5] == '5' || ar[y5][x5] == '6' ||
					ar[y5][x5] == '7' || ar[y5][x5] == '8' || ar[y5][x5] == '9' ||
					ar[y5][x5] == '0' || ar[y5][x5] == '!' || ar[y5][x5] == '@' ||
					ar[y5][x5] == '#' || ar[y5][x5] == '$') y5++;
			}
			if (y5 < y1) {
				y5++;
				if (ar[y5][x5] == '1' || ar[y5][x5] == '2' || ar[y5][x5] == '3' ||
					ar[y5][x5] == '4' || ar[y5][x5] == '5' || ar[y5][x5] == '6' ||
					ar[y5][x5] == '7' || ar[y5][x5] == '8' || ar[y5][x5] == '9' ||
					ar[y5][x5] == '0' || ar[y5][x5] == '!' || ar[y5][x5] == '@' ||
					ar[y5][x5] == '#' || ar[y5][x5] == '$') y5--;
			}

			break;
		}
		if (ar[y1][x1] == ' ') {
			point = point + 100;
			wsprintf(a, TEXT("점수=%d"), point);
			ar[y1][x1] = '%';
		}


		InvalidateRect(hWnd, NULL, 0);
		return 0;

	case WM_KEYDOWN:

		switch (wParam) {
		case VK_RIGHT:

			p = 18; q = 4; mp = 14;
			SetTimer(hWnd, 1, 100, NULL);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
			KillTimer(hWnd, 5);
			//팩맨 오른쪽
			break;
		case VK_LEFT:

			p = 20; q = 2; mp = 18;
			SetTimer(hWnd, 2, 100, NULL);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
			KillTimer(hWnd, 5);
			//팩맨 왼쪽 
			break;

		case VK_UP:

			p = 21; q = 1; mp = 20;
			SetTimer(hWnd, 3, 100, NULL);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 4);
			KillTimer(hWnd, 5);
			//팩맨 위쪽
			break;

		case VK_DOWN:

			p = 19; q = 3; mp = 16;
			SetTimer(hWnd, 4, 100, NULL);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 5);
			//팩맨 아래쪽  
			break;
		}
		SetTimer(hWnd, 5, 100, NULL);
		if (point >= 1500) SetTimer(hWnd, 6, 200, NULL);
		if (point >= 6000) SetTimer(hWnd, 7, 200, NULL);
		if (point >= 10000) SetTimer(hWnd, 8, 200, NULL);
		if (point >= 14000) SetTimer(hWnd, 9, 200, NULL);
		InvalidateRect(hWnd, NULL, 0);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);


		if (x2 <= -1) x2 = 14;
		if (x1 == x2 && y1 == y2) life--;
		if (x1 == x3 && y1 == y3) life--;
		if (x1 == x4 && y1 == y4) life--;
		if (x1 == x5 && y1 == y5) life--;
		if (life <= -1)PostQuitMessage(0);

		DrawBitmap(hdc);
		if (point >= 18000) PostQuitMessage(0);
		// if(point=100)
		if (point == 1500) { x2 = 10; y2 = 8; }
		if (point == 6000) { x3 = 10; y3 = 8; }
		if (point == 10000) { x4 = 10; y4 = 8; }
		if (point == 14000) { x5 = 10; y5 = 8; }
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}



/*비트맵 파일을 화면에 보이게할 함수.
더블 버퍼링을 이용하여 화면의 깜박이는 현상 없앰.
프로그래스와 에디트 부분은 아직 깜박이는 현상이 있음.
*/
void DrawBitmap(HDC hdc)
{
	//실제 비트멥 이미지를 가질 DC핸들과 가상의 DC핸들 변수선언
	HDC hMemDC, hMemDC2;
	HBITMAP hOldBitmap, hBackBit;

	//실제 비트멥 이미지를 가질 DC핸들 지정
	hMemDC = CreateCompatibleDC(hdc);
	hBackBit = CreateCompatibleBitmap(hdc, 1024, 768);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackBit);

	//임시 비트맵 이미지를 가질 가상 DC핸들 지정
	hMemDC2 = CreateCompatibleDC(hdc);
	//배경을 선택
	SelectObject(hMemDC2, background[1]);

	//가상의 hMemDC2를 실제 hMemDC에 복사
	BitBlt(hMemDC, 0, 0, 1024, 768, hMemDC2, 0, 0, SRCCOPY);
	DeleteDC(hMemDC2);

	//투명색으로 빨간색으로 지정 후 hMemDC에 복사

	for (y = 0; y <= 18; y++) {
		for (x = 0; x <= 21; x++) {
			if (ar[y][x] == '1')TransBlt(hMemDC, x * 25, y * 25, background[2], RGB(1, 0, 0));
			if (ar[y][x] == '2')TransBlt(hMemDC, x * 25, y * 25, background[3], RGB(1, 0, 0));
			if (ar[y][x] == '3')TransBlt(hMemDC, x * 25, y * 25, background[4], RGB(1, 0, 0));
			if (ar[y][x] == '4')TransBlt(hMemDC, x * 25, y * 25, background[5], RGB(1, 0, 0));
			if (ar[y][x] == '5')TransBlt(hMemDC, x * 25, y * 25, background[6], RGB(1, 0, 0));
			if (ar[y][x] == '6')TransBlt(hMemDC, x * 25, y * 25, background[7], RGB(1, 0, 0));
			if (ar[y][x] == '7')TransBlt(hMemDC, x * 25, y * 25, background[8], RGB(1, 0, 0));
			if (ar[y][x] == '8')TransBlt(hMemDC, x * 25, y * 25, background[9], RGB(1, 0, 0));
			if (ar[y][x] == '9')TransBlt(hMemDC, x * 25, y * 25, background[10], RGB(1, 0, 0));
			if (ar[y][x] == '0')TransBlt(hMemDC, x * 25, y * 25, background[11], RGB(1, 0, 0));
			if (ar[y][x] == '!')TransBlt(hMemDC, x * 25, y * 25, background[12], RGB(1, 0, 0));
			if (ar[y][x] == '@')TransBlt(hMemDC, x * 25, y * 25, background[13], RGB(1, 0, 0));
			if (ar[y][x] == '#')TransBlt(hMemDC, x * 25, y * 25, background[14], RGB(1, 0, 0));
			if (ar[y][x] == '$')TransBlt(hMemDC, x * 25, y * 25, background[15], RGB(1, 0, 0));
			if (ar[y][x] == ' ')TransBlt(hMemDC, x * 25, y * 25, background[16], RGB(1, 0, 0));
			if (ar[y][x] == '%')TransBlt(hMemDC, x * 25, y * 25, background[17], RGB(1, 0, 0));
			if (ar[y][x] == '^')TransBlt(hMemDC, x * 25, y * 25, background[23], RGB(1, 0, 0));

		}

	}

	TextOut(hMemDC, 600, 700, a, lstrlen(a));
	wsprintf(b, TEXT("목숨=%d"), life);
	TextOut(hMemDC, 600, 680, b, lstrlen(b));
	TransBlt(hMemDC, x1 * 25, y1 * 25, background[p], RGB(0, 0, 0));
	TransBlt(hMemDC, x2 * 25, y2 * 25, background[24], RGB(0, 0, 0));
	TransBlt(hMemDC, x3 * 25, y3 * 25, background[25], RGB(0, 0, 0));
	TransBlt(hMemDC, x4 * 25, y4 * 25, background[26], RGB(0, 0, 0));
	TransBlt(hMemDC, x5 * 25, y5 * 25, background[27], RGB(0, 0, 0));
	if (x1 == -1 && y1 == 9) { x1 = 20; y1 = 9; } //텔레포트 (왼쪽 -> 오른쪽)
	if (x1 == 21 && y1 == 9) { x1 = 0; y1 = 9; } //텔레포트 (오른쪽 -> 왼쪽)
	if (x2 >= 20 || y2 >= 18) { x2 = 1; y2 = 1; }
	BitBlt(hdc, 0, 0, 1024, 768, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBackBit);
	DeleteDC(hMemDC);


}

/*
비트맵의 필요없는 배경부분을 없애줄수 있는 함수.
TransparentBle함수에 비하여 속도나 성능이 뛰어남.
*/
//* TransBlt 함수
// 투명 비트맵을 출력하는 함수. (x,y)에 출력 위치. clrMask에 투명색을 준다.
void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask)
{
	BITMAP bm;
	COLORREF cColor;
	HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC		hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT	ptSize;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize, 1);

	hdcBack = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem = CreateCompatibleDC(hdc);
	hdcSave = CreateCompatibleDC(hdc);

	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	bmBackOld = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld = (HBITMAP)SelectObject(hdcSave, bmSave);

	SetMapMode(hdcTemp, GetMapMode(hdc));

	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	cColor = SetBkColor(hdcTemp, clrMask);

	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	SetBkColor(hdcTemp, cColor);

	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, x, y, SRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);
	BitBlt(hdc, x, y, ptSize.x, ptSize.y, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}