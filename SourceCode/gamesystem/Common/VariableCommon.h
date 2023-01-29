#pragma once
//���ʂ̕ϐ��͂܂Ƃ߂�(��Ƀ}�W�b�N�i���o�[)
const float m_ColorMax = 1.0f;//���ߓx�̍ő�
const float m_ColorMin = 0.0f;//���ߓx�̍ŏ�

//�t���[���̍ő�ƍŏ�(�C�[�W���O�̂��߂̂��)
const float m_FrameMax = 1.0f;
const float m_FrameMin = 0.0f;
//�T�C�Y�؂���T�C�Y
//�t���X�N���[��
const int FullWidth_Cut = 1280;
const int FullHeight_Cut = 720;
//���[�h���
const int LoadWidth_Cut = 712;
const int LoadHeight_Cut = 128;
//�������
const int ExplainWidth_Cut = 1028;
const int ExplainHeight_Cut = 128;
//�Z�[�u���
const int SaveWidth_Cut = 512;
const int SaveHeight_Cut = 64;
//�`���[�g���A�����
const int TutorialWidth_Cut = 256;
const int TutorialHeight_Cut = 128;
//�^�C�g����I�v�V�����̃p�[�c���
const int PartsWidth_Cut = 640;
const int PartsHeight_Cut = 128;

//�X�e�[�W�i���o�[
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
//�U����H���������
enum HitDir {
	NoHit,
	HitRight,
	HitLeft,
	HitUp,
	HitDown,
};
//�u�����h�^�C�v
enum BlendType
{
	AlphaBlendType,
	AddBlendType,
	SubBlendType,
};


//�G�̎��
enum EnemyType {
	Normal,
	Thorn,
	Bound,
	Bird,
	Follow,
};

//�w�iOBJ�̎��
enum BackObjType {
	Rock,
	Box,
	Torch,
};

