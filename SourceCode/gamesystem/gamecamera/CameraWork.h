#pragma once
#include "Player.h"
#include "InterBoss.h"
#include "DebugCamera.h"
#include "Camera.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�Q�[���̃J�����̓���
class CameraWork {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	CameraWork();
	void Update(DebugCamera* camera);//�X�V
	void TitleCamera();//�^�C�g���̃J����
	void IntroductionCamera();//�����̃J����
	void NormalCamera();//���ʂ̃J����(�v���C���[�ɒǏ])
	void RightStickCamera();//�E�X�e�B�b�N�œ������J����
	void AppCamera();//�{�X�o�ꎞ�̃J����
	void AppCameraMove(XMFLOAT3 m_AfterEye, XMFLOAT3 m_AfterTarget,float AddFrame);//��̂�̓���
	void ImGuiDraw();//ImGui

	void SetPlayer(Player* player) { this->player.reset(player); }
	void SetInterBoss(InterBoss* interboss) { this->interboss.reset(interboss); }
public:
	//getter setter
	void SetCameraType(int m_CameraType) { this->m_CameraType = m_CameraType; }
	void SetIntroTimer(int m_IntroTimer) { this->m_IntroTimer = m_IntroTimer; }
	int GetCameraNumber() { return  m_AppCameraNumber; }
	bool GetEndApp() { return  m_EndApp; }
	float GetFrame() { return  m_Frame; }
private:
	//�N���X
	unique_ptr<Player> player;
	unique_ptr<InterBoss> interboss;
	//�C�[�W���O�̕ϐ�
	float m_Frame = 0.0f;
	XMFLOAT3 m_AfterEye = { 0.0f,0.0f,0.0f };
	XMFLOAT3 m_AfterTarget = { 0.0f,0.0f,0.0f };
	//���_���W
	XMFLOAT3 m_eyePos = { 0.0f,0.0f,0.0f };
	//�����_���W
	XMFLOAT3 m_targetPos = { 0.0f,0.0f,0.0f };
	//�^�C�g���̃J�����̕ϐ�
	//�~�^���̂���
	float m_PI = 3.14f;
	float m_TitleCameraRadius = 0.0f;
	float m_TitleCameraSpeed = 0.0f;
	float m_TitleCameraScale = 80.0f;// LaneNum�ƈꏏ�ɕς��邱��
	float m_TitleCameraCircleX = 0.0f;
	float m_TitleCameraCircleZ = 0.0f;
	//�{�X�V�[���̃J�����̓���
	int m_AppCameraNumber = 0;//�o��V�[���̃J�����ԍ�
	int m_Timer = 0;//�^�C�}�[
	bool m_EndApp = false;//�o��V�[�����I�������

	//�E�X�e�B�b�N�œ�������
	float m_MoveCameraY = 0.0f;//�J�����̈ړ���
	float m_AfterMoveCameraY = 0.0f;//�J�����̈ړ��ʂ̏I���_
	float m_Rightframe = 0.0f;//�t���[��
	int m_MoveDir = 0;//��������
	bool m_MoveCamera = false;//�J�����𓮂����Ă��邩
	enum MoveDir {
		NoCamera,
		UpCamera,
		DownCamera,
	};
	enum AppCamera {
		No,
		Camera1,
		Camera2,
		Camera3,
		Camera4,
		Camera5,
		Camera6,
		Camera7,
	};
	//�J�����̃^�C�v
	int m_CameraType = 0;
	enum CameraType {
		Title,
		Introduction,
		Normal,
		BossAPP,
	};

	//�����V�[��
	int m_IntroTimer = 0;
	bool m_IntEyeStart = false;
	bool m_IntTargetStart = false;
};