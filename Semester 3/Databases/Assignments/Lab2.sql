USE SocialMediaApp;


-- Insert data into the Users table
INSERT INTO Users (Username, Email, Age) 
VALUES	('rares.dan', 'rd@ubbcluj.com', 20),
		('tudor_gulin', 'tg@ubbcluj.com', 22),
		('dragos.gavrus17', 'dg@ubbcluj.com', 21),
		('narcisel2003', 'ng@ubbcluj.com', 21),
		('erikh25', 'eh@ubbcluj.com', 19);

SELECT * FROM Users;

-- Insert data into the Posts table
INSERT INTO Posts (PostID, UserID, Content, Likes) 
	VALUES	(1, 3, 'Check out my new dog.', 15),
			(2, 4, 'Holiday in New York City!', 100),
			(3, 1, 'My first internship @Google.', 150),
			(4, 4, 'Reunited with some old colleagues.', 50);

SELECT * FROM Posts;

-- Insert data into Comments
INSERT INTO Comments (CommentID, PostID, UserID, Content) 
	VALUES	(1, 2, 1, 'Have fun in NYC!'),
			(2, 2, 2, 'Buy me a souvenir!'),
			(3, 2, 3, 'What are you doing in the US?'),
			(4, 3, 3, 'Congratulations!');

SELECT * FROM Comments


-- Insert data into Likes
INSERT INTO Likes(LikeID, PostID, UserID) 
VALUES	(6, 1, 1),
		(1, 1, 2),
		(2, 1, 3),
		(3, 1, 4),
		(4, 2, 3),
		(5, 3, 3);

SELECT * FROM Likes;

--Trying to insert invalid data into Comments
INSERT INTO Comments (CommentID, PostID, UserID, Content) 
	VALUES	(1, 50, 100, 'Invalid Comm');

-- Insert data into Groups
INSERT INTO Groups (GroupID, GroupName, Description, CreatedByUserID) 
	VALUES	(2,'Climatea Activists', 'Discuss how to prevent global warmin', 3),
			(1,'Tech Enthusiasts', 'Discuss tech topics', 1);

SELECT * FROM Groups

-- Insert data into GroupMember
INSERT INTO GroupMembers (GroupMemberID,GroupID, UserID) 
	VALUES	(3, 2 ,3),
			(4, 2, 4),
			(1, 1, 1),
			(2, 1, 3);

SELECT * FROM GroupMembers



-- Update data
UPDATE Users SET Age = 17 WHERE UserID = 5
SELECT * FROM Users;

UPDATE Posts SET Content = 'Check out my new cat.' WHERE PostID = 1
SELECT * FROM Posts;

UPDATE Comments SET Content = 'Buy me a nice souvenier' WHERE CommentID = 2 ;
SELECT * FROM Comments;



-- Delete data
DELETE FROM Comments 
WHERE PostID = 2 AND UserID = 3
SELECT * FROM Comments;

DELETE FROM Users WHERE Age < 18
SELECT * FROM Users;



-- a. 2 queries with the union operation

-- gets all users except those who are 20 years old
SELECT Username FROM Users WHERE Age < 20
UNION
SELECT Username FROM Users WHERE Age >= 21;

-- gets the content of posts with over 100 likes and the content of the comments
-- user with id = 3 commented
SELECT Content FROM Posts WHERE Likes >= 100
UNION ALL
SELECT Content FROM Comments WHERE UserID = 3;


-- b. 2 queries with the intersection operation

-- get users which both posted and commented
SELECT UserID FROM Posts
INTERSECT
SELECT UserID FROM Comments;

-- get the usernames of users that belong to any group
SELECT Username FROM Users WHERE UserID IN (SELECT UserID FROM GroupMembers);


-- c. 2 queries with the difference operation

-- get the users which don't belong to any group
SELECT UserID FROM Users
EXCEPT
SELECT UserID FROM GroupMembers;

-- get the usernames of users that do not belong to any group
SELECT Username FROM Users WHERE UserID NOT IN (SELECT UserID FROM Posts); 


-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN 
-- INNER JOIN 
SELECT Users.Username, Groups.GroupName
FROM Users
INNER JOIN GroupMembers ON Users.UserID = GroupMembers.UserID
INNER JOIN Groups ON GroupMembers.GroupID = Groups.GroupID;

-- LEFT JOIN 
SELECT Users.Username, Posts.Content, Likes.LikedAt
FROM Users
LEFT JOIN Posts ON Users.UserID = Posts.UserID
LEFT JOIN Likes ON Posts.PostID = Likes.PostID;

-- RIGHT JOIN
SELECT Groups.GroupName, Users.Username
FROM Groups
RIGHT JOIN GroupMembers ON Groups.GroupID = GroupMembers.GroupID
RIGHT JOIN Users ON GroupMembers.UserID = Users.UserID;

