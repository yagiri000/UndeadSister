#pragma once

#include "bar.h"

bar::bar(){
	ghandle[41] = LoadGraph2("bar_back.png");

	ghandle[50] = LoadGraph2("bar_bullet01.png");
	ghandle[51] = LoadGraph2("bar_bullet02.png");

	ghandle[61] = LoadGraph2("bar_hpbar01.png");
	ghandle[62] = LoadGraph2("bar_hpbar02.png");
	ghandle[63] = LoadGraph2("bar_hpbar03.png");
	ghandle[64] = LoadGraph2("bar_hpbar03d.png");
	LoadDivGraph2("bar_str.png", 3, 1, 3, 63, 15, &ghandle[70]);
}



void bar::update(){


}

void bar::drawhpbar(int x0, int y0, int now, int max, int kind){

	int rate = (int)(1.0 * now /max * 128);
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;
	DrawRotaGraph3(x0,y0,0,0,1.0,1.0,0,ghandle[61],1);
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;
	DrawRotaGraph3(x0,y0,0,0,1.0,1.0,0,ghandle[62],1);
	if(kind == 0){//HPバー（赤)
		DrawRectGraph(x0,y0,0,0, rate, 32, ghandle[63],1, 0);
	}else{//MPバー（青)
		DrawRectGraph(x0-rate+128,y0,0,0, rate, 32, ghandle[64],1, 1);
	}

}

void bar::drawstatus(){
	int x0 = 400, y0 = 22;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 100 ) ;
	DrawRotaGraph2(x0, 0, 256, 0, 1.0, 0, ghandle[41], 1);
	DrawRotaGraph2(-340+256, 600+10, 256, 0, 1.0, PI, ghandle[41], 1);

	//BULLETグラフ
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 120 ) ;
		DrawCircleGauge(x0, y0, 100, ghandle[51]);
	if(ptr->mplayer->reloadcool > 0){
		DrawCircleGauge(x0, y0, 100, ghandle[50],100.0*1.0*ptr->mplayer->reloadcool/ptr->mplayer->reloadneed);
	}else{
		DrawCircleGauge(x0, y0, 100, ghandle[50], 100.0-100.0*ptr->mplayer->bullet/ptr->mplayer->bulletmax);
	}

	//HPグラフ
	int y1 = y0;
	drawhpbar(x0+40, y1-4, ptr->mplayer->hp, ptr->mplayer->hpmax,0);
	drawhpbar(x0-40-128, y1-4, ptr->mstone->hp, ptr->mstone->hpmax, 1);
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 100 ) ;
	DrawRotaGraph3(x0-40-64, 27, 32, 0, 1.0, 1.0, 0.0, ghandle[70], 1); 
	DrawRotaGraph3(x0+40+64, 27, 32, 0, 1.0, 1.0, 0.0, ghandle[72], 1);
	
	DrawRotaGraph3(x0, 42, 32, 0, 1.0, 1.0, 0.0, ghandle[71], 1);

	//BULLET文字
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;
	if(ptr->mplayer->reloadcool > 0){
		int wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[0],  "-%.0lf-", 10.0*ptr->mplayer->reloadcool/ptr->mplayer->reloadneed ));
		DrawFormatStringToHandle((int)x0-wdx, (int)y0-10, 0xFFFFFF, FontHandle[0] , "-%.0lf-", 10.0*ptr->mplayer->reloadcool/ptr->mplayer->reloadneed) ;
	}else{
		int wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[0],  "%d", ptr->mplayer->bullet));
		DrawFormatStringToHandle((int)x0-wdx, (int)y0-10, 0xFFFFFF, FontHandle[0] , "%d", ptr->mplayer->bullet) ;
	}


	//EXP文字
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;
	DrawFormatStringToHandle(5, 600-30 , 0xFFFFFF, FontHandle[0] , "EXP: %d", ptr->mplayer->exp) ;

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255,255,255);

}

void bar::draw(){
	drawstatus();
}



