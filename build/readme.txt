If you are getting "ELF file OS ABI invalid" error, do:
  elfedit --output-osabi=none niceamx.so
OR (freebsd):
  brandelf -f 0 niceamx.so
  
This will change ELF OS/ABI header to System V

