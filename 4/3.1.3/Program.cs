using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace _3._1._3 {
    class Test {
        private int Field_Info = 0;
        private int Method() {
            return 4;
        }
        private int Field {
            get {
                return Field_Info;
            }
            set {
                Field_Info = value;
            }
        }
        public int PMethod() {
            return 2;
        }
    }
    class Program {
        static void Main(string[] args) {
            Test test = new Test();
            MethodInfo private_method = test.GetType().GetMethod("Method", BindingFlags.NonPublic | BindingFlags.Instance);
            Console.WriteLine(private_method.Invoke(test, null));
            PropertyInfo private_property = test.GetType().GetProperty("Field", BindingFlags.NonPublic | BindingFlags.Instance);
            Console.WriteLine(private_property.GetValue(test, null));
            private_property.SetValue(test, 4566, null);
            Console.WriteLine(private_property.GetValue(test, null));
            DateTime start = DateTime.Now;
            for(int i = 0; i < 100000; ++i) {
                test.PMethod();
            }
            DateTime end = DateTime.Now;
            Console.WriteLine("Direct access: " + (end - start));
            start = DateTime.Now;
            MethodInfo public_method;
            for(int i = 0; i < 100000; ++i) {
                public_method = test.GetType().GetMethod("PMethod");
                public_method.Invoke(test, null);
            }
            end = DateTime.Now;
            Console.WriteLine("Reflected access: " + (end - start));
        }
    }
}
