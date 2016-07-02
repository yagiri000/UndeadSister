#pragma once

#include "define.h"
#include <DxLib.h>
#include <iostream>
#include <string>
#include "player.h"
#include "original_func.h"
#include "enemy.h"
#include "effect.h"
#include "str_log.h"
#include "ptr_list.h"
#include "manager.h"
#include "saintstone.h"
#include "bar.h"
#include "title.h"
#include "levelup.h"
#include "result.h"
#include "dying.h"
#include "explain.h"

char buf[256] = {0};//キー取得用
int keystate[256] = {0};
int GHandle[99];
int SHandle[99];
int efGHandle[99];
int FontHandle[99];
int mousex = 0, mousey = 0;//マウス座標
int zanzou;
unsigned long keika = 0;
int gamestate = 0;


int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	ChangeWindowMode( TRUE );
	SetGraphMode( 800 , 600 , 32 );
	SetOutApplicationLogValidFlag( FALSE ) ;//logを生成しないように設定
	if(DxLib_Init() == 1){return -1;}
	SetDrawScreen( DX_SCREEN_BACK ) ;
	SetWindowIconID( 101 ) ;
	SetMainWindowText( "UNDEAD SISTER" ) ;
	load_png_wav();//音・画像読み込み
	
	SetMouseDispFlag( FALSE ) ;//マウス非表示

	player jiki;
	enemy enemy;
	ptr_list ptr;
	effect effect;
	str_log str_log;
	manager manager;
	saintstone stone;
	bar bar;
	title title;
	levelup levelup;
	result result;
	dying dying;
	explain explain;

	ptr.getptr(&jiki, &enemy, &effect, &str_log, &stone);
	
	jiki.getptr(&ptr);
	enemy.getptr(&ptr);
	manager.getptr(&ptr);
	bar.getptr(&ptr);
	levelup.getptr(&ptr);
	result.getptr(&ptr);
	dying.getptr(&ptr);
	explain.getptr(&ptr);

	while( ProcessMessage()==0)
	{
		ClearDrawScreen();//裏画面消す

		GetMousePoint( &mousex, &mousey ); //マウス座標更新
		keyupdate();//キー更新
		keika++;



		switch (gamestate)
		{
		case 0://タイトル
			title.update();
			title.draw();
			break;


		case 10://説明スライド
			explain.update();
			explain.draw();
			break;


		case 20://ゲーム部分
			jiki.update();
			enemy.update();
			stone.update();
			effect.update();
			str_log.update();
			manager.update();

			drawzanzou();
			jiki.draw();
			enemy.draw();
			stone.draw();
			effect.draw();
			str_log.draw();
			bar.draw();
			manager.draw();
			break;


		case 21://ポーズ
			if(keystate[KEY_INPUT_SPACE] == 1){
				PlaySoundMem(SHandle[9], DX_PLAYTYPE_BACK );
				keystate[KEY_INPUT_SPACE]++; 
				gamestate = 20;
			}
			drawzanzou();
			jiki.draw();
			enemy.draw();
			stone.draw();
			effect.draw();
			str_log.draw();
			bar.draw();
			manager.draw();
			break;

		case 22://強化
			levelup.update();
			levelup.draw();
			break;

		case 29://死亡→リザルト移行
			dying.update();
			dying.draw();
			break;


		case 30://リザルト（死亡した後にここへ）
			result.update();
			result.draw();
			
			break;
		}
		
		//終了
		if(gamestate == 44){ break; }
		


		//マウス画像表示
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;SetDrawBright(255,255,255);
		DrawRotaGraph(mousex, mousey, 1.0, 0, GHandle[10], 1);


		//デバッグ用パラメータ表示
		//DrawFormatStringToHandle(20, 50, 0xFFFFFF, FontHandle[0] , "W:%d 被:%d 倒:%d 累:%d", manager.wave, enemy.damagenum, enemy.dienum, jiki.expsum) ;

		if(DEBUG == 1){
			//デバッグ用 マウス位置表示
			if(keystate[44] > 0){
				SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;SetDrawBright(255,255,255);
				int stry = 200;
				DrawFormatStringToHandle(20, stry+=20, 0xFFFFFF, FontHandle[0] , "MX:%3d MY:%3d", mousex,mousey) ;
			}

			//デバッグ用　ゾンビ生成
			//if(keystate[251] == 1){enemy.make(mousex, mousey, 0);}
			
			//デバッグ用　EXP上書き WAVE上書き
			if(keika == 1){
				jiki.exp = 17000;
				manager.wave = 9;
				gamestate = 22;
				str_log.add("[デバッグ][from main]WAVE修正 EXP修正");
			}
			//デバッグ用　ゾンビHP表示
			if(keystate[44] > 0){
				for(auto i : enemy.v){
					int wdx = (int)(0.5 *GetDrawFormatStringWidthToHandle(FontHandle[0],  "%d", i.hp));
					DrawFormatStringToHandle((int)i.x-wdx, (int)i.y-10, 0xFFFFFF, FontHandle[0] , "%d", i.hp) ;
				}
			}
		}
		

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}

