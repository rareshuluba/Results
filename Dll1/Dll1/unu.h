#pragma once
class BaseSkeleton {
private:
	int object_id;
	std::string objtype[32];
public:
	BaseSkeleton(const char* objtype);
	~BaseSkeleton();
	virtual void whoami();
};

class Derived1 : public BaseSkeleton {
private:
	int object_id;
	std::string objectTypeDerived1[32];
public:
	Derived1(const char* objectTypeDerived1);
	~Derived1();
	virtual void whoami();
};

class Derived2 : public BaseSkeleton {
private:
	int object_id;
	std::string objectTypeDerived2[32];
public:
	Derived2(const char* objectTypeDerived2);
	~Derived2();
	virtual void whoami();
};