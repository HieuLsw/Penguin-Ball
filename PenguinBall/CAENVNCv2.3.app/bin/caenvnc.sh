#!/bin/sh
dir1="$(dirname "$0")"

PATH=${dir1}:"${dir1}/../VNC Viewer.app/Contents/MacOS/":$PATH

usage()
{
  printf "Usage : \n $0  [ -g WIDTHxHEIGHT ]  [ -c VNCHOST] \n"
  printf "Example :\n"
  printf "$0  -g 1024x768 -c vnc.engin.umich.edu \n\n\n"
  printf "Geometry values examples: \n"
  printf "\t800x600\n\t1024x768\n\t1400x1050\n\t1600x1200\n\t1280x1024\n\t1280x800\n\t1440x900\n\t1680x1050\n\t1920x1200\n\t2560x1600\n"
  printf "\n\n"
  printf "valid VNCHOSTs include:\n\tcaen-vnc02.engin.umich.edu\n\tcaen-vnc03.engin.umich.edu\n\tcaen-vnc04.engin.umich.edu\n"
  printf "\n\n You can also use the environmental variables CVNCSIZE and CVNCHOST to set defaults for the screen size\n"
  printf "and VNC host you wish to use\n\n"
  printf "Example :\n\tsetenv CVNCSIZE 1024x768\n\tsetenv CVNCHOST caen-vnc03.engin.umich.edu\n\t$0\n\n"
  printf "\n\n"
  printf " Note : Command-line arguments override environmental variable settings\n\n\n"

}

 
while getopts g:c:h o
do	case "$o" in
        c)      myhost="$OPTARG";;
	g)	bgeom="$OPTARG";mgeom="1";;
        h)      usage;exit 0;;
	[?])    usage;
		exit 1;;
	esac
done
#shift $OPTIND-1

#cgeom=`xdpyinfo | grep dime | awk '{print $2}'`
cgeom=1024x768

dimen=${CVNCSIZE:-${cgeom}}
mydimen=${bgeom:-${dimen}}

cvncuser=${CVNCUSER:-${USER}}

NC1=`nc -h 2>&1 |grep 'listen for inbound:	nc -l -p'`


if [ "X${NC1}" = "X" ] ; then 
NCOPTS="-l"
else
NCOPTS="-l -p"
fi


case $mydimen in
      800x600)   rport=50;;
     1024x768)  rport=51;;
     1400x1050) rport=56;;
     1600x1200) rport=53;;
# resolutions 5:4
     1280x1024) rport=52;;
# resolutions 16:10
     1280x800)  rport=57;;
     1440x900)  rport=58;;
     1680x1050) rport=54;;
     1920x1200) rport=55;;
     2560x1600) rport=59;; 
     *) rport=51;;
esac

export CVNCHOST=${CVNCHOST:-"vnc.engin.umich.edu"}
#echo $CVNCHOST
mvnchost=${myhost:-${CVNCHOST}}



FIFO=/tmp/.fifo.$$
mkfifo ${FIFO}


trap 'echo Received SIGPIPE >&2' SIGPIPE


if  [ "X$COTVNCDIR" = "X" ] ;then
	ssh -g -f -L 5984:localhost:5984 ${cvncuser}@${mvnchost} "sleep 30"
else
	 ssh -g -f -L 5984:localhost:5984 ${cvncuser}@${mvnchost} "echo hello ;sleep 30"
fi

(printf "CAENVNC\n${mydimen}\nCAENVNC\n" ;  nc ${NCOPTS}    5985  )  < ${FIFO} | nc 127.0.0.1 5984  >${FIFO} 


#  "${dir1}/../VNC Viewer.app/Contents/MacOS/vncviewer"  localhost:85



