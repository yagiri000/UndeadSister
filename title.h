#pragma once

#include "define.h"
#include "DxLib.h"
#include <string>
#include "original_func.h"

class title{
public:
	int ghandle[99];
	int nowselect;
	title();
	void update();
	void draw();
};
