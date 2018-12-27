
#include <string>
#include "JKClient.hpp"
#include <jni.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include "JKMessageManager.h"
#include "JKTypes.h"

#define MAXDATASIZE 4096

extern JNIEnv *myenv;
#define MAX_PACKAGE_LEN 1024

JKClient::JKClient(std::string ipName): mIpName(ipName),mIpPort("6900"),mStatus(UNCONNECTED),mSockfd(-1) {

}

JKClient::JKClient(char* ipName): mIpName(ipName), mIpPort("6900"),mStatus(UNCONNECTED),mSockfd(-1){

}

JKClient::JKClient(char* ipName,char* port): mIpName(ipName),mIpPort(port),mStatus(UNCONNECTED),mSockfd(-1) {

}

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int JKClient::listen() {
    //listen in new thread
    start();
    return 0;
}




void JKClient::run() {
    int numbytes;
    fd_set master;
    fd_set read_fds;

    if(mSockfd == -1){
        return;
    }
    int maxfd = mSockfd;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(mSockfd,&master); // s is a socket descriptor
    LOGD("mSockfd = %d ,start listen!!!",mSockfd);
    mStatus = LISTENING;
    for(;;){
        if(mStatus == EXITING){
            break;
        }
        read_fds = master;
        if (select(maxfd+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            break;
        }
        if(mStatus == EXITING || mSockfd == -1){
            break;
        }
        for(int i = 0; i <= maxfd; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got information
                if (i == mSockfd) {
                    unsigned char* buf = (unsigned char*)malloc(MAX_PACKAGE_LEN);
                    memset(buf,0x00,MAX_PACKAGE_LEN);
                    if ((numbytes = recv(mSockfd, buf, MAX_PACKAGE_LEN-1, 0)) == -1) {
                        perror("recv");
                        break;
                    }
                    if(numbytes == 0){
                        break;
                    }
                    PackageInfo* pinfo = new PackageInfo();
                    pinfo->len = numbytes;
                    pinfo->pContent = buf;
                    LOGD("recv packages: length = %d",numbytes);
                    JKMessageManager::GetInstance()->addMessage(JKMessageManager::MSG_RECEIVE_NETWORK_PACK,pinfo);
                }
            }
        }
    }
    close(mSockfd);
    mStatus = UNCONNECTED;
    LOGD("maybe error!");
    return;
}

int JKClient::SendBytes(void *buf,int len) {
    return send(mSockfd,buf,len,0);
}


int JKClient::connect() {
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
//    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(mIpName.c_str(), mIpPort.c_str(), &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        LOGD("getaddrinfo: %s\n", gai_strerror(rv));
        return JK_ERROR;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((mSockfd = socket(p->ai_family, p->ai_socktype,
                              p->ai_protocol)) == -1) {
            perror("client: socket");
            LOGD("%s","client: socket 1");
            continue;
        }

        if (::connect(mSockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            LOGD("%s","client: socket 2");
            close(mSockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        LOGD("%s","client: failed to connect");
        return JK_ERROR;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);
    freeaddrinfo(servinfo); // all done with this structure
    mStatus = CONNECTED;
    return JK_OK;
}

int JKClient::disconnect() {
    mStatus = EXITING;
    close(mSockfd);
    mSockfd= -1;
    return 0;
}

int JKClient::getStatus() {
    return mStatus;
}


