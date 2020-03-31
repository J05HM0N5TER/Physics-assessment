# aieBootstrap Template

This is a student made template and not officially recognised or connected to the original in any way.

Original can be found at: https://github.com/AcademyOfInteractiveEntertainment/aieBootstrap

I removed the docs to save space because I've never used them, but they can be found in the Original if needed.

## Setup

Read the setup in the original as well because it includes setup not included here.

Add the bootstrap folder as a project.

Solution Property settings:
```
Common Properties:
	Project Dependencies (Apply to all projects other then bootstrap):
		Depends on:
			(Check) Bootstrap
```

Project Property settings (Apply to all Configurations and Platforms):
```
Configuration properties:
	General:
		Windows SDK Version(Not sure if this needs to be changed): 10.0.17763.0
		Output Directory: $(SolutionDir)temp\$(ProjectName)\$(Platform)\$(Configuration)\
		Intermediate Directory: $(SolutionDir)temp\$(ProjectName)\$(Platform)\$(Configuration)\
		Platform Toolset: Visual Studio 2017 (v141)
		Configuration Type: Application (.exe)
		
	Debugging:
		Working Directory: $(SolutionDir)bin\
	
	VC++ Directories:
		Include Directories: $(IncludePath)
		Library Directories: $(LibraryPath)
	
	C/C++:
		General:
			Additional Include Directories: $(SolutionDir)bootstrap;$(SolutionDir)dependencies/imgui;$(SolutionDir)dependencies/glm;%(AdditionalIncludeDirectories)
			
	Linker:
		General:
			Additional Library Directories: $(SolutionDir)dependencies\Bootstrap\$(Platform)\$(Configuration)\;%(AdditionalLibraryDirectories)
			
		Input:
			Additional Dependencies: bootstrap.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)
```
