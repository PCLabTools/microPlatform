rem Note: When running this script from VSCode it automatically runs it from project root
rem This is why it is important to reference everything as if it is from root folder
rem The Doxyfile configuration has been edited to work as if running from project root
@echo off

rem Create Doxygen output directory if non-existent
if not exist "doc\.doxygen" mkdir "doc\.doxygen"

rem Run Doxygen on the Doxyfile configuration
doxygen doc\Doxyfile

rem When complete launch the browser and show index.html
start doc\.doxygen\html\index.html

rem Note: if you receive the error "'doxygen' is not recognized as an internal or external command, operable program or batch file":
rem Ensure you include the doxygen "bin" folder to the Windows "PATH" environment variables