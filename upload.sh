#!/bin/bash
cd "$(dirname "$0")"

sftp -b upload.sftp root@192.168.203.101
ssh root@192.168.203.101 "cd /kovan/src/Botball2014/; ./linkcommands.sh"
