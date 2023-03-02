#include "BossStagObj.h"
#include "ModelManager.h"
#include "imgui.h"
#include "JsonLoader.h"
#include "ImageManager.h"
#include "ParticleEmitter.h"
#include <random>
using namespace DirectX;
//������
void BossStagObj::Initialize() {
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
void BossStagObj::AppUpdate() {
	//pos = player->GetPosition();
	//�{�X�o��t���O����������^�C�}�[������
	if (m_AppStart && !m_EndApp) {
		//�o��̊Ԃ�true
		m_App = true;
		m_AppTimer++;
		//���t���[���Ńt���O�I��
		if (m_AppTimer == 800) {
			//m_App = false;
			m_AppStart = false;
			m_EndApp = true;
		}
	}

	//Json�p
	for (auto& object : objects) {
		object->Update();
	}
}
void BossStagObj::EndUpdate() {
	m_EndTimer++;
	//Json�p
	for (auto& object : objects) {
		object->Update();
	}
	m_ParticleCount++;
	DeathParticle();
}
//�O�ʕ`��
const void BossStagObj::FrontDraw() {
	//�p�[�e�B�N���̕`��
	IKESprite::PreDraw();
	for (int i = 0; i < CurtainSprite.size(); i++) {
		CurtainSprite[i]->Draw();
	}
	SkipSprite->Draw();
	IKESprite::PostDraw();
}
//�w�i�`��
const void BossStagObj::BackDraw() {
	IKEObject3d::PreDraw();
	//Json�p
	for (auto& object : objects) {
		object->Draw();
	}
	IKEObject3d::PostDraw();
}
//���
void BossStagObj::Finalize() {
}
//���񂾎��̃p�[�e�B�N��
void BossStagObj::DeathParticle() {
	XMFLOAT4 s_color = { 1.0f,0.5f,0.0f,1.0f };
	XMFLOAT4 e_color = { 1.0f,0.5f,0.0f,1.0f };
	float s_scale = 2.0f;
	float e_scale = 4.0f;
	float l_velocity = 0.1f;
	float l_randZ = 0.0f;
	if (m_ParticleCount > 1) {
		//�����w��
		mt19937 mt{ std::random_device{}() };
		uniform_int_distribution<int> l_dist(-4, 4);
		l_randZ = float(l_dist(mt));
		for (int i = 0; i < 3; ++i) {
			ParticleEmitter::GetInstance()->DeathEffect(50, { 0.0f,8.0f,20.0f + l_randZ }, s_scale, e_scale, s_color, e_color, l_velocity);
		}
		m_ParticleCount = 0;
	}
}
