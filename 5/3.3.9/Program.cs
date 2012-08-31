using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _3._3._9 {
    class Program {
        delegate Func<A, R> Recursive<A, R>(Recursive<A, R> r);
        static Func<A, R> Y<A, R>(Func<Func<A, R>, Func<A, R>> f) {
            Recursive<A, R> rec = r => a => f(r(r))(a);
            return rec(rec);
        }
        static void Main(string[] args) {
            List<int> list = new List<int>() { 1, 2, 3, 4, 5 };
            Func<int, int> fi = null;
            foreach(var item in list.Select(fi = i => i <= 2 ? 1 : fi(i - 1) * fi(i - 2))) {
                Console.WriteLine(item);
            }
            Console.WriteLine("COMBO BREAKER");
            //or
            foreach(var item in list.Select(Y<int, int>(f => i => i <= 2 ? 1 : f(i - 1) * f(i - 2)))) {
                Console.WriteLine(item);
            }
        }
    }
}
