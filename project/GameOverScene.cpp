#include "GameOverScene.h"

GameOverScene::~GameOverScene() {
	delete fead_;
}

void GameOverScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	this->spriteCommon_ = spriteCommon;
	this->object3dCommon_ = objCommon;
	this->input_ = input;

	fead_ = new Fead();
	fead_->Initialize(spriteCommon_, "resource/Fead.png");
}

void GameOverScene::Update() {
	input_->Update();
	fead_->Update();

	if (input_->TriggerKey(DIK_SPACE)) {
		fead_->StartFead();
	}

	if (fead_->SceneChange()) {
		sceneNo = SCENE::GAME;
	}
}

void GameOverScene::Draw() {
	fead_->Draw();
}
