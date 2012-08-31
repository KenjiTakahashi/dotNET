using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace _3._3._2 {
    class Program {
        static void Main(string[] args) {
            string path = "E:\\file.txt";
            var query = from str in File.ReadAllLines(path)
                        let liczba = Convert.ToInt32(str)
                        where liczba > 100
                        orderby liczba
                        select liczba;
            foreach(var item in query) {
                Console.WriteLine(item);
            }
            var result = File.ReadAllLines(path)
                .Select(n => new { liczba = Convert.ToInt32(n), n })
                .Where(x => x.liczba > 100)
                .OrderBy(x => x.liczba)
                .Select(x => x.liczba);
            Console.WriteLine("SECOND WAY:");
            foreach(var item in result) {
                Console.WriteLine(item);
            }
        }
    }
}
