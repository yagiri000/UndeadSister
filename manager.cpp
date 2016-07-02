#pragma once

#include "manager.h"


manager::manager(){
	wavetime = 0;
	wavetimemax = 3600;
	clearedtime = 0;
	wave = 1;
}

//��ނ̂ݎw�肵�ă]���r����
void manager::makezombie(int f, int kind){
	if(wavetime%f == 0){
		double angle = -1*wavetime*0.3;
		if(cos(angle)<0){angle += PI;}
		ptr->menemy->make(900, 300+400*sin(angle), kind);
	}
}

//���W�w�肵�ă]���r����
void manager::makezombie(int x, int y,int f, int kind){
	if(wavetime%f == 0){
		ptr->menemy->make(x, y, kind);
	}
}


//wave���ƂɈ�����]���r�𐶐�
void manager::makewave(){

	switch (wave)
	{
	case 1:
		makezombie(190, 0);
		makezombie(257, 0);
		makezombie(310, 1);
		break;

	case 2:
		makezombie(111, 0);
		makezombie(190, 1);
		makezombie(310, 2);
		if(wavetime > 3300 ){
			makezombie(87, 1);
			makezombie(77, 2);
		}
		break;

	case 3:
		makezombie(91, 0);
		makezombie(131, 0);
		makezombie(171, 0);
		makezombie(700, 1);
		makezombie(350, 2);
		makezombie(400, 2);
		break;

	case 4:
		makezombie(211, 1);
		makezombie(271, 2);
		makezombie(111, 3);
		break;

	case 5:
		makezombie(97, 2);
		makezombie(111, 2);
		makezombie(571, 3);
		makezombie(177, 4);
		makezombie(311, 4);
		break;

	case 6:
		makezombie(191, 1);
		makezombie(191, 2);
		makezombie(411, 3);
		makezombie(194, 4);
		makezombie(241, 4);
		makezombie(911, 5);
		break;
		
	case 7:
		makezombie(223, 4);
		makezombie(309, 4);
		makezombie(1111, 5);
		makezombie(311, 6);
		makezombie(313, 7);
		if(wavetime>3000){
			makezombie(900, 600, 34, 0);
		}
		break;
		
	case 8:
		makezombie(223, 4);
		makezombie(811, 5);
		makezombie(199, 6);
		makezombie(411, 7);
		makezombie(453, 8);
		if(wavetime>2400){
			makezombie(131, 0);
			makezombie(133, 2);
		}
		break;
		
	case 9:
		makezombie(151, 2);
		makezombie(400, -100, 153, 2);
		makezombie(400, 600+100, 157, 2);
		makezombie(411, 8);
		makezombie(413, 9);
		if(wavetime>3500){
			makezombie(900, 300, 15, 4);
		}
		break;

	case 10:
		makezombie(250, 1);
		makezombie(300, 2);
		makezombie(270, 4);
		makezombie(280, 6);
		makezombie(600, 8);
		makezombie(300, 9);
		if(wavetime>3550){
			makezombie(900, 0, 10, 7);
			makezombie(900, 600, 10, 7);
		}
		break;
	}

	if(wave>10){
		makezombie(411-wave*20, 0);
		makezombie(1511-wave*20, 1);
		makezombie(413-wave*20, 2);
		makezombie(1511-wave, 3);
		makezombie(471-wave*20, 4);
		makezombie(1411-wave, 5);
		makezombie(513-wave*20, 6);
		makezombie(1611-wave, 7);
		makezombie(551-wave*20, 8);
		makezombie(553-wave*20, 9);
	}

}




//WAVE���n�܂��Ă����̏���
void manager::wavestart(){
	
	if(wavetime == 1){
		
		if(DEBUG == 1){
			ptr->mplayer->exp = 0;//�f�o�b�O�p ���Ƃŏ���
			ptr->mstr_log->add("[�f�o�b�O] EXP 0 ��");//�f�o�b�O�p ���Ƃŏ���
		}

		SetDrawScreen(zanzou);
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		ptr->meffect->make(0, 0, 8, 0, 0);

		if(wave == 1){
			ptr->mstr_log->add("*Welcome to underground*");
			ptr->mstr_log->add("[/W/A/S/D�ňړ��E�}�E�X�N���b�N�Ŏˌ�]");
		}
		if(2 <= wave && wave <= 5 ){
			ptr->mstr_log->add("[�X�y�[�X�L�[�ňꎞ��~]");
		}

		std::ostringstream os;
		os << "WAVE " << wave ;
		ptr->mstr_log->addbigstr(os.str(), "various zombies approaching...");
		PlaySoundMem(SHandle[6], DX_PLAYTYPE_BACK );	
	}
	if(wavetime == 400){
		PlaySoundMem(SHandle[90], DX_PLAYTYPE_LOOP );	
	}

}

void manager::cleared(){
	//WAVE�N���A������i�K�莞�Ԃ𒴂��ēG�|�b�v�������Ȃ�A�G��S�ł�������j
	if(wavetime > wavetimemax && ptr->menemy->v.size() == 0){
		clearedtime++;		//WAVE�N���A���Ă���̎��Ԃ����Z
	}
	if(clearedtime == 150){
		ptr->mstr_log->addbigstr("WAVE CLEAR", "you alive today... you are always strain.");
		StopSoundMem(SHandle[90]);
	}
	if(clearedtime == 150){
		PlaySoundMem(SHandle[11], DX_PLAYTYPE_BACK );	
	}

	if(clearedtime == 500){
		clearedtime = 0;
		wavetime = 0;
		wave++;
		gamestate = 22;
	}
}

void manager::update(){
	wavetime++;

	wavestart();

	cleared();



	//�K�莞�ԂɂȂ�܂Ń]���r���|�b�v
	if(wavetime < wavetimemax){	makewave(); }

	//�|�[�Y
	if(keystate[KEY_INPUT_SPACE] == 1){
		PlaySoundMem(SHandle[8], DX_PLAYTYPE_BACK );
		keystate[KEY_INPUT_SPACE]++; 
		gamestate = 21;
		ptr->meffect->make(0, 0, 8, 0, 0);
	}

	//���S������
	if(ptr->mplayer->hp <= 0 || ptr->mstone->hp <=0){
		gamestate = 29;
	}

}



void manager::draw(){
	int stry = 200;
	if(gamestate == 21){//�|�[�Y��
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 150 ) ;SetDrawBright(255,255,255);
		DrawBox(0,0,800,600,0x000000, 1);
		DrawBox(0,310-50,800,310+50,0x000000, 1);
		int wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[1],  "PAUSE"));
		DrawFormatStringToHandle((int)(400-wdx), (int)(300-20), 0xFF3333, FontHandle[1] , "PAUSE") ;
		wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[0],  "�X�y�[�X�L�[�Ń|�[�Y����"));
		DrawFormatStringToHandle((int)(400-wdx), (int)(300+20), 0xFF3333, FontHandle[0] , "�X�y�[�X�L�[�Ń|�[�Y����") ;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;SetDrawBright(255,255,255);
	}
}

