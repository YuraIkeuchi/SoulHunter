#pragma once
#include"IKESprite.h"
#include "IKETexture.h"
#include"Player.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "VariableCommon.h"
#include <list> // �w�b�_�t�@�C���C���N���[�h
#include <array>
using namespace std;         //  ���O��Ԏw��
//�`���[�g���A���̃N���X(�Ŕ�)
class TutorialText {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	TutorialText();
	//�X�V
	void Update(int TexNumber);
	//�`��
	const void Draw();
	//�����蔻��
	bool Collide(int TexNumber);
	//�}�b�v���Ƃ̏�����
	void InitBoard(int StageNumber,int TexNumber);
	//�e�N�X�`���̓���
	void MoveTex();
	//�X�v���C�g�̏o��
	void SpriteAppear(int TexNumber);
	
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//�萔
	static const int Tutorial_Max = 5;//�`���[�g���A���̐�
	static const int TutorialAnime_Max = 2;//�`���[�g���A���̃A�j���̐�
public:
	//getter
	const XMFLOAT3& GetPosition() { return m_BoardPosition; }
	bool GetAlive() { return m_BoardAlive; }
	//setter
	void SetPosition(const XMFLOAT3& m_BoardPosition) { this->m_BoardPosition = m_BoardPosition; }
	void SetBoardAlive(bool m_BoardAlive) { this->m_BoardAlive = m_BoardAlive; }
private:
	//�N���X
	unique_ptr<Player> player = nullptr;
	//unique_ptr<TextBoard> textboard = nullptr;
	//OBJ
	IKEModel* modelboard = nullptr;
	unique_ptr <IKEObject3d> objboard;
	//�e�N�X�`����X�v���C�g
	unique_ptr<IKETexture> tutorialPointTex;
	//array<array<unique_ptr<IKESprite>,Tutorial_Max>> TutorialSprite;
	unique_ptr<IKESprite> TutorialSprite[Tutorial_Max][TutorialAnime_Max];
	//���̑��ϐ�
	XMFLOAT3 m_TexPosition;//�e�L�X�g�̈ʒu
	XMFLOAT3 m_BoardPosition;//�Ŕ̈ʒu
	//sin�g�Ɏg������
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
	//�Ŕ����邩
	bool m_BoardAlive = true;
	//�e�L�X�g���o�邩
	bool m_TexAlive = false;
	int m_TextNumber = 0;
	//�e�L�X�g�̕ϐ�
	array<bool, Tutorial_Max> m_ReadTex;
	array<float, Tutorial_Max> m_Frame;
	array<bool, Tutorial_Max> m_InCount;
	array<bool, Tutorial_Max> m_OutCount;
	array<XMFLOAT2, Tutorial_Max> m_TexSize;
	
	int m_AnimeTimer = 0;
	int m_AnimeCount = 0;
};