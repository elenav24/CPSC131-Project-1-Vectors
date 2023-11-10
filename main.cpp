
/**
 * You don't have to modify this source file, but can if you want.
 * This will not be used for grading, so you can use it to debug your
 * vector class.
 * This is the program that runs with "make run"
 */

///	Your welcome
#include <iostream>
#include "MyVector.hpp"

///	Your welcome
using std::cout, std::endl;

//
int main()
{
	cout << "Hello! Maybe use this source file for debugging?" << endl;
	MyVector<int> v(64);
	cout << "SIZE: " << v.size() << " CAPACITY: " << v.capacity() << endl;
	for ( size_t i = 0; i < 100; i++ ) {
		int val = i * 2 - (100 / 2);
		v.push_back(val);
	}
	cout << "SIZE: " <<  v.size() << " CAPACITY: " << v.capacity() << endl;
	cout << v.at(47) << " " << v.at(87) << " " << v.at(88) << " " << v.at(89) << endl;
	v.erase(47);
	cout << "SIZE: " <<  v.size() << " CAPACITY: " << v.capacity() << endl;
	cout << v.at(47) << " " << v.at(88) << endl;
	
	return 0;
}

