#pragma once
#include "IKESprite.h"
#include "IKETexture.h"
#include <array>   
#include <memory> 
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��

//�`�F�X�g�J�������G�t�F�N�g�o�܂�
class ChestEffect {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	ChestEffect();

	void Initialize();//������
	void Finalize();//���
	void Update(XMFLOAT3 StartPos,XMFLOAT3 TargetPos,int ChestState);//�X�V
	void Draw();//�`��
	void EffectMove(XMFLOAT3 StartPos, XMFLOAT3 TargetPos, int ChestState);//�G�t�F�N�g�̓���
private:
	//�萔
	static const int ChestEffect_Max = 10;//�p�[�e�B�N���̐�
private:
	//�e�N�X�`��
	array<unique_ptr<IKETexture>, ChestEffect_Max> chesteffect;
	//�ϐ�
	array<bool, ChestEffect_Max> m_Alive;//�����t���O
	array<bool, ChestEffect_Max> m_StartEffect;//�n�܂����u��
	array<XMFLOAT3,ChestEffect_Max> m_pos;//���W
	array<XMFLOAT3, ChestEffect_Max> m_scale;//�傫��
	array<XMFLOAT4, ChestEffect_Max> m_color;//�F
	array<XMFLOAT3, ChestEffect_Max> m_AfterPos;//�C�[�W���O�̌�̃|�W�V����
	array<float, ChestEffect_Max> m_Angle;//��ԕ���
	array<XMFLOAT2, ChestEffect_Max> m_speed;//����
	array<float, ChestEffect_Max> m_Frame;//�t���[����
	array<int, ChestEffect_Max> m_TargetTimer;//�����n�߂�܂ł̎���
	array<int, ChestEffect_Max> m_MoveNumber;//����
	enum MoveNumber {
		Wide,
		TargetPlayer,
	};
};