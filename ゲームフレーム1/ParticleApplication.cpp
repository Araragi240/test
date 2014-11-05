#include "ParticleApplication.h"
#include "Sprite3D.h"
#include <gslib.h>

//初期化
void ParticleApplication::initialize()
{
	//テクスチャの読み込み(textureID,ファイル)
	gsLoadTexture(0, "particle.bmp");
}

//更新
void ParticleApplication::update(float frameTimer)
{}

//描画
void ParticleApplication::draw()
{
	Sprite3D sprite(0);

	/*GSuint textureID = 0;
	GSrect texCoord(0.0f,0.0f,8.0f,8.0f);
	GSrect rect(-0.5f, -0.5f, 0.5f, 0.5f);
	GSvector2 scale(1.0f,1.0f);
	float rotate = 0.0f;
	GSvector3 position(0.0f, 0.0f, 0.0f);
	GScolor color(1.0f, 1.0f, 1.0f, 1.0f);*/

	//スプライトの描画
	sprite.draw();

	/*DrawSprite3D(
		textureID,
		&texCoord,
		&rect,
		&scale,
		rotate,
		&position,
		&color
		);*/

}

//終了
void ParticleApplication::finish()
{
	//テクスチャの削除
	gsDeleteTexture(0);
}