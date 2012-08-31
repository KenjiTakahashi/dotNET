Set PrimeTester = CreateObject("myatl2.PrimeTester")
If PrimeTester.IsPrime2(17) = 0 Then
    MsgBox("It's prime!")
Else
    MsgBox("It's not prime!")
End If
