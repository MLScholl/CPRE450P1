#!/bin/bash
echo "Compile and run"
gcc -o client client.c date_clnt.c
gcc -o server server.c date_svc.c
./server &
./client localhost
