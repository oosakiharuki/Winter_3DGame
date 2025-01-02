#pragma once
#include "MyMath.h"
#include "Object3d.h"
#include "Sprite.h"
#include "Input.h"
#include "PlayerBullet.h"

//#include <list>

class Player{
public:
	~Player();
	void Initialize(Object3dCommon* object3dCommon, SpriteCommon* spriteCommon,Input* input);
	void Update();
	void Attack();
	void Draw();
	void Draw2D();
	
	void OnCollision();
	std::list<PlayerBullet*> GetBullets() { return bullets_; }
	Vector3 GetPosition() { return position; };


private:
	Input* input_ = nullptr;
	WinApp* winApp_ = nullptr;
	Object3dCommon* ObjCommon = nullptr;

	Transform tarnsform;
	uint32_t textureHandle = 0u;

	Object3d* object3d = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;

	const float kMoveX = 7.0f;
	const float kMoveZNear = -2.0f;
	const float kMoveZFar = 10.0f;

	Sprite* sprite = nullptr;


	std::list<PlayerBullet*> bullets_;
	float distanceTime = 0.0f;

};