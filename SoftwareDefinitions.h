#pragma once

/* ������� ��� ������ ���� */
#define OnExitSoftware		1	// ���������� ������ ���������
#define OnButtonClear		2	// ������� ���� �����
#define OnButtonRead		3   // ���������� ���� �����
#define OnSaveFile			4   // ��������� ���������� ������ � ����
#define OnLoadFile			5   // ��������� �� ����� � ������� � ���� ����� 
#define ShowInstructions	6   // ������� � ���� ����� ����������
#define ShowInfo			7   // ������� � ���� ����� �������
#define FileExport			8	// �������������� ������� ���� ����� � ��������� ����
#define FileImport			9	// ������������� ���� � ������� � ���� �����

/* ������� ��� ������ � ������ */
#define OnButtonClearColor	10     // �������� ���� ����� ������ RGB
#define OnButtonSetColor	11     // ���������� ����� ����
#define DlgIndexColorR		200    // ������ ������ � ����� R
#define DlgIndexColorG		201    // ������ ������ � ����� G
#define DlgIndexColorB		202    // ������ ������ � ����� B

/* �������� ����������� ��� ������ � ������ */
HBRUSH brushRectangele; // �����. ������ ����� � ����. RGB ������������ ��� ������������ �����
RECT windowRectangele;  // ������ ��������� �������������� ��������������
PAINTSTRUCT ps;         // ��������� ��� ������ � ������

/* ����� ������ ��� ��������� ��������� ��������� */
#define TextBufferSize	1024   // ����������� ������ (���.�� ��������)
char Buffer[TextBufferSize];   // ����� ��� ������ 
int readChars;                 // ������ ���������� ��������� ��������

/* ���������� �������� ��������� �������� */
HWND hStaticControl; // ������ ��� ������ ������ �� ������
HWND hEditControl;   // ���������� ��� �������� �������

HWND hControlColorR; // ������ ����� ����� � ���� R
HWND hControlColorG; // ������ ����� ����� � ���� G
HWND hControlColorB; // ������ ����� ����� � ���� B

OPENFILENAMEA ofn;   // ������ ��� ����� ��� �������
char pathFile[256];  // ������� ���� � �����

/* ��������� �������� � ������� */
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp); // �������� ���������
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Proctdure); // �������� ������ �������� ������ ���� 

void MainWndAddMenus(HWND hWnd);		// ������� �������� ����
void MainWndAddWidgets(HWND hWnd);		// ������� �������� �������� (������, �����, ���� �����)
void SetOpenFaileParams(HWND hWnd);     // �������� ����������� ����������� ���� ����������
void SaveData(LPCSTR path);				// ������� ������ ������ � ������
void LoadData(LPCSTR path);				// ������� ������ ������ �� �������