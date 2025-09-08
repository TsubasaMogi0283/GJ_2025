#include "BasePlayerCollision.h"

void BasePlayerCollision::OnCollision([[maybe_unused]] const Collider& collider){
	isTouch_ = true;

	if (shouldPushBack_) {
		Vector3 vec = CalculateAABBPushbackVector(collider.GetAABB());

		position_->x += vec.x;
		position_->y += vec.y;
		position_->z += vec.z;
	}
}

void BasePlayerCollision::OffCollision(){
	isTouch_ = false;
}