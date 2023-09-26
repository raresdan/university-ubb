#include "Test.h"
#include "IssuesRepository.h"
#include <assert.h>

void Test::testAddRemove()
{
	IssuesRepository fakeRepo;
	int size = fakeRepo.getAllIssues().size();
	fakeRepo.addIssue(Issue{ "issue", "open","reporter","solver"});
	assert(fakeRepo.getAllIssues().size() == size + 1);
	assert(fakeRepo.getAllIssues()[size].getDescription() == "issue");
	assert(fakeRepo.getAllIssues()[size].getReporter() == "reporter");

	fakeRepo.removeIssue(size);
	assert(fakeRepo.getAllIssues().size() == size);
}

void Test::testUpdate()
{
	IssuesRepository fakeRepo;
	Issue fakeIssue = fakeRepo.getAllIssues()[0];
	fakeRepo.resolveIssue(0, "solver");
	assert(fakeRepo.getAllIssues()[0].getSolver() == "solver");
	assert(fakeRepo.getAllIssues()[0].getStatus() == "closed");

	//cleanup
	fakeRepo.getAllIssues()[0] = fakeIssue;
}

void Test::testAll()
{
	testAddRemove();
	testUpdate();
}