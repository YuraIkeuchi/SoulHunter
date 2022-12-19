#include "ChestEffect.h"
#include "ImageManager.h"
#include "Collision.h"
#include <Easing.h>
#include "imgui.h"
//読み込み
ChestEffect::ChestEffect() {
	IKETexture* chesteffect_[ChestEffect_Max];
	for (int i = 0; i < chesteffect.size(); i++) {
		chesteffect_[i] = IKETexture::Create(ImageManager::ParticleEffect, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
		chesteffect_[i]->TextureCreate();
		chesteffect_[i]->SetPosition({ 0.0f,90.0f,0.0f });
		//DushEffecttexture->SetRotation({ 90,0,0 });
		m_scale[i] = { 0.2f,0.2f,0.2f };
		m_Alive[i] = false;
		m_MoveNumber[i] = Wide;
		m_StartEffect[i] = false;
		m_TargetTimer[i] = 0;
		chesteffect_[i]->SetScale(m_scale[i]);
		chesteffect[i].reset(chesteffect_[i]);
	}
}
//初期化
void ChestEffect::Initialize() {

}
//更新
void ChestEffect::Update(XMFLOAT3 StartPos, XMFLOAT3 TargetPos, int ChestState) {

	EffectMove(StartPos,TargetPos,ChestState);
	for (int i = 0; i < chesteffect.size(); i++) {
		if (m_Alive[i]) {
			//object3d->Update();
			chesteffect[i]->Update();
		}
		chesteffect[i]->SetPosition(m_pos[i]);
		chesteffect[i]->SetScale(m_scale[i]);
	}
}
//描画
void ChestEffect::Draw() {
	/*ImGui::Begin("chesteffect");
	for (int i = 0; i < chesteffect.size(); i++) {
		ImGui::Text("m_Alive[%d]::%d",i, m_Alive[i]);
		ImGui::Text("m_StartEffect[%d]::%d", i, m_StartEffect[i]);
	}
	ImGui::End();*/
	IKETexture::PreDraw(1);
	for (int i = 0; i < chesteffect.size(); i++) {
		if (m_Alive[i]) {
			//object3d->Update();
			chesteffect[i]->Draw();
		}
	}
}
//エフェクトの動き
void ChestEffect::EffectMove(XMFLOAT3 StartPos, XMFLOAT3 TargetPos, int ChestState) {
	for (int i = 0; i < chesteffect.size(); i++) {
		//宝箱を開けた瞬間
		if (ChestState == 1 && !m_Alive[i] && !m_StartEffect[i]) {
			m_scale[i] = { 0.2f,0.2f,0.2f };
			m_Angle[i] = (float)(rand() % 360);
			m_speed[i] = { (float)(rand() % 10 + 5) / 10,(float)(rand() % 10 + 5) / 10 };
			m_pos[i] = StartPos;
			m_Alive[i] = true;
			m_StartEffect[i] = true;
			m_MoveNumber[i] = Wide;
		}
		//最初は広がるように動く
		if (m_Alive[i]) {
			if (m_MoveNumber[i] == Wide) {
				//宝箱の周りに広がる
				m_pos[i].x += float((cos(m_Angle[i])) * m_speed[i].x);
				m_pos[i].y += float((sin(m_Angle[i])) * m_speed[i].y);
				
				//イージング処理
				if (m_Frame[i] < 1.0f) {
					m_Frame[i] += 0.08f;
				}
				else {
					m_MoveNumber[i] = TargetPlayer;
					m_Frame[i] = 0.0f;
				}


				m_speed[i] = {
					Ease(In,Cubic,m_Frame[i],m_speed[i].x,0.0f),
					Ease(In,Cubic,m_Frame[i],m_speed[i].x,0.0f)
				};
			}
			else {
				//プレイヤーに近づく
				m_TargetTimer[i]++;

				//イージング処理
				if (m_TargetTimer[i] >= i * 2) {
					if (m_Frame[i] < 1.0f) {
						m_Frame[i] += 0.08f;
					}
					else {
						m_Frame[i] = 0.0f;
						m_Alive[i] = false;
					}
				}
				m_pos[i] = {
			Ease(In,Cubic,m_Frame[i],m_pos[i].x,TargetPos.x),
			Ease(In,Cubic,m_Frame[i],m_pos[i].y,TargetPos.y),
			Ease(In,Cubic,m_Frame[i],m_pos[i].z,TargetPos.z)
				};

			}
		}
	}
}
