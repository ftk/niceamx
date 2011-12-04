#!/bin/bash -e

file='a_samp.inc'

grep 'native ' $file | grep -v '\.\.\.' > ${file}.tmp1

conv_type()
{
  #expr="`cat`"
  type=`echo $expr | perl -pe 's/^^(([A-Za-z0-9]+):)?.*$/$2/'`
  name=`echo $expr | perl -pe 's/^^([A-Za-z0-9]+:)?([A-Za-z0-9\[\]]+).*$/$2/'`
  ctype='int'
  if [ "$type" = "Float" ]
  then
    ctype='float'
  elif [ "$type" = "&Float" ]
  then
    ctype='float&'
  elif [ `echo $name | grep '\[\]' | wc -l` -ne '0' ] # name[]
  then
    ctype='const std::string&'
    name="${name%[]}"
  fi
  #echo "$ctype" "$name"
}

parse_line()
{
  #echo $line
  #fname=`echo $line | perl -pe 's/^native ([A-Za-z0-9]+:)?([A-Za-z0-9]+).*$/$2/g'`
  #freturn=`echo $line | perl -pe 's/^native (([A-Za-z0-9]+):)?.*$/$2/g'`
  expr=`echo $line | perl -pe 's/^native ([A-Za-z0-9:]+).*$/$1/'`
  conv_type
  fname="$name"
  freturn="$ctype"
  fparams=`echo $line | perl -pe 's/^native [^(]*\((.*)\);.*$/$1/g'`

  convname=`echo $fname | \
    perl -pe 's/[0-9A-Z]+/_\L$&/g' |   \
    perl -pe 's/^_//'`
    
  #echo $fname $convname $freturn

  cargs='' # int a, int b
  args='' # a, b
  types='' # int, int
  IFS=','
  for param in $fparams
  do
    test `echo "$param" | grep -E '(const|sizeof|^[0-9]|=|\.)' | wc -l` -ne '0' && continue
    #echo $param
    expr="$param"
    conv_type
    comma=', '
    test "$cargs" = "" && comma=''
    cargs="${cargs}${comma}$ctype $name"
    args="${args}${comma}$name"
    types="${types}${comma}$ctype"
  done
  unset IFS
  
  #echo "$cargs" "$args" "$types"
  #comma=', '; test "$types" = "" && comma=''
  echo "pawn::marh_t<${types}> ${convname}_t(\"${fname}\", marhs); /* $line */" >&1
  
  echo "/* $line */" >&2
  echo "${freturn} ${convname} (${cargs})" >&2
  echo '{' >&2
  echo "  return ${convname}_t.call(${args});" >&2
  echo '}' >&2
  echo  >&2
}

cat ${file}.tmp1 | while read line
do 
  #echo $line
  line=`echo $line | tr -d '\n\r' `
  parse_line
done