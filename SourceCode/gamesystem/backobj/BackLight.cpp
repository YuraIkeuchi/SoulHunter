#include "BackLight.h"
#include "ImageManager.h"
#include "VariableCommon.h"
//初期化
void BackLight::Initialize() {
	//背景テクスチャ
	IKETexture* backlightTex_ = IKETexture::Create(ImageManager::LightTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	backlightTex_->TextureCreate();
	backlightTex_->SetRotation({ 0,0,45 });
	backlightTex_->SetColor({ 1.0f,1.0f,1.0f,0.8f });
	backlightTex_->SetScale(m_BackLightScale);
	backlightTex.reset(backlightTex_);
}

//更新
void BackLight::Update() {
	backlightTex->Update();
	backlightTex->SetPosition(m_BackLightPos);
	backlightTex->SetScale(m_BackLightScale);
}

//描画
const void BackLight::Draw() {
	IKETexture::PreDraw(AlphaBlendType);
	backlightTex->Draw();
}