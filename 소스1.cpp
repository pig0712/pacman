// 수정파일
#include <windows.h>
#include "resource.h"
#include <time.h> // srand, time 함수 사용을 위해 포함

// 상수 정의
#define TILE_SIZE 25 // 타일 하나의 크기
#define MAP_ROWS 18
#define MAP_COLS 22

// 팩맨 및 유령 속도 타이머 ID
#define TIMER_PACMAN_MOVE_RIGHT 1
#define TIMER_PACMAN_MOVE_LEFT 2
#define TIMER_PACMAN_MOVE_UP 3
#define TIMER_PACMAN_MOVE_DOWN 4
#define TIMER_PACMAN_ANIMATION 5
#define TIMER_GHOST1_MOVE 6
#define TIMER_GHOST2_MOVE 7
#define TIMER_GHOST3_MOVE 8
#define TIMER_GHOST4_MOVE 9

// 팩맨 애니메이션 관련 상수
#define PACMAN_ANIM_START_LEFT 20
#define PACMAN_ANIM_START_RIGHT 18
#define PACMAN_ANIM_START_UP 21
#define PACMAN_ANIM_START_DOWN 19
#define PACMAN_ANIM_INCREMENT_RIGHT 4
#define PACMAN_ANIM_INCREMENT_LEFT 2
#define PACMAN_ANIM_INCREMENT_UP 1
#define PACMAN_ANIM_INCREMENT_DOWN 3
#define PACMAN_ANIM_MAX 23 // 실제 배경 이미지 인덱스에 따라 조정 필요

// 전역 변수
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("팩맨");
HWND hWndMain;

// 팩맨 위치 및 애니메이션 관련
int pacmanX = 1, pacmanY = 1;
int pacmanAnimCurrent = 17, pacmanAnimOffset = 0, pacmanAnimBase = 0;

// 유령 위치
int ghostX[4] = { 10, 9, 10, 11 }; // x2, x3, x4, x5
int ghostY[4] = { 8, 10, 10, 10 }; // y2, y3, y4, y5

// 게임 상태 변수
int point = 0;
int life = 100; // 라이프는 일반적으로 횟수이므로 음수가 되지 않도록 주의
TCHAR scoreText[100];
TCHAR lifeText[100];

// 맵 데이터
char gameMap[MAP_ROWS][MAP_COLS] = {
    "2666666666!6666666661",
    "5          5          5",
    "5 21 2661 5 2661 21 5",
    "5 43 4663 9 4663 43 5",
    "5                    5",
    "5 261 0 76!68 0 261 5",
    "5 463 5    5    5 463 5",
    "5   #68 9 76$     5",
    "468 0 5        5 0 763",
    "    5 9 26661 9 5    ",
    "268 9   5^^^5   9 761",
    "5   0 46663 0     5",
    "5 761 5        5 268 5",
    "5   5 9 76!68 9 5   5",
    "#61 5      9      5 26$",
    "5 9 9 768  768 9 9 5",
    "5          0          5",
    "4666666666@6666666663"
};

// 비트맵 리소스 핸들 (배경 및 아이콘)
HBITMAP background[30];

// 비트맵 이미지의 필요 없는 배경을 없애주는 함수
void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask);

// 비트맵을 윈도우상에 그려주는 함수
void DrawGame(HDC hdc);

// 벽 타일 식별 함수
BOOL IsWall(char tile) {
    // '1'부터 '0'까지, 그리고 '!', '@', '#', '$' 문자가 벽을 나타냅니다.
    // 이는 매직 넘버를 사용하므로, 더 명확한 정의가 필요합니다.
    return (tile >= '0' && tile <= '9') ||
           (tile >= '!' && tile <= '$');
}

