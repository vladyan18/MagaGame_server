#pragma once
#include "Minister.h"
class MinisterOfJustice : public Minister
{
public:
    MinisterOfJustice(Government *its);
    int sue(Government &its, Government &attack, bool proof);
	// получить информацию о министре юстиции
	void getInformation();

};
