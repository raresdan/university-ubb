using System;
using System.Globalization;
using System.Text.RegularExpressions;

namespace BasicDataValidationModule
{
    
    public class BasicDataValidation
    {
        public bool ValidateEmail(string email)
        {
            if (string.IsNullOrWhiteSpace(email)) 
                return false;

            string pattern = @"^(?!\.)(""([^""\r\\]|\\[""\r\\])*""|"
                       + @"([-a-z0-9!#$%&'*+/=?^_`{|}~]|(?<!\.)\.)*)(?<!\.)"
                       + @"[-a-z0-9!#$%&'*+/=?^_`{|}~](?<!\.)"
                       + @"@(((?!-)[a-z0-9-]{1,63}(?<!-)\.)+[a-z]{2,63}|"
                       + @"(\d{1,3}\.){3}\d{1,3})(:\d{4})?$";

            return Regex.IsMatch(email, pattern, RegexOptions.IgnoreCase);
        }

        public void TestValidateEmail()
        {
            string[] emails = {
            "example@example.com",
            "user.name@example.com",
            "first.last@example.com",
            "user123@example.com",
            "user+123@example.com",
            "user-123@example.com",
            "user_123@example.com",
            "user.123@example.com",
            "user@subdomain.example.com",
            "user@192.168.1.1",
            "user@[IPv6:2001:0db8:85a3:0000:0000:8a2e:0370:7334]",
            "\"user\"@example.com",
            "\"user name\"@example.com",
            "\"user\\\"name\"@example.com",
            "\"user\\\\name\"@example.com",
            "example@example.co.uk",
            "user@example.com:1234",
            "user@example..com",
            "user.@example.com",
            ".user@example.com",
            "user@.example.com",
            "user@example_com",
            "user@example.",
            "user@.com",
            "user@-example.com",
            "user@example-",
            "user@111.222.333.44444",
            "user@[111.222.333.444]",
            "user@[111.222.333.44444]",
            "user@example.1234"
        };

            foreach (string email in emails)
            {
                Console.WriteLine($"{email} - {ValidateEmail(email)}");
            }
        }

        public bool ValidatePhone(string phoneNumber)
        {
            if (string.IsNullOrWhiteSpace(phoneNumber))
                return false;

            // Regular expression pattern for validating phone numbers
            string pattern = @"^[\d\s\-\+\(\)]+$";

            // Check if the phone number matches the pattern
            return Regex.IsMatch(phoneNumber, pattern);
        }

        public void TestPhoneValidation()
        {
            string[] phoneNumbers = {
            "+1 (555) 123-4567",
            "1234567890",
            "+1234567890",
            "1-555-123-4567",
            "+1 555 123 4567",
            "1 (555) 123-4567",
            "5551234567",
            "(555) 1234567",
            "(555) 123 4567",
            "555-123-4567",
            "555 123 4567",
            "123 4567",
            "123-4567",
            "1234567",
            "+123 4567",
            "+123-4567",
            "+1234567",
            "+12 34 5678",
            "+12-34-5678",
            "+12 345678",
            "+12345678",
            "+12345678901234567890",
            "1234 567890",
            "+123#4567890", // Invalid - contains '#'
            "+123$4567890"  // Invalid - contains '$'
        };

            foreach (string phoneNumber in phoneNumbers)
            {
                Console.WriteLine($"{phoneNumber} - {ValidatePhone(phoneNumber)}");
            }
        }

        public bool ValidateDate(string date)
        {
            if (string.IsNullOrWhiteSpace(date))
                return false;

            DateTime parsedDate;
            string[] formats = {"dd/MM/yyyy", "MM/dd/yyyy", "yyyy/MM/dd", "dd-MM-yyyy",
                            "MM-dd-yyyy", "yyyy-MM-dd", "dd.MM.yyyy", "MM.dd.yyyy",
                            "yyyy.MM.dd", "dd MM yyyy", "MM dd yyyy", "yyyy MM dd"};

            // Check if the date can be parsed using any of the specified formats
            return DateTime.TryParseExact(date, formats, CultureInfo.InvariantCulture, DateTimeStyles.None, out parsedDate);
        }

        public void TestDatesValidation()
        {
            string[] dates = {
            "12/25/2024",   // MM/dd/yyyy
            "25/12/2024",   // dd/MM/yyyy
            "2024/12/25",   // yyyy/MM/dd
            "12-25-2024",   // MM-dd-yyyy
            "25-12-2024",   // dd-MM-yyyy
            "2024-12-25",   // yyyy-MM-dd
            "12.25.2024",   // MM.dd.yyyy
            "25.12.2024",   // dd.MM.yyyy
            "2024.12.25",   // yyyy.MM.dd
            "12 25 2024",   // MM dd yyyy
            "25 12 2024",   // dd MM yyyy
            "2024 12 25",    // yyyy MM dd
            "1111120448548",
        };

            foreach (string date in dates)
            {
                Console.WriteLine($"{date} - {ValidateDate(date)}");
            }
        }

        public string SanitizeInputAgainstSQLInjection(string input)
        { 
        if (string.IsNullOrWhiteSpace(input))
            return input;

        // Replace single quotes with two single quotes
        string sanitizedInput = input.Replace("'", "''");

        // Remove semicolons to prevent multiple queries
        sanitizedInput = Regex.Replace(sanitizedInput, @";", "");

        // Remove characters commonly used in SQL injection
        string[] sqlInjectionCharacters = { "--", ";", "/*", "*/", "@@", "@", 
                "char", "nchar", "varchar", "nvarchar", "alter", "begin", "cast", 
                "create", "cursor", "declare", "delete", "drop", "end", "exec", 
                "execute", "fetch", "insert", "kill", "select", "sys", "sysobjects", 
                "syscolumns", "table", "update" };
        foreach (string sqlChar in sqlInjectionCharacters)
        {
            sanitizedInput = sanitizedInput.Replace(sqlChar, "");
        }

        return sanitizedInput;
        }
    }


    internal class Program
    {
        static void Main(string[] args)
        {
            BasicDataValidation basicDataValidation = new BasicDataValidation();

            Console.WriteLine("Email Validation:");
            basicDataValidation.TestValidateEmail();

            Console.WriteLine("\nPhone Validation:");
            basicDataValidation.TestPhoneValidation();

            Console.WriteLine("\nDate Validation:");
            basicDataValidation.TestDatesValidation();

            Console.WriteLine("\nSanitize Input Against SQL Injection:");
            string userInput = "'; DROP TABLE Users; --";
            string sanitizedInput = basicDataValidation.SanitizeInputAgainstSQLInjection(userInput);
            Console.WriteLine($"Sanitized input: {sanitizedInput}\n");
        }
    }
}
