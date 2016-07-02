#pragma once

#include "levelup.h"

//名前　説明　EXPを設定
void skill::setname(int num){
	switch (num)
	{
	case 0:
		name = "安息の福音";
		explain = "wave終了時、HPが回復する";
		needexp = 100;
		break;
	case 1:
		name = "再結晶化";
		explain = "wave終了時、聖石HPが回復する";
		needexp = 100;
		break;
	case 2:
		name = "痛覚遮断";
		explain = "最大HPが上昇する";
		needexp = 500;
		break;
	case 3:
		name = "祝福の息吹";
		explain = "最大HPが上昇する";
		needexp = 2000;
		break;
	case 4:
		name = "水晶硬質化";
		explain = "聖石の最大HPが上昇する";
		needexp = 500;
		break;
	case 5:
		name = "硬度の集積";
		explain = "聖石の最大HPが上昇する";
		needexp = 2000;
		break;
	case 6:
		name = "収束弾";
		explain = "銃撃の威力が上昇する";
		needexp = 1000;
		break;
	case 7:
		name = "ホローポイント";
		explain = "銃撃の威力が上昇する";
		needexp = 4000;
		break;
	case 8:
		name = "アンチマテリアル";
		explain = "銃撃の威力が上昇する";
		needexp = 6000;
		break;
	case 9:
		name = "エクスバレット";
		explain = "装填数が増加する";
		needexp = 2000;
		break;
	case 10:
		name = "トレノバレット";
		explain = "装填数が増加する";
		needexp = 4000;
		break;
	case 11:
		name = "替玉";
		explain = "リロード速度が上昇する";
		needexp = 2000;
		break;
	case 12:
		name = "神速装填";
		explain = "リロード速度が上昇する";
		needexp = 4000;
		break;
	case 13:
		name = "超速連射オイル";
		explain = "銃の連射速度が上昇する";
		needexp = 2000;
		break;
	case 14:
		name = "連射機構";
		explain = "銃の連射速度が上昇する";
		needexp = 4000;
		break;
	case 15:
		name = "疾風の靴";
		explain = "移動速度が上昇する";
		needexp = 1000;
		break;
	}
}

void skill::setskill(int xx, int yy, int number, int *ptr_ghandle){
	setname(number);
	num = number;
	x = xx, y = yy;
	size = 48;
	flugbuy = 0;
	ghandle = ptr_ghandle;
}

//対象の座標, 自分の座標、アイコンの大きさ
bool skill::clashrect(int xx, int yy, int cx, int cy, int width, int height){
	if( 2*abs(xx-cx) < width && 2*abs(yy-cy) < height){
		return 1;
	}else{
		return 0;
	}
}

bool skill::update(){
	if(keystate[250] == 1 && clashrect(mousex, mousey, x, y, 48, 48)){
		return true;
	}else{
		return false;
	}
}

void skill::draw(){
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 100 ) ;
	DrawRotaGraph(x, y, 1.0, 0, ghandle[20], 1);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 ) ;
	SetDrawBright(255,126,0);
	DrawRotaGraph(x, y, 1.0, 0.0, ghandle[num], 1);
	if(flugbuy != 0){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;	SetDrawBright(255,255,255);
		DrawRotaGraph(x, y, 1.0, 0, ghandle[23], 1);
	}
	SetDrawBright(255,255,255);
}




levelup::levelup(){
	skillnum = 16;
	x0 = 480;
	y0 = 120;
	xdif = 70, ydif = 70;
	xnum = 4;
	ynum = 4;
	nowselect = 0;
	cur_rate = 1;
	cur_x = 600;
	cur_y = 300;

	for(int i = 0; i < ynum; i++){
		for(int j = 0; j < xnum; j++){
			skill[i*4+j].setskill(x0+j*xdif, y0+i*ydif, j+4*i, ghandle);
		}
	}

	//画像読み込み
	LoadDivGraph2("levelup_icon.png", 16, 4, 4, 40, 40, ghandle);
	ghandle[20] = LoadGraph2("levelup_rect48.png");
	ghandle[21] = LoadGraph2("levelup_select48.png");
	ghandle[22] = LoadGraph2("levelup_rect48_black.png");
	ghandle[23] = LoadGraph2("levelup_get.png");
	ghandle[24] = LoadGraph2("levelup_getskill.png");
	ghandle[25] = LoadGraph2("levelup_getskill2.png");
	ghandle[30] = LoadGraph2("levelup_back.png");
	ghandle[40] = LoadGraph2("levelup_nextwave.png");
	ghandle[41] = LoadGraph2("levelup_nextwave2.png");

	timecount = 0;
}

