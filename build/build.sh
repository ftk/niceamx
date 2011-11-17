#!/bin/bash
#
# USAGE:
# $0 --link
# $0 [--nolink] [--with-lib <lib>] [modules|<file ...>]
#

INC_PARAMS=""
DEF_PARAMS=""
CPP_PARAMS=""
LNK_PARAMS=""

ALL_FILES=""
MODULES_FILES=""

PROJECT="default"


CONFIG_FILE="build.txt"


CC="g++"
OBJDIR="obj"

GCC="$CC"
WINCL=0
OBJEXT="o"

BOOST_LIBS=""
LIBS=""
# 
# MAX_JOBS="1"
# NUM_JOBS="0"

LINK=1
DEBUG=0
SHOW_ONLY=0
QUIET=0

cfg_param()
{
  RES=`cat ${CONFIG_FILE} | awk -F'[ \t]*::[ \t]*' '{if(NF==2&&$1=="'$*'") {print $2}}'`
  if [ "$RES" == "" ]
  then
    if [ $DEBUG -eq 1 ]
    then
      echo "Error getting arg $1 from $CONFIG_FILE" >> /dev/stderr
    fi
    return 1
  fi
  #sh -c "echo \"$RES\""
  echo "$RES"
  return 0
}

preconfigure()
{
  if [ ! -r $CONFIG_FILE ]
  then
    return 1
  fi
  
  CC=`cfg_param compiler || echo "$CC"`
  GCC=`cfg_param gcc || echo "$CC"`
  
  if [ `cfg_param msvc || echo 0` -ne 0 ]
  then
    WINCL=1
  fi
}

configure()
{
  if [ ! -r $CONFIG_FILE ]
  then
    echo "$CONFIG_FILE is not found!" >> /dev/stderr
    exit 1
  fi
  
  PROJECT=`cfg_param project || echo "$PROJECT"`
  
  INC_PARAMS=`cfg_param includes | awk '{for(i=1;i<=NF;i++) {printf "-I%s ", $i}}'`
  DEF_PARAMS=`cfg_param defines | awk '{for(i=1;i<=NF;i++) {printf "-D%s ", $i}}'`
  CPP_PARAMS="$CPP_PARAMS `cfg_param flags`"
  LNK_PARAMS="$LNK_PARAMS `cfg_param ldflags`"

  LIBS="$LIBS `cfg_param libs`"
  BOOST_LIBS="$BOOST_LIBS `cfg_param boost-libs`"

  MODULES_FILES=`cfg_param modules`
  ALL_FILES="`cfg_param sources` $MODULES_FILES"

  # config
  if [ "$BOOST_ROOT" = "" -a "$BOOST_LIBS" != "" ]
  then
    echo '$BOOST_ROOT is not set!' >> /dev/stderr
  fi

  for i in $BOOST_LIBS
  do
    LIBS="$LIBS ${BOOST_ROOT}/stage/lib/libboost_${i}.a"
  done

  OBJDIR=`cfg_param objdir || echo "$OBJDIR"`
  OBJEXT=`cfg_param objext || echo "$OBJEXT"`
#   set -m
#   trap "let NUM_JOBS--" USR2
  #trap "echo SIGUSR2" USR2
}

get_flags()
{
  echo -n "${CPP_PARAMS} ${DEF_PARAMS} ${INC_PARAMS}"
}
get_ldflags()
{
  echo -n "${LNK_PARAMS} $LIBS"
}

# compile [<file(s)>]
compile()
{
  for filename in $@
  do :
    if [ -r $filename ]
    then :

      if [ $SHOW_ONLY -eq 0 -a $QUIET -eq 0 ]
      then
	echo "$filename"
      fi

      cmdline="${CC} $(get_flags) $filename"
      if [ $DEBUG -eq 1 -o $SHOW_ONLY -eq 1 ]
      then
	echo $cmdline
      fi

      if [ $SHOW_ONLY -eq 0 ]
      then
	${cmdline}
	if [ $? -ne 0 ]
	then :
	  exit 1
	fi
      fi
    else
      echo "$filename is not found" >> /dev/stderr
    fi
  done
}

# link_obj
link_obj()
{
  if [ $SHOW_ONLY -eq 0 -a $QUIET -eq 0 ]
  then
    echo "Linking..."
  fi

  cmdline=""
  if [ $WINCL -ne 0 ]
  then
    cmdline="$CC ${OBJDIR}/*.${OBJEXT} $(get_ldflags)"
  else
    cmdline="$CC -o $PROJECT $(get_ldflags) ${OBJDIR}/*.${OBJEXT}"
  fi
  
  if [ $DEBUG -eq 1 -o $SHOW_ONLY -eq 1 ]
  then
    echo $cmdline
  fi
  # link
  
  if [ $SHOW_ONLY -eq 0 ]
  then
    ${cmdline}
    RESULT=$?
    if [ $RESULT -ne 0 ]
    then
      return $RESULT
    fi
  fi
}

# move_obj
move_obj()
{
  cmdline="mv -f *.${OBJEXT} ${OBJDIR}/"
  if [ $SHOW_ONLY -eq 0 ]
  then
    $cmdline
  else
    echo $cmdline
  fi
}


preconfigure

