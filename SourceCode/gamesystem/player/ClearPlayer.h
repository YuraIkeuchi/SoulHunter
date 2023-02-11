#pragma once
#pragma once
#include "DirectXCommon.h"
#include "ObjCommon.h"

class ClearPlayer :
	public ObjCommon
{
public:
	ClearPlayer();
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize() override;

	void StateInitialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

	//����
	void ClearMove(int Timer);

private:

	//�A�j���[�V�����^�C�}�[�p
	struct AnimationTimer {
		int MoveAnimation = 0;
		int NotAnimation = 0;
		int FallAnimation = 0;
	};

	AnimationTimer m_AnimationTimer;
};