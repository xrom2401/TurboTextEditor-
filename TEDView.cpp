#include "stdafx.h"
#include "TEDView.h"


TEDView::TEDView(TEDModel* model)
{
	this->symbolRect = { 5, 5, 25, 25 };
	this->model = model;
	this->coordinateBuffer[0] = symbolRect;
	this->colorText = colorText = RGB(255, 255, 255);
	this->isCursorVisible = true;
}

void TEDView::drawModel(HWND hwnd)
{
	this->hdc = GetDC(hwnd);
	GetClientRect(hwnd, &clientRect);
	int length = model->getSymbolCount();
	WCHAR symbol;
	clearScreen(hwnd);
	clearCoordinates(length);
	this->symbolRect = { 5, 5, 25, 25 };
	this->coordinateBuffer[0] = symbolRect;
	for (int i = 0; i < length; i++)
	{
		symbol = model->getSymbolFromTextBuffer(i);
		if (symbol == (char)13)
		{
			symbolRect.left = 5;
			symbolRect.right = 25;
			symbolRect.bottom += 20;
			symbolRect.top += 20;
			this->coordinateBuffer[i + 1] = symbolRect;
			continue;
		}
		FillRect(hdc, &symbolRect, (HBRUSH)(COLOR_WINDOW + 1));
		DrawText(hdc, (LPWSTR)(&symbol), 1, &symbolRect, DT_CENTER);
		symbolRect.left += 20;
		symbolRect.right += 20;
		if (symbolRect.right >= clientRect.right)
		{
			symbolRect.left = 5;
			symbolRect.right = 25;
			symbolRect.bottom += 20;
			symbolRect.top += 20;
		}
		this->coordinateBuffer[i + 1] = symbolRect;
	}
	ReleaseDC(hwnd, hdc);
}

void TEDView::clearCoordinates(int length) {
	for (int i = 0; i < length; i++)
	{
		coordinateBuffer[i] = { 0,0,0,0 };
	}
}

void TEDView::setCursorToHome()
{
	int symbolCount = model->getSymbolCount();
	cursor = model->getIndexBuffer();
	while (coordinateBuffer[cursor].left != 5 && coordinateBuffer[cursor].right != 25 && cursor != symbolCount + 1)
	{
		--cursor;
	}
	model->setIndexBuffer(cursor);
}

void TEDView::setCursorToEnd()
{
	cursor = model->getIndexBuffer();
	int symbolCount = model->getSymbolCount();
	RECT newCursorRect = coordinateBuffer[cursor];
	newCursorRect.bottom += 20;
	newCursorRect.top += 20;
	while (coordinateBuffer[cursor].bottom != newCursorRect.bottom && cursor != symbolCount + 1)
	{
		++cursor;
	}
	--cursor;
	model->setIndexBuffer(cursor);
}

void TEDView::setCursorFromCoordinates(int x, int y)
{
	cursor = 0;
	int symbolCount = model->getSymbolCount();
	RECT newCursorRect;
	newCursorRect.right = 20 * x + 25;
	newCursorRect.left = 20 * x + 5;
	newCursorRect.bottom = 20 * y + 25;
	newCursorRect.top = 20 * y + 5;
	while (cursor != symbolCount)
	{
		if (newCursorRect.top == coordinateBuffer[cursor].top && newCursorRect.bottom == coordinateBuffer[cursor].bottom)
		{
			break;
		}
		++cursor;
	}
	while (cursor != symbolCount)
	{
		if (newCursorRect.right == coordinateBuffer[cursor].right && newCursorRect.left == coordinateBuffer[cursor].left)
		{
			model->setIndexBuffer(cursor);
			return;
		}
		if (newCursorRect.top < coordinateBuffer[cursor].top && newCursorRect.bottom < coordinateBuffer[cursor].bottom)
		{
			--cursor;
			model->setIndexBuffer(cursor);
			return;
		}
		++cursor;
	}
	model->setIndexBuffer(cursor);
}

void TEDView::clearScreen(HWND hwnd)
{
	int length = model->getSymbolCount();
	for (int i = 0; i < length + 1; i++)
	{
		FillRect(hdc, &coordinateBuffer[i], (HBRUSH)(COLOR_WINDOW + 1));
	}
}

void TEDView::drawCursor(HWND hwnd)
{
	this->hdc = GetDC(hwnd);
	cursor = model->getIndexBuffer();
	MoveToEx(hdc, coordinateBuffer[cursor].left, coordinateBuffer[cursor].top, NULL);
	LineTo(hdc, coordinateBuffer[cursor].left, coordinateBuffer[cursor].bottom);
	ReleaseDC(hwnd, hdc);
}

void TEDView::deleteCursor(HWND hwnd)
{
	this->hdc = GetDC(hwnd);
	cursor = model->getIndexBuffer();
	this->symbolRect = { coordinateBuffer[cursor].left,coordinateBuffer[cursor].top,coordinateBuffer[cursor].left + 1,coordinateBuffer[cursor].bottom };
	FillRect(hdc, &symbolRect, (HBRUSH)(COLOR_WINDOW + 1));
	ReleaseDC(hwnd, hdc);
}

void TEDView::flashCursor(HWND hwnd)
{
	this->hdc = GetDC(hwnd);
	deleteCursor(hwnd);
	if (isCursorVisible) {
		drawCursor(hwnd);
	}
	isCursorVisible = !isCursorVisible;
	ReleaseDC(hwnd, hdc);
}

void TEDView::cursorRight()
{
	cursor = model->getIndexBuffer();
	if (coordinateBuffer[cursor + 1].top == 0 && coordinateBuffer[cursor + 1].bottom == 0 && coordinateBuffer[cursor + 1].left == 0 && coordinateBuffer[cursor + 1].right == 0)
	{
		return;
	}
	model->setIndexBuffer(++cursor);
}

void TEDView::cursorLeft()
{
	cursor = model->getIndexBuffer();
	if (cursor == 0)
	{
		return;
	}
	model->setIndexBuffer(--cursor);
}

void TEDView::cursorUp()
{
	cursor = model->getIndexBuffer();
	int symbolCount = model->getSymbolCount();
	RECT newCursorRect = coordinateBuffer[cursor];
	newCursorRect.bottom -= 20;
	newCursorRect.top -= 20;
	if (newCursorRect.top < 5) {
		return;
	}
	while (newCursorRect.top != coordinateBuffer[cursor].top && cursor != symbolCount + 1)
	{
		--cursor;
	}
	if (coordinateBuffer[cursor].right < newCursorRect.right)
	{
		model->setIndexBuffer(cursor);
		return;
	}
	while (!EqualRect(&newCursorRect, &coordinateBuffer[cursor]) && cursor != symbolCount + 1)
	{
		--cursor;
	}
	model->setIndexBuffer(cursor);
}

void TEDView::cursorDown()
{
	cursor = model->getIndexBuffer();
	int symbolCount = model->getSymbolCount();
	RECT newCursorRect = coordinateBuffer[cursor];
	newCursorRect.bottom += 20;
	newCursorRect.top += 20;
	if (newCursorRect.top > coordinateBuffer[symbolCount].top)
	{
		return;
	}
	while ((!EqualRect(&newCursorRect, &coordinateBuffer[cursor])) && coordinateBuffer[cursor].top != newCursorRect.top + 20 && cursor != symbolCount)
	{
		++cursor;
	}
	if (EqualRect(&newCursorRect, &coordinateBuffer[cursor]))
	{
		model->setIndexBuffer(cursor);
		return;
	}
	model->setIndexBuffer(--cursor);
}
