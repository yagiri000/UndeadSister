#pragma once

#include "enemy.h"

enemyparts::enemyparts(double xx, double yy, int kind, ptr_list *gt_ptr){
	//デフォルト数値
	ptr = gt_ptr;
	x = xx;
	y = yy;
	wait = 60;
	angle = 0;
	ghandle = ptr->menemy->ghandle[kind];
	//setstatus(std::string name, int hp, int atk, int exp, int ai, double speed, double rotangle)
	//ai 0→自機　1→拠点
	switch (kind)
	{
	case 0:
		setstatus("腐敗ゾンビ", 3, 1, 23, 1, 0.7, 0.1*randarc());
		break;

	case 1:
		setstatus("普遍的ゾンビ", 9, 1, 26, 0, 1.2, 0.1);
		break;

	case 2:
		setstatus("軽量化ゾンビ", 1, 1, 27, 0, 1.6, 0.1*randarc());
		break;

	case 3:
		setstatus("半水晶ゾンビ", 15, 2, 31, 1, 0.5, -0.1);
		break;

	case 4:
		setstatus("血染ゾンビ", 9, 2, 34, 0, 1.4, 0.5);
		randnegpos(rotangle);
		break;

	case 5:
		setstatus("暗黒物質ゾンビ", 1, 2, 29, 0, 4.0, 0);
		break;

	case 6:
		setstatus("資本主義ゾンビ", 12, 2, 35, 0, 1.4, 0.2);
		randnegpos(rotangle);
		break;

	case 7:
		setstatus("符号化ゾンビ", 15, 1, 37, 1, 1.0, -0.32);
		break;

	case 8:
		setstatus("三段頭蓋ゾンビ", 15, 2, 41, 0, 1.6, 0);
		randnegpos(rotangle);
		break;

	case 9:
		setstatus("強襲ゾンビ", 15, 3, 41, 0, 1.5, 0.7);
		randnegpos(rotangle);
		break;
	}
}

void enemyparts::setstatus(std::string name, int hp, int atk, int exp, int ai, double speed, double rotangle){
	this->name = name;
	this->hp = hp;
	this->atk = atk;
	this->exp = exp;
	this->ai = ai;
	this->speed = speed;
	this->rotangle = rotangle;
}

bool enemyparts::statewait(){
	if(wait>0){
		wait--;
		x+= randarc()*5;
		y+= randarc()*5;
		double x1 =ptr->mstone->x ,  y1 = ptr->mstone->y;
		if(dist(x, y, x1, y1) < 50){
			double angle = atan2(y1-y, x1-x);
			x += -5 * cos(angle);
			y += -5 * sin(angle);
		}
		return 0;
	}else{
		return 1;
	}
}

void enemyparts::move(){
	if(ai == 0){
		angle = atan2(ptr->mplayer->y - y, ptr->mplayer->x - x);
		x += speed * cos(angle+rotangle);
		y += speed * sin(angle+rotangle);
	}else if(ai == 1){
		angle = atan2(ptr->mstone->y - y, ptr->mstone->x  - x);
		x += speed * cos(angle+rotangle);
		y += speed * sin(angle+rotangle);
	}
}

void enemyparts::attack(){
	if(dist(x, y, ptr->mplayer->x, ptr->mplayer->y)<20){
		for(int i = 0; i < 10; i++){ ptr->meffect->make(ptr->mplayer->x, ptr->mplayer->y, 5, -1, -1);}
		PlaySoundMem(SHandle[3], DX_PLAYTYPE_BACK );
		ptr->mplayer->hp -= atk;
		if(gamestate == 20){ ptr->menemy->damagenum += 1; }
		wait += 30;
		ptr->mstr_log->add("*ガブッ* 「痛い...」ゾンビに噛まれた……");//ログ追加
	}
	
	double x1 =ptr->mstone->x ,  y1 = ptr->mstone->y;
	if(dist(x, y, x1, y1)<50){
		for(int i = 0; i < 10; i++){ ptr->meffect->make(x1, y1, 5, -1, -1);}
		PlaySoundMem(SHandle[3], DX_PLAYTYPE_BACK );
		ptr->mstone->hp -= atk;
		if(gamestate == 20){ ptr->menemy->damagenum += 1; }
		wait += 60;
		ptr->mstr_log->add("*ガリッ* 聖石が傷つけられた");//ログ追加
	}
}

void enemyparts::update(){
	if(statewait()){
		move();
		attack();
	}
}

bool enemyparts::die(){
	if(hp < 1){

		PlaySoundMem(SHandle[2], DX_PLAYTYPE_BACK );
		//血しぶき
		for(int i = 0; i < 7; i++){ ptr->meffect->make(x, y, 4, -1, -1);}
		//血の残像を残像レイヤーに描画
		SetDrawScreen( zanzou ) ;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;
		for(int i = 0; i < 5; i++){
			DrawRotaGraph((int)(x+30*randarc()), (int)(y+30*randarc()), randarc()*1.0+0.7, PI*randarc(), GHandle[7], 1);
		}
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
		SetDrawScreen( DX_SCREEN_BACK ) ;
		
		deadlog();//会話ログ+経験値増加

		return true;
	}else{
		return false;
	}
}

void enemyparts::deadlog(){
	std::string deadsound;
	int rnd = GetRand(10);
		 if(rnd == 0){deadsound = "*バキッ* ";}
	else if(rnd == 1){deadsound = "*グチャッ* ";}
	else if(rnd == 2){deadsound = "*メリッ* ";}
	else if(rnd == 3){deadsound = "*デロッ* ";}
	else if(rnd == 4){deadsound = "*パァンッ* ";}
	else if(rnd == 5){deadsound = "*グシュ* ";}
	else if(rnd == 6){deadsound = "*ザシュ* ";}
	else if(rnd == 7){deadsound = "*バタッ* ";}
	else if(rnd == 8){deadsound = "*ゴリッ* ";}
	else if(rnd == 9){deadsound = "*グニョキッ* ";}

	std::ostringstream  ostr;
	ostr << deadsound << name << "を倒した。EXPが" << exp << "増加した。";
	ptr->mstr_log->add(ostr.str());//ログ追加
	ptr->mplayer->exp += exp;//経験値増加
	ptr->mplayer->expsum += exp;//累積経験値増加
}

void enemyparts::draw(){
	DrawRotaGraph((int)x, (int)y, 1.0, angle-1.57, ghandle, 1);
}

enemy::enemy(){
	damagenum = 0;
	dienum = 0;
	LoadDivGraph2("zombies.png", 16, 16, 1, 64, 64, ghandle);
}


void enemy::make(double xx, double yy, int kind){
	v.push_back(enemyparts(xx, yy, kind, ptr));
}



void enemy::update(){
	for(int i = 0; i < (int)v.size(); i++){
		if(v[i].die()){
			auto p = v.begin() + i;
			v.erase(p);
			i--;
			dienum++;
		}else{
			v[i].update();
		}
	}
}

void enemy::draw(){
	for(int i = 0; i < (int)v.size(); i++){
		v[i].draw();
	}
}
