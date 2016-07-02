#pragma once

#include "original_func.h"



void keyupdate()
{
	GetHitKeyStateAll(buf);
	buf[250] =  GetMouseInput() & MOUSE_INPUT_LEFT;
	buf[251] =  GetMouseInput() & MOUSE_INPUT_RIGHT ? 1 : 0;
	for(int i = 0; i< 256; i++)
	{
		if(buf[i] == 1) keystate[i]++;
		else keystate[i] = 0;
	}
}

//�N�₩�ȐF�̃R�[�h��ԋp HUE�Ŏw�� 360MAX
long gethsv(int hue){
	double k[3];
	for(int i = 0; i < 3; i++){
		k[i] = cos(3.14*(-120*i+hue)/360);
		k[i] = 255 * k[i] * k[i];
	}
	return GetColor((int)k[0],(int)k[1],(int)k[2]);
}

//�N�₩�ȐF�ɕ`��F�w�� HUE�Ŏw�� 360MAX
void SetDrawBrightHSV(int hue){
	double k[3];
	for(int i = 0; i < 3; i++){
		k[i] = cos(3.14*(-120*i+hue)/360);
		k[i] = 255 * k[i] * k[i];
	}
	SetDrawBright((int)k[0],(int)k[1],(int)k[2]);
}

//2�_�̋�����Ԃ�
double dist(double x1, double y1, double x2, double y2){
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

//�n�_�@�I�_�@�����`�̕ӂ̒����@���ʂ�Ԃ��z��(�v�f4�ȏ�)
void LineToModi(double x1, double y1, double x2, double y2, double r, int *xx, int *yy){
	double angle = atan2(y2-y1, x2-x1);
	double deg90 = 1.57079632679;
	xx[0] = (int)( x1 + r * cos(angle - deg90) );
	yy[0] = (int)( y1 + r * sin(angle - deg90) );
	xx[1] = (int)( x2 + r * cos(angle - deg90) );
	yy[1] = (int)( y2 + r * sin(angle - deg90) );
	xx[2] = (int)( x2 + r * cos(angle + deg90) );
	yy[2] = (int)( y2 + r * sin(angle + deg90) );
	xx[3] = (int)( x1 + r * cos(angle + deg90) );
	yy[3] = (int)( y1 + r * sin(angle + deg90) );
}



//�~�Ɛ��̓����蔻��@�n�_�E�I�_�E�~�̒��S�_�E���a
bool ClashCircleLine(double sx, double sy, double ex, double ey, double cx, double cy, double rr){
	if(dist(sx, sy, cx, cy) < rr || dist(ex, ey, cx, cy) < rr ){
		return 1;
	}else {
		double k = ey - sy;
		double l = ex - sx;
		if(!((k*cx-l*cy-k*sx+l*sy)*(k*cx-l*cy-k*sx+l*sy) < rr * rr * (k*k+l*l))){
			return 0;
		}
		if(((sx-cx)*(ex-cx)+(sy-cy)*(ey-cy) ) < 0  ){
			return 1;
		}
	}
	return 0;
}

bool ClashRect(int x, int y, int width, int height, int targetx, int targety){
	if(2 * abs(targetx - x) < width && 2*abs(targety - y) < height){
		return true;
	}else{
		return false;
	}
}

double randarc(){
	return -1 + 0.0002 * GetRand(10000);
}

double arcrand(){
	return -1.0+ GetRand(20000)*0.0001;
}
double arcrand(double a){
	return a * (-1.0+ GetRand(20000)*0.0001);
}

double st_rand(){
	return (arcrand()+arcrand()+arcrand()+arcrand())*0.25;
}

double st_rand(double a){
	return (arcrand()+arcrand()+arcrand()+arcrand())*0.25*a;
}

void randnegpos(double &x){
	if(GetRand(1) == 1)
		x = -x;
}

//�n�ʁE���̎c�����C���[�`��E�X�V
void drawzanzou(){
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255, 255, 255);
	DrawRotaGraph2(0, 0, 0, 0, 1.9, 0.0, GHandle[3], 1);//�n��
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(150, 150, 150);
	DrawGraph(0,0,zanzou,1);

	SetDrawScreen( zanzou ) ;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;	SetDrawBright(255, 255, 255);
	if(keika % 2 == 0){
		int vv = 1;
		DrawRotaGraph(400+vv, 300, 1.0, 0, zanzou, 1);
		DrawRotaGraph(400-vv, 300, 1.0, 0, zanzou, 1);
		DrawRotaGraph(400, 300+vv, 1.0, 0, zanzou, 1);
		DrawRotaGraph(400, 300-vv, 1.0, 0, zanzou, 1);
	}
	if(keika % 30 == 0){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 8 ) ;
		//DrawBox(0,0,800,600,0xA08050,1);
		DrawRotaGraph2(0, 0, 0, 0, 1.9, 0.0, GHandle[3], 1);//�n��
	}
	SetDrawScreen( DX_SCREEN_BACK ) ;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
}


