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
	//テクスチャ全読み込み
	LoadTexture();
	//パーティクルマネージャー生成
	circleParticle.reset(ParticleManager::Create(ImageManager::Normal));
	deathParticle.reset(ParticleManager::Create(ImageManager::Normal));
	smokeParticle.reset(ParticleManager::Create(ImageManager::Smoke));
}

void ParticleEmitter::Update()
{
	//パーティクルマネージャー更新
	circleParticle->Update();
	deathParticle->Update();
	smokeParticle->Update();
}

void ParticleEmitter::DrawAll()
{
	//パーティクルマネージャー描画
	circleParticle->Draw(AddBlendType);
	deathParticle->Draw(AddBlendType);
	smokeParticle->Draw(AlphaBlendType);
}

void ParticleEmitter::FireEffect(int life, XMFLOAT3 l_pos, float startscale, float endscale, XMFLOAT4 startcolor, XMFLOAT4 endcolor)
{
	XMFLOAT3 pos = l_pos;
	const float rnd_vel = 0.05f;
	XMFLOAT3 vel{};
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * rnd_vel * 2.0f;// -rnd_vel / 2.0f;
	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

	circleParticle->Add(life, { pos.x,pos.y,pos.z }, vel, {}, startscale, endscale, startcolor, endcolor);
}

void ParticleEmitter::HootEffect(int life, XMFLOAT3 l_pos, float startscale, float endscale, XMFLOAT4 startcolor, XMFLOAT4 endcolor) {
	XMFLOAT3 pos = l_pos;
	const float rnd_vel = 0.1f;
	XMFLOAT3 vel{};
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.z = pos.z;


	smokeParticle->Add(life, pos, vel, {}, startscale, endscale, startcolor, endcolor);
}

void ParticleEmitter::DeathEffect(int life, XMFLOAT3 l_pos, float startscale, float endscale, XMFLOAT4 startcolor, XMFLOAT4 endcolor, float velocity) {
	XMFLOAT3 pos = l_pos;
	float angle = (float)rand() / RAND_MAX * 360.0f;
		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x =	velocity * sinf(angle);
		vel.y =	velocity * cosf(angle);
		vel.z =	0.0f;
		//const float rnd_sca = 0.1f;
		//float sca{};
		//sca = (float)rand() / RAND_MAX*rnd_sca;
		deathParticle->Add(life, pos, vel, XMFLOAT3(), startscale, endscale, startcolor, endcolor);
}

void ParticleEmitter::AllDelete()
{
	//全パーティクルの削除
	circleParticle->AllDelete();
	deathParticle->AllDelete();
	smokeParticle->AllDelete();
}

void ParticleEmitter::LoadTexture() {
	ImageManager::GetIns()->LoadParticle();
}