using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace _3._3._4 {
    class Program {
        static void Main(string[] args) {
            string path = "E:\\file3.txt";
            var query = from word in File.ReadAllLines(path)
                        group word by new string((
                            from letter in word.ToLower()
                            orderby letter
                            select letter).ToArray())
                            into anagrams
                            orderby anagrams.Count() descending
                            select anagrams;
            foreach(var item in query.First()) {
                Console.WriteLine(item);
            }
        }
    }
}
