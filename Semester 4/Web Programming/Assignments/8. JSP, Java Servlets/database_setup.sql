CREATE DATABASE bookmarksweb;

USE bookmarksweb;

CREATE TABLE Users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);

CREATE TABLE URLs (
    url_id INT AUTO_INCREMENT PRIMARY KEY,
    url VARCHAR(255) NOT NULL,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES Users(user_id)
);

SELECT * FROM Users;
SELECT * FROM URLs;

INSERT INTO Users VALUES (3, 'dan', 'qwerty');

-- Aggreagtion to find the popularity of a table
SELECT URLs.url, COUNT(DISTINCT URLs.user_id) AS user_count
FROM URLs
GROUP BY URLs.url
ORDER BY user_count DESC
LIMIT 5;

INSERT INTO URLs (url_id, url, user_id) VALUES 
(1, 'https://www.example.com', 1),
(2, 'https://www.anotherexample.com', 1),
(3, 'https://www.something.com', 2),
(4, 'https://www.different.com', 2);



