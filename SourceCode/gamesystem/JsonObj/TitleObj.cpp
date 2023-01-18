#include "TitleObj.h"
#include "JsonLoader.h"
#include "ImageManager.h"
using namespace DirectX;	
//������
void TitleObj::Initialize() {

	ParticleManager* fire_ = new ParticleManager();
	fire_->Initialize(ImageManager::ParticleEffect);
	fire.reset(fire_);
	jsonData = JsonLoader::LoadFile("Title");


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
}
//�X�V
void TitleObj::Update() {
	//Json�p
	for (auto& object : objects) {
		object->Update();
	}
	BirthParticle();
}
//�O�ʕ`��
const void TitleObj::FrontDraw() {
	fire->Draw(addBle);
}
//�w�i�`��
const void TitleObj::BackDraw() {
	//Json�p
	for (auto& object : objects) {
		object->Draw();
	}
}
//���
void TitleObj::Finalize() {

}

void TitleObj::BirthParticle() {
	XMFLOAT3 pos = { 0.0f,23.0f,0.0f };

	const float rnd_vel = 0.05f;
	XMFLOAT3 vel{};
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * rnd_vel * 2.0f;// -rnd_vel / 2.0f;
	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

	fire->Add(20, { pos.x,pos.y + 3.0f,pos.z }, vel, {}, 1.0f, 0.0f, { 1.0f,0.5f,0.0f,0.5f }, { 1.0f,0.5f,0.0f,0.5f });

	fire->Update();
}