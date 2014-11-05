#include"Sprite3D.h"
#include <gslib.h>

//�R���X�g���N�^
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

//���W��ݒ�
void Sprite3D::setPosition(const GSvector3& position)
{
	mPosition = position;
}

//�X�P�[���l��ݒ�
void Sprite3D::setScale(const GSvector2& scale)
{
	mScale = scale;
}

//��]�p�x��ݒ�
void Sprite3D::setRotate(float rotate)
{
	mRotate = rotate;
}

//�`��T�C�Y�̒Z�`��ݒ�
void Sprite3D::setRect(const GSrect& rect)
{
	mRect = rect;
}

//�F��ݒ�
void Sprite3D::setColor(const GScolor4& color)
{
	mColor = color;

}

//�]������`�C���[�W�̋�`��ݒ�
void Sprite3D::setImageRect(const GSrect& rect)
{
	//�e�N�X�`�����o�C���h����
	gsBindTexture(mTextureID);

	//�o�C���h���̃e�N�X�`���̕��ƍ������擾
	GLint width, height;
	glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	//�e�N�X�`�����W�̌v�Z���s��
	mTexCoord.left = rect.left / width;
	mTexCoord.top = rect.top / height;
	mTexCoord.right = rect.right / width;
	mTexCoord.bottom = rect.bottom / height;
}

void Sprite3D::draw()
{
	//�e�탌���_�����O���[�h�̑ޔ�
	glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT);

	//�ʃJ�����O�𖳌��ɂ���
	glDisable(GL_CULL_FACE);

	//�e�N�X�`�����o�C���h����
	gsBindTexture(mTextureID);

	//���f���r���[�ϊ��s��̑ޔ�
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//�r���{�[�h�����p�̕ϊ��s����쐬
	GSmatrix4 billboard;
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&billboard);
	billboard.setPosition(GSvector3(0.0f, 0.0f, 0.0f));
	billboard.transpose();

	//���s�ړ��ʂ̐ݒ���s��
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);

	// �r���{�[�h�̕ϊ��s���ݒ肷��
	glMultMatrixf((GLfloat*)&billboard);

	// ��]�p�x�̐ݒ���s��
	glRotatef(mRotate, 0.0f, 0.0f, 1.0f);

	// �g��k�����s
	glScalef(mScale.x, mScale.y, 0.0f);

	// �e�N�X�`���̃J���[��ݒ肷��
	glColor4fv((GLfloat*)&mColor);

	// �l�p�`�̕`��
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

	// ���f���r���[�ϊ��s��𕜋A
	glPopMatrix();

	// �����_�����O���[�h�̕��A
	glPopAttrib();
}

	