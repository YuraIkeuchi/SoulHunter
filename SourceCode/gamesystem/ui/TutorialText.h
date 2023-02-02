#pragma once
#include"IKESprite.h"
#include"Player.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include <array>
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
	//�����蔻��
	bool Collide();
	//�}�b�v���Ƃ̏�����
	void InitBoard(int StageNumber);
	//�e�N�X�`���̓���
	void MoveTex();
	//�X�v���C�g�̏o��
	void SpriteAppear();
	
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//�萔
	static const int Tutorial_Max = 6;//�`���[�g���A���̐�

public:
	////getter
	//const XMFLOAT3& GetPosition() { return m_BoardPosition; }
	////setter
	//void SetPosition(const XMFLOAT3& m_BoardPosition) { this->m_BoardPosition = m_BoardPosition; }
private:
	//�N���X
	unique_ptr<Player> player = nullptr;
	//OBJ
	IKEModel* modelboard = nullptr;
	array<unique_ptr <IKEObject3d>,Tutorial_Max> objboard;
	//�e�N�X�`����X�v���C�g
	//unique_ptr<IKESprite> TutorialSprite[Tutorial_Max][TutorialAnime_Max];
	//���̑��ϐ�
	//XMFLOAT3 m_TexPosition;//�e�L�X�g�̈ʒu
	array<XMFLOAT3,Tutorial_Max> m_BoardPosition;//�Ŕ̈ʒu
	////�Ŕ����邩
	array<bool,Tutorial_Max> m_BoardAlive;
	////sin�g�Ɏg������
	//float m_Angle = 0.0f;
	//float m_Angle2 = 0.0f;
	
	////�e�L�X�g���o�邩
	//bool m_TexAlive = false;
	//int m_TextNumber = 0;
	////�e�L�X�g�̕ϐ�
	//array<bool, Tutorial_Max> m_ReadTex;
	//array<float, Tutorial_Max> m_Frame;
	//array<bool, Tutorial_Max> m_InCount;
	//array<bool, Tutorial_Max> m_OutCount;
	//array<XMFLOAT2, Tutorial_Max> m_TexSize;
	//
	//int m_AnimeTimer = 0;
	//int m_AnimeCount = 0;


	enum TutorialType {
		Move,
		Rolling,
		Jump,
		Pause,
		Map,
		Attack,
	};
};