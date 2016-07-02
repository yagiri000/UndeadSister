#pragma once

#include "define.h"
#include <DxLib.h>
#include <iostream>
#include <string>



void keyupdate();

//�N�₩�ȐF�̃R�[�h��ԋp HUE�Ŏw�� 360MAX
long gethsv(int hue);

//�N�₩�ȐF�ɕ`��F�w�� HUE�Ŏw�� 360MAX
void SetDrawBrightHSV(int hue);

//2�_�̋�����Ԃ�
double dist(double x1, double y1, double x2, double y2);

//�n�_�@�I�_�@�����`�̕ӂ̒����@���ʂ�Ԃ��z��(�v�f4�ȏ�)
void LineToModi(double x1, double y1, double x2, double y2, double r, int *xx, int *yy);


//�~�Ɛ��̓����蔻��@�n�_�E�I�_�E�~�̒��S�_�E���a
bool ClashCircleLine(double sx, double sy, double ex, double ey, double cx, double cy, double rr);

//�����`�Ɠ_�̓����蔻�� �����`���S�E�����E�����@�Ώۓ_�̍��W
bool ClashRect(int x, int y, int width, int height, int targetx, int targety);

//�摜�ǂݍ���
void load_png_wav();

//-1 ~ 1�̂ǂꂩ��Ԃ�
double randarc();

double arcrand();

double arcrand(double a);

double st_rand();

double st_rand(double a);

void randnegpos(double &x);

int LoadGraph2(std::string str);
int LoadSoundMem2(std::string str);
void LoadDivGraph2(std::string str, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf);

void drawzanzou();

//���������_�Ɉړ��Arate�͎������瑊������ւ̈ړ��� 0.0 - 1.0
void moverate(double &x, double tarx, double rate);