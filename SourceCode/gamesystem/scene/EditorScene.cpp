#include "EditorScene.h"
#include "Audio.h"
#include "SceneManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "PlayerSkill.h"
#include "ParticleEmitter.h"
//������
void EditorScene::Initialize(DirectXCommon* dxCommon)
{
	dxCommon->SetFullScreen(false);
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//�G�f�B�^�[�V�[���̃A�N�^�[
	BaseActor* actor_;
	actor_ = new EditorSceneActor();
	actor_->Initialize(dxCommon,camera,lightGroup);
	actor.reset(actor_);
}
//�X�V
void EditorScene::Update(DirectXCommon* dxCommon)
{
	actor->Update(dxCommon, camera, lightGroup);
}
//�`��
void EditorScene::Draw(DirectXCommon* dxCommon)
{
	actor->Draw(dxCommon);
}
//���
void EditorScene::Finalize()
{
	actor->Finalize();
}
