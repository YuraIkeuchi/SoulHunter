#pragma once
#include <map>
#include <string>
#include "IKESprite.h"
#include "IKETexture.h"
//2Dの読み込み処理
class ImageManager  final {
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager& r) = default;
	ImageManager& operator= (const ImageManager& r) = default;

public:
	//スプライトの名前
	enum texName {
		Title = 26,
		TitleParts,
		GameOver,
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
		BossName,
		LoadText1,
		NowLoad1,
		ChestBack,
		LetterMessage,
		Curtain,
		SkipText,
		IntroText,
		ClearText,
	};
	//テクスチャの名前
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
		LetterTex,
		ReadTex,
		OutArea,
	};
public:
	static ImageManager* GetIns();		//取得用

	void Load2D();
	void LoadTex2D();

};

