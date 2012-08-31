import clr
clr.AddReference('System.Windows.Forms')
clr.AddReference('System.DirectoryServices')

from System.Windows.Forms import *
from System.DirectoryServices import DirectoryEntry, DirectorySearcher

class MyForm(Form):
    def __init__(self):
        #entry = DirectoryEntry()
        searcher = DirectorySearcher()
        label = Label()
        for entry in searcher.FindAll():
            label.Text += entry.ToString()
        self.Controls.Add(label)

form = MyForm()
Application.Run(form)
