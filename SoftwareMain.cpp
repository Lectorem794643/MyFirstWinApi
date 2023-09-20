#include <Windows.h>
#include <string>
#include "SoftwareDefinitions.h"   // ���� ���������� ������� � �����������
#include "resource.h"              // ����� �������� (����� ��� icon)

/* ����� ����� � ���� ���������� */
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	// ����� ������ ����������                             
	WNDCLASS SoftwareMainCLass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", SoftwareMainProcedure);

	// ������������ ��� �����, ���� �� ����������� ������ -1
	if (!RegisterClassW(&SoftwareMainCLass)) { return -1; }
	MSG SoftwareMainMessage = { 0 }; // ���������, ���������� ������

	// ������� ����:
	CreateWindow(L"MainWndClass", L"First �++ Window", WS_OVERLAPPEDWINDOW &~ WS_THICKFRAME | WS_VISIBLE, 100, 100, 500, 338, NULL, NULL, NULL, NULL);

	// ������� ����� ���������, �������� ���� �� ������ ��������� � ��������� ���� 
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

/* ������� �������� ������ ���� (�����������) */
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Proctdure) {
	WNDCLASS NWC = { 0 }; // ��������� ������� win class
	NWC.hbrBackground = BGColor;   // Back Ground Color
	NWC.hCursor = Cursor;          // ������
	NWC.hInstance = hInst;         // ?
	NWC.hIcon = Icon;              // ������ 
	NWC.lpszClassName = Name;      // ��� ����
	NWC.lpfnWndProc = Proctdure;   // ��������� win

	return NWC; // NWC - new window class
}

/* ������� ���� ���������� �������� winows */
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	/* ����� Switch �������������� ��� ��������� �� ���� */
	switch (msg) {
	case WM_COMMAND:
		/* � ��������� ��������� ���������� ����� ������ (��. SoftwareDefinitions.h ������ 3 - 19) */
		switch (wp) {
			// ����� ���������� � ���� ����� ������
		case ShowInstructions: LoadData("Instructions.txt"); break;

			// ����� ������� � ��������� � ���� ����� ������
		case ShowInfo: LoadData("Info.txt"); break;

			// ������� ���� �����
		case OnButtonClear:
			SetWindowTextA(hStaticControl, "STATUS: input cleared");
			SetWindowTextA(hEditControl, "");
			break; 

			// ������� ���� ����� COLOR
		case OnButtonClearColor:
			/* ��������� ����-��������� */
			SetWindowTextA(hControlColorR, "R");
			SetWindowTextA(hControlColorG, "G");
			SetWindowTextA(hControlColorB, "B");

			/* ��������� ����� �� ��������� (�����) */
			brushRectangele = CreateSolidBrush(RGB(255, 255, 255));
			RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
			break;

			// ��������� COLOR
		case OnButtonSetColor:
			brushRectangele = CreateSolidBrush(
				RGB(GetDlgItemInt(hWnd, DlgIndexColorR, FALSE, FALSE),
				    GetDlgItemInt(hWnd, DlgIndexColorG, FALSE, FALSE), 
				    GetDlgItemInt(hWnd, DlgIndexColorB, FALSE, FALSE)));

			RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
			break;

			// ������ �� ���� �����
		case OnButtonRead:
			readChars = GetWindowTextA(hEditControl, Buffer, TextBufferSize); // ������� ���������� ���-�� ��������� �������� � readChars
			SetWindowTextA(hStaticControl, ("Symbols read: " + std::to_string(readChars)).c_str()); // ������� ���-�� �������� � �������� ������
			break;

			// ���������� ������ � ���� 
		case OnSaveFile: SaveData("output.txt"); break;

			// ������ �� ����� � �����
		case OnLoadFile: LoadData("output.txt"); break;

			// ������� �����
		case FileExport: if (GetSaveFileNameA(&ofn)) { SaveData(pathFile); }; break;

			// ������ �����
		case FileImport: if (GetSaveFileNameA(&ofn)) { LoadData(pathFile); }; break;

			// ������ ������ (������� � ���������� ����). ��������� ���� ���������
		case OnExitSoftware: PostQuitMessage(0); break;

			// ��������� ��� ����������� ���� ��������
		default: break;
		}
		break;

		// ����������� ����� ����� �������� ����� ��������������
	case WM_PAINT:
		BeginPaint(hWnd, &ps);								  // ������ ���������
		FillRect(ps.hdc, &windowRectangele, brushRectangele); // ������� ����������� ����
		EndPaint(hWnd, &ps);                                  // ����� ���������
		break;

		// ���������� ��� �������� ���� 
	case WM_CREATE:
		SetOpenFaileParams(hWnd);	// ������ �������� ������� ������
		MainWndAddMenus(hWnd);		// ���������� ���� � ����
		MainWndAddWidgets(hWnd);	// ���������� ��������
		break;

		// ���������� ��� �������� ����. ��������� ���� ���������
	case WM_DESTROY: PostQuitMessage(0); break;

		// ����������� � ������ ������
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

/* ���������� ������� ���������� ���� � ���� */
void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();       // ������� ������ ����  (��� "������ �������� ����")		 ������� �����������: 0
	HMENU SubMenu_File = CreateMenu();   // ����� �������        (������ � �������)					 ������� �����������: 1
	HMENU SubMenu_Help = CreateMenu();   // �������	���������    (����� ���������� � �������)		 ������� �����������: 1
	HMENU SubActionMenu_File = CreateMenu();  // ������ �������       (������ � �������, �����������)     ������� �����������: 2

	/* ��������� ������� ���� � ������� �������� - ������������(����������) */
	AppendMenu(SubActionMenu_File, MF_STRING, OnSaveFile, L"Save");					// ��������� ����
	AppendMenu(SubActionMenu_File, MF_STRING, OnLoadFile, L"Load");					// ��������� ����
	AppendMenu(SubMenu_File, MF_POPUP, (UINT_PTR)SubActionMenu_File, L"File S/L");  // ������� << ������ ������� >>
	AppendMenu(SubMenu_File, MF_POPUP, FileExport , L"File Export");				// ������� �����
	AppendMenu(SubMenu_File, MF_POPUP, FileImport, L"File Import");					// ������ �����
	AppendMenu(SubMenu_Help, MF_STRING, ShowInfo, L"Info");							// ������ ������ ����������
	AppendMenu(SubMenu_Help, MF_STRING, ShowInstructions, L"Instructions");			// ������ ������ ����������
	AppendMenu(SubMenu_File, MF_SEPARATOR, NULL, NULL);								// ����������� ����
	AppendMenu(SubMenu_File, MF_STRING, OnExitSoftware, L"Exit");					// ������ ������
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu_File, L"Menu");				// �������� ����� ����
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu_Help, L"Help");				// �������� ����� ����

	SetMenu(hWnd, RootMenu); // ��������� ���� � ����
}

