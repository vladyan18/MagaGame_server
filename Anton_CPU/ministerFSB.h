#pragma once
#include "Minister.h"
class MinisterFSB : public Minister
{
public:
	//�������� ���� �� ����������� ������������ ���-��
    int recruitDefence(Government &its, int help[COUNT_OF_MINISTER]);
	//����� �������� ������� �������� ������������ �����������
	int* findRecruited(Government &its, Government &searching);
	// �������� ���������� � ����������
	void getInformation();
};
