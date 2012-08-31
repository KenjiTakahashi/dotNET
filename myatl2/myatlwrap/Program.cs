using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace myatlwrap {
    class Program {
        static void Main(string[] args) {
            myatl2Lib.PrimeTester obj = new myatl2Lib.PrimeTester();
            Console.Write("Enter number: ");
            if(obj.IsPrime2(Convert.ToInt32(Console.ReadLine())) == 0) {
                Console.WriteLine("It's prime!");
            } else {
                Console.WriteLine("It's not prime!");
            }
        }
    }
}
