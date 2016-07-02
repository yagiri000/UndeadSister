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
#include "player.h"

class dying{
public:
	dying();
	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	unsigned long diedtime;
	void update();
	void startdying();//€‚ñ‚¾uŠÔ‚Ìˆ—
	void draw();
};