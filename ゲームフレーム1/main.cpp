/******************************************************************************
* File Name : main.c                             Ver : 1.00  Date : 2003-04-05
*
* Description :
*
*		簡易ゲームフレームワーク．
*
* Author : Moriharu Ohzu.
*
******************************************************************************/
#include	"game.h"

/****** リンカオプション *****************************************************/

#pragma comment( linker, "/entry:mainCRTStartup" )
#pragma comment( linker, "/SUBSYSTEM:WINDOWS"    )

/****** 関数プロトタイプ宣言 *************************************************/

static void	myInitFunc( void );
static void	myDestoryFunc( void );
static void	myReshapeFunc( int width, int height );
static void	myIdleFunc( void );
static void	myDisplayFunc( void );
static void	myActivateFunc( int state );
static GSboolean gsSwapInterval( GSint Interval );

/*=============================================================================
*
* Purpose : 簡易ゲームフレームワークメイン処理．
*
* Return  : なし．
*
*============================================================================*/
void main( int argc, char *argv[] )
{
	/* ＯｐｅｎＧＬウィンドウを初期化して開く */
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition( WINDOW_POSX, WINDOW_POSY );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );

#if	FULL_SCREEN_MODE
	/* フルスクリーンモード */
	glutGameModeString( GAME_MODE_STRING );
	glutEnterGameMode();
	/* フルスクリーンの場合はマウスカーソルを消す*/
	glutSetCursor(GLUT_CURSOR_NONE);
#else
	/* ウィンドウモード */
	glutCreateWindow( WINDOW_TITLE );
#endif

	/* グラフィックスシステムの初期化 */
	gsInitGraphics();

	/* サウンドシステムの初期化 */
	gsInitSound( (HWND)_glutGetHWND() );

	/* 入力デバイスシステムの初期化 */
	gsInitInput( (HWND)_glutGetHWND() );

	/* Ｖｓｙｎｃを有効にする */
	gsSwapInterval( 1 );

	/* システムの初期化 */
	myInitFunc();

	/* 終了処理の関数を設定する */
	_glutDestroyFunc( myDestoryFunc );

	/* ウィンドウサイズ変更時の関数を設定 */
	glutReshapeFunc( myReshapeFunc );

	/* 表示処理の関数を設定 */
	glutDisplayFunc( myDisplayFunc );

	/* イベントのない時の関数を設定 */
	glutIdleFunc( myIdleFunc );

	/* ウィンドウがアクティブになった時の関数を設定 */
	_glutActivateFunc( myActivateFunc );

	/* フレームタイマのリセット */
	gsFrameTimerReset();

	/* メインループ処理を行う */
	glutMainLoop();
}

/*-----------------------------------------------------------------------------
*
* Purpose : 初期化処理．
*
* Return  : なし．
*
*----------------------------------------------------------------------------*/
static void myInitFunc( void )
{
	/* デフォルトのライトパラメータ */
	static float	LightAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	static float	LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	static float	LightSpeclar[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	static float	LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	/* 乱数の初期化 */
	gsRandamize();

	/* 画面クリア時のカラーの設定 */
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	/* 面カリングの処理を有効にする */
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	/* デプスバッファを１．０でクリアする*/
	glClearDepth( 1.0 );

	/* テプステストを有効にする */
	glEnable( GL_DEPTH_TEST );

	/* パースペクティブ補正を行う */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	/* ブレンドを有効 */
	glEnable( GL_BLEND );

	/* デフォルトのブレンド式を設定 */
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	/* デフォルトの視点変換の変換行列を設定する */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(
		0.0f,  0.0f, 10.0f,
		0.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f
	);

	/* デフォルトのライトの設定 */
	glLightfv( GL_LIGHT0, GL_AMBIENT,  LightAmbient  );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  LightDiffuse  );
	glLightfv( GL_LIGHT0, GL_SPECULAR, LightSpeclar  );
	glLightfv( GL_LIGHT0, GL_POSITION, LightPosition );
	glEnable( GL_LIGHT0 );

	/* ライティングを有効にする */
	glEnable( GL_LIGHTING );

	/* ゲーム初期化処理 */
	gameInit();
}

