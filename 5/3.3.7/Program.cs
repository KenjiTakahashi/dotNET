using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace _3._3._7 {
    class Program {
        static void Main(string[] args) {
            string path = "E:\\file6.txt";
            var query = (from q in File.ReadAllLines(path)
                         group q by new string((
                             q.Split(' ')[1]).ToArray())
                             into qq
                             orderby qq.Count() descending
                             select qq.Key + " " + qq.Count()).Take(3);
            foreach(var item in query) {
                Console.WriteLine(item);
            }
        }
    }
}
