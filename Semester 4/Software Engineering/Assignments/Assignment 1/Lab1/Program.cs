// 6. Write a program to find the longest palindromic substring in
// a given string. For example, in the string "babad", one possible 
// possible longest palindromic substring is "bab"

namespace Lab1
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Enter a string:");
            string inputString = Console.ReadLine();
            Console.WriteLine(LongestPalindromicSubstring.LongestPalindrome(inputString));
        }

        public class LongestPalindromicSubstring
        {
            public static string LongestPalindrome(string stringToCheck)
            {
                if (string.IsNullOrEmpty(stringToCheck) || stringToCheck.Length == 1)
                    return stringToCheck;
                int start = 0, maxLength = 1;
                for (int index = 0; index < stringToCheck.Length; index++)
                {
                    int firstComputedLength = ExpandAroundCenter(stringToCheck, index, index);
                    int secondComputedLength = ExpandAroundCenter(stringToCheck, index, index + 1);
                    int realLength = Math.Max(firstComputedLength, secondComputedLength);
                    if (realLength > maxLength)
                    {
                        maxLength = realLength;
                        start = index - (realLength - 1) / 2;
                    }
                }
                return stringToCheck.Substring(start, maxLength);
            }

            private static int ExpandAroundCenter(string s, int left, int right)
            {
                while (left >= 0 && right < s.Length && s[left] == s[right])
                {
                    left--;
                    right++;
                }
                return right - left - 1;
            }
        }
    }
}
