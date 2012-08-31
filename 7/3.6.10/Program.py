import clr
clr.AddReference('System.Windows.Forms')

from System.Windows.Forms import *
from System.Globalization import CultureInfo
from System import DateTime

class MyForm(Form):
    def __init__(self):
        tab = TabControl()
        tab.Dock = DockStyle.Fill
        self.nextlang("en-GB", tab)
        self.nextlang("de-DE", tab)
        self.nextlang("fr-FR", tab)
        self.nextlang("ru-RU", tab)
        self.nextlang("ar-SA", tab)
        self.nextlang("cs-CZ", tab)
        self.nextlang("pl-PL", tab)
        self.Controls.Add(tab)
    def nextlang(self, code, parent):
        ci = CultureInfo(code, False)
        tp = TabPage()
        tp.Text = ci.NativeName
        layout = TableLayoutPanel()
        layout.Dock = DockStyle.Fill
        self.createcontrols("Months:", ci.DateTimeFormat.MonthNames, layout)
        self.createcontrols("Short months:",
        ci.DateTimeFormat.AbbreviatedMonthNames, layout)
        self.createcontrols("Days:", ci.DateTimeFormat.DayNames, layout)
        self.createcontrols("Short days:",
        ci.DateTimeFormat.AbbreviatedDayNames, layout)
        label = Label()
        label.AutoSize = True
        label.Text = "Date:"
        layout.Controls.Add(label)
        label = Label()
        label.AutoSize = True
        label.Text = DateTime.Now.ToString("d", ci)
        layout.Controls.Add(label)
        tp.Controls.Add(layout)
        parent.TabPages.Add(tp)
    def createcontrols(self, name, clr, layout):
        label = Label()
        label.AutoSize = True
        label.Text = name
        layout.Controls.Add(label)
        box = TextBox()
        box.Dock = DockStyle.Fill
        box.Multiline = True
        box.Text = clr[0]
        for c in clr[1:-1]:
            box.Text += ", " + c
        layout.Controls.Add(box)

form = MyForm()
Application.Run(form)
