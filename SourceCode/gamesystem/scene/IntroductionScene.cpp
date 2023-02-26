#include "IntroductionScene.h"

//������
void IntroductionScene::Initialize(DirectXCommon* dxCommon) {
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	actor = new IntroductionSceneActor();
	actor->Initialize(dxCommon, camera, lightGroup);
}
//�X�V
void IntroductionScene::Update(DirectXCommon* dxCommon) {
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void IntroductionScene::Draw(DirectXCommon* dxCommon) {
	actor->Draw(dxCommon);
}
//���
void IntroductionScene::Finalize() {
	actor->Finalize();
}
