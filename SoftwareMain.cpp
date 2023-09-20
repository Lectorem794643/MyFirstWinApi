#include <Windows.h>
#include <string>
#include "SoftwareDefinitions.h"   // Файл прототипов функций и определений
#include "resource.h"              // Хедор ресурсов (нужен для icon)

/* Точка входа в наше приложение */
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	// Класс нашего приложения                             
	WNDCLASS SoftwareMainCLass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", SoftwareMainProcedure);

	// Регистрируем наш класс, если не получитлось вернет -1
	if (!RegisterClassW(&SoftwareMainCLass)) { return -1; }
	MSG SoftwareMainMessage = { 0 }; // Сообщение, изначально пустое

	// Создаем окно:
	CreateWindow(L"MainWndClass", L"First С++ Window", WS_OVERLAPPEDWINDOW &~ WS_THICKFRAME | WS_VISIBLE, 100, 100, 500, 338, NULL, NULL, NULL, NULL);

	// Главный цимкл программы, работает пока не пришло сообщение о закррытии окна 
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

/* Функция создания нового окна (конструктор) */
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Proctdure) {
	WNDCLASS NWC = { 0 }; // Экземпляр пустого win class
	NWC.hbrBackground = BGColor;   // Back Ground Color
	NWC.hCursor = Cursor;          // Курсор
	NWC.hInstance = hInst;         // ?
	NWC.hIcon = Icon;              // Иконка 
	NWC.lpszClassName = Name;      // Имя окна
	NWC.lpfnWndProc = Proctdure;   // Процедура win

	return NWC; // NWC - new window class
}

/* Создаем свой обработчик процедур winows */
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	/* Через Switch расссматриваем код сообщений от окна */
	switch (msg) {
	case WM_COMMAND:
		/* В подсвитче обработка самописных кодов команд (см. SoftwareDefinitions.h строка 3 - 19) */
		switch (wp) {
			// Вывод инструкции в окно ввода текста
		case ShowInstructions: LoadData("Instructions.txt"); break;

			// Вывод справки о создателе в окно ввода текста
		case ShowInfo: LoadData("Info.txt"); break;

			// Очистка поля ввода
		case OnButtonClear:
			SetWindowTextA(hStaticControl, "STATUS: input cleared");
			SetWindowTextA(hEditControl, "");
			break; 

			// Очистка поля ввода COLOR
		case OnButtonClearColor:
			/* Установка букв-подсказок */
			SetWindowTextA(hControlColorR, "R");
			SetWindowTextA(hControlColorG, "G");
			SetWindowTextA(hControlColorB, "B");

			/* Установка цвета по умолчанию (белый) */
			brushRectangele = CreateSolidBrush(RGB(255, 255, 255));
			RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
			break;

			// Установка COLOR
		case OnButtonSetColor:
			brushRectangele = CreateSolidBrush(
				RGB(GetDlgItemInt(hWnd, DlgIndexColorR, FALSE, FALSE),
				    GetDlgItemInt(hWnd, DlgIndexColorG, FALSE, FALSE), 
				    GetDlgItemInt(hWnd, DlgIndexColorB, FALSE, FALSE)));

			RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
			break;

			// Чтение из поля ввода
		case OnButtonRead:
			readChars = GetWindowTextA(hEditControl, Buffer, TextBufferSize); // Попутно запоминаем кол-во считанных сиволоов в readChars
			SetWindowTextA(hStaticControl, ("Symbols read: " + std::to_string(readChars)).c_str()); // Выводим кол-во символов в веденном тексте
			break;

			// Сохранение буфера в файл 
		case OnSaveFile: SaveData("output.txt"); break;

			// Чтение из файла в буфер
		case OnLoadFile: LoadData("output.txt"); break;

			// Экспорт файла
		case FileExport: if (GetSaveFileNameA(&ofn)) { SaveData(pathFile); }; break;

			// Импорт файла
		case FileImport: if (GetSaveFileNameA(&ofn)) { LoadData(pathFile); }; break;

			// Кнопка выхода (Вариант в выпадающем меню). Завершает цикл программы
		case OnExitSoftware: PostQuitMessage(0); break;

			// Сработает при неизвестном коде операции
		default: break;
		}
		break;

		// Срабатывает когда нужно обновить цвета прямоугольника
	case WM_PAINT:
		BeginPaint(hWnd, &ps);								  // Начало изменений
		FillRect(ps.hdc, &windowRectangele, brushRectangele); // Команда перекрасить окно
		EndPaint(hWnd, &ps);                                  // Конец изменений
		break;

		// Вызывается при создании окна 
	case WM_CREATE:
		SetOpenFaileParams(hWnd);	// Модуль открытия внешних файлов
		MainWndAddMenus(hWnd);		// Добавление меню в окно
		MainWndAddWidgets(hWnd);	// Добавление виджетов
		break;

		// Вызывается при закрытии окна. Завершает цикл программы
	case WM_DESTROY: PostQuitMessage(0); break;

		// Срабатывает в случае ошибки
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

/* Реализация функции добавления меню в окно */
void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();       // Создали корень меню  (или "строка основынх меню")		 Уровень вложенности: 0
	HMENU SubMenu_File = CreateMenu();   // Общее подменю        (работа с файлами)					 Уровень вложенности: 1
	HMENU SubMenu_Help = CreateMenu();   // Подменю	подсказок    (вывод инструкции и справки)		 Уровень вложенности: 1
	HMENU SubActionMenu_File = CreateMenu();  // Второе подменю       (работа с файлами, продолжение)     Уровень вложенности: 2

	/* Добавляем разделы меню с помощью функтции - конструткора(встроенная) */
	AppendMenu(SubActionMenu_File, MF_STRING, OnSaveFile, L"Save");					// Загрузить файл
	AppendMenu(SubActionMenu_File, MF_STRING, OnLoadFile, L"Load");					// Сохранить файл
	AppendMenu(SubMenu_File, MF_POPUP, (UINT_PTR)SubActionMenu_File, L"File S/L");  // Создали << Второе подменю >>
	AppendMenu(SubMenu_File, MF_POPUP, FileExport , L"File Export");				// Экспорт файла
	AppendMenu(SubMenu_File, MF_POPUP, FileImport, L"File Import");					// Импорт файла
	AppendMenu(SubMenu_Help, MF_STRING, ShowInfo, L"Info");							// Кнопка вызова информации
	AppendMenu(SubMenu_Help, MF_STRING, ShowInstructions, L"Instructions");			// Кнопка вызова инструкции
	AppendMenu(SubMenu_File, MF_SEPARATOR, NULL, NULL);								// Разделитель меню
	AppendMenu(SubMenu_File, MF_STRING, OnExitSoftware, L"Exit");					// Кнопка выхода
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu_File, L"Menu");				// Корневая ветка меню
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu_Help, L"Help");				// Корневая ветка меню

	SetMenu(hWnd, RootMenu); // Установка меню в окно
}

