import clr
clr.AddReference('System.Windows.Forms')

import pygold

from System.Windows.Forms import *

class MyForm(Form):
    def __init__(self):
         button = Button()
         button.Text = 'Click Me'
         self.Controls.Add(button)


form = MyForm()
Application.Run(form)
