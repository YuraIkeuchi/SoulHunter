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
	void MoveLoad();
private:
	//�萔
	static const int Now_Max = 4;
	static const int Load_Max = 5;
private://�����o�ϐ�
	array<unique_ptr<IKESprite>, Now_Max> nowsprite;
	array<unique_ptr<IKESprite>, Load_Max> loadsprite;
	XMFLOAT2 m_Position = { 640.0f,320.0f };
	XMFLOAT2 m_Size = { 1028.0f,128.0f };
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

	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
};