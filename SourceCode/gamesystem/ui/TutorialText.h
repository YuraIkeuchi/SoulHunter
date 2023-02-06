#pragma once
#include"IKESprite.h"
#include"Player.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include <array>
#include "CollisionPrimitive.h"
#include "PlayerEffect.h"
using namespace std;         //  ���O��Ԏw��
//�`���[�g���A���̃N���X(�Ŕ�)
class TutorialText {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	TutorialText();
	//�X�V
	void Update();
	//�`��
	const void Draw();
	const void SpriteDraw();//�������`��
	void ImGuiDraw();
	//�����蔻��
	bool Collide();
	//�}�b�v���Ƃ̏�����
	void InitBoard(int StageNumber);
	//�`���[�g���A���̏�
	void Mission();
	//�Ŕ̓���
	void MoveBoard();
	//�X�v���C�g�̓���
	void ChangeSprite();
	//��ƌ��̓����蔻��
	bool RockCollide();
	//��̏��
	void RockState();
	//���[�h�Q�[�����̏ꍇ
	void LoadGame();
	//�p�[�e�B�N��
	void BirthParticle();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//�萔
	static const int Tutorial_Max = 7;//�`���[�g���A���̐�

public:

private:
	//�N���X
	vector<PlayerEffect*> effects;
	unique_ptr<Player> player = nullptr;
	//OBB
	OBB OBB1 = {};
	OBB OBB2 = {};
	//OBJ
	IKEModel* modelboard = nullptr;
	array<unique_ptr <IKEObject3d>,Tutorial_Max> objboard;

	IKEModel* modelblock = nullptr;
	unique_ptr<IKEObject3d> objblock;
	XMFLOAT3 m_blockPosition = {83.0f,-280.0f,5.0f};
	XMFLOAT3 m_blockScale = {1.0f,1.5f,2.5f};
	XMFLOAT4 m_blockColor = {1.0f,1.0f,1.0f,1.0f};
	//�e�N�X�`����X�v���C�g
	array<unique_ptr<IKESprite>,Tutorial_Max> TutorialSprite;
	//���̑��ϐ�
	//XMFLOAT3 m_TexPosition;//�e�L�X�g�̈ʒu
	array<XMFLOAT3,Tutorial_Max> m_BoardPosition;//�Ŕ̈ʒu
	////�Ŕ����邩
	array<bool,Tutorial_Max> m_BoardAlive;
	array<bool, Tutorial_Max> m_BoardDraw;
	array<int, Tutorial_Max> m_ParticleCount;
	//�`���[�g���A���̐i�s��
	int m_TutorialMission = 0;
	//�Ŕ̓�����
	array<int, Tutorial_Max> m_BoardState;
	//�Ŕ̈ʒu(Y���̂�)
	array<float, Tutorial_Max> m_AfterPosY;
	//�t���[��
	array<float, Tutorial_Max> m_Frame;
	////�e�L�X�g�̕ϐ�
	array<int, Tutorial_Max> m_SpriteState;
	array<XMFLOAT2, Tutorial_Max> m_TexSize;
	array<XMFLOAT2, Tutorial_Max> m_AfterTexSize;

	bool m_Damage = false;
	int m_DamageTimer = 0;
	int m_ClearCount = 0;
	enum TutorialType {
		Move,
		CameraMove,
		Jump,
		Rolling,
		Pause,
		Map,
		Attack,
	};

	enum TutorialMission {
		FirstMission,
		SecondMission,
		ThirdMission,
		FinishMission,
	};

	enum BoardState {
		NoMove,
		UpBoard,
		DownBoard
	};

	enum SpriteState {
		NoSize,
		WideSprite,
		ShrinkSprite
	};

	//�`���[�g���A���̏�
	int m_MoveCount = 0;

	//���@������
	int m_AttackCount = 0;
};