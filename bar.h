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
#include "saintstone.h"

class bar{
public:
	int ghandle[99];
	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	bar();
	void update();
	void drawhpbar(int x0, int y0, int now, int max, int kind);
	void drawstatus();
	void draw();
};
