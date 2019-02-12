#include <math.h>
#include "Entity.hpp"

namespace Scene {
	// effectue une translation de vecteur (x,y,z)
	void Entity::translate(float x, float y, float z){
		Math::Matrix mat = Math::Matrix(4, 4, 0);
		
		mat(0, 3) = x;
		mat(1, 3) = y;
		mat(2, 3) = z;
		//this->trans = mat * this->trans;

		this->transInv = this->trans.inverse();
	}

	// effectue une rotation sur l'axe X, de deg radians
	void Entity::rotateX(float deg){
		Math::Matrix mat = Math::Matrix(4, 4, 0);
			
		mat(2, 1) = sin(deg);
		mat(2, 2) = cos(deg);
		mat(1, 1) = cos(deg);
		mat(1, 2) = -sin(deg);
		
		//this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

	// effectue une rotation sur l'axe Y, de deg radians
	void Entity::rotateY(float deg){
		Math::Matrix mat = Math::Matrix(4, 4, 0);
			
		mat(0, 2) = sin(deg);
		mat(2, 2) = cos(deg);
		mat(0, 0) = cos(deg);
		mat(2, 0) = -sin(deg);
		
		//this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

	// effectue une rotation sur l'axe Z, de deg radians
	void Entity::rotateZ(float deg){
		Math::Matrix mat = Math::Matrix(4, 4, 0);
			
		mat(1, 0) = sin(deg);
		mat(0, 0) = cos(deg);
		mat(1, 1) = cos(deg);
		mat(0, 1) = -sin(deg);
		
		//this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

	// effectue un redimensionnement de facteur factor
	void Entity::scale(float factor){
		Math::Matrix mat = Math::Matrix(3, 3, 0);
			
		mat(0, 0) = factor;
		mat(1, 1) = factor;
		mat(2, 2) = factor;
		
		//this->trans = mat * this->trans;
		
		this->transInv = this->trans.inverse();
	}

}