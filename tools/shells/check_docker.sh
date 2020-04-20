#!/bin/bash

which docker > tmp.log 2>&1
if [ $? != 0 ]
then
	echo Please install Docker and Docker Compose.
	exit 1
fi

if [[ "$(docker images -q yvo-solutions/dev:latest 2> /dev/null)" == "" ]]
then
    echo The Docker image does not exist. Please run start.sh.
    exit 1
fi

if [[ "$(docker ps --filter="name=devenv" -q 2> /dev/null)" == "" ]]
then
    echo The Docker container is not started. Please run start.sh.
    exit 1
fi