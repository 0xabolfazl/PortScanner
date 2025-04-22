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

// Thread function to scan a single port
DWORD WINAPI scan_port(LPVOID args) {
    ScanArgs* scan_args = (ScanArgs*)args;
    SOCKET sock;
    struct sockaddr_in server;
    DWORD timeout = TIMEOUT_MS;

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Socket error: %d\n", WSAGetLastError());
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(scan_args->ip);
    server.sin_port = htons(scan_args->port);

    // Set connection timeout
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

    // Attempt connection
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        closesocket(sock);
        return 0;
    }

    // If connection succeeds, port is open
    closesocket(sock);
    printf("[+] Port %5d - Open (%s)\n", scan_args->port, get_service_name(scan_args->port));
    return 0;
}

int main() {
    WSADATA wsa;
    char ip[16];
    int start_port, end_port;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Enter IP address: ");
    scanf("%15s", ip);

    printf("Enter start port: ");
    scanf("%d", &start_port);

    printf("Enter end port: ");
    scanf("%d", &end_port);

    printf("\n[*] Scanning %s (Ports %d-%d)...\n\n", ip, start_port, end_port);


}