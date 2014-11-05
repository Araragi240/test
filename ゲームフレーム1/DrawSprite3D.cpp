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

	/*�e�����_�����O���[�h�̑ޔ�*/
	glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT);

	/*�ʃJ�����O�𖳌��ɂ���*/
	glDisable(GL_CULL_FACE);

	/*�e�N�X�`�����o�C���h����*/
	gsBindTexture(uTextureID);

	/*���f���r���[�ϊ��s��̑ޔ�*/
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	/*����ϊ��s����擾����*/
	glGetFloatv(GL_MODELVIEW_MATRIX,(float*)&matView);

	/*�r���{�[�h�����p�ɕϊ��s����쐬*/
	matView.m[3][0] = 0.0f;
	matView.m[3][1] = 0.0f;
	matView.m[3][2] = 0.0f;
	gsMatrix4Transpose(&matView,&matView);

	/*���s�ړ��ʂ̐ݒ���s��*/
	if (pTranslation != NULL){
		glTranslatef(pTranslation->x, pTranslation->y, pTranslation->z);
	}

	/*�r���{�[�h�����p�̕ϊ��s���ݒ肷��*/
	glMultMatrixf((float*)&matView);

	/*��]�p�x�̐ݒ���s��*/
	glRotatef(fRotation, 0.0f,0.0f,1.0f);

	/*�g��k�����s��*/
	if (pScaling != NULL){
		glScalef(pScaling->x, pScaling->y, 0.0f);
	}

	/*���_�J���[�̐ݒ�*/
	if (pColor != NULL){
		glColor4fv((GLfloat*)pColor);
	}

	/*�o�C���h���̃e�N�X�`���̕��ƍ������擾*/
	glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH, &sTexWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sTexHeight);

	if (pSrcRect != NULL){
		/*�e�N�X�`�����W�̌v�Z���s��*/
		rTexCoord.left = pSrcRect->left / sTexWidth;
		rTexCoord.top = pSrcRect->top / sTexHeight;
		rTexCoord.right = pSrcRect->right / sTexWidth;
		rTexCoord.bottom = pSrcRect->bottom / sTexHeight;
	}
	else{
		/*�e�N�X�`�����̈ʒu���w�肳��Ă��Ȃ��ꍇ�̓e�N�X�`����S�̕\��*/
		rTexCoord.left = 0.0f;
		rTexCoord.top = 0.0f;
		rTexCoord.right = 1.0f;
		rTexCoord.bottom = 1.0f;
	}

	/*�l�p�`�̕`��*/
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

	/*���f���r���[�ϊ��s��𕜋A*/
	glPopMatrix();

	/*�����_�����O���[�h�̕��A*/
	glPopAttrib();
}