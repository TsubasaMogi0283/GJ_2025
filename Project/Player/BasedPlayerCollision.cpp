#include "BasePlayerCollision.h"

void BasePlayerCollision::OnCollision([[maybe_unused]] const Collider& collider){
	isTouch_ = true;

	if (shouldPushBack_) {
		Vector3 vec = CalculateAABBPushbackVector(collider.GetAABB());

		position_->x += vec.x;
		position_->y += vec.y;
		position_->z += vec.z;

		pMatrix_->m[3][0] += vec.x;
		pMatrix_->m[3][1] += vec.y;
		pMatrix_->m[3][2] += vec.z;
	}
}

void BasePlayerCollision::OffCollision(){
	isTouch_ = false;
}