import clr
clr.AddReference('System.Windows.Forms')

from System.Windows.Forms import *

class MyForm(Form):
    def __init__(self):
        self.Closing += self.confirm
    def confirm(self, sender, event_args):
        if MessageBox.Show(u"Are you sure?", u"LOL", \
        MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No:
            event_args.Cancel = True

form = MyForm()
Application.Run(form)
