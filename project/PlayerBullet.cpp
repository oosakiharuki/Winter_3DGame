#include "PlayerBullet.h"
#include "MyMath.h"

PlayerBullet::~PlayerBullet() {
	delete object;
}

void PlayerBullet::Initialize(Object3dCommon* object3dCommon, const Vector3& position, const Vector3& velocity, const Vector3& rotate){

	object = new Object3d();
	object->SetModelFile("bullet.obj");
	object->Initialize(object3dCommon);
	object->SetTranslate(position);

	this->velocity = velocity;
	this->rotation = rotate;
	//rotation.x = 0.0f;
	object->SetRotate(rotation);
}

void PlayerBullet::Update(){
	object->Update();
	
	position = object->GetTranslate();

	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	object->SetTranslate(position);

	//rotation = object->GetRotate();

	//object->SetRotate(rotation);

	lifeTimer -= deltaTimer;
	if (lifeTimer < 0.0f) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(){
	object->Draw();
}