# params
while true
do
  if [ "$1" = "--with-lib" ]
  then
    LIBS="$LIBS $2"
    shift 2
  elif [ "$1" = "--with-boost-lib" ]
  then
    BOOST_LIBS="$BOOST_LIBS $2"
    shift 2
  elif [ "$1" = "--cc" ]
  then
    CC="$2"
    shift 2
  elif [ "$1" = "--verbose" ]
  then
    DEBUG=1
    shift 1
  elif [ "$1" = "--param" ]
  then
    CPP_PARAMS="$CPP_PARAMS $2"
    shift 2
  elif [ "$1" = "--lparam" ]
  then
    LNK_PARAMS="$LNK_PARAMS $2"
    shift 2
#   elif [ "$1" = "--jobs" ]
#   then
#     MAX_JOBS="$2"
#     shift 2
  elif [ "$1" = "--quiet" ]
  then
    QUIET=1
    shift 1
  elif [ "$1" = "--nolink" ]
  then
    LINK=0
    shift 1
  elif [ "$1" = "--link" ]
  then
    LINK=2
    shift 1
  elif [ "$1" = "--config" ]
  then
    if [ -r "$2" ]
    then
      CONFIG_FILE="$2"
      preconfigure
    else
      echo "File $2 not found!"
    fi
    shift 2
  elif [ "$1" = "--configure" ]
  then
    for i in `ls /usr/include/*.h`
    do
      header=`basename $i | tr 'a-z.+\-=' 'A-Z____'`
      header="HAVE_$header=1"
      echo $header
    done
    shift 1
    exit 0
  elif [ "$1" = "--cmd" ]
  then
    SHOW_ONLY=1
    shift 1
  elif [ "$1" = "--makefile" ]
  then
    echo "# generated by $0"
    configure
    shift 1
    cxxflags=`get_flags`
    ldflags=`get_ldflags`
    echo -ne "CXX=${CC}\nCXXFLAGS=${cxxflags}\nOUTFILE=${PROJECT}\nOBJDIR=${OBJDIR}\nOBJS="
    for i in $ALL_FILES
    do
      echo -n '$(OBJDIR)/'`basename ${i%.*}`".$OBJEXT "
    done
      echo -ne "\nSTABLEHEADERS="
    for i in `cfg_param pch`
    do
      echo -n "${i}.gch "
    done
    echo
    echo ".PHONY: all pch clean clean-pch clean-all pre-hooks post-hooks"
    echo 'all: pre-hooks $(OUTFILE) post-hooks'

    echo 'pre-hooks:'
    if cfg_param pre-hooks > /dev/null
    then
      echo -e "\t`cfg_param pre-hooks`"
    fi
    echo 'post-hooks:'
    if cfg_param post-hooks > /dev/null
    then
      echo -e "\t`cfg_param post-hooks`"
    fi
    echo -e 'pch: $(STABLEHEADERS)'
    echo -e 'clean:\n\trm -vf $(OBJS) $(OUTFILE)\nclean-pch:\n\trm -vf $(STABLEHEADERS)\nclean-all: clean clean-pch\n'

    echo -e '$(OBJDIR):\n\tmkdir -p $(OBJDIR)'
    echo '$(OBJS): | $(OBJDIR)'
    echo '$(OUTFILE): $(OBJS)'
    if [ $WINCL -ne 0 ]
    then
      echo -e '\t$(CXX) $(OBJS)' "$ldflags"
      #echo -e '\trm -f *.lib *.exp'
      cxxflags="$INC_PARAMS $DEF_PARAMS"
    else
      echo -e '\t$(CXX)' "$ldflags" '-o $(OUTFILE) $(OBJS)'
    fi
    
    echo '$(OBJDIR)/'"%.${OBJEXT}:"
    if [ $WINCL -ne 0 ]
    then
	  echo -e '\t$(CXX) $(CXXFLAGS) /Fo$@ $<\n'
	else
	  echo -e '\t$(CXX) $(CXXFLAGS) -o $@ $<\n'
	  
	  echo -e '%.gch:\n\t$(CXX) $(CXXFLAGS) -o $@ $<\n'
	fi
    for i in $ALL_FILES
    do
      #echo -n "`dirname $i`/"
	  base=`basename ${i%.*}`
	  ${GCC} -MM $cxxflags -MT '$(OBJDIR)'"/$base.${OBJEXT}" "$i"
      if [ $? -ne 0 ]
      then
		exit 1
      fi
      echo
    done

    for i in `cfg_param pch`
      do
	  ${GCC} -MM $cxxflags -MT ${i}.gch $i
	  if [ $? -ne 0 ]
	  then
		exit 1
	  fi
    done
#     LINK=0
#     QUIET=1
    exit 0
  elif [ "$1" = "--getconf" ]
  then
	configure
    echo "`cfg_param $2`"
    exit 0
    shift 1
  elif [ "$1" = "--help" ]
  then # todo
    #echo "help"
    #exit 1
    shift 1
  elif [ "$1" = "--pch" ]
  then
    configure
    compile `cfg_param pch`
    exit 0
  elif [ "${1:0:1}" = "-" ]
  then
    # wrong param
    echo "unknown option '$1'" >> /dev/stderr
    shift 1
  else
    # filename passed
    break
  fi
done

configure

if [ $LINK -eq 2 ]
then
  link_obj
  exit $?
fi

mkdir -p ${OBJDIR}

if [ "$1" = "modules" ]
then : # build modules only ( fast compiling )
  compile $MODULES_FILES
elif [ "$1" == "" ]
then : # compile all
  rm -f ./*.${OBJEXT}
  compile $ALL_FILES
  rm -f ${OBJDIR}/*.${OBJEXT}
else : # compile custom files
  compile $@
fi

move_obj

if [ $LINK -ne 0 ]
then :
  link_obj
fi

exit $?

