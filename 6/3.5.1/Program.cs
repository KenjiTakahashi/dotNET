using System;
using System.Text;
using System.Runtime.InteropServices;

namespace _3._5._1 {
    class Program {
        [DllImport("Advapi32.dll")]
        static extern bool GetUserName(StringBuilder lpBuffer, ref int nSize);
        [DllImport("user32.dll", CharSet=CharSet.Auto)]
        static extern int MessageBox(IntPtr hWnd, String text, String caption, int options);
        [STAThread]
        static void Main(string[] args) {
            StringBuilder buffer = new StringBuilder(64);
            int nSize = 64;
            GetUserName(buffer, ref nSize);
            MessageBox(IntPtr.Zero, buffer.ToString(), "Caption", 0);
        }
    }
}
