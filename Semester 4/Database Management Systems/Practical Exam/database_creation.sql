CREATE DATABASE DBMSPractical

USE DBMSPractical

CREATE TABLE SemesterProject(
	projectid INT PRIMARY KEY,
	name VARCHAR(50),
);

CREATE TABLE ProjectTeam(
	teamid INT PRIMARY KEY,
	name VARCHAR(50),
	number INT,
	projectid INT,
	FOREIGN KEY (projectid) REFERENCES SemesterProject(projectid)
);

CREATE TABLE StudentMember(
	studentid INT PRIMARY KEY,
	name VARCHAR(50),
	role VARCHAR(50),
	teamid INT,
	FOREIGN KEY (teamid) REFERENCES ProjectTeam(teamid)
);

CREATE TABLE Task(
	taskid INT PRIMARY KEY,
	description VARCHAR(100),
	assignedTo INT,
	FOREIGN KEY (assignedTo) references StudentMember(studentid)
);

CREATE TABLE SoftwareTool(
	toolid INT PRIMARY KEY,
	name VARCHAR(50),
	description VARCHAR(100),
);

CREATE TABLE License(
	teamid INT,
	toolid INT,
	availability INT,
	PRIMARY KEY (teamid, toolid)
);



INSERT INTO SemesterProject (projectid, name) VALUES (1, 'Project Gamma'), (2, 'Project Delta');
SELECT * FROM SemesterProject


INSERT INTO ProjectTeam (teamid,name, number, projectid) VALUES 
(1, 'Team A', 1, 1), 
(2, 'Team B', 2, 1)
SELECT * FROM ProjectTeam


INSERT INTO StudentMember (studentid,name, role, teamid) VALUES 
(1, 'Alice', 'Developer', 1), 
(2, 'Bob', 'Tester', 1), 
(3, 'Charlie', 'Manager', 2), 
(4, 'Dave', 'Analyst', 2)
SELECT * FROM StudentMember

INSERT INTO Task (taskid, description, assignedTo) VALUES 
(1, 'Develop module X', 1), 
(2, 'Test module Y', 2), 
(3, 'Plan project phases', 3), 
(4, 'Analyze requirements', 4)
SELECT * FROM Task

INSERT INTO SoftwareTool (toolid,name , description) VALUES 
(1, 'GitHub', 'Version Control System'), 
(2, 'JIRA', 'Project Management Tool'),
(3, 'Slack', 'Communication Tool'), 
(4, 'Trello', 'Task Management Tool');

SELECT * FROM SoftwareTool


INSERT INTO License (teamid, toolid, availability) VALUES 
(1, 1, 365), 
(1, 2, 180), 
(2, 1, 365), 
(2, 2, 180);

SELECT * FROM License

