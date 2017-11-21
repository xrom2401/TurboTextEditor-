#pragma once
/*!
\brief ����� ��� �������������� � ������� ������
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
	����������� ����������� ������.
	*/
	TEDModel();

	/*!
	����������� ���������� ������.
	*/
	~TEDModel();

	/*!
	��������� ������ � ����� ������.
	\param[out] symbol ����������� ������.
	*/
	void insertSymbol(WCHAR symbol);

	/*!
	������� ������ �� ������ ������.
	*/
	void deleteSymbol();

	/*!
	�������� ���������� �������� � ������ ������.
	\return ���������� �������� � ������ ������.
	*/
	int getSymbolCount();

	/*!
	�������� ������ �� ������ ������ �� �������.
	\param[out] i ������ �������.
	\return ������ �� ������ ������.
	*/
	WCHAR getSymbolFromTextBuffer(int i);

	/*!
	�������� ������� ������� �������.
	\return ������� ������� �������.
	*/
	int getIndexBuffer();

	/*!
	���������� ������� ������� �������.
	*/
	void setIndexBuffer(int index);
};