// 유령 움직임 로직 함수 (반복되는 코드 제거)
void MoveGhost(int ghostIdx, int pacX, int pacY) {
    int* currentGhostX = &ghostX[ghostIdx];
    int* currentGhostY = &ghostY[ghostIdx];
    int prevX = *currentGhostX;
    int prevY = *currentGhostY;

    // 팩맨을 향해 x축 이동 시도
    if (*currentGhostX > pacX) {
        (*currentGhostX)--;
        if (IsWall(gameMap[*currentGhostY][*currentGhostX])) {
            *currentGhostX = prevX; // 벽에 부딪히면 되돌리기
        }
    } else if (*currentGhostX < pacX) {
        (*currentGhostX)++;
        if (IsWall(gameMap[*currentGhostY][*currentGhostX])) {
            *currentGhostX = prevX; // 벽에 부딪히면 되돌리기
        }
    }

    // 팩맨을 향해 y축 이동 시도
    if (*currentGhostY > pacY) {
        (*currentGhostY)--;
        if (IsWall(gameMap[*currentGhostY][*currentGhostX])) {
            *currentGhostY = prevY; // 벽에 부딪히면 되돌리기
        }
    } else if (*currentGhostY < pacY) {
        (*currentGhostY)++;
        if (IsWall(gameMap[*currentGhostY][*currentGhostX])) {
            *currentGhostY = prevY; // 벽에 부딪히면 되돌리기
        }
    }
}


