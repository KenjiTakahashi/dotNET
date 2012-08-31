using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _3._4._1 {
    class Program {
        static int Static(int x, int y) {
            return x * y + y - x;
        }
        static dynamic Dynamic(dynamic x, dynamic y) {
            return x * y + y - x;
        }
        static void Main(string[] args) {
            DateTime start = DateTime.Now;
            for(int i = 0, j = 100000; i < 100000; ++i, --j) {
                Static(i, j);
            }
            DateTime end = DateTime.Now;
            double s = (end - start).TotalMilliseconds;
            Console.WriteLine("Static: " + s);
            start = DateTime.Now;
            for(int i = 0, j = 100000; i < 100000; ++i, --j) {
                Dynamic(i, j);
            }
            end = DateTime.Now;
            double d = (end - start).TotalMilliseconds;
            Console.WriteLine("Dynamic: " + d);
            Console.WriteLine("For 100000 values dynamic was " + (d / s) + " times slower");
        }
    }
}
