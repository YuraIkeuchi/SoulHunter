#include "ClearPlayer.h"
#include "ModelManager.h"
#include "VariableCommon.h"
ClearPlayer::ClearPlayer() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::PlayerFBX);
}

bool ClearPlayer::Initialize() {
	IKEFBXObject3d* fbxobject_ = new IKEFBXObject3d();
	fbxobject_->Initialize();
	fbxobject_->SetModel(m_fbxModel);
	fbxobject_->LoadAnimation();
	m_fbxObject.reset(fbxobject_);

	m_Scale = { 3.0f,3.0f,3.0f };
	return true;
}

void ClearPlayer::Update() {
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}

void ClearPlayer::Draw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}

void ClearPlayer::ClearMove(int Timer) {
	//フレーム数で動きが決まる
	if (Timer == 1) {
		m_Position = { 0.0f,5.0f,-250.0f };
		m_Rotation = { 0.0f,0.0f,0.0f };
	}
	m_Position.z += 0.3f;
	m_AnimationTimer.MoveAnimation++;

	if (m_AnimationTimer.MoveAnimation == 1) {
		//アニメーションのためのやつ
		m_AnimeLoop = true;
		m_AnimationType = Walk;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_AnimationType);
	}
}