#pragma once

#include "title.h"

title::title(){
	nowselect = -1;
	ghandle[0] = LoadGraph2("title.png");
	LoadDivGraph2("titlestr1.png", 2, 1, 2, 100, 90/3, &ghandle[10]);
	LoadDivGraph2("titlestr2.png", 2, 1, 2, 36, 24/2, &ghandle[20]);
}

void title::update(){
	int nowselectlog = nowselect;
	nowselect = -1;
	for(int i = 0; i < 3; i++){
		int x0 = 400;
		int y0 = 400+50*i;
		if(ClashRect(x0, y0, 100, 50, mousex, mousey) ){
			nowselect = i;
		}
	}
	if(nowselect != -1 && nowselect != nowselectlog){
		PlaySoundMem(SHandle[0], DX_PLAYTYPE_BACK );
	}
	
	//à–¾ƒXƒ‰ƒCƒh‚Ö
	if(keystate[250] == 1 && nowselect == 0){
		gamestate = 10;
		PlaySoundMem(SHandle[0], DX_PLAYTYPE_BACK );
	}
	if(keystate[250] == 1 && nowselect == 1){
		PlaySoundMem(SHandle[0], DX_PLAYTYPE_BACK );
		DxLib_End();
	}
}

void title::draw(){
	DrawGraph(0, 0, ghandle[0], 1);

	for(int i = 0; i < 2; i++){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 250 ) ;SetDrawBright(255,255,255);
		int x0 = 400;
		int y0 = 400+50*i;
		DrawRotaGraph(x0, y0, 1.0, 0, ghandle[10+i], 1);
		DrawRotaGraph(x0, y0+15, 1.0, 0, ghandle[20+i], 1);
		if(i == nowselect){
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(50+10*sin(keika*0.1)) ) ;SetDrawBright(255,255,255);
			DrawRotaGraph3(x0, y0+5, 50, 50, 8.0, 0.5, 0, GHandle[0], 1);
		}
	}
}