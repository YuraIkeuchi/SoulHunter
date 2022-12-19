#pragma once
#include "BaseScene.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��

//�Q�[���v���C�V�[��
class FirstStage : public BaseScene
{
private://�����o�ϐ�

public:
	//������
	void Initialize(DirectXCommon* dxCommon) override;
	//�X�V
	void Update(DirectXCommon* dxCommon) override;
	//�`��
	void Draw(DirectXCommon* dxCommon) override;
	//�J��
	void Finalize() override;
	void ModelDraw(DirectXCommon* dxCommon);
	void FrontDraw(DirectXCommon* dxCommon);
	void BackDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void PostImGuiDraw(DirectXCommon* dxCommon);

	//�v�f�S�폜
	void AllDelete();
	//�}�b�v�̏�����
	void MapInitialize();

	//�X�V�����֐��킯
	//�e�N���X�̍X�V
	void AllUpdate();
	//���C�g�̐ݒu
	void LightSet();
	//�{�X�����̍X�V
	void BossRoomUpdate();
	//�V�[���`�F���W�Ȃ�
	void ChangeUpdate();
	//�S�[������
	void GoalHit();
public:
};