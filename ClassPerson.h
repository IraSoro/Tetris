#pragma once
#ifndef CLASS_PERSON
#define CLASS_PERSON

#include <vector>
#include <string>

using namespace std;

class Person {
public:
	int ball = 0;
	bool yes = true;
	string name = "";

	Person(int ball1, string name1) {
		ball = ball1;
		name = name1;
		yes = true;
	}
};
#endif