#include "IntroPlayer.h"
#include "ModelManager.h"
#include "VariableCommon.h"
IntroPlayer::IntroPlayer() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::PlayerFBX);
}
//初期化
bool IntroPlayer::Initialize() {
	IKEFBXObject3d* fbxobject_ = new IKEFBXObject3d();
	fbxobject_->Initialize();
	fbxobject_->SetModel(m_fbxModel);
	fbxobject_->LoadAnimation();
	m_fbxObject.reset(fbxobject_);

	m_Scale = { 3.0f,3.0f,3.0f };
	return true;
}
//更新
void IntroPlayer::Update() {
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
//描画
void IntroPlayer::Draw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}
//動き
void IntroPlayer::IntroMove(int Timer) {
	//フレーム数で動きが決まる
	if (Timer == 1) {
		m_Position = { 0.0f,2.2f,30.0f };
		m_Rotation = { 0.0f,180.0f,0.0f };
	}

	//一定時間立ったら前にすすむ
	if (Timer >= 100) {
		m_Position.z -= 0.3f;
	}

	m_AnimationTimer.MoveAnimation++;

	if (m_AnimationTimer.MoveAnimation == 1) {
		//アニメーションのためのやつ
		m_AnimeLoop = true;
		m_AnimationType = Walk;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_AnimationType);
	}
}