//スキル習得によるステータス上昇
void levelup::statusup(){
	
	std::ostringstream  os;
	os << skill[nowselect].name << "を会得した";

	ptr->mstr_log->add(os.str());

	switch (nowselect)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		ptr->mplayer->hpmax += 10;
		ptr->mplayer->hp = ptr->mplayer->hpmax;
		break;
	case 3:
		ptr->mplayer->hpmax += 10;
		ptr->mplayer->hp = ptr->mplayer->hpmax;
		break;
	case 4:
		ptr->mstone->hpmax += 10;
		ptr->mstone->hp = ptr->mstone->hpmax;
		break;
	case 5:
		ptr->mstone->hpmax += 10;
		ptr->mstone->hp = ptr->mstone->hpmax;
		break;
	case 6:
		ptr->mplayer->atk += 1;
		break;
	case 7:
		ptr->mplayer->atk += 1;
		break;
	case 8:
		ptr->mplayer->atk += 1;
		break;
	case 9:
		ptr->mplayer->bulletmax += 20;
		break;
	case 10:
		ptr->mplayer->bulletmax += 20;
		break;
	case 11:
		ptr->mplayer->reloadneed -=30;
		break;
	case 12:
		ptr->mplayer->reloadneed -=30;
		break;
	case 13:
		ptr->mplayer->firerate -=1;
		break;
	case 14:
		ptr->mplayer->firerate -=1;
		break;
	case 15:
		ptr->mplayer->movespeed += 0.4;
		break;
	}
}

//スキル入手　drawexplainとセット
void levelup::getskill(){
	if(skill[nowselect].flugbuy == 0 && (unsigned)skill[nowselect].needexp <= ptr->mplayer->exp){
		if(ClashRect(400+350/2, 400+100, 200, 40, mousex, mousey) && keystate[250] == 1){
			statusup();
			PlaySoundMem(SHandle[10], DX_PLAYTYPE_BACK );
			ptr->meffect->make(0,0,9,-1,-1);
			ptr->mplayer->exp -= skill[nowselect].needexp;
			skill[nowselect].flugbuy = 1;
		}
	}
}

void levelup::drawexplain(){
	//説明文
	//int x0 = mousex, y0 = mousey;
	int x0 = 400, y0 = 400;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 128 ) ;SetDrawBright(255,255,255);
	DrawBox(x0, y0, x0+350, y0+128, 0x000000, 1); 
	if(nowselect != -1){
		DrawRotaGraph(x0+40, y0+40, 1.0, 0.0, ghandle[20], 1);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;SetDrawBright(255,128,0);
		DrawRotaGraph(x0+40, y0+40, 1.0, 0.0, ghandle[nowselect], 1);

		if(skill[nowselect].flugbuy == 0){
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255,255,255);
			if((unsigned)skill[nowselect].needexp <= ptr->mplayer->exp){
				if(ClashRect(x0+350/2, y0+100, 200, 40, mousex, mousey)){
					DrawRotaGraph(x0+350/2, y0+100, 1.0, 0.0, ghandle[25], 1);
				}else{
					DrawRotaGraph(x0+350/2, y0+100, 1.0, 0.0, ghandle[24], 1);
				}
			}else{
				DrawFormatStringToHandle(x0+100, y0+80, 0xFF8800, FontHandle[0] , "EXP不足") ;
			}
		}

		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;SetDrawBright(255,255,255);
		int strx = x0+80, stry = y0+20;
		stry -=30;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "*%s*", skill[nowselect].name.c_str() ) ;
		if(skill[nowselect].flugbuy == 0){
			DrawFormatStringToHandle(strx, stry+=20, 0xFF8800, FontHandle[0] , "必要EXP: %d (現在EXP: %d)", skill[nowselect].needexp , ptr->mplayer->exp) ;
		}else{
			DrawFormatStringToHandle(strx, stry+=20, 0xFF8800, FontHandle[0] , "*入手済み*") ;
		}
		SetDrawBright(255,255,255);
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "%s", skill[nowselect].explain.c_str() ) ;
	}

	//DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "クリックでEXPを消費してスキル入手") ;
}

//ステージに戻る
void levelup::resume(){
	int x0 = 80+128, y0 = 600-64-80;
	if( ClashRect(x0, y0, 256, 128, mousex, mousey) && keystate[250] == 1 ){
		//スキル入手していればHP回復
		if(skill[0].flugbuy == 1){
			ptr->mplayer->heal(0.3);
			ptr->mstr_log->add("HPが回復した [安息の福音] ");
		}
		if(skill[1].flugbuy == 1){
			ptr->mstone->heal(0.3);
			ptr->mstr_log->add("聖石のHPが回復した [再結晶化] ");
		}

		ptr->meffect->make(0, 0, 8, 0, 0);
		ptr->mplayer->reloadcool = ptr->mplayer->reloadneed;//←危ない
		StopSoundMem(SHandle[12]);

		timecount = 0;
		gamestate = 20;
	}
}

