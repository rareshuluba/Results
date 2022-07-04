#include <iostream>
#include <sysinfoapi.h>
#include "unu.h"
using namespace std;

BaseSkeleton::BaseSkeleton(const char* objtype) {
	object_id = GetTickCount();
	this->objtype = objtype;
}
BaseSkeleton::~BaseSkeleton() {};

void BaseSkeleton::whoami() {
	printf("BaseSkeleton; object_id = %d, objtype = % s\n",object_id, objtype);
}

Derived1::Derived1(const char* objectTypeDerived1) : BaseSkeleton(objectTypeDerived1) {
	this->objectTypeDerived1 = objectTypeDerived1;
}

Derived1::~Derived1() {};

void Derived1::whoami() {
		printf("Class name: %s", typeid(Derived1).name());
}

Derived2::Derived2(const char* objectTypeDerived2) : BaseSkeleton(objectTypeDerived2) {
	this->objectTypeDerived2 = objectTypeDerived2;
}

Derived2::~Derived2() {};

void Derived2::whoami() {
	printf("Class name: %s", typeid(Derived2).name());
}