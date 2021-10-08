#pragma once
#include <stdexcept>

#include "vec4.h"

namespace ML {

	template<typename T>
	class mat4;

	template<typename T>
	vec4<T> operator*(const vec4<T>&, const mat4<T>&);

	template<typename T>
	T det(const mat4<T>&);

	template<typename T>
	mat4<T> adj(const mat4<T>&);

	template<typename T>
	mat4<T> transpose(const mat4<T>&);

	template<typename T>
	mat4<T> inv(const mat4<T>&);

	template<typename T>
	class mat4 {
	public:
		mat4(
			const vec4<T>& v0 = vec4<T>(),
			const vec4<T>& v1 = vec4<T>(),
			const vec4<T>& v2 = vec4<T>(),
			const vec4<T>& v3 = vec4<T>()
		);
		mat4(T fill);
		~mat4() {};

		mat4(const mat4&);
		template<typename U>
		mat4(const mat4<U>&);

		mat4<T>& operator=(const mat4&);
		template<typename U>
		mat4<T>& operator=(const mat4<U>&);

		mat4<T> operator*(const mat4&) const;
		mat4& operator*=(const mat4&);

		mat4<T> operator*(T) const;
		mat4<T>& operator*=(T);
		mat4<T> operator/(T) const;
		mat4<T>& operator/=(T);

		vec4<T>& operator[](size_t);
		const vec4<T>& operator[](size_t) const;

		void setColumn(size_t column, T value);

	private:
		vec4<T> data[4];

		template<typename T> friend vec4<T> operator*(const vec4<T>&, const mat4<T>&);

		template<typename T> friend T det(const mat4<T>&);
		template<typename T> friend mat4<T> adj(const mat4<T>&);
		template<typename T> friend mat4<T> transpose(const mat4<T>&);
		template<typename T> friend mat4<T> inv(const mat4<T>&);

		template<typename U>
		friend class mat4;
	};

}

template<typename T>
inline ML::mat4<T>::mat4(const ML::vec4<T>& v0, const ML::vec4<T>& v1, const ML::vec4<T>& v2, const ML::vec4<T>& v3) : data{ v0,v1,v2,v3 } {}

template<typename T>
inline ML::mat4<T>::mat4(T s) : mat4(
	{ s,0,0,0 },
	{ 0,s,0,0 },
	{ 0,0,s,0 },
	{ 0,0,0,s }
) {}

template<typename T>
inline ML::mat4<T>::mat4(const ML::mat4<T>& in) : data{ in.data[0] ,in.data[1],in.data[2] ,in.data[3] } {}

template<typename T>
template<typename U>
inline ML::mat4<T>::mat4(const ML::mat4<U>& in) : data{
	static_cast<ML::vec4<T>>(in.data[0]),
	static_cast<ML::vec4<T>>(in.data[1]),
	static_cast<ML::vec4<T>>(in.data[2]),
	static_cast<ML::vec4<T>>(in.data[3])
} {}

template<typename T>
inline ML::mat4<T>& ML::mat4<T>::operator=(const ML::mat4<T>& in) {
	data[0] = in.data[0];
	data[1] = in.data[1];
	data[2] = in.data[2];
	data[3] = in.data[3];
	return *this;
}

template<typename T>
template<typename U>
inline ML::mat4<T>& ML::mat4<T>::operator=(const ML::mat4<U>& in) {
	data[0] = static_cast<ML::vec4<T>>(in.data[0]);
	data[1] = static_cast<ML::vec4<T>>(in.data[1]);
	data[2] = static_cast<ML::vec4<T>>(in.data[2]);
	data[3] = static_cast<ML::vec4<T>>(in.data[3]);
	return *this;
}

template<typename T>
inline ML::mat4<T> ML::mat4<T>::operator*(const ML::mat4<T>& in) const {
	mat4<T> result{};
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			result.data[i][j] = this->data[i][0] * in.data[0][j] +
				this->data[i][1] * in.data[1][j] +
				this->data[i][2] * in.data[2][j] +
				this->data[i][3] * in.data[3][j];
		}
	}
	return result;
}

template<typename T>
inline ML::mat4<T>& ML::mat4<T>::operator*=(const ML::mat4<T>& in) {
	mat4<T> result{};
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			result.data[i][j] = this->data[i][0] * in.data[0][j] +
				this->data[i][1] * in.data[1][j] +
				this->data[i][2] * in.data[2][j] +
				this->data[i][3] * in.data[3][j];
		}
	}
	this->data[0] = result.data[0];
	this->data[1] = result.data[1];
	this->data[2] = result.data[2];
	this->data[3] = result.data[3];
	return *this;
}

template<typename T>
inline ML::mat4<T> ML::mat4<T>::operator*(T val) const {
	mat4<T> result(*this);
	result *= val;
	return result;
}

