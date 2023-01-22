#pragma once
#include "IKESprite.h"
#include "Player.h"
#include "Save.h"
#include "MapChip.h"
#include <array>   
using namespace std;         //  ���O��Ԏw��
//�~�j�}�b�v
class MiniMap {
public:
	MiniMap();
	void SetPlayer(Player* player) { this->player = player; }
	void SetSave(Save* save) { this->save = save; }
	void Initialize();//������
	void Update();//�X�V
	void Finalize();//���
	const void Draw();//�`��
	void UseCompass();//�X�L��(�R���p�X)���g���Ă��邩
	void SetMiniPlayerPos(int StageNumber);//�X�e�[�W���Ƃ̏�����
	void InitMap(std::vector<std::vector<int>>& map, int StageNumber);//�}�b�v�̏�����
	void ResetBlock();//�}�b�v�̃��Z�b�g
	void MoveStateTex();//�e�L�X�g�̓���
	//�}�b�v�`�b�v����
	void MapCreate(int mapNumber, int StageNumber);
	//�}�b�v�I����
	void SelectMapType();
	void WholeUpdate();
	void SelectUpdate();
	void ColorChange();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//getter
	bool GetReturnMap() { return m_ReturnMap; }
	int GetMapType() { return m_MapType; }
	XMFLOAT4 GetMapColor() { return m_MapColor; }
	//setter
	void SetReturnMap(bool m_ReturnMap) { this->m_ReturnMap = m_ReturnMap; }
	void SetDushDraw(bool m_DushDraw) { this->m_DushDraw = m_DushDraw; }
	void SetChangeColorType(int m_ColorChangeType) { this->m_ColorChangeType = m_ColorChangeType; }
	void SetMapType(int m_MapType) { this->m_MapType = m_MapType; }
private:
	const float m_LAND_SCALEX = 22.0f;
	const float m_LAND_SCALEY = 12.0f;
	Player* player = nullptr;
	Save* save = nullptr;
	XMFLOAT2 m_PlayerPos;
	XMFLOAT2 m_SavePos;
	XMFLOAT2 m_DushPos;
	//�X�v���C�g
	unique_ptr<IKESprite> MiniMapSprite;
	unique_ptr<IKESprite> MiniPlayerSprite;
	unique_ptr<IKESprite> MiniSaveSprite;
	unique_ptr<IKESprite> MiniDushSprite;
	unique_ptr<IKESprite> MiniBlockSprite[map_max_y][map_max_x]; //�X�e�[�W�u���b�N
	unique_ptr<IKESprite> MiniBlockTogeSprite[map_max_y][map_max_x]; //�X�e�[�W�u���b�N(��)
	unique_ptr<IKESprite> WholeMapSprite;
	unique_ptr<IKESprite> MapStateSprite;
	//�ϐ�
	XMFLOAT3 m_Distance[map_max_y][map_max_x];
	bool LookMap[map_max_y][map_max_x];
	//�e�}�b�v�̓ǂݍ���
	std::vector<std::vector<int>> stagemap; //1�}�b�v
	bool m_ReturnMap = false;
	bool LookPlayer = false;
	//�X�e�[�W�i���o�[
	int m_StageNumber = 0;
	//�_�b�V���̃X�v���C�g�̕`�攻��
	bool m_DushDraw = false;
	enum StageNumber {
		Map1,
		Map2,
		Map3,
		Map4,
		Map5,
		Map6,
		BossMap,
		TutoRial,
	};
	//�F
	XMFLOAT4 m_PlayerColor = { 1.0f,1.0f,1.0f,0.0f };
	XMFLOAT4 m_SaveColor = { 1.0f,1.0f,1.0f,0.0f };
	XMFLOAT4 m_MapColor = { 1.0f,1.0f,1.0f,0.0f };
	XMFLOAT4 m_WholeColor = { 1.0f,1.0f,1.0f,1.0f };
	XMFLOAT4 m_DushColor = { 1.0f,1.0f,1.0f,0.0f };
	//���߂̓���
	int m_ColorChangeType = 0;
	enum ChangeType {
		No,
		Add,
		Sub,
	};
	//���ɗ����e�L�X�g�֌W�̊֐�
	XMFLOAT2 m_SelectPos;
	XMFLOAT2 m_SelectSize = { 96.0f,96.0f };
	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;

	bool m_MapTypeChange = false;
	int m_MapType = 0;
	enum MapType {
		Whole,
		SelectMap
	};
	int m_StateTextNumber = 0;
	int m_TextTimer = 0;
	XMFLOAT2 m_StatePos = { 0.0f,0.0f };
	XMFLOAT2 m_AfterStatePos = { 0.0f,0.0f };
	float m_Frame = 0.0f;
	enum StateTextNumber {
		NoText,
		StartText,
		BackText,
	};
};