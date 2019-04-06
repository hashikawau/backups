#!/bin/sh

QMAKE="qmake -project -norecursive src/"

RET=${QMAKE}
if test ${RET} -eq 0
then
    echo "seijou"
else
    echo "ijou"
fi
