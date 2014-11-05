#include "DrawSprite3D.h"
extern void

DrawSprite3D(
GSuint				uTextureID,
const GSrect*		pSrcRect,
const GSrect*		pRect,
const GSvector2*		pScaling,
GSfloat				fRotation,
const GSvector3*	pTranslation,
const GScolor*		pColor
)
{
	GSrect			rTexCoord;
	GLsizei			sTexWidth;
	GLsizei			sTexHeight;
	GSmatrix4		matView;

	/*各レンダリングモードの退避*/
	glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT);

	/*面カリングを無効にする*/
	glDisable(GL_CULL_FACE);

	/*テクスチャをバインドする*/
	gsBindTexture(uTextureID);

	/*モデルビュー変換行列の退避*/
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	/*視野変換行列を取得する*/
	glGetFloatv(GL_MODELVIEW_MATRIX,(float*)&matView);

	/*ビルボード処理用に変換行列を作成*/
	matView.m[3][0] = 0.0f;
	matView.m[3][1] = 0.0f;
	matView.m[3][2] = 0.0f;
	gsMatrix4Transpose(&matView,&matView);

	/*平行移動量の設定を行う*/
	if (pTranslation != NULL){
		glTranslatef(pTranslation->x, pTranslation->y, pTranslation->z);
	}

	/*ビルボード処理用の変換行列を設定する*/
	glMultMatrixf((float*)&matView);

	/*回転角度の設定を行う*/
	glRotatef(fRotation, 0.0f,0.0f,1.0f);

	/*拡大縮小を行う*/
	if (pScaling != NULL){
		glScalef(pScaling->x, pScaling->y, 0.0f);
	}

	/*頂点カラーの設定*/
	if (pColor != NULL){
		glColor4fv((GLfloat*)pColor);
	}

	/*バインド中のテクスチャの幅と高さを取得*/
	glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH, &sTexWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sTexHeight);

	if (pSrcRect != NULL){
		/*テクスチャ座標の計算を行う*/
		rTexCoord.left = pSrcRect->left / sTexWidth;
		rTexCoord.top = pSrcRect->top / sTexHeight;
		rTexCoord.right = pSrcRect->right / sTexWidth;
		rTexCoord.bottom = pSrcRect->bottom / sTexHeight;
	}
	else{
		/*テクスチャ内の位置が指定されていない場合はテクスチャを全体表示*/
		rTexCoord.left = 0.0f;
		rTexCoord.top = 0.0f;
		rTexCoord.right = 1.0f;
		rTexCoord.bottom = 1.0f;
	}

	/*四角形の描画*/
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(rTexCoord.left, rTexCoord.top);
	glVertex2f(pRect->left,pRect->top);

	glTexCoord2f(rTexCoord.left, rTexCoord.bottom);
	glVertex2f(pRect->left, pRect->bottom);

	glTexCoord2f(rTexCoord.right, rTexCoord.bottom);
	glVertex2f(pRect->right, pRect->bottom);

	glTexCoord2f(rTexCoord.right, rTexCoord.top);
	glVertex2f(pRect->right, pRect->top);
	glEnd();

	/*モデルビュー変換行列を復帰*/
	glPopMatrix();

	/*レンダリングモードの復帰*/
	glPopAttrib();
}