#pragma once
#include <map>
#include <string>
#include "IKESprite.h"
#include "IKETexture.h"
#include "ParticleManager.h"
//2D�̓ǂݍ��ݏ���
class ImageManager  final {
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager& r) = default;
	ImageManager& operator= (const ImageManager& r) = default;

public:
	//�X�v���C�g�̖��O
	enum texName {
		Title = 27,
		TitleParts,
		BlackFilter,
		PauseBack,
		Pause1,
		PauseParts,
		PauseSkill,
		Option1,
		VolumBar,
		PauseSelect,
		NoItem,
		DushExplain,
		CompassExplain,
		LibraExplain,
		HealExplain,
		Save1,
		LoadText1,
		NowLoad1,
		ChestBack,
		Curtain,
		SkipText,
		IntroText,
		ClearText,
	};
	//�e�N�X�`���̖��O
	enum tex2dName {
		DushEffect,
		AttackEffect,
		ParticleEffect,
		DamageEffect,
		NormalEffect,
		SmokeTex,
		HealEffect,
		HitEffect,
		TutorialTex,
		ChestTex,
		WingEffect,
		LightTex,
		ReadTex,
		OutArea,
	};

	enum ParticleTex {
		Normal,
		Hoot
	};
public:
	static ImageManager* GetIns();		//�擾�p

	void Load2D();
	void LoadTex2D();
	void LoadParticle();

	static bool load;
};

