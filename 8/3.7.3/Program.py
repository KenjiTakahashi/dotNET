import clr
clr.AddReference('System.Windows.Forms')
clr.AddReference('System.Drawing')

from System.Windows.Forms import *
from System.Drawing import *

class SmoothProgressBar(UserControl):
    def __init__(self):
        UserControl.__init__(self)
        self.__min = 0
        self.__max = 100
        self.__value = 0
    def getmin(self):
        return self.__min
    def setmin(self, min):
        self.__min = min
        self.Invalidate()
    min = property(getmin, setmin)
    def getmax(self):
        return self.__max
    def setmax(self, max):
        if max < self.__min:
            max = self.__min
        self.__max = max
        self.Invalidate()
    max = property(getmax, setmax)
    def getvalue(self):
        return self.__value
    def setvalue(self, value):
        if value < self.__min:
            value = self.__min
        elif value > self.__max:
            value = self.__max
        self.__value = value
        self.Invalidate()
    value = property(getvalue, setvalue)
    def OnPaint(self, e):
        g = e.Graphics
        b = SolidBrush(Color.DarkViolet)
        p = float(self.__value - self.__min) / float(self.__max - self.__min)
        r = self.ClientRectangle
        r.Width = int(r.Width * p)
        g.FillRectangle(b, r)
        pw = Pens.White.Width
        g.DrawLine(Pens.DarkGray,
        Point(self.ClientRectangle.Left, self.ClientRectangle.Top),
        Point(self.ClientRectangle.Width - pw, self.ClientRectangle.Top))
        g.DrawLine(Pens.DarkGray,
        Point(self.ClientRectangle.Left, self.ClientRectangle.Top),
        Point(self.ClientRectangle.Left, self.ClientRectangle.Height - pw))
        g.DrawLine(Pens.White,
        Point(self.ClientRectangle.Left, self.ClientRectangle.Height - pw),
        Point(self.ClientRectangle.Width - pw, self.ClientRectangle.Height - pw))
        g.DrawLine(Pens.White,
        Point(self.ClientRectangle.Width - pw, self.ClientRectangle.Top),
        Point(self.ClientRectangle.Width - pw, self.ClientRectangle.Height - pw))
    def OnResize(self, e):
        self.Invalidate()

class MyForm(Form):
    def __init__(self):
        self.Size = Size(100, 160)
        pbar = SmoothProgressBar()
        pbar.max = 155
        pbar.value = 100
        pbar.Height = 20
        pbar.Width = 90
        pbar.Left = 10
        pbar.Top = 10
        self.Controls.Add(pbar)
        abut = Button()
        abut.Top = 40
        abut.Left = 10
        abut.Width = 90
        abut.Text = "Advance!"
        def aclick(sender, e):
            pbar.value += 1
        abut.Click += aclick
        self.Controls.Add(abut)
        dbut = Button()
        dbut.Top = 70
        dbut.Left = 10
        dbut.Width = 90
        dbut.Text = "Drop!"
        def dclick(sender, e):
            pbar.value -= 1
        dbut.Click += dclick
        self.Controls.Add(dbut)

form = MyForm()
Application.Run(form)
