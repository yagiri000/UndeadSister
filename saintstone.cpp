#pragma once

#include "saintstone.h"

saintstone::saintstone(){
	x = 150;
	y = 300;
	hp = hpmax = 30;
	counttime = 0;
	saint_GHandle[0] = LoadGraph2("saint32.png");
	saint_GHandle[1] = LoadGraph2("saint_foot.png");
}

void saintstone::heal(double rate){
	hp += (int)(hpmax * rate);
	if(hp > hpmax){
		hp = hpmax;
	}
}

void saintstone::update(){
	counttime++;
}



void saintstone::drawstone(){
	int max = 100;
	double high =  (5*sin(counttime * 0.01)+50.0) / max;
	for(int i = 10; i < max-5; i+=2){
		double ax[4];
		double ay[4];
		double 
			dd = counttime * 0.01,
			rr = 40,
			h1 = -high * i + y,
			h2 = -high * (i+1) + y,
			k1 = sin((double)i/max * 3.14),
			k2 = sin((double)(i+1)/max * 3.14),
			kat = 0.4,
			angle = i * 0.41 + dd,
			angle2 = (i+1) * 0.41 + dd;
		ax[0] = k1 * rr * cos(angle) + x;
		ay[0] = kat * rr * sin(angle) + h1;
		ax[1] = k2 * rr * cos(angle2) + x;
		ay[1] = kat * rr * sin(angle2) + h2;
		ax[2] = ax[1] ;
		ay[2] = ay[1] - 20;
		ax[3] = ax[0];
		ay[3] = ay[0] - 20;
		DrawModiGraph((int)ax[0], (int)ay[0], (int)ax[1], (int)ay[1], (int)ax[2], (int)ay[2], (int)ax[3], (int)ay[3], saint_GHandle[0],1);
	}
}

void saintstone::drawdiedstone(){	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;	SetDrawBright(0,0,0);
	DrawRotaGraph3((int)x, (int)y, 64, 64, 1.0, 0.6, 0, saint_GHandle[1], 1);
	drawstone();
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255,255,255);
}

void saintstone::draw(){
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255,255,255);
	DrawRotaGraph3((int)x, (int)y, 64, 64, 1.0, 0.6, 0, saint_GHandle[1], 1);

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;	SetDrawBright(255,255,255);
	drawstone();

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255,255,255);
}