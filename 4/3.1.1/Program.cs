using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _3._1._1 {
    class Program {
        static bool Divisible(int n) {
            int sum = 0;
            while(n != 0) {
                if(n % 10 != 0) {
                    if(n % (n % 10) != 0) {
                        return false;
                    }
                    sum += n % 10;
                }
                n /= 10;
            }
            return n % sum == 0;
        }
        static void Main(string[] args) {
            for (int i = 1; i <= 100000; ++i) {
                if(Divisible(i)) {
                    Console.WriteLine(i);
                }
            }
        }
    }
}
