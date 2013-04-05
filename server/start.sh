cd ../build
make -j 8 config=debug install
status=$?
cd ../server
[ $status -eq "0" ] && exec ./samp03svr-u2
