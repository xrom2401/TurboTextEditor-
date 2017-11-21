#pragma once
/*!
\brief Класс для взаимодействия с буфером текста
*/
class TEDModel
{
private:
	int textBufferCount;
	WCHAR textBuffer[4096];
	int indexBuffer;
	int symbolCount;
public:
	/*!
	Стандартный конструктор класса.
	*/
	TEDModel();

	/*!
	Стандартный деструктор класса.
	*/
	~TEDModel();

	/*!
	Вставляет символ в буфер текста.
	\param[out] symbol Вставляемый символ.
	*/
	void insertSymbol(WCHAR symbol);

	/*!
	Удаляет символ из буфера текста.
	*/
	void deleteSymbol();

	/*!
	Получить количество символов в буфере текста.
	\return Количество символов в буфере текста.
	*/
	int getSymbolCount();

	/*!
	Получить символ из буфере текста по индексу.
	\param[out] i Индекс символа.
	\return Символ из буфера текста.
	*/
	WCHAR getSymbolFromTextBuffer(int i);

	/*!
	Получить текущую позицию индекса.
	\return Текущая позиция индекса.
	*/
	int getIndexBuffer();

	/*!
	Установить текущую позицию индекса.
	*/
	void setIndexBuffer(int index);
};

