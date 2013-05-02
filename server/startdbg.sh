cd ../build
make -j 8 config=debug install
status=$?
cd ../server
cp cfgdebug.txt server.cfg
[ $status -eq "0" ] && exec ./samp03svr-u2
