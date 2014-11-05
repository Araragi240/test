#ifndef _SPRITE3D_H_
#define _SPRITE3D_H_

#include<gslib.h>
class Sprite3D
{
public:
	Sprite3D(unsigned int textureID);
	void setPosition(const GSvector3& position);
	void setRotate(float rotate);
	void setScale(const GSvector2& scale);
	void setColor(const GSvector4& color);
	void setRect(const GSrect& rect);
	void setImageRect(const GSrect& rect);
	void draw();

private:
	unsigned int	mTextureID;
	GSvector3		mPosition;
	float			mRotate;
	GSvector2		mScale;
	GScolor4		mColor;
	GSrect			mRect;
	GSrect			mTexCoord;
};


#endif