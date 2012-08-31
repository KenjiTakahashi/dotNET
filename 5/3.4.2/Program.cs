using System;
using System.Collections.Generic;
using System.Text;
using Word = Microsoft.Office.Interop.Word;

namespace _3._4._2 {
    class Program {
        static void Main(string[] args) {
            object filename = "E:\\file7.docx";
            Word.Application word = new Word.Application();
            word.Documents.Add();
            word.Selection.TypeText("Programowanie pod Windows");
            word.ActiveDocument.SaveAs2(ref filename);
            word.Documents.Close();
        }
    }
}
