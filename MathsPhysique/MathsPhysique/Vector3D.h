#pragma once

class Vector3D
{
private:
	float x;
	float y;
	float z;

public:
	//Constructors
	Vector3D(float x = 0.0, float y = 0.0, float z = 0.0);
	Vector3D(const Vector3D& other);

	//Assignation
	Vector3D& operator=(const Vector3D& other);

	//Setters
	void setCoord(float x, float y, float z);
	void setCoord(const Vector3D& vector);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	//Getters
	float getX() const;
	float getY() const;
	float getZ() const;

	//Operations
	//	with a Vector3D
	Vector3D operator+(const Vector3D& vector) const;
	Vector3D operator-(const Vector3D& vector) const;
	float scalarProduct(const Vector3D& vector) const;
	Vector3D crossProduct(const Vector3D& vector) const;
	//	with a scalar
	Vector3D operator*(float scalar) const;
	Vector3D operator/(float scalar) const;
	Vector3D operator^(float scalar) const;

	//Other methods
	float getNorm() const;
	Vector3D getDifferential() const;
};

