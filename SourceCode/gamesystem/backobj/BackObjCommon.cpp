#include "BackObjCommon.h"
#include"Collision.h"
//�X�V
void BackObjCommon::Update() {
	//�e�I�u�W�F�̂��ꂼ��̂܂Ƃ�
	SetObj();
	if (UpdateCollide()) {
		object3d->Update();
	}
}

//�`��
void BackObjCommon::Draw() {
	specialDraw();
	//�I�u�W�F�N�g�̕`��
	IKEObject3d::PreDraw();
	if (DrawCollide()) {
		object3d->Draw();
	}
}

//�X�V��͈͓��ɓ��������̂�
bool BackObjCommon::UpdateCollide() {
	//�}�W�b�N�i���o�[�����̂��߂̕ϐ�(�֐����ł����g��Ȃ��̂Ń��[�J��)
	const float l_UpdateRadius = 210.0f;//�X�V�͈�
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_pos.x, m_pos.y, l_UpdateRadius, m_PlayerPos.x, m_PlayerPos.y, l_UpdateRadius)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

//�`���͈͓��ɓ��������̂�
bool BackObjCommon::DrawCollide() {
	//�}�W�b�N�i���o�[�����̂��߂̕ϐ�(�֐����ł����g��Ȃ��̂Ń��[�J��)
	const float l_DrawRadius = 200.0f;//�`��͈�
	XMFLOAT3 m_PlayerPos = player->GetPosition();
	if (Collision::CircleCollision(m_pos.x, m_pos.y, l_DrawRadius, m_PlayerPos.x, m_PlayerPos.y, l_DrawRadius)) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

