#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

//Just a small visual space saving tool used to allow a definition of a structure as dirty without needing a seperate member variable inside the object that contains it.

template <typename structure> struct  DirtiableObject : structure
{
	bool isdirty = true;
	DirtiableObject() { };
	DirtiableObject(const structure & Other ) : structure(Other) { };
	DirtiableObject& operator=(const structure & Other) { this->structure::operator=(Other); return *this; };
};

class Transform
{

	QuaternionLibrary::Vec3f Position = QuaternionLibrary::Vec3f(0,0,0);
	QuaternionLibrary::Vec3f Scale = QuaternionLibrary::Vec3f(1,1,1);
	QuaternionLibrary::Quaternionf Rotation;

	DirtiableObject<QuaternionLibrary::Vec3f> Up;
	DirtiableObject<QuaternionLibrary::Vec3f> Side;
	DirtiableObject<QuaternionLibrary::Vec3f> Forward;

	DirtiableObject<QuaternionLibrary::Matrix4x4f> MatrixFormat;

public:
	
	Transform();

	~Transform();

	QuaternionLibrary::Vec3f GetPosition() const;
	QuaternionLibrary::Vec3f GetScale() const;
	QuaternionLibrary::Quaternionf GetRotation() const;
	QuaternionLibrary::Matrix4x4f const & GetMatrix();
	QuaternionLibrary::Vec3f GetUp();
	QuaternionLibrary::Vec3f GetSide();
	QuaternionLibrary::Vec3f GetForward();

	void SetPosition(QuaternionLibrary::Vec3f newposition);
	void SetScale(QuaternionLibrary::Vec3f newscale);
	void SetRotation(QuaternionLibrary::Quaternionf NewRotation);

};

