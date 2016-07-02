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
	int ai;//0でプレイヤー、1で拠点（聖石）を狙う

	int wait;//wait>0なら停止
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
	unsigned long damagenum;//プレイヤーにダメージを与えた回数
	unsigned long dienum;//倒されたゾンビ数
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	std::vector<enemyparts> v;//の配列
	enemy();
	void make(double xx, double yy, int kind);
	void update();
	void draw();
};

