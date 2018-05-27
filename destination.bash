#!/bin/bash
echo -n "Enter name of destination node: "
read dest
case $dest in
  baran | Baran ) mtr 10.10.5.2 --report --no-dns;;
  cerf | Cerf ) mtr 10.10.1.1 --report --no-dns;;
  hopper | Hopper ) mtr 10.10.3.1 --report --no-dns;;
  lovelace | Lovelace ) mtr 10.10.4.1 --report --no-dns;;
  knuth | Knuth ) mtr 10.10.8.2 --report --no-dns;;
  * ) echo "Invalid input."
esac
