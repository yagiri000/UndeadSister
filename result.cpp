#pragma once

#include "result.h"

result::result(){
	counttime = 0;
}

void result::update(){
	counttime++;

	//�I��
	if(keystate[KEY_INPUT_SPACE] == 1){	gamestate = 44;	}
	ptr->meffect->update();
}

void result::draw(){
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 100 ) ;	SetDrawBright(255,255,255);
	DrawRotaGraph(400, 300, 1, 0, GHandle[11] , 1);

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255,255,255);
	int stry = 60;
	int wdx;
	wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  "RESULT"));
	DrawFormatStringToHandle((int)400-wdx, (int)stry, 0xFFFFFF, FontHandle[1] , "RESULT") ;
	stry+= 80;
	wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  "�|�����]���r��: %d", ptr->menemy->dienum));
	DrawFormatStringToHandle((int)400-wdx, (int)stry, 0xFFFFFF, FontHandle[1] , "�|�����]���r��: %d", ptr->menemy->dienum) ;
	stry+= 80;
	wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  "�ݐόo���l: %d", ptr->mplayer->expsum));
	DrawFormatStringToHandle((int)400-wdx, (int)stry, 0xFFFFFF, FontHandle[1] , "�ݐόo���l: %d", ptr->mplayer->expsum) ;
	stry+= 80;
	wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  "��_���[�W��: %d", ptr->menemy->damagenum));
	DrawFormatStringToHandle((int)400-wdx, (int)stry, 0xFFFFFF, FontHandle[1] , "��_���[�W��: %d", ptr->menemy->damagenum) ;
	stry+= 80;
	wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  "�����X�R�A: %ld", ptr->menemy->dienum*1000 + ptr->mplayer->expsum*10 - ptr->menemy->damagenum*200));
	DrawFormatStringToHandle((int)400-wdx, (int)stry, 0xFFFFFF, FontHandle[1] , "�����X�R�A: %ld", ptr->menemy->dienum*1000 + ptr->mplayer->expsum*10 - ptr->menemy->damagenum*200) ;
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(128+128*sin(keika*0.05) ) ) ;	
	wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  "THANK YOU FOR PLAYING!!"));
	DrawFormatStringToHandle((int)400-wdx, (int)460, 0xFFFFFF, FontHandle[1] , "THANK YOU FOR PLAYING!!") ;
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255,255,255);
	wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[0],  "[�X�y�[�X�L�[�ŏI��]"));
	DrawFormatStringToHandle((int)400-wdx, (int)550, 0xFF8800, FontHandle[0] , "[�X�y�[�X�L�[�ŏI��]") ;

	ptr->meffect->draw();
}