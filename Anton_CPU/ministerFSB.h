#pragma once
#include "Minister.h"
class MinisterFSB : public Minister
{
public:
    MinisterFSB(Government *its);
	//защитить роль от воздействия иностранного гос-ва
    int recruitDefence(Government &its, int minister, int count);
	//найти министра внешней разведки иностранного государства
    int findRecruited(Government &its, Government &searching);
	// получить информацию о президенте
	void getInformation();
    int kgbPower = 100;
    bool isDefending = false;
private:

};
