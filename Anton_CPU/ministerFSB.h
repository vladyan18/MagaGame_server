#pragma once
#include "Minister.h"
class MinisterFSB : public Minister
{
public:
	//�������� ���� �� ����������� ������������ ���-��
    int recruitDefence(Government &its, int minister, int count);
	//����� �������� ������� �������� ������������ �����������
    int findRecruited(Government &its, Government &searching);
	// �������� ���������� � ����������
	void getInformation();

private:
    bool isDefending = false;
};
