#pragma once

#include "define.h"
#include "DxLib.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "player.h"
#include "original_func.h"
#include "str_log.h"
#include "ptr_list.h"
#include "saintstone.h"

class skill{
public:
	void setskill(int xx, int yy, int number, int *ptr_ghandle);
	std::string name;
	std::string explain;
	int flugbuy;
	int needexp;
	int x, y;
	int size;
	int num;
	int *ghandle;
	void setname(int num);
	bool clashrect(int xx, int yy, int cx, int cy, int width, int height);
	bool update();
	void draw();
};


class levelup{
public:
	unsigned long timecount;
	
	int xnum, ynum;//x�̍��ڐ��A���̍��ڐ�
	int xdif, ydif;//x��y�̃A�C�R�����S�Ԃ̕�
	int x0, y0 ; //�A�C�R����_�@����
	int ghandle[99];
	skill skill[16];
	int skillnum;
	int nowselect;//���ݑI�����Ă���J�[�\���ԍ�
	double cur_rate;//�J�[�\���̊g�嗦
	double cur_x, cur_y;
	
	levelup();
	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}

	void getselect();
	void getskill();
	void statusup();
	void drawexplain();

	void resume();
	void drawresume();

	void drawstatus();

	void update();
	void draw();
};
