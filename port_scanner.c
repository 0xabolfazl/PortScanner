#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") // Auto-link Winsock library

#define MAX_PORTS 1000
#define TIMEOUT_MS 2000 // 2 seconds timeout
#define MAX_THREADS 50

typedef struct {
    char ip[16];
    int port;
} ScanArgs;

// Get well-known service name by port number
const char* get_service_name(int port) {
    switch (port) {
        case 21: return "FTP";
        case 22: return "SSH";
        case 23: return "Telnet";
        case 25: return "SMTP";
        case 53: return "DNS";
        case 80: return "HTTP";
        case 110: return "POP3";
        case 143: return "IMAP";
        case 443: return "HTTPS";
        case 3306: return "MySQL";
        case 3389: return "RDP";
        default: return "Unknown";
    }
}