using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace _3._3._6 {
    public class Personal {
        public string Name { get; set; }
        public string Surname { get; set; }
        public string PESEL { get; set; }
    }
    public class Accounting {
        public string PESEL { get; set; }
        public string Number { get; set; }
    }
    class Program {
        static void Main(string[] args) {
            string path1 = "E:\\file4.txt";
            string path2 = "E:\\file5.txt";
            var personal = from pertmp in File.ReadAllLines(path1)
                        let pertmp_ = pertmp.Split(new string[] { ", " }, StringSplitOptions.None)
                        select new Personal() {
                            Name = pertmp_[0],
                            Surname = pertmp_[1],
                            PESEL = pertmp_[2]
                        };
            var accounting = from acctmp in File.ReadAllLines(path2)
                             let acctmp_ = acctmp.Split(new string[] { ", " }, StringSplitOptions.None)
                             select new Accounting() {
                                 PESEL = acctmp_[0],
                                 Number = acctmp_[1]
                             };
            var query = from per in personal
                        join acc in accounting on per.PESEL equals acc.PESEL
                        select per.Name + ", " + per.Surname + ", " + per.PESEL + ", " + acc.Number;
            var query2 = from pertmp in File.ReadAllLines(path1)
                         let person = pertmp.Split(new string[] { ", " }, StringSplitOptions.None)
                         join account in File.ReadAllLines(path2) on
                         person[2] equals account.Split(new string[] { ", " }, StringSplitOptions.None)[0]
                         select person[0] + ", " + person[1] + ", " + account;
            foreach(var item in query) {
                Console.WriteLine(item);
            }
            foreach(var item in query2) {
                Console.WriteLine(item);
            }
        }
    }
}
