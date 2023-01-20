#include "PlayerEffect.h"

PlayerEffect::PlayerEffect() {
	
}

void PlayerEffect::CreateEffect(const std::string& newname, XMFLOAT3 pos, int dir) {
	if (newname == "Attack") {
		AttackEffect* newAttackEffect;
		newAttackEffect = new AttackEffect();
		newAttackEffect->Initialize();
		newAttackEffect->SetEffect(pos, dir);
		attackeffects.push_back(newAttackEffect);
	}
	else if (newname == "Damege") {
		PlayerDamageEffect* newDamageEffect;
		newDamageEffect = new PlayerDamageEffect();
		newDamageEffect->Initialize();
		damageeffects.push_back(newDamageEffect);
	}
	else if (newname == "Wall") {
		WallAttackEffect* newwallEffect;
		newwallEffect = new WallAttackEffect();
		newwallEffect->Initialize();
		walleffects.push_back(newwallEffect);
	}
	else if (newname == "Dush") {
		PlayerDushEffect* newDushEffect;
		newDushEffect = new PlayerDushEffect();
		newDushEffect->Initialize();
		dusheffects.push_back(newDushEffect);
	}
}

void PlayerEffect::Initialize() {

}

void PlayerEffect::Update(XMFLOAT3 pos, XMFLOAT3 attackpos,bool dush, bool damage, int dir) {
	//エフェクト関係
	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Update();
		}
	}

	for (WallAttackEffect* walleffect : walleffects) {
		if (walleffect != nullptr) {
			walleffect->Update(attackpos, dir);
		}
	}

	for (PlayerDushEffect* dusheffect : dusheffects) {
		if (dusheffect != nullptr) {
			dusheffect->Update(pos, dush);
		}
	}

	for (PlayerDamageEffect* damageeffect : damageeffects) {
		if (damageeffect != nullptr) {
			damageeffect->Update(pos, damage);
		}
	}
}

void PlayerEffect::Draw() {
	//エフェクトの描画
	for (AttackEffect* attackeffect : attackeffects) {
		if (attackeffect != nullptr) {
			attackeffect->Draw();
		}
	}

	for (WallAttackEffect* walleffect : walleffects) {
		if (walleffect != nullptr) {
			walleffect->Draw();
		}
	}

	for (PlayerDushEffect* dusheffect : dusheffects) {
		if (dusheffect != nullptr) {
			dusheffect->Draw();
		}
	}

	for (PlayerDamageEffect* damageeffect : damageeffects) {
		if (damageeffect != nullptr) {
			damageeffect->Draw();
		}
	}
}