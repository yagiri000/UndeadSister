#pragma once

#include "define.h"
#include "DxLib.h"
#include <string>
#include "original_func.h"
#include "ptr_list.h"
#include "effect.h"

class explain{
public:
	explain();
	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	int ghandle[99];
	int counttime;
	int nowselect;
	int x0, y0;//スタート表示位置
	void update();
	void draw();
};