void levelup::drawresume(){
	int x0 = 80+128, y0 = 600-64-80;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 230 ) ;SetDrawBright(255,255,255);
	if(ClashRect(x0, y0, 256, 128, mousex, mousey)){
		DrawRotaGraph(x0, y0, 1.0, 0, ghandle[41], 1);
	}else{
		DrawRotaGraph(x0, y0, 1.0, 0, ghandle[40], 1);
	}
}

void levelup::update(){

	timecount++;
	if(timecount == 30){
		PlaySoundMem(SHandle[12], DX_PLAYTYPE_LOOP );	
	}


	int nowselectlog = nowselect;
	for(int i = 0; i < skillnum; i++){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 100 ) ;
		if(skill[i].update()){
			nowselect = i;
		}
	}
	if(nowselect != -1){
		moverate(cur_x, skill[nowselect].x, 0.4);
		moverate(cur_y, skill[nowselect].y, 0.4);
	}
	if(keystate[17] == 1)nowselect -= 4;
	if(keystate[31] == 1)nowselect += 4;
	if(keystate[30] == 1)nowselect -= 1;
	if(keystate[32] == 1)nowselect += 1;
	if(nowselect < 0){nowselect = 0;}
	if(nowselect > 15){nowselect = 15;}

	if(nowselect != nowselectlog){
		PlaySoundMem(SHandle[0], DX_PLAYTYPE_BACK );	
	}

	getskill();
	resume();
	ptr->meffect->update();
	ptr->mstr_log->update();
}

void levelup::drawstatus(){
	if(1){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;SetDrawBright(255,255,255);
		int strx = 80;
		int stry = 60;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "*ステータス*") ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "EXP: %d", ptr->mplayer->exp) ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "HP: %d/%d", ptr->mplayer->hp, ptr->mplayer->hpmax) ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "聖石HP: %d/%d", ptr->mstone->hp, ptr->mstone->hpmax) ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "弾発射間隔: %.1lf per sec", 60.0 / ptr->mplayer->firerate) ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "リロード時間: %.1lf sec", ptr->mplayer->reloadneed / 60.0) ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "装填弾数: %d", ptr->mplayer->bulletmax) ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "弾丸威力: %d00", ptr->mplayer->atk) ;
		DrawFormatStringToHandle(strx, stry+=20, 0xFFFFFF, FontHandle[0] , "移動速度: %.0lf", ptr->mplayer->movespeed*10) ;
	}
}

void levelup::draw(){
	//背景
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;SetDrawBright(255,255,255);
	DrawGraph(0, 0, ghandle[30], 1);
	//アイコン
	SetDrawBlendMode( DX_BLENDMODE_ADD , 30 ) ;SetDrawBright(0,128,200);
	DrawRotaGraph(400, 300, 8, keika * 0.01, ghandle[nowselect], 1);
	SetDrawScreen(zanzou);
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 20 ) ;
	DrawBox(0, 0, 800, 600, 0x000000, 1);
	SetDrawBlendMode( DX_BLENDMODE_ADD , 100 ) ;SetDrawBright(0,128,200);
	DrawRotaGraph(400, 300, 8, keika * 0.01, ghandle[nowselect], 1);
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;SetDrawBright(255,255,255);
	DrawRotaGraph(400, 300, 1.05, 0, zanzou, 1);
	DrawRotaGraph(400, 300, 1, 0.01, zanzou, 1);
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode( DX_BLENDMODE_ADD , 50 ) ;
	DrawGraph(0, 0, zanzou, 1);
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;SetDrawBright(255,255,255);
	DrawFormatStringToHandle(x0, y0-48-20-20, 0xFFFFFF, FontHandle[0] , "クリックでスキルを選択し、") ;
	DrawFormatStringToHandle(x0, y0-48-20, 0xFFFFFF, FontHandle[0] , "GET SKILLでスキルを入手できます") ;

	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 100 ) ;
	int dif = 40;
	DrawBox(x0-dif, y0-dif, x0+3*xdif+dif, y0+3*ydif+dif, 0x000000, 1);

	//アイコン
	for(int i = 0; i < skillnum; i++){
		skill[i].draw();
	}

	//現在選択に四角カーソル表示
	if(nowselect != -1){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(200+50*sin(keika*0.1)) );	SetDrawBright(255,255,255);
		DrawRotaGraph((int)(cur_x), (int)(cur_y), 1.0, 0, ghandle[21], 1);
	}

	drawexplain();
	drawresume();
	drawstatus();

	ptr->meffect->draw();
	ptr->mstr_log->draw();
}

