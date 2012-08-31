using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.FSharp.Collections;

namespace _3._8._1c {
    public class PrimeFibonacci {
        private bool IsPrime(int n) {
            for(int i = 2; i * 2 < n; ++i) {
                if(n % i == 0) {
                    return true;
                }
            }
            return false;
        }
        public List<int> get(int n) {
            List<int> results = new List<int>();
            foreach(int i in Fibonacci.list(n)) {
                if(IsPrime(i)) {
                    results.Add(i);
                }
            }
            return results;
        }
    }
}
