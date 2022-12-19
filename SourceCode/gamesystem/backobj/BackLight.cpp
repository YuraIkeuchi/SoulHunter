#include "BackLight.h"
#include "ImageManager.h"
//‰Šú‰»
void BackLight::Initialize() {

	//”wŒiƒeƒNƒXƒ`ƒƒ
	IKETexture* backlightTex_ = IKETexture::Create(ImageManager::LightTex, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	backlightTex_->TextureCreate();
	backlightTex_->SetRotation({ 0,0,45 });
	backlightTex_->SetColor({ 1.0f,1.0f,1.0f,0.8f });
	backlightTex_->SetScale(m_BackLightScale);
	backlightTex.reset(backlightTex_);
}

//XV
void BackLight::Update() {
	backlightTex->Update();
	backlightTex->SetPosition(m_BackLightPos);
	backlightTex->SetScale(m_BackLightScale);
}

//•`‰æ
const void BackLight::Draw() {
	/*ImGui::Begin("Back");
	ImGui::SliderFloat("position.x", &m_BackLightPos.x, 360, -360);
	ImGui::SliderFloat("position.y", &m_BackLightPos.y, 360, -360);
	ImGui::SliderFloat("position.z", &m_BackLightPos.z, 360, -360);
	ImGui::SliderFloat("scale.x", &m_BackLightScale.x, 360, -360);
	ImGui::SliderFloat("scale.y", &m_BackLightScale.y, 360, -360);
	ImGui::SliderFloat("scale.z", &m_BackLightScale.z, 360, -360);
	ImGui::End();*/

	IKETexture::PreDraw(0);
	backlightTex->Draw();
}