#pragma once
#include "Minister.h"
class MinisterFSB : public Minister
{
public:
	//защитить роль от воздействия иностранного гос-ва
    int recruitDefence(Government &its, int help[COUNT_OF_MINISTER]);
	//найти министра внешней разведки иностранного государства
	int* findRecruited(Government &its, Government &searching);
	// получить информацию о президенте
	void getInformation();
};
