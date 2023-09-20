#pragma once

/* Команды для работы меню */
#define OnExitSoftware		1	// Завершение работы программы
#define OnButtonClear		2	// Очистка поля ввода
#define OnButtonRead		3   // Считывание поля ввода
#define OnSaveFile			4   // Созранить содержимое буфера в файл
#define OnLoadFile			5   // Прочитать из файла и вывести в поле ввода 
#define ShowInstructions	6   // Вывести в поле ввода инструкцию
#define ShowInfo			7   // Вывести в поле ввода справку
#define FileExport			8	// Экспортировать текущее поле ввода в отдельный файл
#define FileImport			9	// Импортировать файл и вывести в поле ввода

/* Команды для работы с цветом */
#define OnButtonClearColor	10     // Очистить поле ввода цветов RGB
#define OnButtonSetColor	11     // Установить новый цвет
#define DlgIndexColorR		200    // Хранит данные о цвете R
#define DlgIndexColorG		201    // Хранит данные о цвете G
#define DlgIndexColorB		202    // Хранит данные о цвете B

/* Элементы необходимые для работы с цветом */
HBRUSH brushRectangele; // Кисть. Хранит цвета в форм. RGB используется для закрашивания фигур
RECT windowRectangele;  // Хранит положение закрашиваемого прямоугольника
PAINTSTRUCT ps;         // Необходим для работы с цветом

/* Буфер памяти для обработки текстовых сообщений */
#define TextBufferSize	1024   // Размерность буфера (кол.во символов)
char Buffer[TextBufferSize];   // Буфер для чтения 
int readChars;                 // Текуше количество считанных символов

/* Переменные хранящие состояния виджетов */
HWND hStaticControl; // Виджет для вывода текста из буфера
HWND hEditControl;   // Переменная для хранения виджета

HWND hControlColorR; // Хранит текст ввода в поле R
HWND hControlColorG; // Хранит текст ввода в поле G
HWND hControlColorB; // Хранит текст ввода в поле B

OPENFILENAMEA ofn;   // Хранит имя файла для импорта
char pathFile[256];  // Хранить путь к файлу

/* Прототипы процедцр и функций */
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp); // Прототип процедуры
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Proctdure); // Прототип класса создания нового окна 

void MainWndAddMenus(HWND hWnd);		// Функция создания меню
void MainWndAddWidgets(HWND hWnd);		// Функция создания виджетов (кнопка, лейбл, поле ввода)
void SetOpenFaileParams(HWND hWnd);     // Функцция конструктор диалогового окна проводника
void SaveData(LPCSTR path);				// Функция записи данных в файлик
void LoadData(LPCSTR path);				// Функция чтения данных из файлика