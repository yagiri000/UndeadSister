#pragma once
#include <iostream>

const int DEBUG = 0;

const double PI = 4 * atan(1);
const double arcrad = PI / 180;
const int linemax = 100;

extern int GHandle[99];
extern int efGHandle[99];
extern int zanzou;
extern int SHandle[99];
extern int FontHandle[99];
extern int mousex, mousey;
extern unsigned long keika;
extern int gamestate;

extern char buf[256];
extern int keystate[256];


class ptr_list;
class player;
class enemy;
class enemyparts;
class effect;
class str_log;
class manager;
class saintstone;
class bar;