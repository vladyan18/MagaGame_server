#pragma once
#include "Minister.h"
#include <listofgovernments.h>
class President : public Minister
{
public:
	//������� ��������
    int dismiss(Government &its, int numOfMinister);
	// �������� ���������� � ����������
	void getInformation();
    President(Government *its,ListOfGovernments *govs);

private:
    ListOfGovernments *governments;
};
