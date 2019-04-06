
qmake -project
echo 'CONFIG += qt debug' >> sample.qt.pro
make mocable

qmake
make

