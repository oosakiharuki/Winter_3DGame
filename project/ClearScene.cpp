#include "ClearScene.h"

ClearScene::~ClearScene(){
	delete fead_;
}

void ClearScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	this->spriteCommon_ = spriteCommon;
	this->object3dCommon_ = objCommon;
	this->input_ = input;

	fead_ = new Fead();
	fead_->Initialize(spriteCommon_,"resource/FeadWin.png");
}

void ClearScene::Update() {
	input_->Update();
	fead_->Update();

	if (input_->TriggerKey(DIK_SPACE)) {
		fead_->ChangeSpriteFile("resource/Fead.png");
		fead_->StartFead();
	}

	if (fead_->SceneChange()) {
		sceneNo = SCENE::Title;
	}
}

void ClearScene::Draw() {
	fead_->Draw();
}
