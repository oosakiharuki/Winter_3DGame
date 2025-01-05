#pragma once
#include "MyMath.h"
#include "Object3d.h"
#include "Input.h"
#include "PlayerBullet.h"

//#include <list>

class Player{
public:
	~Player();
	void Initialize(Object3dCommon* object3dCommon,Input* input);
	void Update();
	void Attack();
	void Draw();
		
	void OnCollision();
	std::list<PlayerBullet*> GetBullets() { return bullets_; }
	AABB GetAABB();


private:
	Input* input_ = nullptr;
	WinApp* winApp_ = nullptr;
	Object3dCommon* ObjCommon = nullptr;

	Transform tarnsform;

	Object3d* object3d = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;
	float speed = 0.1f;

	const float kMoveX = 7.0f;
	const float kMoveZNear = -2.0f;
	const float kMoveZFar = 10.0f;

	bool Move = true;



	std::list<PlayerBullet*> bullets_;
	float distanceTime = 0.0f;

};