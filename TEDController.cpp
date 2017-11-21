#include "stdafx.h"
#include "TEDController.h"


TEDController::TEDController()
{
	this->model = new TEDModel();
	this->view = new TEDView(model);
}


TEDController::~TEDController()
{
}

void TEDController::handleInsertSymbol(HWND hwnd, WCHAR wParam)
{
	view->deleteCursor(hwnd);
	view->clearScreen(hwnd);
	model->insertSymbol(wParam);
	view->drawModel(hwnd);
	view->drawCursor(hwnd);
}

void TEDController::windowUpdate(HWND hwnd)
{
	view->deleteCursor(hwnd);
	view->clearScreen(hwnd);
	view->drawModel(hwnd);
	view->drawCursor(hwnd);
}

void TEDController::cursorTimer(HWND hwnd)
{
	view->flashCursor(hwnd);
}

void TEDController::moveCursor(Direction direction, HWND hwnd)
{
	if (direction == this->RIGHT) {
		view->deleteCursor(hwnd);
		view->cursorRight();
		view->drawCursor(hwnd);
		return;
	}

	if (direction == this->LEFT) {
		view->deleteCursor(hwnd);
		view->cursorLeft();
		view->drawCursor(hwnd);
		return;
	}

	if (direction == this->UP)
	{
		view->deleteCursor(hwnd);
		view->cursorUp();
		view->drawCursor(hwnd);
		return;
	}

	if (direction == this->DOWN)
	{
		view->deleteCursor(hwnd);
		view->cursorDown();
		view->drawCursor(hwnd);
		return;
	}
}

void TEDController::handleKey(Key key, HWND hwnd)
{
	if (key == this->HOME)
	{
		view->deleteCursor(hwnd);
		view->setCursorToHome();
		view->drawCursor(hwnd);
		return;
	}
	if (key == this->END)
	{
		view->deleteCursor(hwnd);
		view->setCursorToEnd();
		view->drawCursor(hwnd);
		return;
	}

	if (key == this->DEL)
	{
		if (model->getIndexBuffer() >= model->getSymbolCount())
		{
			return;
		}
		view->deleteCursor(hwnd);
		view->clearScreen(hwnd);
		model->deleteSymbol();
		view->drawModel(hwnd);
		view->drawCursor(hwnd);
		return;
	}

	if (key == this->BACKSPASE)
	{
		if (model->getIndexBuffer() == 0)
		{
			return;
		}
		view->deleteCursor(hwnd);
		view->clearScreen(hwnd);
		view->cursorLeft();
		model->deleteSymbol();
		view->drawModel(hwnd);
		view->drawCursor(hwnd);
		return;

	}
}

void TEDController::handleMouseClick(int x, int y, HWND hwnd)
{
	view->deleteCursor(hwnd);
	view->setCursorFromCoordinates(x, y);
	view->drawCursor(hwnd);
}


