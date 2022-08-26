cd..
cd..

xcopy .\AR41Engine\Include\*.h .\Engine\Include\ /d /s /y /i
xcopy .\AR41Engine\Include\*.inl .\Engine\Include\ /d /s /y /i
xcopy .\AR41Engine\Bin\*.* .\Engine\Bin\ /d /s /y /i /exclude:Exclude.txt
xcopy .\AR41Engine\Bin\*.* .\AR41Editor\Bin\ /d /s /y /i /exclude:Exclude.txt
xcopy .\AR41Engine\Bin\*.* .\Client2D\Bin\ /d /s /y /i /exclude:Exclude.txt

:: Create Component Folder If Does not exists
if not exist .\AR41Editor\Include\GameObject ( mkdir .\AR41Editor\Include\GameObject )
if not exist .\AR41Editor\Include\Component ( mkdir .\AR41Editor\Include\Component )