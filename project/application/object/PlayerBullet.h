#pragma once
#include "Object3d.h"

class PlayerBullet {
public:
	~PlayerBullet();
	void Initialize(Object3dCommon* object3dCommon, const Vector3& position, const Vector3& velocity,const Vector3& rotate);
	void Update();
	void Draw();
	bool IsDead() { return isDead_; }

	void OnCollision();
	AABB GetAABB();

private:
	Object3d* object;

	Vector3 position;
	Vector3 velocity;
	Vector3 rotation;


	bool isDead_ = false;
	float lifeTimer = 1.0f;
	const float deltaTimer = 1.0f / 60.0f;
};