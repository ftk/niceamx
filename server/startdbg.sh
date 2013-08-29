cd ../build
make CXX='g++-4.8' -j 8 config=debug install
status=$?
cd ../server
cp cfgdebug.txt server.cfg
[ $status -eq "0" ] && exec ./samp03svr-a1