// 윈도우 메인 부분
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASS WndClass;
    g_hInst = hInstance;

    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WndProc;
    WndClass.lpszClassName = lpszClass;
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&WndClass);

    hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
        0, 0, 1024, 768,
        NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);

    // 메시지 루프
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

    switch (iMessage) {
    case WM_CREATE:
        hWndMain = hWnd;
        // 비트맵 리소스들을 background[] 배열에 등록
        for (int i = 1; i <= 27; ++i) {
            background[i] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i - 1));
        }
        return 0;

    case WM_TIMER:
        switch (wParam) {
        case TIMER_PACMAN_MOVE_RIGHT:
            if (!IsWall(gameMap[pacmanY][pacmanX + 1])) {
                if (gameMap[pacmanY][pacmanX + 1] == ' ') {
                    point += 100;
                    gameMap[pacmanY][pacmanX + 1] = '%'; // 먹은 아이템 표시
                }
                pacmanX++;
            } else {
                KillTimer(hWnd, TIMER_PACMAN_MOVE_RIGHT);
                KillTimer(hWnd, TIMER_PACMAN_ANIMATION);
            }
            break;
        case TIMER_PACMAN_MOVE_LEFT:
            if (!IsWall(gameMap[pacmanY][pacmanX - 1])) {
                if (gameMap[pacmanY][pacmanX - 1] == ' ') {
                    point += 100;
                    gameMap[pacmanY][pacmanX - 1] = '%';
                }
                pacmanX--;
            } else {
                KillTimer(hWnd, TIMER_PACMAN_MOVE_LEFT);
                KillTimer(hWnd, TIMER_PACMAN_ANIMATION);
            }
            break;
        case TIMER_PACMAN_MOVE_UP:
            if (!IsWall(gameMap[pacmanY - 1][pacmanX])) {
                if (gameMap[pacmanY - 1][pacmanX] == ' ') {
                    point += 100;
                    gameMap[pacmanY - 1][pacmanX] = '%';
                }
                pacmanY--;
            } else {
                KillTimer(hWnd, TIMER_PACMAN_MOVE_UP);
                KillTimer(hWnd, TIMER_PACMAN_ANIMATION);
            }
            break;
        case TIMER_PACMAN_MOVE_DOWN:
            if (!IsWall(gameMap[pacmanY + 1][pacmanX])) {
                if (gameMap[pacmanY + 1][pacmanX] == ' ') {
                    point += 100;
                    gameMap[pacmanY + 1][pacmanX] = '%';
                }
                pacmanY++;
            } else {
                KillTimer(hWnd, TIMER_PACMAN_MOVE_DOWN);
                KillTimer(hWnd, TIMER_PACMAN_ANIMATION);
            }
            break;
        case TIMER_PACMAN_ANIMATION:
            pacmanAnimCurrent = pacmanAnimBase + pacmanAnimOffset;
            pacmanAnimOffset = (pacmanAnimOffset + 1) % 4; // 0, 1, 2, 3 반복 (p 변수에 따라 다름)
            break;

        case TIMER_GHOST1_MOVE:
            MoveGhost(0, pacmanX, pacmanY);
            break;
        case TIMER_GHOST2_MOVE:
            MoveGhost(1, pacmanX, pacmanY);
            break;
        case TIMER_GHOST3_MOVE:
            MoveGhost(2, pacmanX, pacmanY);
            break;
        case TIMER_GHOST4_MOVE:
            MoveGhost(3, pacmanX, pacmanY);
            break;
        }

        // 텔레포트 처리
        if (pacmanX == -1 && pacmanY == 9) { pacmanX = MAP_COLS - 2; pacmanY = 9; }
        if (pacmanX == MAP_COLS - 1 && pacmanY == 9) { pacmanX = 0; pacmanY = 9; }

        // 유령 초기화 (포인트 달성 시)
        if (point == 1500) { ghostX[0] = 10; ghostY[0] = 8; SetTimer(hWnd, TIMER_GHOST1_MOVE, 200, NULL); }
        if (point == 6000) { ghostX[1] = 10; ghostY[1] = 8; SetTimer(hWnd, TIMER_GHOST2_MOVE, 200, NULL); }
        if (point == 10000) { ghostX[2] = 10; ghostY[2] = 8; SetTimer(hWnd, TIMER_GHOST3_MOVE, 200, NULL); }
        if (point == 14000) { ghostX[3] = 10; ghostY[3] = 8; SetTimer(hWnd, TIMER_GHOST4_MOVE, 200, NULL); }

        // 충돌 검사
        for (int i = 0; i < 4; ++i) {
            if (pacmanX == ghostX[i] && pacmanY == ghostY[i]) {
                life--;
                // 충돌 시 유령을 시작 지점으로 돌려보내거나 잠시 무적 시간을 주는 등의 추가 로직이 필요할 수 있습니다.
                // 여기서는 간단히 라이프만 감소시키고 유령은 계속 움직입니다.
                // Reset ghost to start position after collision
                // ghostX[i] = initialGhostX[i];
                // ghostY[i] = initialGhostY[i];
            }
        }

        if (life <= 0) {
            PostQuitMessage(0); // 게임 종료
        }
        if (point >= 18000) {
            PostQuitMessage(0); // 게임 승리 종료
        }
        InvalidateRect(hWnd, NULL, FALSE); // 배경을 지우지 않고 다시 그리기 (깜박임 감소)
        return 0;

    case WM_KEYDOWN:
        // 기존 타이머 모두 비활성화
        KillTimer(hWnd, TIMER_PACMAN_MOVE_RIGHT);
        KillTimer(hWnd, TIMER_PACMAN_MOVE_LEFT);
        KillTimer(hWnd, TIMER_PACMAN_MOVE_UP);
        KillTimer(hWnd, TIMER_PACMAN_MOVE_DOWN);
        KillTimer(hWnd, TIMER_PACMAN_ANIMATION); // 애니메이션 타이머도 재설정

        switch (wParam) {
        case VK_RIGHT:
            pacmanAnimBase = PACMAN_ANIM_START_RIGHT;
            pacmanAnimOffset = PACMAN_ANIM_INCREMENT_RIGHT;
            SetTimer(hWnd, TIMER_PACMAN_MOVE_RIGHT, 100, NULL);
            break;
        case VK_LEFT:
            pacmanAnimBase = PACMAN_ANIM_START_LEFT;
            pacmanAnimOffset = PACMAN_ANIM_INCREMENT_LEFT;
            SetTimer(hWnd, TIMER_PACMAN_MOVE_LEFT, 100, NULL);
            break;
        case VK_UP:
            pacmanAnimBase = PACMAN_ANIM_START_UP;
            pacmanAnimOffset = PACMAN_ANIM_INCREMENT_UP;
            SetTimer(hWnd, TIMER_PACMAN_MOVE_UP, 100, NULL);
            break;
        case VK_DOWN:
            pacmanAnimBase = PACMAN_ANIM_START_DOWN;
            pacmanAnimOffset = PACMAN_ANIM_INCREMENT_DOWN;
            SetTimer(hWnd, TIMER_PACMAN_MOVE_DOWN, 100, NULL);
            break;
        }
        SetTimer(hWnd, TIMER_PACMAN_ANIMATION, 100, NULL); // 애니메이션 타이머 다시 시작
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawGame(hdc);
        EndPaint(hWnd, &ps);
        return 0;

    case WM_DESTROY:
        // 로드한 비트맵 리소스 해제
        for (int i = 1; i <= 27; ++i) {
            if (background[i]) {
                DeleteObject(background[i]);
                background[i] = NULL;
            }
        }
        PostQuitMessage(0);
        return 0;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// 비트맵 파일을 화면에 보이게 할 함수. 더블 버퍼링을 이용하여 화면의 깜박이는 현상 없앰.
