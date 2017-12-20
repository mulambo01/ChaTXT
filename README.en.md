#ChaTXT

# Description:
This chat has the purpose of ensuring greater control over conversations that need to be kept confidential. To access the chat, all the users need to be in the same server running any GNU/Linux system (I think it's not a big challenge to run the program in any BSD). Basically, just the root and "chatxt" user will have reading and writing permission and the binary can only be executed by the members of "chatxt" group and it will have SUID pointing to the chatxt user. In this way, those who execute the program will be doing it in the name of chatxt user then they will be able to read and write in the text files. Unlike the IRC protocoll, that generate logs in all the clients computer, the ChatTXT will generate just one log in the server, this log should be erased all the time, but you can use the crontab to automate it. Besides that, since the local network isn't used to send the messages, it's more difficult to some invaders to listen the conversation. It is obvious that the security depends of others factors like the vulnerability level of the server. I am considering the possibility of adding a strong encryption to keep the content of the messages safe, if even any invader gets the root access. To increase the security of users, I suggest the use of tor service for tunneling the data exchanged between the client and SSH service. As the public will be limited, I recommend the implementation of token authentication in the Tor HiddenService.

# Dependencies:
* libncurses-devel

# Instalation:
Initially, you should install all the dependencies listed above and the "compile.sh" file should become executable, to do it:

$ chmod +x compile.sh

After the execution by root, the script must have configured all the environment realizing the following tasks:

* make the user and group with name "chatxt"
* make the chat.txt and pass.txt files
* change the ownership and the permissions of all the files
* compile the program

After that, all the users of the chat should be added in the group "chatxt". If the script return any strange error, you should open it and do all the tasks manually. It is a small script and I am sure that you will not have any obstacle doing that.

IMPORTANT: when I test in my system (Slackware 14.2), I had a small problem because I needed to restart my actual session to be recognized like a member of the "chatxt" group.

# Post Installation:
I don't implement any procedure to add new users, change password and all that account management tasks. I chose that because this type of not necessary complexity could bring vulnerabilities and harm some area more important than the procedure automation. In this way, each user will need to run the "genpass.sh" script, choose his nickname and password and then pass the returned line to the system administrator who should append manually it in the "pass.txt" file. The generated line will contain the username and a simple hash of the chosen password. This hash is just a md5 of the md5 of the password (in the future I intend improve this procedure, for example, add a salt number).

# Use:
There are a few commands in the program, before you know them, it is necessary to understand some particularities of the program. Looking for simplicity represented by the acronym KISS (Keep It Simple, Stupid) it is not possible to write and receive messages at the same time. Therefore, when the user press down any key, the program goes into insert mode being deaf to new messages, after the user press the Enter key, the message will be sent and all the user window will be updated marking the point where the user stops to receive the output. There will be two types of insert mode, I will explain the paricularities of each one below.

1) When I was implementing the fast insert mode, I had one simple problem, because the first characters are the responsible to active the funtion that open the insert mode and, thanks to any reason that I don't know, those chars can't be deleted if the user needs to correct the text. Therefore, to cancel the shipping of the message, you will, simply, add a # at the end of the text and, then, press Enter.

2) Due to the fact that the above problem is very uncomfortable when the text is big, the second insert method allows the user to edit the message normaly. To do that, you just need to press the Enter key before you put any characters and, then, a text "MESSAGE:" will show up in the output and you can correct your text normaly since you dont break the line of the terminal.

To quit the program, you just need to type /quit and send it.

made by pixote.

Special thanks to srGaton.

The fuction of md5 was been copy of https://gist.github.com/creationix/4710780
