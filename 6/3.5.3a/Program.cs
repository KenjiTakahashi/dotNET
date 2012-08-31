using System;
using System.Text;
using System.Runtime.InteropServices;

namespace _3._5._3a {
    class Program {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int F(int n);
        [DllImport("3.5.3l.dll")]
        static extern int ExecuteC(int n, F f);
        [DllImport("3.5.2l.dll")]
        static extern int IsPrimeC(int n);
        static int IsPrimeCs(int n) {
            return IsPrimeC(n);
        }
        static void Main(string[] args) {
            Console.Write("Enter number: ");
            string line = Console.ReadLine();
            Console.WriteLine(line + ": " + (ExecuteC(Convert.ToInt32(line), IsPrimeCs) == 0 ? "True" : "False"));
        }
    }
}
