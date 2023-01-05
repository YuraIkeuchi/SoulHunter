#pragma once
#include "BaseScene.h"
#include "ImGuiEditor.h"
#include "EnemyEdit.h"
#include "ObjEdit.h"
#include <array>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��

//�Q�[���v���C�V�[��
class EditorScene : public BaseScene
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
	void EnemyDelete();
	void ObjDelete();
	//�}�b�v�̏�����
	void MapInitialize();
	//�}�b�v�̐؂�ւ��̊֐�
	void StageMapChange(int StageNumber);
	//�v���C���[�ƃX�e�[�W�̓ǂݏ���
	void SaveGame();
	void LoadGame();


	//�X�V�����֐��킯
	//�e�N���X�̍X�V
	void AllUpdate();
	//���C�g�̐ݒu
	void LightSet();
	//�V�[���`�F���W�Ȃ�
	void ChangeUpdate();
	//�G�f�B�^�֌W
	void EditorUpdate();
private:
	//�G�f�B�^
	unique_ptr<ImGuiEditor> imguieditor;
	EnemyEdit* enemyedit = nullptr;
	ObjEdit* objedit = nullptr;
};