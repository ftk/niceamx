cd ../build
make CXX='g++-4.8' -j 8 install
status=$?
cd ../server
cp cfgrelease.txt server.cfg
[ $status -eq "0" ] && exec ./samp03svr-u2
