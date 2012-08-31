import clr
clr.AddReferenceToFile("3.8.1c.dll")

from _3._8._1c import PrimeFibonacci

pf = PrimeFibonacci()
print "Prime Fibonacci: ", pf.get(45)