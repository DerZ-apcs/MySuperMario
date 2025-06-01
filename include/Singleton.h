#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>
#include <stdexcept>
using namespace std;

template <class T>
class Singleton {
public:
	template <typename... Args>
	static T& getInstance(Args&&... args) {
		if (!instance) {
			instance.reset(new T(forward<Args>(args)...));
		}
		return *instance;
	}
	// delete copy construtor and assignment operator
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	Singleton(){} // private constructor to prevent instantiation
	~Singleton(){}
	static unique_ptr<T> instance; // smart pointer for automatic memory management
};
// Initialize the static member
template <class T>
unique_ptr<T> Singleton<T>::instance = nullptr;
#endif