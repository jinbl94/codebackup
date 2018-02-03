#!/bin/bash -

##run program with proxy
export http_proxy="127.0.0.1:1080"
export https_proxy=$http_proxy
export ftp_proxy=$http_proxy
export rsync_proxy=$http_proxy
export HTTP_PROXY=$http_proxy
export HTTPS_PROXY=$http_proxy
export FTP_PROXY=$http_proxy
export RSYNC_PROXY=$http_proxy
export no_proxy="localhost,127.0.0.1,localaddress"
$@
exit

