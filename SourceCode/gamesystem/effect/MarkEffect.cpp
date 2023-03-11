#include "MarkEffect.h"
#include "ImageManager.h"
#include <Easing.h>
#include "imgui.h"
#include "VariableCommon.h"
//読み込み
MarkEffect::MarkEffect() {
	IKETexture* markEffect_;
		markEffect_ = IKETexture::Create(ImageManager::NormalEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		markEffect_->TextureCreate();
		markEffect_->SetPosition({ 0.0f,90.0f,0.0f });
	
		markEffect.reset(markEffect_);
		helper = make_unique< Helper>();
}
//初期化
void MarkEffect::Initialize() {
	m_Color = m_InitColor;
	m_Scale = m_ResetThirdFew;
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
	IKETexture::PreDraw(AlphaBlendType);
	markEffect->Draw();
}
//エフェクトの動き
void MarkEffect::EffectMove(XMFLOAT3 StartPos) {
	m_Position = StartPos;
	float l_AddFrame = 0.01f;//加算されるフレーム数
	float l_ScaleMax = 2.5f;//最大の大きさ
	//イージングで大きさと色を変えてる
	if(helper->CheckMin(m_Frame,m_ColorMax,l_AddFrame)){
		m_Frame = m_FrameMin;
		m_Color.w = m_ColorMax;
		m_Scale = m_ResetThirdFew;
	}
	m_Color.w = Ease(In, Cubic, m_Frame, m_Color.w, m_ColorMin);

	m_Scale = { Ease(In, Cubic, m_Frame, m_Scale.x, l_ScaleMax),
		Ease(In, Cubic, m_Frame, m_Scale.y, l_ScaleMax),
		Ease(In, Cubic, m_Frame, m_Scale.z, l_ScaleMax),
	};
}
