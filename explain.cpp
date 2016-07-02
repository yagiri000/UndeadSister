#pragma once

#include "explain.h"

explain::explain(){
	counttime = 0;
	nowselect = 0;
	x0 = 400, y0 = 550;
	ghandle[0] = LoadGraph2("explain.png");
	ghandle[1] = LoadGraph2("explain_str.png");
}

void explain::update(){
	counttime++;
	if(counttime == 1){
		ptr->meffect->make(0, 0, 8, -1, -1);
	}
	nowselect = -1;
	if(ClashRect(x0, y0, 800, 50, mousex, mousey) ){
		nowselect = 1;
	}

	//ƒQ[ƒ€–{•Ò‚Ö
	if(keystate[250] == 1 && nowselect == 1){
		gamestate = 20;
		PlaySoundMem(SHandle[0], DX_PLAYTYPE_BACK );
	}
	ptr->meffect->update();
}

void explain::draw(){
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;SetDrawBright(255,255,255);

	DrawGraph(0, 0, ghandle[0], 1);
	DrawRotaGraph(x0, y0, 1.0, 0, ghandle[1], 1);
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(50+30*sin(keika*0.1)) ) ;SetDrawBright(255,255,255);
	DrawRotaGraph3(x0, y0, 50, 50, 8.0, 0.5, 0, GHandle[0], 1);

	if(nowselect == 1){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(50+30*sin(keika*0.1)) ) ;SetDrawBright(255,255,255);
		DrawRotaGraph3(x0, y0, 50, 50, 8.0, 0.5, 0, GHandle[0], 1);
	}
	
	ptr->meffect->draw();
}