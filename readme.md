# Simple C++ UDP Server and Client

This project contains a simple UDP server and client written in C++ for Windows using Winsock2.

## Prerequisites
- Windows OS
- MinGW-w64 or similar compiler (with `g++.exe`)
- Ensure `g++.exe` is in your system PATH

## Files
- `simple_udp_server.cpp`: UDP server
- `simple_udp_client.cpp`: UDP client

## Compile Instructions

Open a terminal in the project directory and run:

### Compile the server
```
g++.exe simple_udp_server.cpp -o simple_udp_server.exe -lws2_32
```

### Compile the client
```
g++.exe simple_udp_client.cpp -o simple_udp_client.exe -lws2_32
```

## Run Instructions

Start the server first:
```
./simple_udp_server.exe
```

Then run the client in another terminal:
```
./simple_udp_client.exe
```

## Notes
- The server listens on port 8888.
- The client sends messages to `127.0.0.1:8888`.
- Type `exit` in the client to quit.

## Troubleshooting
- If you get errors like `undefined reference to WSAStartup`, make sure to add `-lws2_32` to your compile command.
- If `g++` is not recognized, use the full path to `g++.exe` or add MinGW's `bin` directory to your PATH.