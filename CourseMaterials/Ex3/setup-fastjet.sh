wget http://fastjet.fr/repo/fastjet-3.2.0.tar.gz
tar -zxvf fastjet-3.2.0.tar.gz
cd fastjet-3.2.0
./configure --prefix=$PWD/../fastjet-install
make
make check
make install
cd ..
