var wshshell = WScript.CreateObject("WScript.Shell");
var path = wshshell.SpecialFolders("Desktop") + "\\date.txt";
var date = new Date();
var fcs = WScript.CreateObject("Scripting.FileSystemObject");
var file = fcs.OpenTextFile(path, 2, true);
file.WriteLine(date);
file.Close();
WScript.Echo("DONE");