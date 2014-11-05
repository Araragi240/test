#include"Sprite3D.h"
#include <gslib.h>

//コンストラクタ
Sprite3D::Sprite3D(GLuint textuteID) :
	mTextureID(textuteID),
	mPosition(0.0f, 0.0f, 0.0f),
	mRotate(0.0f),
	mScale(1.0f, 1.0f),
	mColor(1.0f, 1.0f, 1.0f, 1.0f),
	mRect(-0.5f, -0.5f, 0.5f, 0.5f),
	mTexCoord(0.0f, 0.0f, 1.0f, 1.0f)
{
}

//座標を設定
void Sprite3D::setPosition(const GSvector3& position)
{
	mPosition = position;
}

//スケール値を設定
void Sprite3D::setScale(const GSvector2& scale)
{
	mScale = scale;
}

//回転角度を設定
void Sprite3D::setRotate(float rotate)
{
	mRotate = rotate;
}

//描画サイズの短形を設定
void Sprite3D::setRect(const GSrect& rect)
{
	mRect = rect;
}

//色を設定
void Sprite3D::setColor(const GScolor4& color)
{
	mColor = color;

}

//転送元矩形イメージの矩形を設定
void Sprite3D::setImageRect(const GSrect& rect)
{
	//テクスチャをバインドする
	gsBindTexture(mTextureID);

	//バインド中のテクスチャの幅と高さを取得
	GLint width, height;
	glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	//テクスチャ座標の計算を行う
	mTexCoord.left = rect.left / width;
	mTexCoord.top = rect.top / height;
	mTexCoord.right = rect.right / width;
	mTexCoord.bottom = rect.bottom / height;
}

void Sprite3D::draw()
{
	//各種レンダリングモードの退避
	glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT);

	//面カリングを無効にする
	glDisable(GL_CULL_FACE);

	//テクスチャをバインドする
	gsBindTexture(mTextureID);

	//モデルビュー変換行列の退避
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//ビルボード処理用の変換行列を作成
	GSmatrix4 billboard;
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&billboard);
	billboard.setPosition(GSvector3(0.0f, 0.0f, 0.0f));
	billboard.transpose();

	//平行移動量の設定を行う
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);

	// ビルボードの変換行列を設定する
	glMultMatrixf((GLfloat*)&billboard);

	// 回転角度の設定を行う
	glRotatef(mRotate, 0.0f, 0.0f, 1.0f);

	// 拡大縮小を行
	glScalef(mScale.x, mScale.y, 0.0f);

	// テクスチャのカラーを設定する
	glColor4fv((GLfloat*)&mColor);

	// 四角形の描画
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(mTexCoord.left, mTexCoord.top);
	glVertex2f(mRect.left, mRect.top);
	glTexCoord2f(mTexCoord.left, mTexCoord.bottom);
	glVertex2f(mRect.left, mRect.bottom);
	glTexCoord2f(mTexCoord.right, mTexCoord.bottom);
	glVertex2f(mRect.right, mRect.bottom);
	glTexCoord2f(mTexCoord.right, mTexCoord.top);
	glVertex2f(mRect.right, mRect.top);
	glEnd();

	// モデルビュー変換行列を復帰
	glPopMatrix();

	// レンダリングモードの復帰
	glPopAttrib();
}

	