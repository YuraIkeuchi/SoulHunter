#include "EnemyEdit.h"
#include "Enemy.h"
#include "ThornEnemy.h"
#include "BirdEnemy.h"
#include "BoundEnemy.h"
#include "FollowEnemy.h"
#include "ChestEnemy.h"
//’Êí‚Ì“G‚Ì¶¬
void EnemyEdit::NormalEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player,
	Block* block){
	InterEnemy* newEnemy;
	newEnemy = new Enemy();
	newEnemy->Initialize();
	newEnemy->SetPlayer(player);
	newEnemy->SetBlock(block);
	newEnemy->SetPosition(player->GetPosition());
	newEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newEnemy);
}
//™‚Ì“G‚Ì¶¬
void EnemyEdit::ThornEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player) {
	InterEnemy* newThornEnemy;
	newThornEnemy = new ThornEnemy();
	newThornEnemy->Initialize();
	newThornEnemy->SetPlayer(player);
	newThornEnemy->SetThornPos(player->GetPosition().y - 5.0f);
	newThornEnemy->SetPosition({ player->GetPosition().x, 0.0f, player->GetPosition().z });
	enemy.push_back(newThornEnemy);
}
//’µ‚Ë‚é“G‚Ì¶¬
void EnemyEdit::BoundEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player,
	Block* block) {
	InterEnemy* newBoundEnemy;
	newBoundEnemy = new BoundEnemy();
	newBoundEnemy->Initialize();
	newBoundEnemy->SetPlayer(player);
	newBoundEnemy->SetBlock(block);
	newBoundEnemy->SetPosition(player->GetPosition());
	newBoundEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newBoundEnemy);
}
//”ò‚Ô“G‚Ì¶¬
void EnemyEdit::BirdEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player,
	Block* block) {
	InterEnemy* newBirdEnemy;
	newBirdEnemy = new BirdEnemy();
	newBirdEnemy->Initialize();
	newBirdEnemy->SetPlayer(player);
	newBirdEnemy->SetBlock(block);
	newBirdEnemy->SetPosition(player->GetPosition());
	newBirdEnemy->SetStartPos(player->GetPosition());
	enemy.push_back(newBirdEnemy);
}
//’Ç]‚Ì“G‚Ì¶¬
void EnemyEdit::FollowEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player,Block* block) {
	InterEnemy* newFollowEnemy;
	newFollowEnemy = new FollowEnemy();
	newFollowEnemy->Initialize();
	newFollowEnemy->SetPlayer(player);
	newFollowEnemy->SetPosition(player->GetPosition());
	newFollowEnemy->SetStartPos(player->GetPosition());
	newFollowEnemy->SetBlock(block);
	enemy.push_back(newFollowEnemy);
}
//’Êí‚Ì“G‚Ì¶¬
void EnemyEdit::ChestEnemyArgment(std::vector<InterEnemy*>& enemy, GamePlayer* player,
	Block* block) {
	InterEnemy* newChestEnemy;
	newChestEnemy = new ChestEnemy();
	newChestEnemy->Initialize();
	newChestEnemy->SetPlayer(player);
	newChestEnemy->SetBlock(block);
	newChestEnemy->SetPosition({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + 5.0f });
	newChestEnemy->SetStartPos({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + 5.0f });
	enemy.push_back(newChestEnemy);
}