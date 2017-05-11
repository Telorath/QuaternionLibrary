#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

//Just a small visual space saving tool used to allow a definition of a structure as dirty without needing a seperate member variable inside the object that contains it.

template <typename structure> struct  DirtiableObject : public structure
{
	bool isdirty = true;
	DirtiableObject() { };
	DirtiableObject(const structure & Other ) : structure(Other) { };
	DirtiableObject& operator=(const structure & Other) { this->structure::operator=(Other); return *this; };
};

template <typename numtype> class Transform
{

	QuaternionLibrary::Vector3<numtype> Position = QuaternionLibrary::Vector3<numtype>(0,0,0);
	QuaternionLibrary::Vector3<numtype> Scale = QuaternionLibrary::Vector3<numtype>(1,1,1);
	QuaternionLibrary::Quaternion<numtype> Rotation;

	DirtiableObject<QuaternionLibrary::Vector3<numtype>> Up;
	DirtiableObject<QuaternionLibrary::Vector3<numtype>> Side;
	DirtiableObject<QuaternionLibrary::Vector3<numtype>> Forward;

	DirtiableObject<QuaternionLibrary::Matrix4x4<numtype>> MatrixFormat;

public:
	
	Transform() : Position(0, 0, 0), Scale(1, 1, 1), Rotation(1, 0, 0, 0), MatrixFormat(QuaternionLibrary::Matrix4x4<numtype>::Identity())
	{

	}

	~Transform()
	{
	}

	QuaternionLibrary::Vector3<numtype> GetPosition() const
	{
		return Position;
	}
	QuaternionLibrary::Vector3<numtype> GetScale() const
	{
		return Scale;
	}
	QuaternionLibrary::Quaternion<numtype> GetRotation() const
	{
		return Rotation;
	}
	QuaternionLibrary::Matrix4x4<numtype> const & GetMatrix()
	{
		//The matrix we have stored isn't correct, we must fix it..
		if (MatrixFormat.isdirty)
		{
			GetSide();
			GetUp();
			GetForward();
			MatrixFormat.RowX = Row<numtype>(Side.X, Side.Y, Side.Z, 0);
			MatrixFormat.RowY = Row<numtype>(Up.X, Up.Y, Up.Z, 0);
			MatrixFormat.RowZ = Row<numtype>(Forward.X, Forward.Y, Forward.Z, 0);
			MatrixFormat.RowW = Row<numtype>(0, 0, 0, 1);

			Matrix4x4<numtype> ScaleMatrix;

			ScaleMatrix.RowX = Row<numtype>(Scale.X, 0, 0, 0);
			ScaleMatrix.RowY = Row<numtype>(0, Scale.Y, 0, 0);
			ScaleMatrix.RowZ = Row<numtype>(0, 0, Scale.Z, 0);
			ScaleMatrix.RowW = Row<numtype>(0, 0, 0, 1);

			MatrixFormat = MatrixFormat * ScaleMatrix;

			MatrixFormat.RowW = Row<numtype>(Position.X, Position.Y, Position.Z, 1);

			MatrixFormat.isdirty = false;
		}
		return MatrixFormat;
	}
	QuaternionLibrary::Vector3<numtype> GetUp()
	{
		if (Up.isdirty)
		{
			Up = Vector3<numtype>(0, 1, 0) * Rotation;
			Up.Normalize();
			Up.isdirty = false;
		}
		return Up;
	}
	QuaternionLibrary::Vector3<numtype> GetSide()
	{
		if (Side.isdirty)
		{
			Side = Vector3<numtype>(1, 0, 0) * Rotation;
			Side.Normalize();
			Side.isdirty = false;
		}
		return Side;
	}
	QuaternionLibrary::Vector3<numtype> GetForward()
	{
		if (Forward.isdirty)
		{
			Forward = Vector3<numtype>(0, 0, 1) * Rotation;
			Forward.Normalize();
			Forward.isdirty = false;
		}
		return Forward;
	}

	void SetPosition(QuaternionLibrary::Vector3<numtype> newposition)
	{
		Position = newposition;
		MatrixFormat.isdirty = true;
	}

	void SetScale(QuaternionLibrary::Vector3<numtype> newscale)
	{
		Scale = newscale;
		MatrixFormat.isdirty = true;
	}

	void SetRotation(QuaternionLibrary::Quaternion<numtype> NewRotation)
	{
		Rotation = NewRotation;
		Up.isdirty = true;
		Side.isdirty = true;
		Forward.isdirty = true;
		MatrixFormat.isdirty = true;
	}

};

