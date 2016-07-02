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

class enemyparts{
public:
	double x, y, speed, angle, rotangle;
	std::string name;
	int hp;
	int atk;
	int exp;
	int ai;//0�Ńv���C���[�A1�ŋ��_�i���΁j��_��

	int wait;//wait>0�Ȃ��~
	int ghandle;
	enemyparts(double xx, double yy, int kind, ptr_list *gt_ptr);
	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	void setstatus(std::string name, int hp, int atk, int exp, int ai, double speed, double rotangle);
	bool statewait();
	void move();
	void attack();
	bool die();
	void deadlog();
	void update();
	void draw();
};


class enemy{
public:
	ptr_list *ptr;
	int ghandle[99];
	unsigned long damagenum;//�v���C���[�Ƀ_���[�W��^������
	unsigned long dienum;//�|���ꂽ�]���r��
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	std::vector<enemyparts> v;//�̔z��
	enemy();
	void make(double xx, double yy, int kind);
	void update();
	void draw();
};

