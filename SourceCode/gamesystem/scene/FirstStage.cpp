#include "FirstStage.h"

//������
void FirstStage::Initialize(DirectXCommon* dxCommon)
{
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	actor = new PlaySceneActor();
	actor->Initialize(dxCommon,camera,lightGroup);
}
//�X�V
void FirstStage::Update(DirectXCommon* dxCommon)
{
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void FirstStage::Draw(DirectXCommon* dxCommon)
{
	actor->Draw(dxCommon);
}
//���
void FirstStage::Finalize()
{
	actor->Finalize();
}
