#pragma once
#include "InterBoss.h"

class FirstBoss :public InterBoss {
public:
	FirstBoss();
	void Initialize() override;//������
	void Spec() override;//�{�X�̍s��
	void End() override;//�{�X���S
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void App() override;//�{�X�o��
	void DrawOutArea();//�A�E�g���C���̕`��
	void NotAttack();//�U�����Ă��Ȃ�
	void BesideAttack();//���ړ�
	void StabbingAttack();//�˂��h���Ă���U��
private:
	//�A�E�g�G���A�̕`��
	unique_ptr<IKETexture> OutAreatexture;
	XMFLOAT3 m_OutPos = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_OutColor = { 1.0f,1.0f,1.0f,1.0f };
	XMFLOAT3 m_OutScale = { 0.5f,10.0f,1.0f };
	bool m_DrawArea = false;
};