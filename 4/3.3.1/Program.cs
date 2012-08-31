using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace _3._3._1 {
    public static class StringExtender {
        public static bool IsPalindrome(this String s) {
            string t = Regex.Replace(s.ToLower(), @"[\s\W\p{P}]", string.Empty);
            return t == new string(t.Reverse().ToArray());
        }
    }
    class Program {
        static void Main(string[] args) {
            string text = Console.ReadLine();
            if(text.IsPalindrome()) {
                Console.WriteLine("IT IS!");
            } else {
                Console.WriteLine("IT IS NOT!");
            }
        }
    }
}
