USE SocialMediaApp
GO

SELECT * FROM Groups
GO

CREATE VIEW UsersAgeView AS
SELECT Username, Age
FROM Users;
GO

CREATE VIEW UsersPostsView AS
SELECT Users.UserID, Users.Username, Posts.PostID, Posts.Content
FROM Users
JOIN Posts ON Users.UserID = Posts.UserID;
GO

CREATE VIEW GroupAdminsView AS
SELECT
    G.GroupID,
    G.GroupName
FROM
    Groups G INNER JOIN Users U ON G.CreatedByUserID = U.UserID
GROUP BY
    G.GroupID, G.GroupName;
GO