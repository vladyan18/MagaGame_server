#pragma once
#include "Minister.h"
class MinisterFSB : public Minister
{
public:
    MinisterFSB(Government *its);
	//�������� ���� �� ����������� ������������ ���-��
    int recruitDefence(Government &its, int minister, int count);
	//����� �������� ������� �������� ������������ �����������
    int findRecruited(Government &its, Government &searching);
	// �������� ���������� � ����������
	void getInformation();
    int kgbPower = 100;
    bool isDefending = false;
private:

};
