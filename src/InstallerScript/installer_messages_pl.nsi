; installer_messages_pl.nsi
; This file should not to be compiled. It is included in the "KrxImpExp.nsi" main script file.

!insertmacro MUI_LANGUAGE "Polish"

LangString WelcomeText ${LANG_POLISH} "Program instalacyjny poprowadzi cię przez instalację KrxImpExp. \r\n\r\nKrxImpExp is a set of plugins for 3D Studio Max. Te pluginy pozwolą ci na importowanie i eksportowanie plików ASC i 3DS do formatu Gothic i Gothic II. Gothic i Gothic II są grami Piranhi Bytes.\r\n\r\nZanim rozpoczniesz instalację, upewnij się, że program 3D Studio Max nie jest uruchomiony."
LicenseLangString LicText ${LANG_POLISH} "gpl-3.0.txt"
LangString DestDirText ${LANG_POLISH} "Wybierz główny folder 3D Studio"

LangString VCRedist_HeaderText ${LANG_POLISH} "Required Libraries"
LangString VCRedist_HeaderSubText ${LANG_POLISH} "This program requires additional libraries, which should be installed separately"
LangString VCRedist_X86Text ${LANG_POLISH} "This program requires the following 32-bit dynamic libraries: msvcp90.dll, msvcr90.dll. These libraries can be installed with Microsoft Visual C++ 2008 Redistributable Package (x86), which can be downloaded with a link below. However you may ignore this warning and continue the installation."
LangString VCRedist_X64Text ${LANG_POLISH} "This program requires the following 64-bit dynamic libraries: msvcp90.dll, msvcr90.dll. These libraries can be installed with Microsoft Visual C++ 2008 Redistributable Package (x64), which can be downloaded with a link below. However you may ignore this warning and continue the installation."
