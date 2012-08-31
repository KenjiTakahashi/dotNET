import clr
clr.AddReference('System.Windows.Forms')
clr.AddReference('System.Drawing')

from System.Windows.Forms import *
from System.Drawing import *
from System import DateTime, Array
from math import sin, cos, pi

class MyForm(Form):
    __timer = Timer()
    def __init__(self):
        self.__timer.Tick += self.__tick
        self.__timer.Interval = 50
        self.__timer.Enabled = True
        self.SetStyle(ControlStyles.UserPaint, True)
        self.SetStyle(ControlStyles.AllPaintingInWmPaint, True)
        self.SetStyle(ControlStyles.DoubleBuffer, True)
    def OnPaint(self, e):
        g = e.Graphics
        g.SmoothingMode = Drawing2D.SmoothingMode.AntiAlias
        g.Clear(Color.White)
        h = DateTime.Now.Hour
        m = DateTime.Now.Minute
        center = PointF(self.Width / 2, self.Height / 2)
        h = DateTime.Now.Hour
        m = DateTime.Now.Minute
        s = DateTime.Now.Second
        matrix = Drawing2D.Matrix()
        matrix.RotateAt((360 / 60) * s, center)
        spa = Array[PointF]([PointF(self.Width / 2, 56)])
        matrix.TransformPoints(spa)
        matrix.Reset()
        matrix.RotateAt((360 / 60) * m + (0.1 * s), center)
        mpa = Array[PointF]([PointF(self.Width / 2, 70)])
        matrix.TransformPoints(mpa)
        matrix.Reset()
        matrix.RotateAt((360 / 12) * h + (0.5 * m), center)
        hpa = Array[PointF]([PointF(self.Width / 2, 92)])
        matrix.TransformPoints(hpa)
        f = Font("Courier", 8, FontStyle.Regular)
        for i in range(1, 13):
            matrix.Reset()
            matrix.RotateAt((360 / 12) * i, center)
            a = Array[PointF]([PointF(self.Width / 2, 56)])
            matrix.TransformPoints(a)
            size = g.MeasureString(str(i), f)
            pa = PointF(a[0].X - (size.Width / 2), a[0].Y - (size.Height / 2))
            g.DrawString(str(i), f, Brushes.BurlyWood, pa)
        for i in set(range(1, 60)) - set(range(5, 56, +5)):
            matrix.Reset()
            matrix.RotateAt((360 / 60) * i, center)
            a = Array[PointF]([
                PointF(self.Width / 2, 56),
                PointF(self.Width / 2, 59)
            ])
            matrix.TransformPoints(a)
            g.DrawLine(Pen(Color.Firebrick, 1), a[0], a[1])
        g.DrawLine(Pen(Color.MidnightBlue, 1), center, spa[0])
        g.DrawLine(Pen(Color.BlueViolet, 2), center, mpa[0])
        g.DrawLine(Pen(Color.SaddleBrown, 3), center, hpa[0])
    def __tick(self, sender, e):
        self.Refresh()

form = MyForm()
Application.Run(form)
