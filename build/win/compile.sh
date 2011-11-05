#!/bin/sh
curdir=`pwd`
cd ..
for i in ../api/*.cpp ../system/*.cpp ../system/pawn/*.cpp ../system/SDK/*.cpp ../util/*.cpp ../modules/*.cpp
do
  clwrapper /c /nologo /W3 /WX- /O2 /Ob2 /Oi /Ot /Ox /GL /Gm- /EHsc /GS /Gy /Zc:wchar_t /Zc:forScope /DNDEBUG /DWIN32 /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS /DMULTITHREADED /I../ /I../system /ID:/dev/boost-trunk $i
  if [ $? -ne 0 ]
  then
    exit 1
  fi
done
cd $curdir
rm -f  *.obj
mv -f ../*.obj ./
clwrapper *.obj /nologo /link /OUT:"niceamx.dll" /DEF:plugin.def /INCREMENTAL:NO /NOLOGO /DLL /SUBSYSTEM:WINDOWS /OPT:REF /OPT:ICF /LTCG /DYNAMICBASE /NXCOMPAT /MACHINE:X86
mv -f niceamx.dll ../../server/plugins/
