#pragma once
#include <vector>
#include "User.h"
#include "Issue.h"
#include "Subject.h"

class IssuesRepository : public Subject
{
private:
	std::vector<User> allUsers;
	std::vector<Issue> allIssues;
public:
	IssuesRepository(std::vector<User> initialUsers = {}, std::vector<Issue> initialIssues = {}) 
	{
		this->readUsers();
		this->readIssues();
	}

	std::vector<User> getAllUsers() { return this->allUsers; }
	std::vector<Issue> getAllIssues() { return this->allIssues; }

	void addIssue(Issue issueToAdd);
	void removeIssue(int indexOfIssueToRemove);
	void resolveIssue(int indexOfIssueToResolve, std::string resolver);

	void readUsers();
	void readIssues();

	void writeIssues();
};

