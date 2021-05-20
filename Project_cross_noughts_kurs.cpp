// Project_cross_noughts_kurs.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Project_cross_noughts_kurs.h"


#define INIT_POS_X 100
#define INIT_POS_Y 100
#define WIND_WIDTH 680
#define WIND_HEIGHT 600
#define MAX_LOADSTRING 100

const int n = 20;                               // количество строк и столбцов на игровом поле (последняя строка под статистику)

HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HINSTANCE hInstance, help;

int i, j, counter, x, y, x1, y1, win = -1;
int mas[n][n], YourStat[3];
int* p[n];
bool tmp = true, new_game;                      // tmp отвечает за очередность хода. При 1 ходят крестики, при 0 - нолики
char stat[100];

COLORREF crFirstPl = RGB(255, 0, 0);//цвет крестиков
COLORREF crSecondPl = RGB(89, 89, 255);//цвет ноликов

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);               
BOOL				InitInstance(HINSTANCE, int);                       
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);                
INT_PTR CALLBACK	About1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SettingsDlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                         //основная функция оконного приложения.
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	for (i = 0; i < 3; i++)
		YourStat[i] = 0;
	strcpy_s(stat, _countof(stat), "");

	for (i = 0; i < n; i++)
		p[i] = (int*)&mas[i];                 //для последующей передачи массива в функцию

	new_game = false;
	counter = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			mas[i][j] = 0;                   
	for (i = 0; i < n; i++)
		mas[i][n - 1] = 5;                  
	UNREFERENCED_PARAMETER(hPrevInstance);  
	UNREFERENCED_PARAMETER(lpCmdLine);      

	
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PROJECTCROSSNOUGHTSKURS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECTCROSSNOUGHTSKURS));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)            
{
	WNDCLASSEX wcex;                                 

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECTCROSSNOUGHTSKURS));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_PROJECTCROSSNOUGHTSKURS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);                    
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;         // дескриптор окна

	hInst = hInstance; 

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		INIT_POS_X, INIT_POS_Y, WIND_WIDTH, WIND_HEIGHT, NULL, NULL, hInstance, NULL);  

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);    //отображение окна
	UpdateWindow(hWnd);            //обновление окна

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)   //обработчик сообщений
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;           //прорисовка
	HDC hdc;                  //экземпляр контекста устройства  
	static RECT rt, rect;     //прмоугольная область окна
	static HPEN hF, hOldF, hS, hOldS, hLine, hOldLine;  //перья для рисования 

	switch (message)
	{
	case WM_CREATE:           //сообщение о создании окна
		break;

	case WM_SIZE:             //сообщение отправляется в окно, если меняется его размер
		x = LOWORD(lParam) / n; //в переменную х помещается ширина одной клетки
		y = HIWORD(lParam) / n; //в y высота.
		break;

	case WM_LBUTTONDOWN:      //сообщение о нажатии левой кнопки мыши в области окна.
		x1 = LOWORD(lParam) / x;   //установить в x1 абсциссу курсора и поделить ее на ширину клетки. Таким образом,
		y1 = HIWORD(lParam) / y;   //в x1 будет храниться не абсцисса, а номер нажатой клетки по горизонтали. Для y1 аналогично по вертикали

		if (mas[x1][y1] == 0)  //далее, если в нажатой клетке ничего не стоит, то
		{
			if (tmp)           //проверяем tmp, отвечающий за очередность хода. Если крестики(1)
			{
				mas[x1][y1] = 1;  //то присвоим этой клетке значение 1.
				tmp = false;      //передаем ход другому игроку
			}
			else
			{
				mas[x1][y1] = 2;  //иначе присваиваем клетке значение 2. 
				tmp = true;       //передаем ход другому игроку
			}
			counter++;            //считает количество ходов 1 и 2 игрока в сумме.
		}

		win = fwinner(p, x1, y1, n);

		rect.left = x1 * x;
		rect.top = y1 * y;
		rect.right = (x1 + 1) * x;
		rect.bottom = (y1 + 1) * y;
		InvalidateRect(hWnd, &rect, FALSE);
		break;

	case WM_COMMAND:                 
		wmId = LOWORD(wParam);       
		wmEvent = HIWORD(wParam);    

		// Разобрать выбор в меню:
		switch (wmId)
		{
		case ID_STAT:                //нажали на статистику
			sprintf_s(stat, 100, "Статистика игр в данной сессии:\n\nПобед 1го игрока - %d;\nПобед 2го игрока - %d;\nНичей - %d;", YourStat[0], YourStat[1], YourStat[2]);  
			MessageBox(hWnd, stat, "Статистика", NULL);
			break;
		case ID_NEWGAME:             //нажали на новую игру
			if (new_game == false)   
				new_game = true;
			else
			{
				new_game = false;
				counter = 0;
				for (i = 0; i < n; i++)
					for (j = 0; j < n; j++)
						mas[i][j] = 0;
				for (i = 0; i < n; i++)
					mas[i][n - 1] = 5;
				win = -1;
				tmp = true;
			}
			InvalidateRect(hWnd, NULL, TRUE);  
			break;
		case ID_PRODUCE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About1);
			break;
		case ID_SETTINGS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, SettingsDlgProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:                        //отрисовка
		hdc = BeginPaint(hWnd, &ps);      
		hF = CreatePen(PS_SOLID, 2, crFirstPl); 
		hS = CreatePen(PS_SOLID, 2, crSecondPl); 
		hLine = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); 
		hOldLine = (HPEN)SelectObject(hdc, hLine); 
		hOldF = (HPEN)SelectObject(hdc, hF);
		hOldS = (HPEN)SelectObject(hdc, hS);
		GetClientRect(hWnd, &rt); 

		TEXTMETRIC tm;    //структура, содержащая информацию о шрифте
		GetTextMetrics(hdc, &tm);

		if (new_game)
		{
			SelectObject(hdc, hLine);
			for (i = 1; i <= n; i++)
				for (j = 1; j < n; j++)
					Rectangle(hdc, rt.right / n * (i - 1), (j - 1) * rt.bottom / n, i * rt.right / n, j * rt.bottom / n); //рисуем прямоугольные клеточки

			sprintf_s(stat, 100, "Статистика игр в данной сессии:  Побед 1го игрока - %d;  Побед 2го игрока - %d;  Ничей - %d;", YourStat[0], YourStat[1], YourStat[2]);
			TextOut(hdc, rt.right / n, (n - 0.95) * rt.bottom / n, stat, strlen(stat));

			for (x1 = 0; x1 < n; x1++)              
				for (y1 = 0; y1 < n - 1; y1++)
				{
					if (mas[x1][y1] == 1)
					{
						SelectObject(hdc, hF);
						MoveToEx(hdc, x1 * x, y1 * y, NULL);
						LineTo(hdc, (x1 + 1) * x, (y1 + 1) * y);
						MoveToEx(hdc, x1 * x, (y1 + 1) * y, NULL);
						LineTo(hdc, (x1 + 1) * x, y1 * y);
					}
					if (mas[x1][y1] == 2)
					{
						SelectObject(hdc, hS);
						Ellipse(hdc, x1 * x, y1 * y, (x1 + 1) * x, (y1 + 1) * y);
					}

				}

			if (win == 1)
			{
				MessageBox(hWnd, "Победил 1 игрок", "Победа!", NULL);
				new_game = false;
				counter = 0;
				for (i = 0; i < n; i++)
					for (j = 0; j < n; j++)
						mas[i][j] = 0;
				for (i = 0; i < n; i++)
					mas[i][n - 1] = 5;
				win = -1;
				tmp = true;
				YourStat[0]++;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else if (win == 0)
			{
				MessageBox(hWnd, "Победил 2 игрок", "Победа!", NULL);
				new_game = false;
				counter = 0;
				for (i = 0; i < n; i++)
					for (j = 0; j < n; j++)
						mas[i][j] = 0;
				for (i = 0; i < n; i++)
					mas[i][n - 1] = 5;
				win = -1;
				tmp = true;
				YourStat[1]++;
				InvalidateRect(hWnd, NULL, TRUE);
			}

			if (counter == n * n)
			{
				MessageBox(hWnd, "Боевая ничья, пожмите друг-другу руки!;)", "Ничья!", NULL);
				new_game = false;
				counter = 0;
				for (i = 0; i < n; i++)
					for (j = 0; j < n; j++)
						mas[i][j] = 0;
				for (i = 0; i < n; i++)
					mas[i][n - 1] = 5;
				win = -1;
				tmp = true;
				YourStat[2]++;
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}

		SelectObject(hdc, hOldF);
		DeleteObject(hF);
		SelectObject(hdc, hOldS);
		DeleteObject(hS);
		SelectObject(hdc, hOldLine);
		DeleteObject(hLine);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//Нaстройки
INT_PTR CALLBACK CALLBACK SettingsDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HDC hdcSet;
	PAINTSTRUCT ps;
	COLORREF crFirst, crSecond;
	static CHOOSECOLOR cc;//структура "выбора" цвета
	static COLORREF CustClr[16];

	switch (uMsg)
	{
	case WM_INITDIALOG:
		//инициализируем станд. окно выбора цвета
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hDlg;
		cc.lpCustColors = (LPDWORD)CustClr;
		cc.Flags = CC_FULLOPEN || CC_RGBINIT;
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CHOOSE1:
			if (ChooseColor(&cc))crFirstPl = cc.rgbResult;
			break;
		case IDC_CHOOSE2:
			if (ChooseColor(&cc))crSecondPl = cc.rgbResult;
			break;
		case IDC_OK:
			EndDialog(hDlg, 0);
			break;
		}
		InvalidateRect(hDlg, NULL, TRUE);	//переисовываем модальное окно, чтоб квадратики были выбраного цвета
		break;

	case WM_PAINT://здесь выводяться 2 квадратика с соотв. цветами
		crFirst = crFirstPl;
		crSecond = crSecondPl;

		hdcSet = BeginPaint(hDlg, &ps);
		HBRUSH hBrushF, hOldBrush, hBrushS;

		hBrushF = CreateSolidBrush(crFirst);
		hBrushS = CreateSolidBrush(crSecond);
		hOldBrush = (HBRUSH)SelectObject(hdcSet, hBrushF);

		SelectObject(hdcSet, hBrushF);
		Rectangle(hdcSet, 140, 50, 160, 70);

		SelectObject(hdcSet, hBrushS);
		Rectangle(hdcSet, 140, 87, 160, 107);

		SelectObject(hdcSet, hOldBrush);
		DeleteObject(hBrushF);
		EndPaint(hDlg, &ps);
		break;
	}
	return FALSE;
}

// Обработчик сообщений для окна "О создателе".
INT_PTR CALLBACK About1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			EndDialog(hDlg, LOWORD(wParam));
		break;
	}
	return FALSE;
}