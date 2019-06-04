#!/bin/bash

if [[ $EUID -ne 0 ]]; then
  echo "This script must be run as root, exiting!"
  exit
fi

echo "Setting CAP_NET_RAW capability to raw socket programs so we can execute w/o root!"
for f in raw_socket_*[^.c]; do
  setcap cap_net_raw+ep $f
done
