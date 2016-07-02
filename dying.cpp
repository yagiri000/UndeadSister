#pragma once

#include "dying.h"

dying::dying(){
	diedtime = 0;
}

void dying::startdying(){		
	//ptr->mstr_log->add("死んでしまった。");
	ptr->mstr_log->addbigstr("YOU DIED...", "you can live eternally as zombie...");
	StopSoundMem(SHandle[90]);
	PlaySoundMem(SHandle[7], DX_PLAYTYPE_BACK );
	int x1 = (int)ptr->mplayer->x;
	int y1 = (int)ptr->mplayer->y;
	for(int i = 0; i < 30; i++){ ptr->meffect->make(x1, y1, 4, -1, -1);}
	SetDrawScreen( zanzou ) ;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;
	for(int i = 0; i < 15; i++){
		double angle = PI * randarc();
		double rr = 30*randarc();
		DrawRotaGraph((int)(x1+rr*cos(angle)), (int)(y1+rr*sin(angle)), randarc()*1.0+0.7, PI*randarc(), GHandle[7], 1);
	}
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
	SetDrawScreen( DX_SCREEN_BACK ) ;
}

void dying::update(){
	diedtime++;

	//死んだ瞬間の処理
	if(diedtime == 1){startdying();}

	//一定時間経過でリザルトへ移行
	if(diedtime > 360){
		ptr->meffect->make(0, 0, 10, 0, 0);
		gamestate = 30;
	}

	//血を出す
	if((keika % 3)== 0){
		ptr->meffect->make((int)ptr->mplayer->x, (int)ptr->mplayer->y, 4, -1, -1);
		SetDrawScreen( zanzou ) ;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;
		DrawRotaGraph((int)ptr->mplayer->x, (int)ptr->mplayer->y, randarc()*1.0+0.7, PI*randarc(), GHandle[7], 1);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
		SetDrawScreen( DX_SCREEN_BACK ) ;
	}


	ptr->menemy->update();
	ptr->meffect->update();
	ptr->mstr_log->update();
}

void dying::draw(){

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
	drawzanzou();
	DrawRotaGraph((int)ptr->mplayer->x, (int)ptr->mplayer->y, 2, PI*0.5, ptr->mplayer->p_GHandle[0], 1);
	ptr->menemy->draw();
	ptr->mstone->drawdiedstone();
	ptr->meffect->draw();
	ptr->mstr_log->draw();
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(255.0 * (diedtime-240) / 80.0) ) ;
	DrawBox(0,0,800,600, 0x000000, 1);

}

/*

enemy.update();
effect.update();
str_log.update();
dying.update();

drawzanzou();
dying.draw();
enemy.draw();
effect.draw();
str_log.draw();
*/