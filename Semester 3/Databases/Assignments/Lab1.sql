CREATE DATABASE SocialMediaApp;

USE SocialMediaApp;


CREATE TABLE Users (
    UserID INT IDENTITY(1,1) PRIMARY KEY,
    Username VARCHAR(50) NOT NULL,
    Email VARCHAR(100) NOT NULL,
    Age INT NOT NULL
);


CREATE TABLE Posts (
    PostID INT PRIMARY KEY,
    UserID INT,
    Content TEXT NOT NULL,
	Likes INT DEFAULT 0,
    CreatedAt DATETIME DEFAULT SYSDATETIME(),
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);


CREATE TABLE Comments (
    CommentID INT PRIMARY KEY,
    PostID INT,
    UserID INT,
    Content TEXT NOT NULL,
    CommentedAt DATETIME DEFAULT SYSDATETIME(),
    FOREIGN KEY (PostID) REFERENCES Posts(PostID),
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);


--(M:N relationship between Users and Posts)
CREATE TABLE Likes (
    LikeID INT PRIMARY KEY,
    PostID INT,
    UserID INT,
    LikedAt DATETIME DEFAULT SYSDATETIME(),
    FOREIGN KEY (PostID) REFERENCES Posts(PostID),
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);


--(1:N relationship between Users and Users)
CREATE TABLE Followers (
    FollowID INT PRIMARY KEY,
    UserID INT,
    FollowsUserID INT,
    FOREIGN KEY (UserID) REFERENCES Users(UserID),
    FOREIGN KEY (FollowsUserID) REFERENCES Users(UserID)
);


--(1:N relationship between Users and Users)
CREATE TABLE FriendRequests (
    RequestID INT PRIMARY KEY,
    SenderUserID INT,
    ReceiverUserID INT,
    Status VARCHAR(20),
    FOREIGN KEY (SenderUserID) REFERENCES Users(UserID),
    FOREIGN KEY (ReceiverUserID) REFERENCES Users(UserID)
);


CREATE TABLE Groups (
    GroupID INT PRIMARY KEY,
    GroupName VARCHAR(100) NOT NULL,
    Description TEXT,
    CreatedByUserID INT,
    CreatedAt DATETIME DEFAULT SYSDATETIME(),
    FOREIGN KEY (CreatedByUserID) REFERENCES Users(UserID)
);


--(M:N relationship between Users and Groups)
CREATE TABLE GroupMembers (
    GroupMemberID INT PRIMARY KEY,
    GroupID INT,
    UserID INT,
    FOREIGN KEY (GroupID) REFERENCES Groups(GroupID),
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);


CREATE TABLE Messages (
    MessageID INT PRIMARY KEY,
    SenderUserID INT,
    ReceiverUserID INT,
    Content TEXT NOT NULL,
    SentAt DATETIME DEFAULT SYSDATETIME(),
    FOREIGN KEY (SenderUserID) REFERENCES Users(UserID),
    FOREIGN KEY (ReceiverUserID) REFERENCES Users(UserID)
);


CREATE TABLE Stories (
    StoryID INT PRIMARY KEY,
    UserID INT,
    Content TEXT NOT NULL,
	Views INT DEFAULT 0,
    CreatedAt DATETIME DEFAULT SYSDATETIME(),
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);