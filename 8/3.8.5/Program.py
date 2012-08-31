import clr
clr.AddReference('System.Windows.Forms')
clr.AddReference("System.Management")

from System.Windows.Forms import *
from System.Management import *
from System.ComponentModel import BackgroundWorker
from System import Array, Environment
from System.Threading.Thread import Sleep
from System.Diagnostics import FileVersionInfo
from System.Reflection import Assembly
from Microsoft.Win32 import Registry, RegistryKey

class MyForm(Form):
    __stoper = False
    def __init__(self):
        self.Width = 400
        self.Closing += self.del_
        tc = TabControl()
        tc.Dock = DockStyle.Fill
        tp1 = TabPage("Hardware")
        layout1 = TableLayoutPanel()
        layout1.Dock = DockStyle.Fill
        layout1.AutoSize = True
        self.processor = self.__panel("Processor:", layout1, 0)
        self.freeram = self.__panel("Free RAM:", layout1, 1)
        self.allram = self.__panel("All RAM:", layout1, 2)
        self.lv = ListView()
        self.lv.Dock = DockStyle.Fill
        self.lv.Columns.Add("Name")
        layout1.Controls.Add(self.lv)
        tp1.Controls.Add(layout1)
        layout1.SetColumnSpan(self.lv, 2)
        tp2 = TabPage("Software")
        layout2 = TableLayoutPanel()
        layout2.Dock = DockStyle.Fill
        layout2.AutoSize = True
        self.system = self.__panel("Operating system:", layout2, 0)
        self.cenv = self.__panel("Compiled on:", layout2, 1)
        self.uenv = self.__panel("Running on:", layout2, 2)
        self.iname = self.__panel("User info:", layout2, 3)
        self.display = self.__panel("Display:", layout2, 4)
        self.ie = self.__panel("Internet Explorer:", layout2, 5)
        self.word = self.__panel("Microsoft Word:", layout2, 6)
        tp2.Controls.Add(layout2)
        tc.TabPages.AddRange(Array[TabPage]([tp1, tp2]))
        self.Controls.Add(tc)
        bw = BackgroundWorker()
        bw.WorkerReportsProgress = True
        bw.DoWork += self.__refresh
        bw.ProgressChanged += self.__redraw
        bw.RunWorkerAsync()
    def __panel(self, label, layout, i):
        l = Label()
        l.Text = label
        t = TextBox()
        t.ReadOnly = True
        t.Dock = DockStyle.Fill
        layout.Controls.Add(l, 0, i)
        layout.Controls.Add(t, 1, i)
        return t
    def __redraw(self, sender, e):
        self.processor.Text = e.UserState["processor"]
        self.freeram.Text = e.UserState["freeram"]
        self.allram.Text = e.UserState["allram"]
        self.system.Text = e.UserState["system"]
        self.iname.Text = e.UserState["iname"]
        self.display.Text = e.UserState["display"]
        self.ie.Text = e.UserState["ie"]
        self.word.Text = e.UserState["word"]
        self.cenv.Text = e.UserState["cenv"]
        self.uenv.Text = e.UserState["uenv"]
        self.lv.Clear()
        for i, printer in enumerate(e.UserState["printer"]):
            item = ListViewItem(printer, i)
            self.lv.Items.Add(item)
    def __refresh(self, sender, e):
        while not self.__stoper:
            result = dict()
            s = ManagementObjectSearcher("select Name from Win32_Processor")
            for mo in s.Get():
                result["processor"] = mo["Name"].ToString()
            s = ManagementObjectSearcher(
            "select FreePhysicalMemory from Win32_OperatingSystem")
            for mo in s.Get():
                result["freeram"] = mo["FreePhysicalMemory"].ToString()
            s = ManagementObjectSearcher(
            "select Capacity from Win32_PhysicalMemory")
            partial = 0
            for mo in s.Get():
                partial += mo["Capacity"]
            result["allram"] = partial.ToString()
            s = ManagementObjectSearcher(
            "select Caption,Version,ServicePackMajorVersion,ServicePackMinorVersion from Win32_OperatingSystem")
            for mo in s.Get():
                result["system"] = mo["Caption"].ToString() + \
                mo["Version"].ToString() + \
                "SP" + mo["ServicePackMajorVersion"].ToString() + \
                "." + mo["ServicePackMinorVersion"].ToString()
            s = ManagementObjectSearcher(
            "select Username from Win32_ComputerSystem")
            for mo in s.Get():
                result["iname"] = mo["Username"].ToString()
            s = ManagementObjectSearcher(
            "select CurrentHorizontalResolution,CurrentVerticalResolution,CurrentBitsPerPixel from Win32_VideoController")
            for mo in s.Get():
                result["display"] = mo["CurrentHorizontalResolution"].ToString() + \
                " x " + mo["CurrentVerticalResolution"].ToString() + \
                " (" + mo["CurrentBitsPerPixel"].ToString() + ")"
            key = Registry.LocalMachine.OpenSubKey(
            "SOFTWARE\\Microsoft\\Internet Explorer\\Version Vector")
            try:
                result["ie"] = key.GetValue("IE").ToString()
            except:
                result["ie"] = "NO IE FOUND!"
            key = Registry.LocalMachine.OpenSubKey(
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Winword.exe")
            try:
                result["word"] = FileVersionInfo.GetVersionInfo(key.GetValue(
                "Path").ToString() + "\\winword.exe").FileVersion.ToString()
            except:
                result["word"] = "NO MS WORD FOUND!"
            result["cenv"] = Assembly.GetExecutingAssembly(
            ).ImageRuntimeVersion.ToString()
            result["uenv"] = Environment.Version.ToString()
            s = ManagementObjectSearcher("select Name from Win32_Printer")
            result["printer"] = list()
            for mo in s.Get():
                result["printer"].append(mo["Name"].ToString())
            sender.ReportProgress(0, result)
            Sleep(200)
    def del_(self, sender, e):
        self.__stoper = True
        Sleep(200)

form = MyForm()
Application.Run(form)
