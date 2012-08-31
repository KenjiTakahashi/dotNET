using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _3._3._8 {
    class Program {
        static void Main(string[] args) {
            var item = new { Field1 = "The Value", Field2 = 5 };
            List<object> theList = new List<object>(); // also: object = dynamic
            theList.Add(item);
            var item2 = new { Field2 = 5, Field3 = "Value" };
            theList.Add(item2);
            // or
            var list = new[] { item }.ToList();
            var item3 = new { Field1 = "Valueee", Field2 = 3 };
            list.Add(item);
            list.Add(item3);
            Console.WriteLine(list[0].Field1);
            Console.WriteLine(list[1].Field2);
        }
    }
}