/*-----------------------------------------------------------------------------
*
* Purpose : 終了処理．
*
* Return  : なし．
*
*----------------------------------------------------------------------------*/
static void	myDestoryFunc( void )
{
	/* ゲーム終了処理 */
	gameFinish();

	/* 入力デバイスシステムの終了処理 */
	gsFinishInput();

	/* サウンドシステムの終了処理 */
	gsFinishSound();
}

/*-----------------------------------------------------------------------------
*
* Purpose : ウィンドウサイズ変更時の処理．
*
* Return  : なし．
*
*----------------------------------------------------------------------------*/
static void myReshapeFunc( int width, int height )
{
	/* 高さが０にならないように調整 */
	height = ( height == 0 ) ? 1: height;

	/* ビューポートの設定 */
	glViewport( 0, 0, width, height );

	/* 透視射影の変換行列を設定する */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(
		PERSPECTIVE_FOV,
		(float)width / (float)height,
		PERSPECTIVE_NEAR,
		PERSPECTIVE_FAR
	);

	/* モデルビューモードにする */
	glMatrixMode( GL_MODELVIEW );
}

/*-----------------------------------------------------------------------------
*
* Purpose : イベントのない時の処理．（ ゲームメイン処理 ）
*
* Return  : なし．
*
*----------------------------------------------------------------------------*/
static void myIdleFunc( void )
{
	/* フレームタイマの更新 */
	gsFrameTimerUpdate();

	do
	{
		/* 入力デバイスの読み込み */
		gsReadInput();

		/* ゲームメイン処理 */
		gameMain();

		/* エスケープキーが押されたか？ */
		if ( GetAsyncKeyState( VK_ESCAPE ) != 0 ) {
#if	FULL_SCREEN_MODE
			/* ゲームモードを終了する */
			glutLeaveGameMode();
#else
			/* 終了処理を呼び出す */
			myDestoryFunc();
#endif
			/* 強制終了する */
			exit( 0 );
		}
	} while ( gsFrameTimerIsSkip() == GS_TRUE );

	/* 描画処理を呼び出す */
	glutPostRedisplay();
}

/*-----------------------------------------------------------------------------
*
* Purpose : 描画処理．
*
* Return  : なし．
*
*----------------------------------------------------------------------------*/
static void myDisplayFunc( void )
{
	/* 画面クリア */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/* ゲーム描画処理 */
	gameDraw();

	/* ダブルバッファの切り替え */
	glutSwapBuffers();

	/* タイマウェイトを行う */
	gsFrameTimerWait();
}

/*-----------------------------------------------------------------------------
*
* Purpose : ウィンドウがアクティブになった時の処理．
*
* Return  : なし．
*
*----------------------------------------------------------------------------*/
static void myActivateFunc( int state )
{
	/* 入力デバイスシステムにアクティブ状態を伝える */
	gsActivateInput( state );

	/* サウンドシステムにアクティブ状態を伝える */
	gsActivateSound( state );
}

/*-----------------------------------------------------------------------------
*
* Purpose : スワップインターバルの設定．（ Ｖｓｙｎｃの有効・無効 ）
*
* Return  : なし．
*
*----------------------------------------------------------------------------*/
static GSboolean gsSwapInterval( GSint Interval )
{
	/* wglSwapIntervalEXT拡張関数のポインタ関数型 */
	typedef BOOL (WINAPI * LPFNWGLSWAPINTERVALEXTPROC)( int interval );

	LPFNWGLSWAPINTERVALEXTPROC	wglSwapIntervalEXT = NULL;

	/* SwapIntervalEXTの関数ポインタを取得 */
	wglSwapIntervalEXT = (LPFNWGLSWAPINTERVALEXTPROC)
		wglGetProcAddress( "wglSwapIntervalEXT" );

	/* SwapIntervalEXT関数が取得できたか？ */
	if ( wglSwapIntervalEXT != NULL )
	{
		/* スワップのインターバルを設定 */
		wglSwapIntervalEXT( Interval );

		return	GS_TRUE;
	}

	return	GS_FALSE;
}

/********** End of File ******************************************************/
