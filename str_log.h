#pragma once

#include "define.h"
#include "DxLib.h"
#include <string>
#include "original_func.h"


class str_log{
public:
	int x0,y0;
	int fonthandle;
	int ghandle[9];
	double alpharate;
	double yshift, ydif;
	std::string str[9];
	std::string bigstr;
	std::string bigstr_under;
	int bigstrtime;
	int bigstralpha;
	str_log();
	void addbigstr(std::string str, std::string ministr);
	void setbigalpha();
	void add(std::string addstr);
	void update();
	void draw();
};
