#include "GameManager.h"

GameManager::GameManager(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	sceneArr_[GAME] = std::make_unique<GameScene>();

	prevSceneNo_ = 0;
	currentSceneNo_ = GAME;

	spriteCommon_ = spriteCommon;
	objCommon_ = objCommon;
	input_ = input;
}

GameManager::~GameManager() {

}

void GameManager::Initialize() {
	sceneArr_[currentSceneNo_]->Initialize(spriteCommon_, objCommon_, input_);
}


void GameManager::Update() {

	prevSceneNo_ = currentSceneNo_;
	currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

	if (prevSceneNo_ != currentSceneNo_) {
		sceneArr_[currentSceneNo_]->Initialize(spriteCommon_, objCommon_, input_);
	}

	sceneArr_[currentSceneNo_]->Update();
}

void GameManager::Draw() {
	sceneArr_[currentSceneNo_]->Draw();
}