#!/bin/bash

# Wenn man eine DynDNS Adresse für seinen Home-Server besitzt und immer über die aktuelle IP per E-Mail benachrichtigt werden will, 
# kann man dieses Script als Cronjob eintragen

dir=/home/usr/scripts/dyndns/
if [ $# -lt 1 ]; then
        echo -e "[!] Es wurde keine Domain angegeben!\n[*] Anwendung: $0 <domain>"
else
        checkip=$(/usr/bin/host $1 | /bin/grep 'has address' | /usr/bin/cut -d" " -f 4)
        if [ ! -f $dir$1.ip ]; then
                echo $checkip > $dir$1.ip
        elif [ -f $dir$1.ip ]; then
                line=$(/usr/bin/head -1 $dir$1.ip)
                if [ ! "$line" == "$checkip" ]; then
                        echo -e 'Subject: New IP for '$1'\nDomain '$1' has a new IP: '$checkip'\n.' | /usr/sbin/sendmail -t "<E-Mail>"
                        echo $checkip > $dir$1.ip
                fi  
        fi  
fi

