#include "ParticleApplication.h"
#include "Sprite3D.h"
#include <gslib.h>

//������
void ParticleApplication::initialize()
{
	//�e�N�X�`���̓ǂݍ���(textureID,�t�@�C��)
	gsLoadTexture(0, "particle.bmp");
}

//�X�V
void ParticleApplication::update(float frameTimer)
{}

//�`��
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

	//�X�v���C�g�̕`��
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

//�I��
void ParticleApplication::finish()
{
	//�e�N�X�`���̍폜
	gsDeleteTexture(0);
}