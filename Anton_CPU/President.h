#pragma once
#include "Minister.h"
#include <listofgovernments.h>
class President : public Minister
{
public:
	//уволить министра
    int dismiss(Government &its, int numOfMinister);
	// получить информацию о президенте
	void getInformation();
    President(ListOfGovernments *govs);

private:
    ListOfGovernments *governments;
};