-- FULL JOIN
SELECT Users.Username, Groups.GroupName
FROM Users
FULL JOIN GroupMembers ON Users.UserID = GroupMembers.UserID
FULL JOIN Groups ON GroupMembers.GroupID = Groups.GroupID;


-- e. 2 queries with the IN operator and a subquery in the WHERE clause

-- Users in group with id 1
SELECT Username
FROM Users
WHERE UserID IN 
	(SELECT UserID 
	FROM GroupMembers 
	WHERE GroupID = 1);

-- Content of the posts of the users in the group 'Tech Enthusiasts'
SELECT Content
FROM Posts
WHERE UserID IN 
	(SELECT UserID 
	FROM GroupMembers 
	WHERE GroupID IN 
		(SELECT GroupID 
		FROM Groups 
		WHERE GroupName = 'Tech Enthusiasts'));


-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause

-- get the users that belong in any groups
SELECT Username
FROM Users u
WHERE EXISTS (SELECT * 
			FROM GroupMembers gm 
			WHERE gm.UserID = u.UserID);

-- content of the posts which have coments by the users over 20 years old
SELECT Content
FROM Posts p
WHERE EXISTS (SELECT 1 
			FROM Comments c
			WHERE c.PostID = p.PostID AND EXISTS 
					(SELECT 1 
					FROM Users u 
					WHERE u.UserID = c.UserID AND u.Age > 20));


-- g. 2 queries with a subquery in the FROM clause

-- calculates the average age of users in each group
SELECT GroupName, AVG(Age) AS AverageAge
FROM (
    SELECT g.GroupName, u.Age
    FROM Groups g
    JOIN GroupMembers gm ON g.GroupID = gm.GroupID
    JOIN Users u ON gm.UserID = u.UserID
) AS Subquery
GROUP BY GroupName;


-- users who have posted at least twice
SELECT Username, TotalPosts
FROM (
    SELECT u.Username, COUNT(p.PostID) AS TotalPosts
    FROM Users u
    LEFT JOIN Posts p ON u.UserID = p.UserID
    GROUP BY u.Username
) AS Subquery
WHERE TotalPosts > 1;


-- h. 4 queries with the GROUP BY clause

-- total posts and total likes of users having over 100 likes
SELECT u.Username, COUNT(p.PostID) AS TotalPosts, SUM(p.Likes) AS TotalLikes
FROM Users u
JOIN Posts p ON u.UserID = p.UserID
GROUP BY u.Username
HAVING SUM(p.Likes) > 100;


-- Total comments of each user
SELECT u.Username, COUNT(c.CommentID) AS TotalComments
FROM Users u
JOIN Comments c ON u.UserID = c.UserID
GROUP BY u.Username
HAVING COUNT(c.CommentID) = (
    SELECT MAX(CommentCount)
    FROM (
        SELECT COUNT(CommentID) AS CommentCount
        FROM Comments
        GROUP BY UserID
    ) AS SubQuery
);

-- groups with 2 or more members
SELECT g.GroupName, COUNT(gm.GroupMemberID) AS TotalMembers
FROM Groups g
JOIN GroupMembers gm ON g.GroupID = gm.GroupID
GROUP BY g.GroupName
HAVING COUNT(gm.GroupMemberID) >= 2;

-- user with the highest average of likes
SELECT u.Username, AVG(p.Likes) AS AvgLikesPerPost
FROM Users u
JOIN Posts p ON u.UserID = p.UserID
GROUP BY u.Username
HAVING AVG(p.Likes) = (
    SELECT MAX(AvgLikes)
    FROM (
        SELECT AVG(p.Likes) AS AvgLikes
        FROM Users u
        JOIN Posts p ON u.UserID = p.UserID
        GROUP BY u.Username
    ) AS SubQuery
);


-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause

-- finds posts that have been liked by at least one user older than 21
SELECT Content
FROM Posts
WHERE PostID = ANY (
    SELECT PostID
    FROM Likes
    WHERE UserID IN (
        SELECT UserID
        FROM Users
        WHERE Age > 21
    )
);

-- finds users older than all users in a specific group
SELECT p.Content
FROM Posts p
WHERE p.PostID = ALL (
    SELECT p.PostID
    FROM GroupMembers gm
    JOIN Likes l ON gm.UserID = l.UserID
    JOIN Posts p ON l.PostID = p.PostID
    WHERE gm.GroupID = 3
);

-- identifies users who have commented on posts 
SELECT Username
FROM Users
WHERE UserID = ANY (
    SELECT DISTINCT UserID
    FROM Comments
);

-- finds posts that have been liked by all users younger than 21
SELECT Content
FROM Posts
WHERE PostID = ALL (
    SELECT PostID
    FROM Likes l
    WHERE l.UserID = ALL (
        SELECT UserID
        FROM Users
        WHERE Age < 21
    )
);


