#include "stdafx.h"
#include "TEDModel.h"


TEDModel::TEDModel()
{
	this->symbolCount = 0;
	this->indexBuffer = 0;
	this->textBufferCount = 4096;
	for (int i = 0; i < textBufferCount; i++)
	{
		this->textBuffer[i] = NULL;
	}
}


TEDModel::~TEDModel()
{
}

void TEDModel::insertSymbol(WCHAR symbol)
{
	if (indexBuffer == symbolCount)
	{
		this->textBuffer[indexBuffer] = symbol;
		++indexBuffer;
		++symbolCount;
	}
	else
	{
		for (int i = symbolCount + 1; i > indexBuffer; i--)
		{
			this->textBuffer[i] = this->textBuffer[i - 1];
		}
		this->textBuffer[indexBuffer] = symbol;
		++indexBuffer;
		++symbolCount;
	}
}

void TEDModel::deleteSymbol()
{
	for (int i = indexBuffer; i < symbolCount - 1; i++)
	{
		this->textBuffer[i] = textBuffer[i + 1];
	}
	this->textBuffer[symbolCount - 1] = NULL;
	symbolCount--;
}

int TEDModel::getSymbolCount()
{
	return symbolCount;
}

WCHAR TEDModel::getSymbolFromTextBuffer(int i)
{
	return this->textBuffer[i];
}

int TEDModel::getIndexBuffer()
{
	return this->indexBuffer;
}

void TEDModel::setIndexBuffer(int index)
{
	this->indexBuffer = index;
}
