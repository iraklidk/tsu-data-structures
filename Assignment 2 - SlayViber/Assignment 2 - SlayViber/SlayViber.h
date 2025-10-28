#pragma once
using namespace std;
#include <string>
#include <random>
#include <vector>
#include <set>
#include <iostream>

class SlayViber
{

private:
	string username, password;
	bool streaming, isRegistered, hasRestriction, deleted, invalid;
	int followers;
	vector<string> visitors;
	static random_device rd;
	static set<string> usernames;

public:
	SlayViber();
	SlayViber(string username, string password, int followers = 0, bool hasRestriction = false);
	void visit(SlayViber& other);
	void registration();
	void print() const;
	void deleteUser();
	void goLive();

	// Getters
	bool isDeleted() const;
	int getFollowers() const;
	string getUsername() const;
	bool getRestrictionStatus() const;

	// Setters
	void setFollowers(int f);
	void setRestrictionStatus(bool r);

};