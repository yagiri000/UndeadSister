#pragma once

#include "define.h"
#include "DxLib.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "player.h"
#include "original_func.h"
#include "str_log.h"
#include "ptr_list.h"
#include "effect.h"

class manager{
public:
	ptr_list *ptr;
	void getptr(ptr_list *get_ptr){ptr = get_ptr;}
	manager();
	unsigned long wavetime;
	unsigned long wavetimemax;//�]���r���|�b�v����t���[����
	unsigned long clearedtime;//WAVE�N���A���Ă���̎���
	int wave;
	void makewave();
	void wavestart();
	void cleared();
	void makezombie(int f, int kind);//f�͎���
	void makezombie(int x, int y,int f, int kind);//f�͎���
	void update();
	void draw();

};
