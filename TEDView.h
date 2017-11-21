#pragma once
#include "TEDModel.h"

/*!
\brief Класс для отображения буфера текста на экране
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

	//! Переменная хранящая цвет текста.
	COLORREF colorText;

	/*!
	Конструктор принимающий ссылку на модель.
	\param[out] model Ссылка на модель.
	*/
	TEDView(TEDModel* model);

	/*!
	Стандартный конструктор класса.
	*/
	TEDView();

	/*!
	Стандартный деструктор класса.
	*/
	~TEDView();

	/*!
	Отрисовывает модель.
	\param[out] hwnd Идентификатор окна
	*/
	void drawModel(HWND hwnd);

	/*!
	Очищает экран.
	\param[out] hwnd Идентификатор окна
	*/
	void clearScreen(HWND hwnd);

	/*!
	Рисует курсор.
	\param[out] hwnd Идентификатор окна
	*/
	void drawCursor(HWND hwnd);

	/*!
	Удалет курсор.
	\param[out] hwnd Идентификатор окна
	*/
	void deleteCursor(HWND hwnd);

	/*!
	Метод необходимый для мигания курсора.
	\param[out] hwnd Идентификатор окна
	*/
	void flashCursor(HWND hwnd);

	/*!
	Передвинуть курсор вправо.
	*/
	void cursorRight();

	/*!
	Передвинуть курсор влево.
	*/
	void cursorLeft();

	/*!
	Передвинуть курсор вверх.
	*/
	void cursorUp();

	/*!
	Передвинуть курсор вниз.
	*/
	void cursorDown();

	/*!
	Отчистить массив координат.
	\param[out] length Количество элементов в буфере текста
	*/
	void clearCoordinates(int length);

	/*!
	Передвинуть курсор в начало строки.
	*/
	void setCursorToHome();

	/*!
	Передвинуть курсор в конец строки.
	*/
	void setCursorToEnd();

	/*!
	Передвинуть курсор по координатам.
	\param[out] x Х-координата.
	\param[out] y Y-координата.
	*/
	void setCursorFromCoordinates(int x, int y);
};

