#include "Transform.h"

using namespace QuaternionLibrary;

Transform::Transform() : Position(0, 0, 0), Scale(1, 1, 1), Rotation(1, 0, 0, 0), MatrixFormat(QuaternionLibrary::Matrix4x4f::Identity())
{

}


Transform::~Transform()
{
}

QuaternionLibrary::Vec3f Transform::GetPosition() const
{
	return Position;
}

QuaternionLibrary::Vec3f Transform::GetScale() const
{
	return Scale;
}

QuaternionLibrary::Quaternionf Transform::GetRotation() const
{
	return Rotation;
}

QuaternionLibrary::Matrix4x4f const & Transform::GetMatrix()
{
	//The matrix we have stored isn't correct, we must fix it..
	if (MatrixFormat.isdirty)
	{
		GetSide();
		GetUp();
		GetForward();
		MatrixFormat.RowX = Row<float>(Side.X, Side.Y, Side.Z, 0);
		MatrixFormat.RowY = Row<float>(Up.X, Up.Y, Up.Z, 0);
		MatrixFormat.RowZ = Row<float>(Forward.X, Forward.Y, Forward.Z, 0);
		MatrixFormat.RowW = Row<float>(0, 0, 0, 1);

		Matrix4x4f ScaleMatrix;

		ScaleMatrix.RowX = Row<float>(Scale.X, 0, 0, 0);
		ScaleMatrix.RowY = Row<float>(0, Scale.Y, 0, 0);
		ScaleMatrix.RowZ = Row<float>(0, 0, Scale.Z, 0);
		ScaleMatrix.RowW = Row<float>(0, 0, 0, 1);

		MatrixFormat = MatrixFormat * ScaleMatrix;

		MatrixFormat.RowW = Row<float>(Position.X, Position.Y, Position.Z, 1);

		MatrixFormat.isdirty = false;
	}
	return MatrixFormat;
}

QuaternionLibrary::Vec3f Transform::GetUp()
{
	if (Up.isdirty)
	{
		Up = Vec3f(0, 1, 0) * Rotation;
		Up.isdirty = false;
	}
	return Up;
}

QuaternionLibrary::Vec3f Transform::GetSide()
{
	if (Side.isdirty)
	{
		Side = Vec3f(1, 0, 0) * Rotation;
		Side.isdirty = false;
	}
	return Side;
}

QuaternionLibrary::Vec3f Transform::GetForward()
{
	if (Forward.isdirty)
	{
		Forward = Vec3f(0, 0, 1) * Rotation;
		Forward.isdirty = false;
	}
	return Forward;
}

void Transform::SetPosition(QuaternionLibrary::Vec3f newposition)
{
	Position = newposition;
	MatrixFormat.isdirty = true;
}

void Transform::SetScale(QuaternionLibrary::Vec3f newscale)
{
	Scale = newscale;
	MatrixFormat.isdirty = true;
}

void Transform::SetRotation(QuaternionLibrary::Quaternionf NewRotation)
{
	Rotation = NewRotation;
	Up.isdirty = true;
	Side.isdirty = true;
	Forward.isdirty = true;
	MatrixFormat.isdirty = true;
}
