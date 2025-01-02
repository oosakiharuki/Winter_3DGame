#include "Skydorm.h"

Skydorm::~Skydorm() {
	delete object3d;
}


void Skydorm::Initialize(Object3dCommon* object3dCommon,Camera* camera, std::string objFile) {
	object3dCommon_ = object3dCommon;
	camera_ = camera;

	object3dCommon_->SetDefaultCamera(camera_);

	object3d = new Object3d();
	object3d->SetModelFile(objFile);
	object3d->Initialize(object3dCommon_);
}

void Skydorm::Update() {
	camera_->Update();

	object3d->Update();
	Vector3 a = { 0.0f,0.0f,0.0f };
	object3d->SetTranslate(a);


	Vector3 b = object3d->GetRotate();
	object3d->SetRotate(b);
}

void Skydorm::Draw() {
	object3d->Draw();
}