template<typename T>
inline ML::mat4<T>& ML::mat4<T>::operator*=(T val) {
	this->data[0] *= val;
	this->data[1] *= val;
	this->data[2] *= val;
	this->data[3] *= val;
	return *this;
}

template<typename T>
inline ML::mat4<T> ML::mat4<T>::operator/(T val) const {
	mat4<T> result(*this);
	result /= val;
	return result;
}

template<typename T>
inline ML::mat4<T>& ML::mat4<T>::operator/=(T val) {
	this->data[0] /= val;
	this->data[1] /= val;
	this->data[2] /= val;
	this->data[3] /= val;
	return *this;
}

template<typename T>
inline ML::vec4<T>& ML::mat4<T>::operator[](size_t index) {
	return data[index];
}

template<typename T>
inline const ML::vec4<T>& ML::mat4<T>::operator[](size_t index) const {
	return data[index];
}

template<typename T>
inline void ML::mat4<T>::setColumn(size_t column, T value) {
	this->data[0][column] = value;
	this->data[1][column] = value;
	this->data[2][column] = value;
	this->data[3][column] = value;
}

template<typename T>
ML::vec4<T> ML::operator*(const ML::vec4<T>& v, const ML::mat4<T>& m) {
	vec4<T> result{};
	for (size_t j = 0; j < 4; j++) {
		result[j] = v[0] * m.data[0][j] +
			v[1] * m.data[1][j] +
			v[2] * m.data[2][j] +
			v[3] * m.data[3][j];
	}
	return result;
}

#define minor3x3(matrix,firstRow,secondRow,thirdRow,firstCol,secondCol,thirdCol) ( \
	 (matrix[firstRow][firstCol]*matrix[secondRow][secondCol]*matrix[thirdRow][thirdCol]) \
	-(matrix[firstRow][firstCol]*matrix[secondRow][thirdCol]*matrix[thirdRow][secondCol]) \
	-(matrix[firstRow][secondCol]*matrix[secondRow][firstCol]*matrix[thirdRow][thirdCol]) \
	+(matrix[firstRow][secondCol]*matrix[secondRow][thirdCol]*matrix[thirdRow][firstCol]) \
	+(matrix[firstRow][thirdCol]*matrix[secondRow][firstCol]*matrix[thirdRow][secondCol]) \
	-(matrix[firstRow][thirdCol]*matrix[secondRow][secondCol]*matrix[thirdRow][firstCol]) )

template<typename T>
T ML::det(const mat4<T>& m) {
	return m.data[0][0] * minor3x3(m.data, 1, 2, 3, 1, 2, 3) - m.data[0][1] * minor3x3(m.data, 1, 2, 3, 0, 2, 3) + m.data[0][2] * minor3x3(m.data, 1, 2, 3, 0, 1, 3) - m.data[0][3] * minor3x3(m.data, 1, 2, 3, 0, 1, 2);
}

template<typename T>
ML::mat4<T> ML::adj(const mat4<T>& m) {
	auto t = transpose(m);
	return mat4<T>({
		{minor3x3(t.data, 1, 2, 3, 1, 2, 3),-minor3x3(t.data, 1, 2, 3, 0, 2, 3),minor3x3(t.data, 1, 2, 3, 0, 1, 3),-minor3x3(t.data, 1, 2, 3, 0, 1, 2)},
		{-minor3x3(t.data, 0, 2, 3, 1, 2, 3),minor3x3(t.data, 0, 2, 3, 0, 2, 3),-minor3x3(t.data, 0, 2, 3, 0, 1, 3),minor3x3(t.data, 0, 2, 3, 0, 1, 2)},
		{minor3x3(t.data, 0, 1, 3, 1, 2, 3),-minor3x3(t.data, 0, 1, 3, 0, 2, 3),minor3x3(t.data, 0, 1, 3, 0, 1, 3),-minor3x3(t.data, 0, 1, 3, 0, 1, 2)},
		{-minor3x3(t.data, 0, 1, 2, 1, 2, 3),minor3x3(t.data, 0, 1, 2, 0, 2, 3),-minor3x3(t.data, 0, 1, 2, 0, 1, 3),minor3x3(t.data, 0, 1, 2, 0, 1, 2)} });
}

template<typename T>
ML::mat4<T> ML::transpose(const mat4<T>& m) {
	return mat4<T>({
		{m.data[0][0],m.data[1][0],m.data[2][0],m.data[3][0]},
		{m.data[0][1],m.data[1][1],m.data[2][1],m.data[3][1]},
		{m.data[0][2],m.data[1][2],m.data[2][2],m.data[3][2]},
		{m.data[0][3],m.data[1][3],m.data[2][3],m.data[3][3]} });
}

template<typename T>
ML::mat4<T> ML::inv(const mat4<T>& m) {
	T d = det(m);
	if (d == 0)
		throw std::logic_error("Determinant is 0");
	return adj(m) / det(m);
}