/* Реализация функции добавления виджета в окно */
void MainWndAddWidgets(HWND hWnd) {
	// Аналог Лейбла, статический текст
	hStaticControl = CreateWindow(L"static", L"STATUS: Hello Window!", WS_VISIBLE | WS_CHILD, 250, 5, 250, 20, hWnd, NULL, NULL, NULL);

	// Поле ввода текста пользователем
	hEditControl = CreateWindow(L"edit", L"Это поле ввода пользователя!", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 5, 40, 475, 145, hWnd, NULL, NULL, NULL);

	// Прямоугольник цвета (Его координаты)
	windowRectangele = { 465, 273, 95, 195 };

	// Три поля для RGB
	hControlColorR = CreateWindowA("edit", "R", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER,  5, 195, 25, 15, hWnd, (HMENU)DlgIndexColorR, NULL, NULL);
	hControlColorG = CreateWindowA("edit", "G", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 35, 195, 25, 15, hWnd, (HMENU)DlgIndexColorG, NULL, NULL);
	hControlColorB = CreateWindowA("edit", "B", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 65, 195, 25, 15, hWnd, (HMENU)DlgIndexColorB, NULL, NULL);

	// Кнопки для сброса и установки Цвета
	CreateWindow(L"button", L"Clear", WS_VISIBLE | WS_CHILD, 5, 215, 85, 27, hWnd, (HMENU)OnButtonClearColor, NULL, NULL);
	CreateWindow(L"button",   L"Set", WS_VISIBLE | WS_CHILD, 5, 247, 85, 27, hWnd, (HMENU)OnButtonSetColor,   NULL, NULL);

	// Кнопки
	CreateWindow(L"button", L"Clear", WS_VISIBLE | WS_CHILD, 5,  5, 80, 30, hWnd, (HMENU)OnButtonClear, NULL, NULL); // Кнопка очистки 
	CreateWindow(L"button", L"Enter", WS_VISIBLE | WS_CHILD, 90, 5, 80, 30, hWnd, (HMENU)OnButtonRead,  NULL, NULL); // Кнопка ввода
}

void SaveData(LPCSTR path) {
	// Создаем или открываем файл
	HANDLE FileToSave = CreateFileA(
		path, // Путь к файлу
		GENERIC_WRITE, // Тип доступа - только запись
		0,
		NULL,
		CREATE_ALWAYS, // Если файла нет, он создаст пустой, если есть то перезапишет как пустой 
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	int saveLenth = GetWindowTextLength(hEditControl) + 1; // Узнаем какой длинны файл который мы будем записывать
	char* data = new char[saveLenth]; // Создаем буфер символов

	saveLenth = GetWindowTextA(hEditControl, data, saveLenth); // Заполняем буфер символов

	DWORD bytesIterated; // Хранит данные о том сколько символов было заисано в файл

	// Выполняем запись в файл с помощью втроенной функции
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	CloseHandle(FileToSave); // Закрываем файл после записи
	delete[] data; // Удаляем буфер
}

void LoadData(LPCSTR path) {
	// Открываем файл
	HANDLE FileToload = CreateFileA(
		path, // Путь к файлу
		GENERIC_READ, // Тип доступа - только чтение 
		0,
		NULL,
		OPEN_EXISTING, // Открываем файл если он существует
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated; // Хранит кол-во сичтанных символов

	// Очищаем буфер перед считыванием в него файла
	int i = 0; while (Buffer[i] != NULL && i != 1023) { Buffer[i] = NULL; ++i; }

	// Выполняем считывание из файла с помощью втроенной функции
	ReadFile(FileToload, Buffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hEditControl, Buffer); // Выводим текст в виджет
	CloseHandle(FileToload); // Закрываем файл после чтения
}

void SetOpenFaileParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = pathFile;
	ofn.nMaxFile = sizeof(pathFile);
	ofn.lpstrFilter = "*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}
