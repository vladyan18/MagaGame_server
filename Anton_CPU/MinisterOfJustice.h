#pragma once
#include "Minister.h"
class MinisterOfJustice : public Minister
{
public:
    int sue(Government &its, Government &attack, bool proof);
	// получить информацию о министре юстиции
	void getInformation();
};
