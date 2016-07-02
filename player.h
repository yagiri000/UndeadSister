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
	unsigned long exp, expsum;//exp��exp�̗݌v�i�݌v�̓X�R�A�Z�o�Ɏg���j
	double gunangle;
	int hp, hpmax;
	int houkou, aruku;
	int firecool,firerate;//���̒e���˂܂ł̃N�[������, ���v����
	int reloadcool, reloadneed;//�����[�h�N�[������(>0�Œe�łĂȂ�) , �����[�h���v����
	int bullet, bulletmax;//���ݒe��, �ő�e��
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
