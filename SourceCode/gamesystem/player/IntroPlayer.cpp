#include "IntroPlayer.h"
#include "ModelManager.h"
#include "VariableCommon.h"
IntroPlayer::IntroPlayer() {
	m_fbxModel = ModelManager::GetInstance()->GetFBXModel(ModelManager::PlayerFBX);
}
//������
bool IntroPlayer::Initialize() {
	IKEFBXObject3d* fbxobject_ = new IKEFBXObject3d();
	fbxobject_->Initialize();
	fbxobject_->SetModel(m_fbxModel);
	fbxobject_->LoadAnimation();
	m_fbxObject.reset(fbxobject_);

	m_Scale = { 3.0f,3.0f,3.0f };
	return true;
}
//�X�V
void IntroPlayer::Update() {
	Fbx_SetParam();
	m_fbxObject->FollowUpdate(m_AnimeLoop, m_AnimeSpeed, m_AnimationStop);
}
//�`��
void IntroPlayer::Draw(DirectXCommon* dxCommon) {
	Fbx_Draw(dxCommon);
}
//����
void IntroPlayer::IntroMove(int Timer) {
	//�t���[�����œ��������܂�
	if (Timer == 1) {
		m_Position = { 0.0f,2.2f,30.0f };
		m_Rotation = { 0.0f,180.0f,0.0f };
	}

	//��莞�ԗ�������O�ɂ�����
	if (Timer >= 100) {
		m_Position.z -= 0.3f;
	}

	m_AnimationTimer.MoveAnimation++;

	if (m_AnimationTimer.MoveAnimation == 1) {
		//�A�j���[�V�����̂��߂̂��
		m_AnimeLoop = true;
		m_AnimationType = Walk;
		m_AnimeSpeed = 1;
		m_fbxObject->PlayAnimation(m_AnimationType);
	}
}