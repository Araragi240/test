/******************************************************************************
* File Name : game.h                             Ver : 1.00  Date : 2003-01-04
*
* Description :
*
*		簡易ゲームフレームワークヘッダファイル．
*
* Author : Moriharu Ohzu.
*
******************************************************************************/
#ifndef		_GAME_H_
#define		_GAME_H_

#include	<GL/glut.h>
#include	<gslib.h>

/*---- ウィンドウパラメータ -------------------------------------------------*/

#define	WINDOW_TITLE		"GameWindow"	/* ウィンドウタイトル	*/
#define	WINDOW_POSX			0				/* ウィンドウのｘ座標	*/
#define	WINDOW_POSY			0				/* ウィンドウのｙ座標	*/
#define	WINDOW_WIDTH		640				/* ウィンドウの幅		*/
#define	WINDOW_HEIGHT		480				/* ウィンドウの高さ		*/
#define	FULL_SCREEN_MODE	0				/* フルスクリーンモード	*/
#define	GAME_MODE_STRING	"640x480@60"	/* 画面モード			*/

/*---- 視野変換パラメータ ---------------------------------------------------*/

#define	PERSPECTIVE_FOV		50.0f			/* 視野角				*/
#define	PERSPECTIVE_NEAR	0.5f			/* 近クリップ面			*/
#define	PERSPECTIVE_FAR		100.0f			/* 遠クリップ面			*/

/*---- ウェイトタイマ -------------------------------------------------------*/

#define	FPS_WAIT_TIME		( 1000 / 60 )	/* ＦＰＳウェイトタイマ */

/****** 関数プロトタイプ宣言 *************************************************/

extern void gameInit( void );				/* ゲーム初期化処理		*/
extern void gameMain( void );				/* ゲームメイン処理		*/
extern void gameDraw( void );				/* ゲーム描画処理		*/
extern void gameFinish( void );				/* ゲーム終了処理		*/

#endif

/********** End of File ******************************************************/
