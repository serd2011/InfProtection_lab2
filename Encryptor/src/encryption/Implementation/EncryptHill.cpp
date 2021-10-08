#include "encryption\Implementation\EncryptHill.h"

#include "utils/MathLib/mat4.h"

#define ALPHABET_SIZE 256

static_assert((ENC_BUFFER_SIZE % 4 == 0), "ENC_BUFFER_SIZE must be devidable by 4 (matrix size)");

int gcd(int a, int b);
int gcdex(int a, int b, int& x, int& y);

void ENC::EncryptHill::encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass.size() < 16)
		throw Encryptor::EncryptorException(PASSWORD_IS_TOO_SHORT);

	ML::mat4<int> key{
		{pass[0],pass[1],pass[2],pass[3]},
		{pass[4],pass[5],pass[6],pass[7]},
		{pass[8],pass[9],pass[10],pass[11]},
		{pass[12],pass[13],pass[14],pass[15]} };

	auto det = ML::det(key);
	if (det == 0 || (gcd(det, ALPHABET_SIZE) != 1))
		throw Encryptor::EncryptorException(PASSWORD_CANT_BE_USED);

	this->progress = 0;

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	unsigned char buffer[ENC_BUFFER_SIZE];
	unsigned char* bufferIterator;
	unsigned char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	ML::mat4<unsigned char> encryptKey = key;
	ML::vec4<unsigned char> vec;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(reinterpret_cast<char*>(buffer), ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			vec[0] = *(bufferIterator);
			vec[1] = *(bufferIterator + 1);
			vec[2] = *(bufferIterator + 2);
			vec[3] = *(bufferIterator + 3);
			vec = vec * encryptKey;
			*(bufferIterator++) = vec[0];
			*(bufferIterator++) = vec[1];
			*(bufferIterator++) = vec[2];
			*(bufferIterator++) = vec[3];
			this->progress += 4;
		}

		outputStream.write(reinterpret_cast<char*>(buffer), inputStream.gcount());
	}

}

void ENC::EncryptHill::decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass.size() < 16)
		throw Encryptor::EncryptorException(PASSWORD_IS_TOO_SHORT);

	ML::mat4<int> key{
		{pass[0],pass[1],pass[2],pass[3]},
		{pass[4],pass[5],pass[6],pass[7]},
		{pass[8],pass[9],pass[10],pass[11]},
		{pass[12],pass[13],pass[14],pass[15]} };

	auto det = ML::det(key);
	if (det == 0 || (gcd(det, ALPHABET_SIZE) != 1))
		throw Encryptor::EncryptorException(PASSWORD_CANT_BE_USED);

	this->progress = 0;

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	unsigned char buffer[ENC_BUFFER_SIZE];
	unsigned char* bufferIterator;
	unsigned char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	int x, y;
	int g = gcdex(det, ALPHABET_SIZE, x, y);
	x = (x % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
	ML::mat4<unsigned char> decryptKey = ML::adj(key) * x;
	ML::vec4<unsigned char> vec;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(reinterpret_cast<char*>(buffer), ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			vec[0] = *(bufferIterator);
			vec[1] = *(bufferIterator + 1);
			vec[2] = *(bufferIterator + 2);
			vec[3] = *(bufferIterator + 3);
			vec = vec * decryptKey;
			*(bufferIterator++) = vec[0];
			*(bufferIterator++) = vec[1];
			*(bufferIterator++) = vec[2];
			*(bufferIterator++) = vec[3];
			this->progress += 4;
		}

		outputStream.write(reinterpret_cast<char*>(buffer), inputStream.gcount());
	}
}

int gcd(int a, int b) {
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

int gcdex(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcdex(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
