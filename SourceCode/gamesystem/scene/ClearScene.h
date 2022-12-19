#pragma once
#include "IKESprite.h"
#include "BaseScene.h"
/// �^�C�g���V�[��
class ClearScene : public BaseScene {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;

private://�����o�ϐ�
	IKESprite* sprite = { nullptr };
};

