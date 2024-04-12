# TCP/IP Chat Application

This project implements a TCP/IP communication protocol using IPv4 to create a chat application in C language. The application allows users to communicate with each other over a network using TCP sockets.

## Features

- **Client-Server Architecture**: Utilizes a client-server model for communication.
- **TCP/IP Protocol**: Implements the TCP/IP protocol stack for reliable data transmission.
- **IPv4 Addressing**: Supports IPv4 addressing for network communication.
- **Chat Interface**: Provides a simple chat interface for users to send and receive messages.
- **Multi-User Support**: Allows multiple users to connect to the server and engage in simultaneous conversations.

## Getting Started

### Prerequisites

- C compiler (e.g., gcc)
- Basic understanding of TCP/IP networking

### Usage

1. Clone the repository:

```bash
git clone https://github.com/your_username/tcp-ip-chat.git
```
2. Navigate to the project directory:
```bash
cd tcp-ip-chat
```
3. Compile the server and client:
```bash
gcc server.c -o server
gcc client.c -o client
```
4. Start the server:
```bash
./server
```
5. Connect clients to the server:
```bash
./client
```
6. Start chatting!

## Contributing
Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

1. Fork the repository
2. Create your feature branch (git checkout -b feature/YourFeature)
3. Commit your changes (git commit -am 'Add some feature')
4. Push to the branch (git push origin feature/YourFeature)
5. Create a new Pull Request

## Acknowledgments
Special thanks to the contributors and developers of the C language and related libraries for providing the tools necessary to build this application.
