cd..
cd..
xcopy .\AR41Editor\Include\GameObject\*.* .\Client2D\Include\GameObject\ /d /s /y /i
xcopy .\AR41Editor\Include\Scene\*.* .\Client2D\Include\Scene\ /d /s /y /i /exclude:EditorExclude.txt

xcopy .\AR41Editor\Bin\*.* .\Client2D\Bin\ /d /s /y /i /exclude:Exclude.txt