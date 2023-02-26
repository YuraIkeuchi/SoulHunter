#pragma once
#include "BaseActor.h"
#include "ImGuiEditor.h"
/// �^�C�g���V�[��
class EditorSceneActor : public BaseActor {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;
	void ModelDraw(DirectXCommon* dxCommon);
	void FrontDraw(DirectXCommon* dxCommon);
	void BackDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void PostImGuiDraw(DirectXCommon* dxCommon);
	//�}�b�v�̐؂�ւ��̊֐�
	void StageMapChange(int StageNumber,LightGroup* lightgroup);
	//�}�b�v�̏�����
	void MapInitialize();
	//�X�V�����֐��킯
	//�e�N���X�̍X�V
	void AllUpdate(DebugCamera* camera);
	//���C�g�̐ݒu
	void LightSet(LightGroup* lightgroup);
	//�V�[���`�F���W�Ȃ�
	void ChangeUpdate();
	//�G�f�B�^�֌W
	void EditorUpdate();
private:
	//�G�f�B�^
	unique_ptr<ImGuiEditor> imguieditor;
	bool m_EnemyDelete = false;
	bool m_ObjDelete = false;

	bool m_MapChange = false;
};