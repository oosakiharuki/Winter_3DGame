#pragma once
#include "IScene.h"

class TitleScene : public IScene {
public:
	~TitleScene() override;
	void Initialize(SpriteCommon* spriteCommon, Object3dCommon* objCommon, Input* input) override;
	void Update() override;
	void Draw() override;
private:
	Input* input_ = nullptr;
	Object3dCommon* object3dCommon_ = nullptr;
	SpriteCommon* spriteCommon_ = nullptr;
	float time = 2.0f;
};