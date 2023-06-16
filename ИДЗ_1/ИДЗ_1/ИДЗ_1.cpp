// ИДЗ_1.cpp : Определяет точку входа для приложения.
//

#include <math.h>
#include <windows.h>
#include "framework.h"
#include "ИДЗ_1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

class Figure
{
public:
    // Функция рисования прямоугольника с кругом и линией
    void Draw(HWND hwnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Рисование прямоугольника
        Rectangle(hdc, 50, 100, 400, 300);

        // Рисование круга в правом верхнем углу
        DrawCircle(hdc, 350, 150, 50);

        // Рисование линии в левом нижнем углу
        DrawLine(hdc, 50, 200, 200, 300);

        EndPaint(hwnd, &ps);
    }

    // Функция рисования окружности по алгоритму Брезенхэма
    void DrawCircle(HDC hdc, int x0, int y0, int radius)
    {
        int x = 0, y = radius;
        int d = 3 - 2 * radius;
        while (x <= y)
        {
            SetPixel(hdc, x0 + x, y0 + y, RGB(0, 0, 255));
            SetPixel(hdc, x0 - x, y0 + y, RGB(0, 255, 0));
            SetPixel(hdc, x0 + x, y0 - y, RGB(255, 0, 0));
            SetPixel(hdc, x0 - x, y0 - y, RGB(255, 255, 255));
            SetPixel(hdc, x0 + y, y0 + x, RGB(0, 255, 255));
            SetPixel(hdc, x0 - y, y0 + x, RGB(255, 0, 255));
            SetPixel(hdc, x0 + y, y0 - x, RGB(255, 255, 0));
            SetPixel(hdc, x0 - y, y0 - x, RGB(192, 192, 192));
            if (d < 0)
                d += 4 * x++ + 6;
            else
                d += 4 * (x++ - y--) + 10;
        }
    }

    // Функция рисования линии по алгоритму Брезенхэма
    void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
    {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;
        int e2;
        while (true)
        {
            SetPixel(hdc, x1, y1, RGB(0, 0, 0));
            if (x1 == x2 && y1 == y2)
                break;
            e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y1 += sy;
            }
        }
    }
};

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    static POINT ptOld;
    static int iTransformation = 0; // начальное преобразование - поворот
    static HDC hdc, hdcMem;
    static HBITMAP hBitmap, hBitmapOld;
    static int x = 100, y = 100; // координаты центра фигуры
    static int r = 50; // радиус фигуры
    static int angle = 30; // угол поворота фигуры
    static int sign = 1; // знак отражения фигуры

    switch (message)
    {
    case WM_LBUTTONDOWN:
        ptOld.x = LOWORD(lParam);
        ptOld.y = HIWORD(lParam);
        break;

    case WM_LBUTTONUP:
    {
        int dx = LOWORD(lParam) - ptOld.x;
        int dy = HIWORD(lParam) - ptOld.y;

        // вычисление новых координат центра фигуры
        x += dx;
        y += dy;

        // отрисовка фигуры в буфере
        Figure figure;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Рисование прямоугольника
        Rectangle(hdc, 50 - r, 100 - r, 400 + r, 300 + r);

        // Рисование круга в правом верхнем углу
        figure.DrawCircle(hdc, 350 - r, 150 - r, 50 + r);

        // Рисование линии в левом нижнем углу
        figure.DrawLine(hdc, 50 - r, 200 - r, 200 + r, 300 + r);

        EndPaint(hWnd, &ps);

        // перенос фигуры с буфера на экран
        hdc = GetDC(hWnd);
        BitBlt(hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(hWnd, hdc);
    }
    break;

    case WM_RBUTTONDOWN:
        iTransformation = (iTransformation + 1) % 2; // переключение преобразования
        break;

    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON)
        {
            int dx = LOWORD(lParam) - ptOld.x;
            int dy = HIWORD(lParam) - ptOld.y;

            // вычисление угла поворота фигуры
            angle = (int)(atan2(y - ptOld.y, ptOld.x - x) / 3.141592654 * 180);

            // отрисовка старой фигуры в буфере
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            Figure figure;
            figure.Draw(hWnd);

            // поворот фигуры в буфере
            SelectObject(hdcMem, GetStockObject(BLACK_BRUSH));
            SetGraphicsMode(hdcMem, GM_ADVANCED);
            XFORM xform;
            xform.eM11 = (FLOAT)cos((angle + 90) / 180.0 * 3.141592654);
            xform.eM12 = (FLOAT)sin((angle + 90) / 180.0 * 3.141592654);
            xform.eM21 = (FLOAT)-sin((angle + 90) / 180.0 * 3.141592654);
            xform.eM22 = (FLOAT)cos((angle + 90) / 180.0 * 3.141592654);
            xform.eDx = (FLOAT)ptOld.x;
            xform.eDy = (FLOAT)ptOld.y;
            SetWorldTransform(hdcMem, &xform);

            // отражение фигуры в буфере
            if (sign == -1)
            {
                SelectObject(hdcMem, GetStockObject(WHITE_BRUSH));

                // Рисование прямоугольника
                Rectangle(hdc, 50 - r, 100 - r, 400 + r, 300 + r);

                // Рисование круга в правом верхнем углу
                figure.DrawCircle(hdc, 350 - r, 150 - r, 50 + r);

                // Рисование линии в левом нижнем углу
                figure.DrawLine(hdc, 50 - r, 200 - r, 200 + r, 300 + r);

                EndPaint(hWnd, &ps);
            }
            SelectObject(hdcMem, GetStockObject(BLACK_BRUSH));
            SetGraphicsMode(hdcMem, GM_ADVANCED);
            xform.eM11 = (FLOAT)sign;
            xform.eM12 = 0;
            xform.eM21 = 0;
            xform.eM22 = (FLOAT)sign;
            xform.eDx = (FLOAT)(2 * x - ptOld.x);
            xform.eDy = 0;
            SetWorldTransform(hdcMem, &xform);

            // перенос фигуры с буфера на экран
            hdc = GetDC(hWnd);
            BitBlt(hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0, SRCCOPY);
            ReleaseDC(hWnd, hdc);

            // сохранение старой позиции мыши
            ptOld.x = LOWORD(lParam);
            ptOld.y = HIWORD(lParam);
        }
        break;
    case WM_KEYUP:
        if (wParam == VK_ESCAPE)
        {
            // очистка экрана и выход из программы
            SelectObject(hdcMem, GetStockObject(WHITE_BRUSH));
            SelectObject(hdcMem, GetStockObject(WHITE_PEN));
            Rectangle(hdcMem, 0, 0, cxClient, cyClient);
            hdc = GetDC(hWnd);
            BitBlt(hdc, 0, 0, cxClient, cyClient, hdcMem, 0, 0, SRCCOPY);
            ReleaseDC(hWnd, hdc);
            SendMessage(hWnd, WM_DESTROY, 0, 0);
        }
        else if (wParam == VK_RETURN)
        {
            // изменение знака отражения фигуры
            sign = -sign;
        }
        break;
    case WM_PAINT:
        {
            Figure figure;
            figure.Draw(hWnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
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