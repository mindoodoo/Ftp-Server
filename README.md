# Ftp-Server

The goal of this project was to implement a basic **FTP server in C** compliant with [RFC959](https://www.rfc-editor.org/rfc/rfc959).

For this purpose, access to the standard library was restricted :

> All the standard C library is authorized except recv, send and all system calls that make
a socket non-blocking.

## Features

- **Multiple client support**
- Authentication commands
- Two **transfer modes**
    - Passive
    - Active

### Implemented Commands

```
USER <SP> <username> <CRLF>   : Specify user for authentication
PASS <SP> <password> <CRLF>   : Specify password for authentication

CWD  <SP> <pathname> <CRLF>   : Change working directory
CDUP <CRLF>                   : Change working directory to parent directory

QUIT <CRLF>                   : Disconnection

DELE <SP> <pathname> <CRLF>   : Delete file on the server

PWD  <CRLF>                   : Print working directory

PASV <CRLF>                   : Enable "passive" mode for data transfer

PORT <SP> <host-port> <CRLF>  : Enable "active" mode for data transfer


HELP [<SP> <string>] <CRLF>   : List available commands

NOOP <CRLF>                   : Do nothing

(the following are commands using data transfer )

RETR <SP> <pathname> <CRLF>   : Download file from server to client
STOR <SP> <pathname> <CRLF>   : Upload file from client to server
LIST [<SP> <pathname>] <CRLF> : List files in the current working directory
```

## Building

The server can be built using ```make```.
This produces a binary called ```myftp```.

## Usage

```
./myftp port path
```

You may then use any ftp client implementing the commands implemented by this server in order to connect and interact with the server.