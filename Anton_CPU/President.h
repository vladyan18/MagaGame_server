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
    President(ListOfGovernments *govs);

private:
    ListOfGovernments *governments;
};
