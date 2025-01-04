#pragma once
#include "IScene.h"
#include "Input.h"
#include "Fead.h"
#include "Skydorm.h"

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
	Fead* fead_ = nullptr;

	Sprite* sprite_ = nullptr;
	Camera* camera = nullptr;
	Skydorm* skydorm_ = nullptr;
};