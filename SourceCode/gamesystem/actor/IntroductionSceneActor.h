#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
/// �^�C�g���V�[��
class IntroductionSceneActor : public BaseActor {
public:
	/// ������
	void Initialize(DirectXCommon* dxCommon) override;
	/// �I��
	void Finalize() override;
	/// ���t���[���X�V
	void Update(DirectXCommon* dxCommon) override;
	/// �`��
	void Draw(DirectXCommon* dxCommon) override;

};