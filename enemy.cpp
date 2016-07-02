#pragma once

#include "enemy.h"

enemyparts::enemyparts(double xx, double yy, int kind, ptr_list *gt_ptr){
	//�f�t�H���g���l
	ptr = gt_ptr;
	x = xx;
	y = yy;
	wait = 60;
	angle = 0;
	ghandle = ptr->menemy->ghandle[kind];
	//setstatus(std::string name, int hp, int atk, int exp, int ai, double speed, double rotangle)
	//ai 0�����@�@1�����_
	switch (kind)
	{
	case 0:
		setstatus("���s�]���r", 3, 1, 23, 1, 0.7, 0.1*randarc());
		break;

	case 1:
		setstatus("���ՓI�]���r", 9, 1, 26, 0, 1.2, 0.1);
		break;

	case 2:
		setstatus("�y�ʉ��]���r", 1, 1, 27, 0, 1.6, 0.1*randarc());
		break;

	case 3:
		setstatus("�������]���r", 15, 2, 31, 1, 0.5, -0.1);
		break;

	case 4:
		setstatus("�����]���r", 9, 2, 34, 0, 1.4, 0.5);
		randnegpos(rotangle);
		break;

	case 5:
		setstatus("�Í������]���r", 1, 2, 29, 0, 4.0, 0);
		break;

	case 6:
		setstatus("���{��`�]���r", 12, 2, 35, 0, 1.4, 0.2);
		randnegpos(rotangle);
		break;

	case 7:
		setstatus("�������]���r", 15, 1, 37, 1, 1.0, -0.32);
		break;

	case 8:
		setstatus("�O�i���W�]���r", 15, 2, 41, 0, 1.6, 0);
		randnegpos(rotangle);
		break;

	case 9:
		setstatus("���P�]���r", 15, 3, 41, 0, 1.5, 0.7);
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
		ptr->mstr_log->add("*�K�u�b* �u�ɂ�...�v�]���r�Ɋ��܂ꂽ�c�c");//���O�ǉ�
	}
	
	double x1 =ptr->mstone->x ,  y1 = ptr->mstone->y;
	if(dist(x, y, x1, y1)<50){
		for(int i = 0; i < 10; i++){ ptr->meffect->make(x1, y1, 5, -1, -1);}
		PlaySoundMem(SHandle[3], DX_PLAYTYPE_BACK );
		ptr->mstone->hp -= atk;
		if(gamestate == 20){ ptr->menemy->damagenum += 1; }
		wait += 60;
		ptr->mstr_log->add("*�K���b* ���΂�������ꂽ");//���O�ǉ�
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
		//�����Ԃ�
		for(int i = 0; i < 7; i++){ ptr->meffect->make(x, y, 4, -1, -1);}
		//���̎c�����c�����C���[�ɕ`��
		SetDrawScreen( zanzou ) ;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;
		for(int i = 0; i < 5; i++){
			DrawRotaGraph((int)(x+30*randarc()), (int)(y+30*randarc()), randarc()*1.0+0.7, PI*randarc(), GHandle[7], 1);
		}
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
		SetDrawScreen( DX_SCREEN_BACK ) ;
		
		deadlog();//��b���O+�o���l����

		return true;
	}else{
		return false;
	}
}

void enemyparts::deadlog(){
	std::string deadsound;
	int rnd = GetRand(10);
		 if(rnd == 0){deadsound = "*�o�L�b* ";}
	else if(rnd == 1){deadsound = "*�O�`���b* ";}
	else if(rnd == 2){deadsound = "*�����b* ";}
	else if(rnd == 3){deadsound = "*�f���b* ";}
	else if(rnd == 4){deadsound = "*�p�@���b* ";}
	else if(rnd == 5){deadsound = "*�O�V��* ";}
	else if(rnd == 6){deadsound = "*�U�V��* ";}
	else if(rnd == 7){deadsound = "*�o�^�b* ";}
	else if(rnd == 8){deadsound = "*�S���b* ";}
	else if(rnd == 9){deadsound = "*�O�j���L�b* ";}

	std::ostringstream  ostr;
	ostr << deadsound << name << "��|�����BEXP��" << exp << "���������B";
	ptr->mstr_log->add(ostr.str());//���O�ǉ�
	ptr->mplayer->exp += exp;//�o���l����
	ptr->mplayer->expsum += exp;//�ݐόo���l����
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
