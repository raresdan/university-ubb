-- For this query to work I had to create a 'Database Mail' profile
-- Object Exporer -> Management -> Database Mail ->
-- -> Follow the steps to create a new profile is one doesn't already exist
-- I created a new profile using my personal Gmail adress and details

-- This query checks existing Database Mail profiles
USE msdb;
SELECT name, profile_id
FROM sysmail_profile;

-- Start of the operation
USE SocialMediaApp;

SELECT * FROM Users;

-- Changed my user's email to the real UBB email
UPDATE Users 
SET Email = 'rares.goia@stud.ubbcluj.ro'
WHERE UserID = 1;

-- Enable Database Mail XPs (From the Microsoft Documentation)
EXEC sp_configure 'show advanced options', 1;
RECONFIGURE;
EXEC sp_configure 'Database Mail XPs', 1;
RECONFIGURE;

-- Pick a subject and a body
DECLARE @Subject NVARCHAR(255) = 'Hello user!';
DECLARE @Body NVARCHAR(MAX) = 'Our Social Media App has recieved new updates!';

-- Create a comma-separated list of email addresses from the Users table
DECLARE @Recipients NVARCHAR(MAX);
SELECT @Recipients = COALESCE(@Recipients + ';', '') + Email
FROM Users;

-- Send the email to all Recipients (Also from the Microsoft Documentation)
-- If multiple profiles exist a '@profile-name' parameter should be filled,
-- otherwise the profile set to default will be used
-- in my case, I only have one profile which is set to default
EXEC msdb.dbo.sp_send_dbmail
    @recipients = @Recipients,
    @subject = @Subject,
    @body = @Body;


-- I think this query can be useful such that all users can be emailed the same message at once,
-- just by fetching their emails from the database.
-- This query can be used as a newsletter.