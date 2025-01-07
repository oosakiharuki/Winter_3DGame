#pragma once
#include "MyMath.h"
#include "Object3d.h"
#include "DeathParticle.h"
#include "Audio.h"

enum Action {
	move,//動く
	stop,//突撃
	bom//爆発
};

class Enemy {
public:	
	~Enemy();
	void Initialize(Object3dCommon* object3dCommon,const Vector3& position,float speed);
	void Update();
	void Draw();

	void OnCollision();
	void OnCollisionWall();

	bool IsDead() { return isDead_; }
	bool IsBow() { return isBow; }

	AABB GetAABB();
	//DeathParticle* GetParticle() { return deathBom; }
	//bool SetBom(bool enemyType) { enemyBom = enemyType; }

private:
	Transform tarnsform;

	Object3d* object3d = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;

	float speed = 0.0f;

	Action action;
	DeathParticle* deathBom = nullptr;
	bool enemyBom = false;

	Object3dCommon* ObjCommon = nullptr;

	bool isDead_ = false;
	bool isHit = false;
	bool isBow = false;
	uint32_t hp = 5;

};