#pragma once
#include "TEDModel.h"
#include "TEDView.h"

/*!
\brief ����� ��� �������������� � ������� � ������������
*/
class TEDController
{
private:
	TEDModel *model;
	TEDView *view;
	int cursor;
public:
	//! ����� ��������� ����������� ������������ �������
	enum Direction
	{
		//! ���������, ��� ������ ������������� �����
		LEFT,

		//! ���������, ��� ������ ������������� �����
		UP,

		//! ���������, ��� ������ ������������� ������
		RIGHT,

		//! ���������, ��� ������ ������������� ����
		DOWN
	};

	//! ����� �������������� ������
	enum Key
	{
		//! ���������, ��� �������������� ������ HOME
		HOME,

		//! ���������, ��� �������������� ������ END
		END,

		//! ���������, ��� �������������� ������ BACKSPASE
		BACKSPASE,

		//! ���������, ��� �������������� ������ DEL
		DEL
	};

	/*!
	����������� ����������� ������.
	*/
	TEDController();

	/*!
	����������� ���������� ������.
	*/
	~TEDController();

	/*!
	����������� ������� ������ �������. ��������� ������ � ����� � �������������� ������ � ������.
	\param[out] hwnd ������������� ����.
	\param[out] wParam ������� ������.
	*/
	void handleInsertSymbol(HWND hwnd, WCHAR wParam);

	/*!
	������������� ������.
	\param[out] hwnd ������������� ����.
	*/
	void windowUpdate(HWND hwnd);

	/*!
	����� ���������� �������� ��� ������� �������.
	\param[out] hwnd ������������� ����.
	*/
	void cursorTimer(HWND hwnd);

	/*!
	����������� ������� �������. ����������� ������ � �������������� ������.
	\param[out] direction ����������� ���� ������������� ������.
	\param[out] hwnd ������������� ����.
	*/
	void moveCursor(Direction direction, HWND hwnd);

	/*!
	����������� ������� ������. ����������� ������ � �������������� ������.
	\param[out] key �������������� ������.
	\param[out] hwnd ������������� ����.
	*/
	void handleKey(Key key, HWND hwnd);

	/*!
	����������� ������� ������ ����. ����������� ������ � �������������� ������.
	\param[out] x �-����������.
	\param[out] y Y-����������.
	\param[out] hwnd ������������� ����.
	*/
	void handleMouseClick(int x, int y, HWND hwnd);
};

