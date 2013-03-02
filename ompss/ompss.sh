#!/bin/bash

args=("$@");

SCRIPTNAME="./OMPSS"
PIDFILE=/var/run/ompss.pid
cd /etc/ompss

if [ "${args[0]}" == "start" ]
  then
	if [ -f ${PIDFILE} ]; then
	   #verify if the process is actually still running under this pid
	   OLDPID=`cat ${PIDFILE}`
	   RESULT=`ps -ef | grep ${OLDPID} | grep ${SCRIPTNAME}`  

	   if [ -n "${RESULT}" ]; then
	     echo "Script already running! Exiting"
	     exit 255
	   else
	      PID=`ps -ef | grep ${SCRIPTNAME} | grep -v sudo | grep -v color | head -n1 |  awk ' {print $2;} '`
	      echo ${PID} > ${PIDFILE}
	   fi
 	else
	  sudo ./OMPSS &
	  sleep 2;
	  PID=`ps -ef | grep ${SCRIPTNAME} | grep -v sudo | grep -v color | head -n1 |  awk ' {print $2;} '`
	  echo ${PID} > ${PIDFILE}
	fi
elif [ "${args[0]}" == "stop" ]
   then 
	if [ -f ${PIDFILE} ]; then
	   OLDPID=`cat ${PIDFILE}`
	   RESULT=`ps -ef | grep ${OLDPID} | grep ${SCRIPTNAME}`  

	   if [ -n "${RESULT}" ]; then
	     echo "Script is stopping now!"
	     `sudo kill -9 ${OLDPID}`
	   else
	      echo "Process was not found! Exiting"
	   fi
	   rm ${PIDFILE}
	else
	   echo "Process was not found! Exiting"
	fi
fi
