#!/bin/bash

LOG_FILE='download.log'
GIT_DOWNLOADER="git clone"

# SSH
SSH_SOURCES="git@github.com:semenovf/scripts.git -b master scripts
git@github.com:semenovf/portable-target.git -b master portable-target
git@github.com:semenovf/common-lib.git -b master common"

# HTTPS
HTTPS_SOURCES="https://github.com/semenovf/scripts.git --depth=1 -b master scripts
https://github.com/semenovf/portable-target.git -b master portable-target
https://github.com/semenovf/common-lib.git -b master common"

DEFAULT_SOURCES=${SSH_SOURCES}
DEFAULT_DOWNLOADER=${GIT_DOWNLOADER}

IFS=$'\n'

echo `date` > ${LOG_FILE}

for src in ${DEFAULT_SOURCES} ; do
    eval "${DEFAULT_DOWNLOADER} $src" >> ${LOG_FILE} 2>&1

    if [ $? -eq 0 ] ; then
        echo "Cloning $src: SUCCESS"
    else
        echo "Cloning $src: FAILURE"
    fi
done
