#pragma once

#include "define.h"
#include <DxLib.h>
#include <iostream>
#include <vector>
#include "player.h"
#include "original_func.h"
#include "enemy.h"
#include "ptr_list.h"

//個々のエフェクト
class effectparts{
	double x, y;
	double vx, vy;
	double ax, ay;
	double spdrate;
	int centerx, centery;
	double exratex, exratey;
	double exratex_plus, exratey_plus;
	double angle, angle_plus;
	double alpha, alpha_plus;
	int turnflug;
	int transalpha;//←＝timeのフレームにアルファプラスに-1をかける
	int ghandle;
	int time;
	double k1, k2;
public:

	effectparts(double xx, double yy, int kind, double kk1, double kk2);
	void normalset();
	bool update();
	void draw();
};

//エフェクト管理クラス
class effect{
public:
	std::vector<effectparts> v;//エフェクトの配列
	//int efGHandle[99];
	effect();
	void make(double xx, double yy, int kind, double kk1, double kk2);
	void update();
	void draw();
};