
xcopy .\AR41Editor\Include\GameObject\*.* .\Client3D\Include\GameObject\ /d /s /y /i
xcopy .\AR41Editor\Include\Scene\*.* .\Client3D\Include\Scene\ /d /s /y /i /exclude:ClientCopy3DExclude.txt
xcopy .\AR41Editor\Include\UI\*.* .\Client3D\Include\UI\ /d /s /y /i /exclude:ClientCopy3DExclude.txt
xcopy .\AR41Editor\Include\Setting\*.* .\Client3D\Include\Setting\ /d /s /y /i /exclude:ClientCopy3DExclude.txt
xcopy .\AR41Editor\Include\Component\*.* .\Client3D\Include\Component\ /d /s /y /i /exclude:ClientCopy3DExclude.txt

xcopy .\AR41Editor\Bin\*.* .\Client3D\Bin\ /d /s /y /i /exclude:ClientCopy3DExclude.txt

:: Create Component Folder If does not exists
if not exist .\Client3D\Include\GameObject ( mkdir .\Client3D\Include\GameObject )
if not exist .\Client3D\Include\Component ( mkdir .\Client3D\Include\Component )
