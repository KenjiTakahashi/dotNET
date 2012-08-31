using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace _3._1._4 {
    [AttributeUsage(System.AttributeTargets.Method, Inherited = false)]
    class Oznakowane : System.Attribute { }
    public class Foo {
        [Oznakowane]
        public int Bar() {
            return 1;
        }
        public int Qux() {
            return 2;
        }
        public int Alg(int attr) {
            return 3;
        }
        public string ToStr() {
            return this.Qux().ToString();
        }
    }
    public class Searcher {
        Type type;
        public Searcher(Object obj) {
            this.type = obj.GetType();
        }
        public List<MethodInfo> findAll() {
            List<MethodInfo> results = new List<MethodInfo>();
            foreach(MethodInfo mi in type.GetMethods()) {
                if(mi.GetParameters().Length == 0
                    && mi.ReturnType == typeof(int)
                    && mi.IsPublic && !mi.IsStatic) {
                    results.Add(mi);
                }
            }
            return results;
        }
        public List<MethodInfo> findTagged(List<MethodInfo> arg) {
            List<MethodInfo> results = new List<MethodInfo>();
            foreach(MethodInfo mi in arg) {
                if(Attribute.IsDefined(mi, typeof(Oznakowane))) {
                    results.Add(mi);
                }
            }
            return results;
        }
        public List<int> execute(List<MethodInfo> arg) {
            List<int> results = new List<int>();
            Object invokation = Activator.CreateInstance(this.type);
            foreach(MethodInfo mi in arg) {
                Object r = mi.Invoke(invokation, null);
                results.Add(System.Convert.ToInt32(r.ToString()));
            }
            return results;
        }
    }
    class Program {
        static void Main(string[] args) {
            Foo foo = new Foo();
            Searcher searcher = new Searcher(foo);
            List<MethodInfo> all = searcher.findAll();
            Console.WriteLine("All public methods of int type, with no parameters:");
            foreach(MethodInfo mi in all) {
                Console.WriteLine(mi.Name);
            }
            List<MethodInfo> tagged = searcher.findTagged(all);
            Console.WriteLine("Oznakowane from above:");
            foreach(MethodInfo mi in tagged) {
                Console.WriteLine(mi.Name);
            }
            List<int> results = searcher.execute(tagged);
            Console.WriteLine("Results: ");
            foreach(int i in results) {
                Console.WriteLine(i);
            }
        }
    }
}
