#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
/// �^�C�g���V�[��
class LoadSceneActor : public BaseActor {
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
	void GameDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void SpriteDraw();
private://�����o�ϐ�
	unique_ptr<IKESprite> nowsprite[4];
	unique_ptr<IKESprite> loadsprite[2];
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,1.0f };
	//�ǂ̃e�L�X�g���o����
	int m_LoadNumber = 0;
	enum TitleSelect {
		Pause,
		Soul
	};

	//�A�j���[�V����
	int m_LoadAnimeTimer = 0;
	int m_LoadAnimeCount = 0;
	//���[�f�B���O��ʂ̃^�C�}�[
	int m_LoadTimer = 0;
	int m_LoadChackCount = 0;
};