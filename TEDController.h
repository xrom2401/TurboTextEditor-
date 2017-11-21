#pragma once
#include "TEDModel.h"
#include "TEDView.h"

/*!
\brief Класс для взаимодействия с Моделью и Отображением
*/
class TEDController
{
private:
	TEDModel *model;
	TEDView *view;
	int cursor;
public:
	//! Набор возможных направлений передвижения курсора
	enum Direction
	{
		//! Указывает, что курсор передвигается влево
		LEFT,

		//! Указывает, что курсор передвигается вверх
		UP,

		//! Указывает, что курсор передвигается вправо
		RIGHT,

		//! Указывает, что курсор передвигается вниз
		DOWN
	};

	//! Набор обрабатываемых кнопок
	enum Key
	{
		//! Указывает, что обрабатывается кнопка HOME
		HOME,

		//! Указывает, что обрабатывается кнопка END
		END,

		//! Указывает, что обрабатывается кнопка BACKSPASE
		BACKSPASE,

		//! Указывает, что обрабатывается кнопка DEL
		DEL
	};

	/*!
	Стандартный конструктор класса.
	*/
	TEDController();

	/*!
	Стандартный деструктор класса.
	*/
	~TEDController();

	/*!
	Отлавливает нажатие кнопки символа. Вставляет символ в буфер и перерисовывает курсор и модель.
	\param[out] hwnd Идентификатор окна.
	\param[out] wParam Нажатая кнопка.
	*/
	void handleInsertSymbol(HWND hwnd, WCHAR wParam);

	/*!
	Перерисовывет модель.
	\param[out] hwnd Идентификатор окна.
	*/
	void windowUpdate(HWND hwnd);

	/*!
	Метод вызываемый таймером для мигания курсора.
	\param[out] hwnd Идентификатор окна.
	*/
	void cursorTimer(HWND hwnd);

	/*!
	Отлавливает нажатие стрелок. Передвигает курсор и перерисовывает модель.
	\param[out] direction Направление куда передвигается курсор.
	\param[out] hwnd Идентификатор окна.
	*/
	void moveCursor(Direction direction, HWND hwnd);

	/*!
	Отлавливает нажатие кнопок. Передвигает курсор и перерисовывает модель.
	\param[out] key Обрабатываемая кнопка.
	\param[out] hwnd Идентификатор окна.
	*/
	void handleKey(Key key, HWND hwnd);

	/*!
	Отлавливает нажатие кнопок мыши. Передвигает курсор и перерисовывает модель.
	\param[out] x Х-координата.
	\param[out] y Y-координата.
	\param[out] hwnd Идентификатор окна.
	*/
	void handleMouseClick(int x, int y, HWND hwnd);
};

