#pragma once
#include "InterBoss.h"

class FirstBoss :public InterBoss {
public:
	FirstBoss();
	bool Initialize() override;//������
	bool BattleInitialize() override;//������
	void Spec() override;//�{�X�̍s��
	void End() override;//�{�X���S
	void specialDraw() override;//���̃V�[���݂̂̕`��
	void specialDrawApp() override;//���̃V�[���݂̂̕`��
	void App() override;//�{�X�o��
	void DrawOutArea();//�A�E�g���C���̕`��
	void NotAttack();//�U�����Ă��Ȃ�
	void BesideAttack();//���ړ�
	void StabbingAttack();//�˂��h���Ă���U��
	void AppBossMove(XMFLOAT3 AfterPos, float AddFrame);//�{�X�o��V�[���̃C�[�W���O�֐�(���W)
	void AppBossRot(XMFLOAT3 AfterRot, float AddFrame);//�{�X�o��V�[���̃C�[�W���O�֐�(��])
private:
	//�A�E�g�G���A�̕`��
	unique_ptr<IKETexture> OutAreatexture;
	XMFLOAT3 m_OutPos = { 0.0f,0.0f,0.0f };
	XMFLOAT4 m_OutColor = { 1.0f,1.0f,1.0f,1.0f };
	XMFLOAT3 m_OutScale = { 0.5f,10.0f,1.0f };
	bool m_DrawArea = false;
	//�A�j���[�V�����֌W
	int m_Number = 0;
	bool m_AnimeLoop = false;
	int m_AnimeTimer = 0;
	int m_AnimeSpeed = 1;
	bool m_AnimationStop = false;
	int m_AppTimer = 0;
	int m_AppNumber = 0;
	enum AppNumber {
		NoMove,
		FirstMove,
		SecondMove,
		ThirdMove,
		FourthMove,
		FifthMove,
	};
};