#pragma once

#include "player.h"

player::player(){
	x = 400;
	y = 300;
	hp = hpmax = 30;
	gunangle = 0;
	exp = 0;expsum = 0;
	houkou = 0, aruku = 0;
	firecool=0,firerate=9;//次の弾発射までのクール時間, 所要時間
	reloadcool = reloadneed = 120;//リロードクール時間(>0で弾打てない) , リロード所要時間
	bullet=60, bulletmax = 60;//現在弾数, 最大弾数
	atk = 2;//銃威力
	movespeed = 1.8;//移動速度
	LoadDivGraph2("player01.png", 24,6,4,20,28,p_GHandle );
	p_GHandle[30] = LoadGraph2("gun.png");
	p_GHandle[33] = LoadGraph2("dot100_black.png");
	p_GHandle[34] = LoadGraph2("rect100_black.png");
}


void player::movelimit(int width, int height){
	double x1 =ptr->mstone->x ,  y1 = ptr->mstone->y;
	if(dist(x, y, x1, y1) < 50){
		double angle = atan2(y1-y, x1-x);
		x += -4 * cos(angle);
		y += -4 * sin(angle);
	}

	if(x < 0){x = 0;}
	if(x > width){x = width;}
	if(y < 0){y = 0;}
	if(y > height){y = height;}
}

void player::move(){
	double vv = movespeed;
	int angle = -1;

	if(keystate[KEY_INPUT_RIGHT] > 0){angle = 0;}
	if(keystate[KEY_INPUT_DOWN] > 0){angle = 90;}
	if(keystate[KEY_INPUT_LEFT] > 0){angle = 180;}
	if(keystate[KEY_INPUT_UP] > 0){angle = 270;}
	if(keystate[KEY_INPUT_RIGHT] > 0 && keystate[KEY_INPUT_DOWN] > 0){angle = 45;}
	if(keystate[KEY_INPUT_DOWN] > 0 && keystate[KEY_INPUT_LEFT] > 0){angle = 135;}
	if(keystate[KEY_INPUT_LEFT] > 0 && keystate[KEY_INPUT_UP] > 0){angle = 225;}
	if(keystate[KEY_INPUT_UP] > 0 && keystate[KEY_INPUT_RIGHT] > 0){angle = 315;}

	if(keystate[32] > 0){angle = 0;}
	if(keystate[31] > 0){angle = 90;}
	if(keystate[30] > 0){angle = 180;}
	if(keystate[17] > 0){angle = 270;}
	if(keystate[32] > 0 && keystate[31] > 0){angle = 45;}
	if(keystate[31] > 0 && keystate[30] > 0){angle = 135;}
	if(keystate[30] > 0 && keystate[17] > 0){angle = 225;}
	if(keystate[17] > 0 && keystate[32] > 0){angle = 315;}
	if(angle != -1){
		x += vv * cos(angle*arcrad);
		y += vv * sin(angle*arcrad);
		aruku++;
	}
}

void player::sethoukou(){
	double angle = atan2(mousey - y, mousex - x);
	angle += 6.28/16;
	if(angle<0){angle += 6.284;}
	int houkou8 = 0;
	int houkouset[9] ={12,9,0,3,6,15,18,21};
	houkou8 = (int)(angle /arcrad)/45;
	houkou8 = houkou8 % 8;
	houkou = houkouset[houkou8];
}



void player::fire(){

	if(firecool >0){firecool--;}

	if(reloadcool > 0){
		reloadcool--;
		if(reloadcool == 5){PlaySoundMem(SHandle[5], DX_PLAYTYPE_BACK );}
		if(reloadcool == 0){
			ptr->mstr_log->add("*カチッ* リロード完了 [クリックし続けると自動連射]");
			bullet = bulletmax;	
		}
	}

	if(keystate[250]> 0 && firecool <= 0 && reloadcool <= 0){
		double angle = atan2(mousey - y, mousex - x);
		double xd2 = x + 20 * cos(angle);
		double yd2 = y + 20 * sin(angle);
		//エフェクト　弾道・閃光・煙
		ptr->meffect->make(xd2, yd2, 6, -1, -1);
		for(int i = 0; i < 3; i++){	ptr->meffect->make(xd2, yd2, 1, angle, -1);}
		PlaySoundMem(SHandle[1], DX_PLAYTYPE_BACK );
		firecool = firerate;
		hitenemy();
		bullet--;


	}
	//リロード中で無ければ
	if(reloadcool <= 0){
		//弾が無い、または右クリックで
		if(bullet <= 0 || keystate[251] == 1){
			ptr->mstr_log->add("*ガチャ...* リロード開始 [右クリックでもリロード可]");
			PlaySoundMem(SHandle[4], DX_PLAYTYPE_BACK );
			reloadcool = reloadneed;
		}
	}
}

void player::hitenemy(){
	double angle = atan2(mousey - y, mousex - x);
	auto v = ptr->menemy->v.begin();
	const double enemysize = 10;
	double dst = 400;
	int hitnum = -1;//あたった敵の番号
	for(int i = 0; i < (int)ptr->menemy->v.size(); i++){
		if(ClashCircleLine(x, y, x+400*cos(angle), y+400*sin(angle), v[i].x, v[i].y, enemysize)){
			if(dst > dist(x, y, v[i].x, v[i].y)){
				hitnum = i;
				dst = dist(x, y, v[i].x, v[i].y);
			}
		}
	}
	if(hitnum != -1){
		int i = hitnum;
		for(int j = 0; j < 2; j++){ptr->meffect->make(v[i].x-10*cos(angle), v[i].y-10*sin(angle), 2, -1, -1);}
		ptr->meffect->make(v[i].x-15*cos(angle), v[i].y-15*sin(angle), 3, angle+PI, -1);
		ptr->menemy->v[i].hp -= atk;
		ptr->menemy->v[i].x += 20 * cos(angle);
		ptr->menemy->v[i].y += 20 * sin(angle);
	}
	double angle2 = atan2(mousey - y, mousex - x);
	double xd = x + 28 * cos(angle2);
	double yd = y + 28 * sin(angle2);
	ptr->meffect->make(xd, yd, 0, angle, dst/256.0);
}

void player::heal(double rate){
	hp += (int)(hpmax * rate);
	if(hp > hpmax){
		hp = hpmax;
	}
}

void player::update(){
	gunangle = atan2(mousey - y, mousex - x);
	fire();
	sethoukou();
	move();
	movelimit(800, 600);
}

//主人公描画
void player::draw(){

	//自機と銃描画
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 250 ) ;
	int ar = (int)(aruku *0.1);
	ar = ar % 4;
	if(ar == 3){ar = 1;}
	if(gunangle <0){
		DrawRotaGraph3((int)x,(int)y,-5,8,1,1,gunangle,p_GHandle[30] ,1);
		DrawRotaGraph3((int)x,(int)y,10,20,2,2,0,p_GHandle[houkou+ar],1);
	}else{
		DrawRotaGraph3((int)x,(int)y,10,20,2,2,0,p_GHandle[houkou+ar],1);
		DrawRotaGraph3((int)x,(int)y,-5,8,1,1,gunangle,p_GHandle[30] ,1);
	}


}

