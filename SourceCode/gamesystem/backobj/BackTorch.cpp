#include "BackTorch.h"
#include "ImageManager.h"
BackTorch::BackTorch() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::BackTorch);
}

//初期化
bool BackTorch::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	IKEObject3d* object3d_ = new IKEObject3d();
	object3d_ = IKEObject3d::Create();
	object3d_->SetModel(m_Model);
	m_Position = { 110.0f,-90.0,0.0f };
	m_Scale =  { 3.0f,6.0f,1.0f };
	object3d_->SetScale(m_Scale);
	m_Object.reset(object3d_);


	ParticleManager* fire_ = new ParticleManager();
	fire_->Initialize(ImageManager::Normal);
	fire.reset(fire_);

	return true;
}

//セット
void BackTorch::SetObj() {
	/*object3d->SetPosition(m_pos);
	object3d->SetRotation(m_rot);
	object3d->SetScale(m_scale);*/

	//パーティクルの更新
	BirthParticle();
	
}
//特別な描画
void BackTorch::specialDraw() {
	//ImGui::Begin("Torch");
	//ImGui::Text("m_Position.x : %f", m_rot.x);
	//ImGui::Text("m_Position.y : %f", m_rot.y);
	//ImGui::Text("m_Position.z : %f", m_rot.z);
	//ImGui::End();
	fire->Draw(AlphaBlendType);
}
//描画
void BackTorch::Draw(DirectXCommon* dxCommon) {
	specialDraw();
	//オブジェクトの描画
	IKEObject3d::PreDraw();
	if (DrawCollide()) {
		Obj_Draw();
	}
}

void BackTorch::BirthParticle() {
	XMFLOAT3 pos = m_Position;

	const float rnd_vel = 0.05f;
	XMFLOAT3 vel{};
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * rnd_vel * 2.0f;// -rnd_vel / 2.0f;
	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

	fire->Add(200, { pos.x,pos.y + 3.0f,pos.z }, vel, {}, 1.0f, 0.0f, { 1.0f,0.5f,0.0f,0.5f }, { 1.0f,0.5f,0.0f,0.5f });

	fire->Update();
}
