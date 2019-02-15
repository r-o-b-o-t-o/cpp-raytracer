#include <cmath>
#include "scene/Entity.hpp"

namespace scene {

	Entity::Entity(): pos(maths::Point()),
	trans(maths::Matrix()),
	transInv(maths::Matrix()) {
	}

	Entity::Entity(maths::Point point):
	trans(maths::Matrix()),
	transInv(maths::Matrix()) {
		this->pos = point;
		this->translate(point[0], point[1], point[2]);
	}

	void Entity::setPos(maths::Point point){
		this->pos = point;
		this->translate(point[0], point[1], point[2]);
	}

	void Entity::setPos(float x, float y, float z){
		this->pos = maths::Point(x,y,z);
		this->translate(x, y, z);
	}

	maths::Point Entity::getPos() {
		return this->pos;
	}
	// effectue une translation de vecteur (x,y,z)
	void Entity::translate(float x, float y, float z){
		maths::Matrix mat = maths::Matrix();
		
		mat(0, 3) = x;
		mat(1, 3) = y;
		mat(2, 3) = z;
		this->trans = mat * this->trans;

		this->transInv = this->trans.inverse();
	}

	// effectue une rotation sur l'axe X, de deg radians
	void Entity::rotateX(float deg){
		maths::Matrix mat = maths::Matrix();
			
		mat(2, 1) = sinf(deg);
		mat(2, 2) = cosf(deg);
		mat(1, 1) = cosf(deg);
		mat(1, 2) = -sinf(deg);
		
		this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

	// effectue une rotation sur l'axe Y, de deg radians
	void Entity::rotateY(float deg){
		maths::Matrix mat = maths::Matrix();
			
		mat(0, 2) = sinf(deg);
		mat(2, 2) = cosf(deg);
		mat(0, 0) = cosf(deg);
		mat(2, 0) = -sinf(deg);
		
		this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

	// effectue une rotation sur l'axe Z, de deg radians
	void Entity::rotateZ(float deg){
		maths::Matrix mat = maths::Matrix();
			
		mat(1, 0) = sinf(deg);
		mat(0, 0) = cosf(deg);
		mat(1, 1) = cosf(deg);
		mat(0, 1) = -sinf(deg);
		
		this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

	// effectue un redimensionnement de facteur factor
	void Entity::scale(float factor){
		maths::Matrix mat = maths::Matrix(3, 3);
			
		mat(0, 0) = factor;
		mat(1, 1) = factor;
		mat(2, 2) = factor;
		
		this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

}