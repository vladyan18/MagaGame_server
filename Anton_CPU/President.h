#pragma once
#include "Minister.h"
class President : public Minister
{
public:
	//������� ��������
    int dismiss(Government &its, int numOfMinister);
	// �������� ���������� � ����������
	void getInformation();
	President();
};
