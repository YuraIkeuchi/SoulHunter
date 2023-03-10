#include "EnemyEdit.h"
#include "Enemy.h"
#include "ThornEnemy.h"
#include "BirdEnemy.h"
#include "BoundEnemy.h"
#include "FollowEnemy.h"
#include "ChestEnemy.h"
//通常の敵の生成
void EnemyEdit::NormalEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player){
	InterEnemy* newEnemy;
	newEnemy = new Enemy();
	newEnemy->Initialize();
	newEnemy->SetPlayer(player);
	newEnemy->SetPosition(player->GetPosition());
	newEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newEnemy);
}
//棘の敵の生成
void EnemyEdit::ThornEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player) {
	InterEnemy* newThornEnemy;
	newThornEnemy = new ThornEnemy();
	newThornEnemy->Initialize();
	newThornEnemy->SetPlayer(player);
	newThornEnemy->SetThornPos(player->GetPosition().y - 5.0f);
	newThornEnemy->SetPosition({ player->GetPosition().x, 0.0f, player->GetPosition().z });
	enemy.push_back(newThornEnemy);
}
//跳ねる敵の生成
void EnemyEdit::BoundEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player) {
	InterEnemy* newBoundEnemy;
	newBoundEnemy = new BoundEnemy();
	newBoundEnemy->Initialize();
	newBoundEnemy->SetPlayer(player);
	newBoundEnemy->SetPosition(player->GetPosition());
	newBoundEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newBoundEnemy);
}
//飛ぶ敵の生成
void EnemyEdit::BirdEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player) {
	InterEnemy* newBirdEnemy;
	newBirdEnemy = new BirdEnemy();
	newBirdEnemy->Initialize();
	newBirdEnemy->SetPlayer(player);
	newBirdEnemy->SetPosition(player->GetPosition());
	newBirdEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newBirdEnemy);
}
//追従の敵の生成
void EnemyEdit::FollowEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player) {
	InterEnemy* newFollowEnemy;
	newFollowEnemy = new FollowEnemy();
	newFollowEnemy->Initialize();
	newFollowEnemy->SetPlayer(player);
	newFollowEnemy->SetPosition(player->GetPosition());
	newFollowEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newFollowEnemy);
}
//通常の敵の生成
void EnemyEdit::ChestEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player) {
	InterEnemy* newChestEnemy;
	newChestEnemy = new ChestEnemy();
	newChestEnemy->Initialize();
	newChestEnemy->SetPlayer(player);
	newChestEnemy->SetPosition({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + 5.0f });
	newChestEnemy->SetStartPos({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + 5.0f });
	enemy.push_back(newChestEnemy);
}