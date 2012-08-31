using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace _3._3._3 {
    class Program {
        static void Main(string[] args) {
            string path = "E:\\file2.txt";
            var query = from nazwisko in File.ReadAllLines(path)
                        group nazwisko by nazwisko[0] into result
                        orderby result.Key
                        select result.Key;
            foreach(var item in query) {
                Console.WriteLine(item);
            }
        }
    }
}
