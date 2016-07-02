#pragma once

#include "define.h"
#include <DxLib.h>
#include <iostream>
#include <string>



void keyupdate();

//鮮やかな色のコードを返却 HUEで指定 360MAX
long gethsv(int hue);

//鮮やかな色に描画色指定 HUEで指定 360MAX
void SetDrawBrightHSV(int hue);

//2点の距離を返す
double dist(double x1, double y1, double x2, double y2);

//始点　終点　長方形の辺の長さ　結果を返す配列(要素4以上)
void LineToModi(double x1, double y1, double x2, double y2, double r, int *xx, int *yy);


//円と線の当たり判定　始点・終点・円の中心点・半径
bool ClashCircleLine(double sx, double sy, double ex, double ey, double cx, double cy, double rr);

//長方形と点の当たり判定 長方形中心・高さ・横幅　対象点の座標
bool ClashRect(int x, int y, int width, int height, int targetx, int targety);

//画像読み込み
void load_png_wav();

//-1 ~ 1のどれかを返す
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

//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0
void moverate(double &x, double tarx, double rate);