#pragma once

#include "str_log.h"

str_log::str_log(){
	fonthandle = CreateFontToHandle( "Segoe UI" , 16 , 5 ,DX_FONTTYPE_ANTIALIASING_4X4) ;
	ghandle[0] =  LoadGraph2("gra100_black.png");
	ghandle[1] =  LoadGraph2("gra100_black2.png");
	yshift = 0;
	ydif = 17;
	alpharate = 0;
	bigstrtime = 0;
	bigstralpha = 0;
	x0 = 20;
	y0 = (int)(600-ydif-5);
}

void str_log::add(std::string addstr){
	alpharate = 1;
	yshift = ydif;
	for(int i = 7; i >= 0; i--){
		str[i+1] = str[i];
	}
	str[0] = addstr;
}

//‰æ–Ê’†‰›‚É‘å‚«‚È•¶Žš‚ð•`‰æŠJŽn
void str_log::addbigstr(std::string str, std::string ministr){
	bigstrtime = 600;
	bigstr = str;
	bigstr_under = ministr;
}

void str_log::setbigalpha(){
	if(bigstrtime > 600-120){
		bigstralpha = (600 - bigstrtime) * 2; 
	}else if(bigstrtime > 120){
		bigstralpha = 240;
	}else{
		bigstralpha = bigstrtime * 2;
	}
}


void str_log::update(){
	if(bigstrtime > 0){bigstrtime -= 2;}
	if(alpharate>0){alpharate -= 0.002;}
	if(yshift > 0){yshift -= 2.5;}
	if(yshift <0){yshift = 0;}
	setbigalpha();
}

void str_log::draw(){

	if(bigstrtime > 0){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(bigstralpha*0.7)) ;
		DrawRotaGraph3(400, 300, 50, 50, 8.0, 1.0, 0.0, ghandle[1], 1);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(bigstralpha)) ;
		int wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  bigstr.c_str()));
		DrawFormatStringToHandle((int)400-wdx, (int)300-30, 0xFFFFFF, FontHandle[1] , bigstr.c_str()) ;
		wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[0],  bigstr_under.c_str()));
		DrawFormatStringToHandle((int)(400-wdx), (int)(300+10), 0xFFFFFF, FontHandle[0] , bigstr_under.c_str()) ;
	}
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(100*alpharate)) ;
	DrawRotaGraph3(400, 600, 50, 100, 8.0, 1.0*0.6, 0, ghandle[0], 1);
	for(int i = 0; i < 3; i++){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)((200-(i*ydif - yshift)*2)*alpharate) ) ;
		int wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[0],  str[i].c_str()));
		DrawFormatStringToHandle(400-wdx, (int)(y0 - i * ydif + yshift), 0xFFFFFF, fonthandle , str[i].c_str()) ;
	}	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
}