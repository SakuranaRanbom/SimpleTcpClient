// cardClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <sys/stat.h>
#include <WinSock2.h>


void runClient() {
    SOCKET client = socket(PF_INET, SOCK_STREAM, 0);
    if (client == INVALID_SOCKET) {
        std::cout << "Socket Error!\n";
    }
    sockaddr_in serv_add;
    int strLen = 0;
    memset(&serv_add, 0, sizeof(serv_add));
    serv_add.sin_family = AF_INET;
    serv_add.sin_port = htons(9527);
    serv_add.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    //int ret = connect(client, (sockaddr*)&serv_add, sizeof(serv_add));

    {
        char buffer[256] = "";
        int idx = 0;

        int ret = connect(client, (sockaddr*)&serv_add, sizeof(serv_add));
        std::cout << ret;
        while (ret == 0) {
            fputs("Input message", stdout);
            fgets(buffer, BUFSIZ - 1, stdin);
            if (strcmp(buffer, "q\n") == 0) {
                break;
            }

            send(client, buffer, strlen(buffer), 0);
            memset(buffer, 0, sizeof(buffer));
            recv(client, buffer, sizeof(buffer), 0);

            std::cout << buffer;
            closesocket(client);//然后connect的ret就变成-1了。
            ret = connect(client, (sockaddr*)&serv_add, sizeof(serv_add));
            std::cout << ret;
        }



    }
    
    
}


int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    for (int i = 0; 1;) runClient();
    WSACleanup();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
