#include "TitleScene.h"

TitleScene::~TitleScene() {
	delete fead_;
}

void TitleScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	this->spriteCommon_ = spriteCommon;
	this->object3dCommon_ = objCommon;
	this->input_ = input;

	fead_ = new Fead();
	fead_->Initialize(spriteCommon_, "resource/Fead.png");
}

void TitleScene::Update() {
	input_->Update();
	fead_->Update();

	if (input_->TriggerKey(DIK_SPACE)) {
		fead_->StartFead();
	}

	if (fead_->SceneChange()) {
		sceneNo = SCENE::GAME;
	}
}

void TitleScene::Draw() {
	fead_->Draw();
}
