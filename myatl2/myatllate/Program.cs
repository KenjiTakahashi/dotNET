using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace myatllate {
    class Program {
        static void Main(string[] args) {
            Console.Write("Enter number: ");
            object[] param = { Convert.ToInt32(Console.ReadLine()) };
            try {
                Type type = Type.GetTypeFromProgID("myatl2.PrimeTester");
                object PrimeTester = Activator.CreateInstance(type);
                object result = type.InvokeMember("IsPrime",
                    BindingFlags.InvokeMethod, null, PrimeTester, param);
                if(result.Equals((object)0)) {
                    Console.WriteLine("It's prime!");
                } else {
                    Console.WriteLine("It's not prime!");
                }
            }
            catch(Exception e) {
                Console.WriteLine("Error stack: {0}", e.Message);
            }
        }
    }
}
