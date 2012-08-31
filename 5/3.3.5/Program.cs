using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace _3._3._5 {
    class Program {
        static void Main(string[] args) {
            string path = "E:\\folder";
            long result = Directory.GetFiles(path).Aggregate(0L, (count, file) =>
                count += (new FileInfo(file)).Length);
            Console.WriteLine(result);
        }
    }
}
