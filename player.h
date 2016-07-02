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

class player{
public:
	double x,y;
	int p_GHandle[99];
	unsigned long exp, expsum;//expとexpの累計（累計はスコア算出に使う）
	double gunangle;
	int hp, hpmax;
	int houkou, aruku;
	int firecool,firerate;//次の弾発射までのクール時間, 所要時間
	int reloadcool, reloadneed;//リロードクール時間(>0で弾打てない) , リロード所要時間
	int bullet, bulletmax;//現在弾数, 最大弾数
	int atk;
	double movespeed;
	player();
	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	void move();
	void movelimit(int width, int height);
	void sethoukou();
	void fire();
	void hitenemy();
	void heal(double rate);
	void update();
	void draw();
};
