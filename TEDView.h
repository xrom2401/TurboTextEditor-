#pragma once
#include "TEDModel.h"

/*!
\brief ����� ��� ����������� ������ ������ �� ������
*/

class TEDView
{
private:
	RECT coordinateBuffer[4097];
	RECT symbolRect;
	RECT clientRect;
	int cursor;
	TEDModel* model;
	HDC hdc;
	bool isCursorVisible;
public:

	//! ���������� �������� ���� ������.
	COLORREF colorText;

	/*!
	����������� ����������� ������ �� ������.
	\param[out] model ������ �� ������.
	*/
	TEDView(TEDModel* model);

	/*!
	����������� ����������� ������.
	*/
	TEDView();

	/*!
	����������� ���������� ������.
	*/
	~TEDView();

	/*!
	������������ ������.
	\param[out] hwnd ������������� ����
	*/
	void drawModel(HWND hwnd);

	/*!
	������� �����.
	\param[out] hwnd ������������� ����
	*/
	void clearScreen(HWND hwnd);

	/*!
	������ ������.
	\param[out] hwnd ������������� ����
	*/
	void drawCursor(HWND hwnd);

	/*!
	������ ������.
	\param[out] hwnd ������������� ����
	*/
	void deleteCursor(HWND hwnd);

	/*!
	����� ����������� ��� ������� �������.
	\param[out] hwnd ������������� ����
	*/
	void flashCursor(HWND hwnd);

	/*!
	����������� ������ ������.
	*/
	void cursorRight();

	/*!
	����������� ������ �����.
	*/
	void cursorLeft();

	/*!
	����������� ������ �����.
	*/
	void cursorUp();

	/*!
	����������� ������ ����.
	*/
	void cursorDown();

	/*!
	��������� ������ ���������.
	\param[out] length ���������� ��������� � ������ ������
	*/
	void clearCoordinates(int length);

	/*!
	����������� ������ � ������ ������.
	*/
	void setCursorToHome();

	/*!
	����������� ������ � ����� ������.
	*/
	void setCursorToEnd();

	/*!
	����������� ������ �� �����������.
	\param[out] x �-����������.
	\param[out] y Y-����������.
	*/
	void setCursorFromCoordinates(int x, int y);
};