void load_png_wav(){
	GHandle[0] = LoadGraph2("rect100.png");
	GHandle[1] = LoadGraph2("dot100.png");
	GHandle[3] = LoadGraph2("suna.png");
	GHandle[6] = LoadGraph2("fog01.png");
	GHandle[7] = LoadGraph2("blood01.png");
	GHandle[10] = LoadGraph2("mousetarget.png");
	GHandle[11] = LoadGraph2("ruin(90).png");
	
	zanzou = MakeScreen(800,600,TRUE);

	efGHandle[0] = LoadGraph2("dot32.png");
	efGHandle[1] = LoadGraph2("senkou.png");
	efGHandle[2] = LoadGraph2("fireboost02.png");
	efGHandle[3] = LoadGraph2("blood01.png");
	efGHandle[4] = LoadGraph2("dot32_black.png");
	efGHandle[5] = LoadGraph2("light01.png");
	efGHandle[6] = LoadGraph2("rect32_black.png");
	efGHandle[7] = LoadGraph2("rect32.png");

	SHandle[0] = LoadSoundMem2("cut00.wav") ;//���j���[�I��ύX��
	SHandle[1] = LoadSoundMem2("gun30_r.wav") ;//�e��
	SHandle[2] = LoadSoundMem2("bosu34.wav") ;//�G���j��
	SHandle[3] = LoadSoundMem2("zusa.ogg") ;//��e��
	SHandle[4] = LoadSoundMem2("kachi18_r.wav") ;//�����[�h�J�n
	SHandle[5] = LoadSoundMem2("kachi22.wav") ;//�����[�h�I��
	SHandle[6] = LoadSoundMem2("magicstart.ogg") ;//WAVE�J�n
	SHandle[7] = LoadSoundMem2("sousou3.ogg") ;//�Q�[���I�[�o�[��
	SHandle[8] = LoadSoundMem2("enter16.ogg") ;//�|�[�Yin
	SHandle[9] = LoadSoundMem2("cancel7.ogg") ;//�|�[�Yout
	SHandle[10] = LoadSoundMem2("soundlogo1.ogg") ;//�X�L������
	SHandle[11] = LoadSoundMem2("soundlogo5.ogg") ;//wave�N���A��
	SHandle[12] = LoadSoundMem2("thinking.ogg") ;//���j���[
	SHandle[90] = LoadSoundMem2("bgm01.ogg") ;//�퓬��BGM

	
	FontHandle[0] = CreateFontToHandle( "Segoe UI" , 18 , 5 ,DX_FONTTYPE_ANTIALIASING_4X4) ;
	FontHandle[1] = CreateFontToHandle( "Segoe UI" , 40 , 5 ,DX_FONTTYPE_ANTIALIASING_4X4) ;
}

int LoadGraph2(std::string str){
	str = "source/" + str;
	return  LoadGraph(str.c_str());
}

int LoadSoundMem2(std::string str){
	str = "source/" + str;
	return  LoadSoundMem(str.c_str());
}


void LoadDivGraph2(std::string str, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf){
	str = "source/" + str;
	LoadDivGraph(str.c_str(), AllNum, XNum, YNum, XSize, YSize, HandleBuf);
}

//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0
void moverate(double &x, double tarx, double rate){
	x = x * (1 - rate) + tarx * rate;
	if(abs(x-tarx) < 2){
		x = tarx;
	}
}
