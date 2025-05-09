#pragma once
#include <cmath>
#include <numbers>
#include <glm/vec3.hpp>

struct Vector3
{
	float x, y, z;

	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) {
	}

	float dot(const Vector3& other) const noexcept {
		return x * other.x + y * other.y + z * other.z;
	}

	float length() const noexcept {
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3 normalize() const noexcept {
		float len = length();
		if (len == 0) {
			return { 0, 0, 0 };
		}
		return { x / len, y / len, z / len };
	}

	Vector3 cross(const Vector3& other) const noexcept {
		return {
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		};
	}

	float distance_to(const Vector3& other) const noexcept {
		return std::sqrt((x - other.x) * (x - other.x) +
						 (y - other.y) * (y - other.y) +
						 (z - other.z) * (z - other.z));
	}

	constexpr const Vector3& operator-(const Vector3& other) const noexcept {
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr const Vector3& operator+(const Vector3& other) const noexcept {
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr const Vector3& operator/(const float scalar) const noexcept {
		return { x / scalar, y / scalar, z / scalar };
	}

	constexpr const Vector3& operator*(const float scalar) const noexcept {
		return { x * scalar, y * scalar, z * scalar };
	}

	constexpr const bool operator>(const Vector3& other) const noexcept {
		return x > other.x && y > other.y && z > other.z;
	}

	constexpr const bool operator>=(const Vector3& other) const noexcept {
		return x >= other.x && y >= other.y && z >= other.z;
	}

	constexpr const bool operator<(const Vector3& other) const noexcept {
		return x < other.x && y < other.y && z < other.z;
	}

	constexpr const bool operator<=(const Vector3& other) const noexcept {
		return x <= other.x && y <= other.y && z <= other.z;
	}
	constexpr const bool operator==(const Vector3& other) const noexcept {
		return x == other.x && y == other.y && z == other.z;
	}
	constexpr const bool operator==(const glm::vec3& other) const noexcept {
		return x == other.x && y == other.y && z == other.z;
	}
};

struct Vector4 {
	float x, y, z, w;
	Vector4(const Vector3& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}

	Vector3 xyz() const noexcept {
		return { x, y, z };
	}

};

struct Vector2 {
	float x, y;

	Vector2(float x, float y) : x(x), y(y) {}
};