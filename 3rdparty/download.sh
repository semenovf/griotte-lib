#!/bin/bash

LOG_FILE='download.log'
GIT_DOWNLOADER="git clone"

GLFW_RELEASE=3.4
PLUTOVG_RELEASE=main
SDL2_RELEASE=release-2.30.5
SFML_RELEASE=2.6.1

# HTTPS
HTTPS_SOURCES="--depth 1 -b ${GLFW_RELEASE} --single-branch https://github.com/glfw/glfw.git glfw
--depth 1 -b ${PLUTOVG_RELEASE} --single-branch https://github.com/sammycage/plutovg.git plutovg
--depth 1 -b ${SDL2_RELEASE} --single-branch https://github.com/libsdl-org/SDL.git SDL2
--depth 1 -b ${SFML_RELEASE} --single-branch https://github.com/SFML/SFML.git SFML"

DEFAULT_SOURCES=${HTTPS_SOURCES}
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
