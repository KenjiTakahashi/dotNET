using System;
using System.Collections.Generic;
using System.Text;
using Excel = Microsoft.Office.Interop.Excel;

namespace sharp3._5._5 {
    class Program {
        static void Main(string[] args) {
            object filename = "E:\\file8.xlsx";
            Excel.Application excel = new Excel.Application();
            Excel.Workbooks workbooks = excel.Workbooks;
            Excel.Workbook workbook = workbooks.Add();
            Excel.Worksheet sheet = workbook.Worksheets.get_Item(1);
            Excel.Range range = sheet.get_Range("A1", "C1");
            object[] headers = { "Order ID", "Amount", "Tax" };
            range.Value = headers;
            range.Font.Bold = true;
            object[,] data = new object[20, 3];
            Random rand = new Random((int)DateTime.Now.Ticks);
            double order, tax;
            for(int i = 0; i < 20; ++i) {
                data[i, 0] = "ORD" + i.ToString("0000");
                order = rand.Next(1000);
                data[i, 1] = order.ToString("c");
                tax = order * 0.07;
                data[i, 2] = tax.ToString("c");
            }
            range = sheet.get_Range("A2");
            range = range.get_Resize(20, 3);
            range.Value = data;
            workbook.SaveAs(filename);
            workbook.Close(false);
            excel.Quit();
        }
    }
}
