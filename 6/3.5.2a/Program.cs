using System;
using System.Text;
using System.Runtime.InteropServices;

namespace _3._5._2a {
    class Program {
        [DllImport("3.5.2l.dll")]
        static extern int IsPrimeC(int number);
        static void Main(string[] args) {
            Console.Write("Enter number: ");
            string line = Console.ReadLine();
            Console.WriteLine(line + ": " + (IsPrimeC(Convert.ToInt32(line)) == 0 ? "True" : "False"));
        }
    }
}
