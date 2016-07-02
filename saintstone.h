#pragma once

#include "define.h"
#include <DxLib.h>
#include <iostream>
#include <string>
#include <vector>
#include "original_func.h"
#include "enemy.h"
#include "ptr_list.h"
#include "str_log.h"
#include "effect.h"

class saintstone{
public:
	double x,y;
	int saint_GHandle[99];
	int hp, hpmax;
	int counttime;

	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}

	saintstone();
	void drawstone();
	void drawdiedstone();
	void heal(double rate);
	void update();
	void draw();
};
