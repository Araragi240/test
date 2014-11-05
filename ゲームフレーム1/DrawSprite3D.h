#ifndef _DRAWSPRITE3D_H_
#define _DRAWSPRITE3D_H_
#include <gslib.h>

extern void
DrawSprite3D(
	GSuint				uTextureID,		
	const GSrect*		pSrcRect,
	const GSrect*		pRect,
	const GSvector2*		pScaling,
	GSfloat				fRotation,
	const GSvector3*	pTranslation,
	const GScolor*		pColor

);
#endif