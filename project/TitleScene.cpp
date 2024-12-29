#include "TitleScene.h"

TitleScene::~TitleScene() {

}

void TitleScene::Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) {
	spriteCommon_ = spriteCommon;
	object3dCommon_ = objCommon;
	input_ = input;
}

void TitleScene::Update() {
	time -= 1.0f / 60.0f;
	if (time < 0.0f) {
		sceneNo = SCENE::GAME;
		time = 2.0f;
	}
}

void TitleScene::Draw() {

}
