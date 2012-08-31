Module Module1

    Sub Main()
        Dim excel As Object
        excel = CreateObject("Excel.Application")
        If excel Is Nothing Then
            MsgBox("Could not achieve object")
        Else
            Dim workbooks As Object
            Dim workbook As Object
            Dim sheets As Object
            Dim sheet As Object
            Dim range As Object
            Dim font As Object
            workbooks = CallByName(excel, "Workbooks", CallType.Get)
            workbook = CallByName(workbooks, "Add", CallType.Method)
            sheets = CallByName(workbook, "Worksheets", CallType.Get)
            sheet = CallByName(sheets, "Item", CallType.Get, 1)
            range = CallByName(sheet, "Range", CallType.Get, "A1", "C1")
            Dim headers As Object
            headers = {"Order ID", "Amount", "Tax"}
            CallByName(range, "Value", CallType.Let, headers)
            font = CallByName(range, "Font", CallType.Get)
            CallByName(font, "Bold", CallType.Let, True)
            Dim data(20, 3) As Object
            Dim order As Double
            Dim tax As Double
            Dim rand As New Random(System.DateTime.Now.Millisecond)
            For i As Integer = 0 To 20 Step 1
                data(i, 0) = "ORD" + i.ToString("0000")
                order = rand.Next(1000)
                data(i, 1) = order.ToString("c")
                tax = order * 0.070000000000000007
                data(i, 2) = tax.ToString("c")
            Next i
            range = CallByName(sheet, "Range", CallType.Get, "A2")
            range = CallByName(range, "Resize", CallType.Get, New Object() {20, 3})
            CallByName(range, "Value", CallType.Let, New Object() {data})
            CallByName(workbook, "SaveAs", CallType.Method, "E:\file10.xlsx")
            CallByName(workbook, "Close", CallType.Method, False)
            CallByName(excel, "Quit", CallType.Method)
        End If
    End Sub

End Module
