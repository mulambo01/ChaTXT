#!/bin/bash

groupadd chatxt

useradd chatxt -g chatxt

touch pass.txt
touch chat.txt

gcc client.c -o chatxt -lcurses

chown chatxt:chatxt pass.txt
chown chatxt:chatxt chat.txt
chown chatxt:chatxt chatxt
chown chatxt:chatxt genpass.sh
chown chatxt:chatxt ../chatxt
chown chatxt:chatxt compile.sh
chown chatxt:chatxt client.c
chown chatxt:chatxt README.en.md
chown chatxt:chatxt README.md

chmod 700 compile.sh
chmod 600 client.c
chmod 710 chatxt
chmod u+s chatxt
chmod 600 pass.txt
chmod 600 chat.txt
chmod 750 genpass.sh
chmod 750 ../chatxt

echo "So that the user can execute the chatxt, he will need to be at the chatxt group, to do that, just execute:"
echo "# gpasswd -a USUARIO chatxt"
