using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace sharp3._5._5late {
    class Program {
        static void Main(string[] args) {
            try {
                Type type = Type.GetTypeFromProgID("Excel.Application");
                object excel = Activator.CreateInstance(type);
                object workbooks = type.InvokeMember("Workbooks",
                    BindingFlags.GetProperty, null, excel, null);
                object workbook = workbooks.GetType().InvokeMember("Add",
                    BindingFlags.InvokeMethod, null, workbooks, null);
                object sheets = workbook.GetType().InvokeMember("Worksheets",
                    BindingFlags.GetProperty, null, workbook, null);
                object sheet = sheets.GetType().InvokeMember("Item",
                    BindingFlags.GetProperty, null, sheets, new object[] { 1 });
                object range = sheet.GetType().InvokeMember("Range",
                    BindingFlags.GetProperty, null, sheet,
                    new object[] { "A1", "C1" });
                object[] headers = { "Order ID", "Amount", "Tax" };
                range.GetType().InvokeMember("Value", BindingFlags.SetProperty,
                    null, range, new object[] { headers });
                object font = range.GetType().InvokeMember("Font",
                    BindingFlags.GetProperty, null, range, null);
                font.GetType().InvokeMember("Bold", BindingFlags.SetProperty,
                    null, font, new object[] { true });
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
                range = sheet.GetType().InvokeMember("Range",
                    BindingFlags.GetProperty, null, sheet,
                    new object[] { "A2" });
                range = range.GetType().InvokeMember("Resize",
                    BindingFlags.GetProperty, null, range,
                    new object[] { 20, 3 });
                range.GetType().InvokeMember("Value", BindingFlags.SetProperty,
                    null, range, new object[] { data });
                workbook.GetType().InvokeMember("SaveAs",
                    BindingFlags.InvokeMethod, null, workbook,
                    new object[] { "E:\\file9.xlsx" });
                workbook.GetType().InvokeMember("Close",
                    BindingFlags.InvokeMethod, null, workbook,
                    new object[] { false });
                type.InvokeMember("Quit", BindingFlags.InvokeMethod,
                    null, excel, null);
            }
            catch(Exception e) {
                Console.WriteLine("Error stack: {0}", e);
            }
        }
    }
}
