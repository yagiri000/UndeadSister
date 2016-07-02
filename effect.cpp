#pragma once

#include "effect.h"

//消滅時間ならtrue返す
bool effectparts::update(){
	vx *= spdrate, vy *= spdrate;
	vx += ax, vy += ay;
	x += vx, y += vy;
	exratex += exratex_plus, exratey += exratey_plus;
	angle += angle_plus;
	alpha += alpha_plus;

	if(transalpha == time){alpha_plus *= -1;}
	time--;
	if(time < 1){return true;}else{return false;}
}

void effectparts::draw(){
	//SetDrawBlendMode( DX_BLENDMODE_ADD , (int)alpha ) ;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)alpha ) ;
	DrawRotaGraph3((int)x, (int)y, centerx, centery, exratex, exratey, angle, ghandle, 1, turnflug);
}

void effectparts::normalset(){
	vx = vy = 0;
	ax = ay = 0;
	spdrate = 1.0;
	centerx = centery = 0;
	exratex = exratey = 1.0;
	exratex_plus = exratey_plus = 0;
	angle = angle_plus = 0;
	alpha = 255;
	alpha_plus = 0;
	turnflug = 0;
	transalpha = 0;
	time = 0;
}

effectparts::effectparts(double xx, double yy, int kind, double kk1, double kk2){

	x = xx, y = yy;
	normalset();//全値に初期値入れる
	
	double ang = randarc() * PI;
	double spd = (randarc() + 3) * 0.333;
	switch (kind)
	{
	case 0://銃撃閃光
		ghandle = efGHandle[1];
		centerx = 0;
		centery = 2;
		exratex = kk2;
		alpha = 200;
		alpha_plus = -30;
		angle = kk1;
		time = 3;
		break;

	case 1://銃撃煙
		ghandle = efGHandle[4];
		centerx = centery = 16;
		exratex = exratey = 0.2;
		vx = 4 * cos(ang*0.1+kk1);
		vy = 4 * sin(ang*0.1+kk1);
		x+=randarc();y+=randarc();
		ax = randarc();
		ay = -1;
		spdrate = 0.9;
		alpha = 100;
		alpha_plus = 0;
		time = 5;
		break;

	case 2://斬撃エフェクト
		ghandle = efGHandle[4];
		centerx = centery = 16;
		angle = ang;
		alpha = 100;
		alpha_plus = -10;
		exratex = exratey = 0.2;
		exratex_plus = -0.02;
		exratey_plus = 0.3;
		time = 10;
		break;

	
	case 3://血しぶき
		ghandle = efGHandle[3];
		centerx = centery = 16;
		exratex = exratey = 0.6;
		exratex_plus =exratey_plus =-0.06;
		vx = 5 * spd * cos(ang*0.2+kk1);
		vy = 5 * spd * sin(ang*0.2+kk1);
		alpha = 250;
		//alpha_plus = -25;
		time = 10;
		break;
		
	case 4://血しぶき死亡時
		ghandle = efGHandle[3];
		centerx = centery = 16;
		exratex = exratey = 0.7+randarc()*0.1;
		angle = ang;
		exratex_plus =exratey_plus =-0.025;
		vx = 5 * spd * cos(ang);
		vy = 5 * spd * sin(ang);
		spdrate = 0.95;
		alpha = 250;
		//alpha_plus = -25;
		time = 25;
		break;

	case 5://血しぶき自機被弾時
		ghandle = efGHandle[3];
		centerx = centery = 16;
		exratex = exratey = 0.7+randarc()*0.1;
		angle = ang;
		exratex_plus =exratey_plus =-0.025;
		vx = 10 * spd * cos(ang);
		vy = 10 * spd * sin(ang);
		spdrate = 0.95;
		alpha = 100;
		time = 25;
		break;
		
	case 6://銃撃閃光
		ghandle = efGHandle[5];
		centerx = 32;
		centery = 32;
		alpha = 200;
		alpha_plus = -50;
		angle = ang;
		time = 3;
		break;
		
	case 7://火炎放射（未使用）
		ghandle = efGHandle[2];
		centerx = 0;
		centery = 256;
		alpha = 255;
		alpha_plus = -25;
		exratex = exratey = 0.5;
		exratex_plus = 0.01;
		exratey_plus = -0.01;
		angle = kk1;
		time = 10;
		break;

	case 8://画面全体暗め→明るめに
		ghandle = efGHandle[6];
		centerx = 0;
		centery = 0;
		alpha = 120;
		alpha_plus = -6;
		exratex = exratey = 32;
		time = 20;
		break;

	case 9://画面全体フラッシュ
		ghandle = efGHandle[7];
		centerx = 0;
		centery = 0;
		alpha = 120;
		alpha_plus = -12;
		exratex = exratey = 32;
		time = 10;
		break;

	case 10://画面全体暗め→明るめに
		ghandle = efGHandle[6];
		centerx = 0;
		centery = 0;
		alpha = 240;
		alpha_plus = -2;
		exratex = exratey = 32;
		time = 120;
		break;
	}
}


effect::effect(){
}


//エフェクト管理クラス関数
void effect::make(double xx, double yy, int kind, double kk1, double kk2){
	v.push_back(effectparts(xx, yy, kind, kk1, kk2));
}

void effect::update(){
	for(int i = 0; i < (int)v.size(); i++){
		if(v[i].update()){
			auto p = v.begin();
			p+= i;
			v.erase(p);
			i--;
		}
	}
}

void effect::draw(){
	for(int i = 0; i < (int)v.size(); i++){
		v[i].draw();
	}
}