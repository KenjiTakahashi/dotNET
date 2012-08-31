using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace _3._2._1 {
    class Arrays<T> where T : System.Collections.IList {
        private T array;
        private DateTime start, end;
        string type;
        public Arrays(T array) {
            this.array = array;
            this.type = array.GetType().ToString() + ": ";
        }
        public void Add() {
            this.start = DateTime.Now;
            for(int i = 0; i < 1000000; ++i) {
                this.array.Add(i);
            }
            this.end = DateTime.Now;
            Console.WriteLine(this.type + (end - start));
        }
        public void Access() {
            this.start = DateTime.Now;
            object tmp;
            for(int i = 0; i < 1000000; ++i) {
                tmp = this.array[i];
            }
            this.end = DateTime.Now;
            Console.WriteLine(this.type + (end - start));
        }
        public void Remove() {
            this.start = DateTime.Now;
            for(int i = 0; i < 1000000; ++i) {
                this.array.Remove(i);
            }
            this.end = DateTime.Now;
            Console.WriteLine(this.type + (end - start));
        }
    }
    class Hashes<T> where T : System.Collections.IDictionary {
        private T hash;
        private DateTime start, end;
        private string type;
        public Hashes(T hash) {
            this.hash = hash;
            this.type = hash.GetType().ToString() + ": ";
        }
        public void Add() {
            this.start = DateTime.Now;
            for(int i = 0; i < 1000000; ++i) {
                this.hash.Add(i, i);
            }
            this.end = DateTime.Now;
            Console.WriteLine(this.type + (end - start));
        }
        public void Access() {
            this.start = DateTime.Now;
            object temp;
            for(int i = 0; i < 1000000; ++i) {
                temp = this.hash[i];
            }
            this.end = DateTime.Now;
            Console.WriteLine(this.type + (end - start));
        }
        public void Remove() {
            this.start = DateTime.Now;
            for(int i = 0; i < 1000000; ++i) {
                this.hash.Remove(i);
            }
            this.end = DateTime.Now;
            Console.WriteLine(this.type + (end - start));
        }
    }
    class Program {
        static void Main(string[] args) {
            Arrays<ArrayList> arr_list = new Arrays<ArrayList>(new ArrayList());
            Arrays<List<int>> list = new Arrays<List<int>>(new List<int>());
            Hashes<Hashtable> hashtable = new Hashes<Hashtable>(new Hashtable());
            Hashes<Dictionary<int, int>> dict = new Hashes<Dictionary<int, int>>(
                new Dictionary<int, int>());
            Console.WriteLine("Adding:");
            arr_list.Add();
            list.Add();
            hashtable.Add();
            dict.Add();
            Console.WriteLine("Accessing:");
            arr_list.Access();
            list.Access();
            hashtable.Access();
            dict.Access();
            Console.WriteLine("Removing: ");
            arr_list.Remove();
            list.Remove();
            hashtable.Remove();
            dict.Remove();
        }
    }
}