void DrawGame(HDC hdc)
{
    HDC hMemDC, hMemDC2;
    HBITMAP hOldBitmap, hBackBit;

    hMemDC = CreateCompatibleDC(hdc);
    hBackBit = CreateCompatibleBitmap(hdc, 1024, 768);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackBit);

    hMemDC2 = CreateCompatibleDC(hdc);
    SelectObject(hMemDC2, background[1]); // 배경 이미지 (맵 아래에 깔리는 이미지)
    BitBlt(hMemDC, 0, 0, 1024, 768, hMemDC2, 0, 0, SRCCOPY);
    DeleteDC(hMemDC2);

    // 맵 그리기
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            // 벽, 아이템 등 맵 요소 그리기
            // 각 문자에 해당하는 비트맵 ID를 매핑하는 더 나은 방법이 필요
            int bitmapIndex = 0;
            switch (gameMap[y][x]) {
                case '1': bitmapIndex = 2; break;
                case '2': bitmapIndex = 3; break;
                case '3': bitmapIndex = 4; break;
                case '4': bitmapIndex = 5; break;
                case '5': bitmapIndex = 6; break;
                case '6': bitmapIndex = 7; break;
                case '7': bitmapIndex = 8; break;
                case '8': bitmapIndex = 9; break;
                case '9': bitmapIndex = 10; break;
                case '0': bitmapIndex = 11; break;
                case '!': bitmapIndex = 12; break;
                case '@': bitmapIndex = 13; break;
                case '#': bitmapIndex = 14; break;
                case '$': bitmapIndex = 15; break;
                case ' ': bitmapIndex = 16; break; // 먹을 아이템 (점)
                case '%': bitmapIndex = 17; break; // 먹은 아이템 (빈 공간)
                case '^': bitmapIndex = 23; break; // 유령 집 문
                default: continue; // 정의되지 않은 문자는 그리지 않음
            }
            if (bitmapIndex != 0) {
                TransBlt(hMemDC, x * TILE_SIZE, y * TILE_SIZE, background[bitmapIndex], RGB(1, 0, 0));
            }
        }
    }

    wsprintf(scoreText, TEXT("점수=%d"), point);
    TextOut(hMemDC, 600, 700, scoreText, lstrlen(scoreText));
    wsprintf(lifeText, TEXT("목숨=%d"), life);
    TextOut(hMemDC, 600, 680, lifeText, lstrlen(lifeText));

    // 팩맨 그리기
    TransBlt(hMemDC, pacmanX * TILE_SIZE, pacmanY * TILE_SIZE, background[pacmanAnimCurrent], RGB(0, 0, 0));

    // 유령 그리기
    TransBlt(hMemDC, ghostX[0] * TILE_SIZE, ghostY[0] * TILE_SIZE, background[24], RGB(0, 0, 0));
    TransBlt(hMemDC, ghostX[1] * TILE_SIZE, ghostY[1] * TILE_SIZE, background[25], RGB(0, 0, 0));
    TransBlt(hMemDC, ghostX[2] * TILE_SIZE, ghostY[2] * TILE_SIZE, background[26], RGB(0, 0, 0));
    TransBlt(hMemDC, ghostX[3] * TILE_SIZE, ghostY[3] * TILE_SIZE, background[27], RGB(0, 0, 0));

    // 실제 화면에 복사
    BitBlt(hdc, 0, 0, 1024, 768, hMemDC, 0, 0, SRCCOPY);

    // DC 및 비트맵 해제
    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hBackBit);
    DeleteDC(hMemDC);
}

// TransBlt 함수 (기존과 동일)
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
