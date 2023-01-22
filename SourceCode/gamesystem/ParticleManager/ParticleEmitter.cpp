#include "ParticleEmitter.h"
#include "VariableCommon.h"
#include "ImageManager.h"
ParticleEmitter* ParticleEmitter::GetInstance()
{
	static ParticleEmitter instance;

	return &instance;
}

void ParticleEmitter::Initialize()
{
	//�e�N�X�`���S�ǂݍ���
	LoadTexture();
	//�p�[�e�B�N���}�l�[�W���[����
	circleParticle.reset(ParticleManager::Create(ImageManager::Normal));
}

void ParticleEmitter::Update()
{
	//�p�[�e�B�N���}�l�[�W���[�X�V
	circleParticle->Update();
}

void ParticleEmitter::DrawAll()
{
	//�p�[�e�B�N���}�l�[�W���[�`��
	circleParticle->Draw(AddBlendType);
}

void ParticleEmitter::DemoEffect(XMFLOAT3 l_pos)
{
	XMFLOAT3 pos = l_pos;
	XMFLOAT4 s_color = { 1.0f,0.5f,0.0f,0.5f };
	XMFLOAT4 e_color = { 1.0f,0.5f,0.0f,0.5f };
	const float rnd_vel = 0.05f;
	XMFLOAT3 vel{};
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * rnd_vel * 2.0f;// -rnd_vel / 2.0f;
	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

	circleParticle->Add(100, { pos.x,pos.y,pos.z }, vel, {}, 5.0f, 0.0f, s_color, e_color);
}

void ParticleEmitter::AllDelete()
{
	//�S�p�[�e�B�N���̍폜
	circleParticle->AllDelete();
}

void ParticleEmitter::LoadTexture() {
	ImageManager::GetIns()->LoadParticle();
}