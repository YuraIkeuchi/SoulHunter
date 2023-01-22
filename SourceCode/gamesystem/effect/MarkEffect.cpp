#include "MarkEffect.h"
#include "ImageManager.h"
#include <Easing.h>
#include "imgui.h"
//読み込み
MarkEffect::MarkEffect() {
	IKETexture* markEffect_;
		markEffect_ = IKETexture::Create(ImageManager::NormalEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		markEffect_->TextureCreate();
		markEffect_->SetPosition({ 0.0f,90.0f,0.0f });
	
		markEffect.reset(markEffect_);
}
//初期化
void MarkEffect::Initialize() {
	m_Color = { 1.0f,1.0f,1.0f,0.0f };
	m_Scale = { 0.0f,0.0f,0.0f };
}
//更新
void MarkEffect::Update(XMFLOAT3 StartPos) {

	EffectMove(StartPos);
	markEffect->SetPosition(m_Position);
	markEffect->SetScale(m_Scale);
	markEffect->SetColor(m_Color);
	markEffect->Update();
}
//描画
void MarkEffect::Draw() {
	//ImGui::Begin("Mark");
	//ImGui::Text("m_Frame:%f", m_Frame);
	//ImGui::Text("m_Scale.x:%f", m_Scale.x);
	//ImGui::Text("m_Color.w:%f", m_Color.w);
	//ImGui::End();
	IKETexture::PreDraw(0);
	markEffect->Draw();
}
//エフェクトの動き
void MarkEffect::EffectMove(XMFLOAT3 StartPos) {
	m_Position = StartPos;

	//イージングで大きさと色を変えてる
	if (m_Frame < 1.0f) {
		m_Frame += 0.01f;
	}
	else {
		m_Frame = 0.0f;
		m_Color.w = 1.0f;
		m_Scale = { 0.0f,0.0f,0.0f };
	}
	m_Color.w = Ease(In, Cubic, m_Frame, m_Color.w, 0.0f);

	m_Scale = { Ease(In, Cubic, m_Frame, m_Scale.x, 2.5f),
		Ease(In, Cubic, m_Frame, m_Scale.y, 2.5f),
		Ease(In, Cubic, m_Frame, m_Scale.z, 2.5f),
	};
}
