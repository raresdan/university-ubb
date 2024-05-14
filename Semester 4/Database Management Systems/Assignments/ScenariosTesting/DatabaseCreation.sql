CREATE DATABASE UniversityDBMS;
USE UniversityDBMS;

CREATE TABLE Students (
    StudentID INT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50)
);


CREATE TABLE Courses (
    CourseID INT PRIMARY KEY,
    CourseName VARCHAR(100)
);

-- Table for many-to-many relationship
CREATE TABLE Enrollments (
    StudentID INT,
    CourseID INT,
    PRIMARY KEY (StudentID, CourseID),
    FOREIGN KEY (StudentID) REFERENCES Students(StudentID),
    FOREIGN KEY (CourseID) REFERENCES Courses(CourseID)
);

CREATE TABLE LogTable (
	info varchar(100),
	error varchar(1000),
	logTime DATETIME
)
GO


SELECT * FROM Students;
SELECT * FROM Courses;
SELECT * FROM Enrollments;