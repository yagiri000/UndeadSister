#pragma once

#include "define.h"


//**ポインタのリスト**
class ptr_list
{
public:
	player *mplayer;
	enemy *menemy;
	effect *meffect;
	str_log *mstr_log;
	saintstone *mstone;
	void getptr(player *p1, enemy *p2, effect  *p3,str_log *p4, saintstone *p5){
		mplayer = p1;
		menemy = p2;
		meffect = p3;
		mstr_log = p4;
		mstone = p5;
	}
};