/* ���������� ������� ���������� ������� � ���� */
void MainWndAddWidgets(HWND hWnd) {
	// ������ ������, ����������� �����
	hStaticControl = CreateWindow(L"static", L"STATUS: Hello Window!", WS_VISIBLE | WS_CHILD, 250, 5, 250, 20, hWnd, NULL, NULL, NULL);

	// ���� ����� ������ �������������
	hEditControl = CreateWindow(L"edit", L"��� ���� ����� ������������!", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 5, 40, 475, 145, hWnd, NULL, NULL, NULL);

	// ������������� ����� (��� ����������)
	windowRectangele = { 465, 273, 95, 195 };

	// ��� ���� ��� RGB
	hControlColorR = CreateWindowA("edit", "R", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER,  5, 195, 25, 15, hWnd, (HMENU)DlgIndexColorR, NULL, NULL);
	hControlColorG = CreateWindowA("edit", "G", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 35, 195, 25, 15, hWnd, (HMENU)DlgIndexColorG, NULL, NULL);
	hControlColorB = CreateWindowA("edit", "B", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 65, 195, 25, 15, hWnd, (HMENU)DlgIndexColorB, NULL, NULL);

	// ������ ��� ������ � ��������� �����
	CreateWindow(L"button", L"Clear", WS_VISIBLE | WS_CHILD, 5, 215, 85, 27, hWnd, (HMENU)OnButtonClearColor, NULL, NULL);
	CreateWindow(L"button",   L"Set", WS_VISIBLE | WS_CHILD, 5, 247, 85, 27, hWnd, (HMENU)OnButtonSetColor,   NULL, NULL);

	// ������
	CreateWindow(L"button", L"Clear", WS_VISIBLE | WS_CHILD, 5,  5, 80, 30, hWnd, (HMENU)OnButtonClear, NULL, NULL); // ������ ������� 
	CreateWindow(L"button", L"Enter", WS_VISIBLE | WS_CHILD, 90, 5, 80, 30, hWnd, (HMENU)OnButtonRead,  NULL, NULL); // ������ �����
}

void SaveData(LPCSTR path) {
	// ������� ��� ��������� ����
	HANDLE FileToSave = CreateFileA(
		path, // ���� � �����
		GENERIC_WRITE, // ��� ������� - ������ ������
		0,
		NULL,
		CREATE_ALWAYS, // ���� ����� ���, �� ������� ������, ���� ���� �� ����������� ��� ������ 
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	int saveLenth = GetWindowTextLength(hEditControl) + 1; // ������ ����� ������ ���� ������� �� ����� ����������
	char* data = new char[saveLenth]; // ������� ����� ��������

	saveLenth = GetWindowTextA(hEditControl, data, saveLenth); // ��������� ����� ��������

	DWORD bytesIterated; // ������ ������ � ��� ������� �������� ���� ������� � ����

	// ��������� ������ � ���� � ������� ��������� �������
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	CloseHandle(FileToSave); // ��������� ���� ����� ������
	delete[] data; // ������� �����
}

void LoadData(LPCSTR path) {
	// ��������� ����
	HANDLE FileToload = CreateFileA(
		path, // ���� � �����
		GENERIC_READ, // ��� ������� - ������ ������ 
		0,
		NULL,
		OPEN_EXISTING, // ��������� ���� ���� �� ����������
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated; // ������ ���-�� ��������� ��������

	// ������� ����� ����� ����������� � ���� �����
	int i = 0; while (Buffer[i] != NULL && i != 1023) { Buffer[i] = NULL; ++i; }

	// ��������� ���������� �� ����� � ������� ��������� �������
	ReadFile(FileToload, Buffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hEditControl, Buffer); // ������� ����� � ������
	CloseHandle(FileToload); // ��������� ���� ����� ������
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
