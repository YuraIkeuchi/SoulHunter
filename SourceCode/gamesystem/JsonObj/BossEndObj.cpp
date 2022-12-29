#include "BossEndObj.h"
#include "ModelManager.h"
#include "imgui.h"
#include "JsonLoader.h"
#include "ImageManager.h"
using namespace DirectX;
//������
void BossEndObj::Initialize() {

	jsonData = JsonLoader::LoadFile("BossApp");

	//���X�|�[���ʒu
	for (auto& objectData : jsonData->objects) {
		if (objectData.GimmickName == "NoGimmick") {
			// �t�@�C��������o�^�ς݃��f��������
			IKEModel* model = IKEModel::LoadFromOBJ(objectData.fileName, true);
			decltype(models)::iterator it = models.find(objectData.fileName);
			if (it != models.end()) {
				model = it->second;
			}

			// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			IKEObject3d* newObject = IKEObject3d::Create();
			newObject->SetModel(model);
			XMFLOAT3 Startpos;

			// ���W
			DirectX::XMStoreFloat3(&Startpos, objectData.translation);

			newObject->SetPosition(Startpos);

			// ��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			newObject->SetRotation(rot);

			// ���W
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			newObject->SetScale(scale);

			newObject->SetTiling(30.0f);
			// �z��ɓo�^
			objects.push_back(newObject);
		}
	}

	//�X�v���C�g����
	IKESprite* CurtainSprite_[2];
	//gaussian = new PostEffect();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite_[i] = IKESprite::Create(ImageManager::Curtain, { 0.0f,0.0f });
		CurtainSprite_[i]->SetAnchorPoint({ 0.5f,0.0f });
		CurtainSprite[i].reset(CurtainSprite_[i]);
	}

	CurtainSprite[0]->SetPosition({ 640.0f,0.0f });
	CurtainSprite[1]->SetPosition({ 640.0f,620.0f });

	IKESprite* SkipSprite_;
	SkipSprite_ = IKESprite::Create(ImageManager::SkipText, { 0.0f,0.0f });
	SkipSprite_->SetAnchorPoint({ 0.5f,0.0f });
	SkipSprite_->SetPosition({ 1000.0f,620.0f });
	SkipSprite.reset(SkipSprite_);

}
//�X�V
void BossEndObj::Update() {
	//pos = player->GetPosition();
	//�{�X�o��t���O����������^�C�}�[������
	if (m_EndStart && !m_EndEnd) {
		//�o��̊Ԃ�true
		m_End = true;
		m_EndTimer++;
		//���t���[���Ńt���O�I��
		if (m_EndTimer == 800) {
			//m_End = false;
			m_EndStart = false;
			m_EndEnd = true;
		}
	}

	//Json�p
	for (auto& object : objects) {
		object->Update();
	}

}
//�O�ʕ`��
const void BossEndObj::FrontDraw() {
}
//�w�i�`��
const void BossEndObj::BackDraw() {
	/*ImGui::Begin("BossEnd");
	ImGui::Text("m_End:%d", m_End);
	ImGui::Text("m_EndTimer:%d", m_EndTimer);
	ImGui::Text("m_End:%d", m_EndEnd);
	ImGui::Text("m_EndStart:%d", m_EndStart);
	ImGui::End();*/
	//Json�p
	for (auto& object : objects) {
		object->Draw();
	}

	IKESprite::PreDraw();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite[i]->Draw();
	}
	SkipSprite->Draw();
	IKESprite::PostDraw();
}
//���
void BossEndObj::Finalize() {

}