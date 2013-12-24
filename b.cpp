#include <iostream>
#include <windows.h>
#include <math.h>
#include <stdio.h>
 

using namespace std;

class Line
{
public:
    double a;
    double b;
public:
    Line(double i, double j): a(i), b(j) 
    {}
    bool Draw(HDC hdc, HWND hWnd)
    {
        RECT rcWind;
        GetClientRect(hWnd, &rcWind); 
        MoveToEx(hdc, rcWind.left, rcWind.bottom - b, NULL); //сделать текущими координаты x1, y1
        return LineTo(hdc, rcWind.right, rcWind.bottom - a*(rcWind.right - rcWind.left) - b);
    }
    
};

class Circle
{
public:
    double x;
    double y;
    double r;	
public:
    Circle(double i, double j, double k): x(i), y(j), r(k) 
    {}
    bool Draw(HDC hdc, HWND hWnd)
    {
        RECT rcWind;
        GetClientRect(hWnd, &rcWind); 
        //MoveToEx(hdc, rcWind.left, rcWind.bottom, NULL); //сделать текущими координаты x1, y1
        //return Ellipse(hdc,
        return Arc (hdc, 
           rcWind.left + x - r, 
           rcWind.bottom - y + r,
           rcWind.left + x + r,
           rcWind.bottom - y - r,
           rcWind.left + x,
           rcWind.left + y,
           rcWind.left + x,
           rcWind.left + y
        );
    }
    
};


static LOGFONT lf;

void Intersection (HDC hdc, HWND hWnd, Line l, Circle c) {

    RECT rcWind;
    GetClientRect(hWnd, &rcWind); 
    

    double b1 = -2*c.x + 2*l.a*l.b - 2*l.a*c.y;
    double D = b1*b1 - 4*(1 + l.a*l.a)*(c.x*c.x + l.b*l.b + c.y*c.y - 2*l.b*c.y - c.r*c.r);
    double x1 = (-b1 + sqrt(D)) / (2*(1+l.a*l.a));
    double x2 = (-b1 - sqrt(D)) / (2*(1+l.a*l.a));
    double y1 = l.a*(x1 - rcWind.left) + l.b;
    double y2 = l.a*(x2 - rcWind.left) + l.b;
    
    
    char buff [20];


    lf.lfHeight = 20*(log (c.r))/5; //высота
    lf.lfWidth = 10*(log (c.r))/5; //ширина

    HFONT hFont=CreateFontIndirect(&lf); //Cоздали шрифт
    SelectObject(hdc, hFont);
    
    for (int i=0; i < 20; i++) {
        buff[i] = ' ';
    }
    sprintf (buff, "(%.4g, %.4g)", x1, y1);
    TextOut(hdc, rcWind.left + x1, rcWind.bottom - y1, buff, 20);
    
    
    for (int i=0; i < 20; i++) {
        buff[i] = ' ';
    }
    sprintf (buff, "(%.4g, %.4g)", x2, y2);
    TextOut(hdc, rcWind.left + x2, rcWind.bottom - y2, buff, 20);

}

Line l = Line(0.5,0);
Circle c = Circle(200, 100, 100);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szProgName[]="Line and circle";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
 {
 HWND hWnd;
 MSG lpMsg;
 WNDCLASS w;

 w.lpszClassName=szProgName; //имя программы
 w.hInstance=hInstance; //идентификатор текущего приложения
 w.lpfnWndProc=WndProc; //указатель на функцию окна
 w.hCursor=LoadCursor(NULL, IDC_ARROW); //курсор
 w.hIcon=0; //icon
 w.lpszMenuName=0; //menu
 w.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); //цвет фона окна
 w.style=CS_HREDRAW|CS_VREDRAW; //стиль - перерисовываемое по х и по у
 w.cbClsExtra=0;
 w.cbWndExtra=0;

 if(!RegisterClass(&w)) //registration
 return 0;

 hWnd=CreateWindow(szProgName, //Имя программы
 szProgName, //Заголовок окна
 WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
 0, //положение окна на экране по х
 0, //положение по у
 1200, //ширина
 700, //высота
 (HWND)NULL, //идентификатор родительского окна
 (HMENU)NULL, //идентификатор меню
 (HINSTANCE)hInstance, //идентификатор экземпляра программы
 (HINSTANCE)NULL); //отсутствие дополнительных параметров


 ShowWindow(hWnd, nCmdShow); //Выводим окно из памяти на экран
 UpdateWindow(hWnd); //Обновим содержимое окна

 //Цикл обработки сообщений

 while(GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
 TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
 DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
 }
 return(lpMsg.wParam); 
 }

 //Функция окна
 LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, 
 WPARAM wParam, LPARAM lParam)
 {
 HDC hdc; //создаём контекст устройства
 PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

 //Цикл обработки сообщений
 

 switch(messg)
 {
 //сообщение рисования
 case WM_PAINT :
 hdc=BeginPaint(hWnd, &ps);
 
 
 
 l.Draw(hdc, hWnd);
 c.Draw(hdc, hWnd);
 
 Intersection (hdc, hWnd, l, c);       
 
 
 ValidateRect(hWnd, NULL); //обновляем окно
 EndPaint(hWnd, &ps); //заканчиваем рисовать
 break;

 //сообщение выхода
 case WM_DESTROY:
 PostQuitMessage(0); //сообщение выхода с кодом 0 - нормальное завершение
 break;

 default:
 return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
 }
 return 0;
}