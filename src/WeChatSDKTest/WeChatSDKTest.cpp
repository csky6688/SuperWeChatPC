// WeChatSDKTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <windows.h>

#include "../WeChatSDK/sdk.h"
#pragma comment(lib, "../WeChatSDKCore/Release/WeChatSDK.lib")

int UniTest()
{
    DWORD pid = WXOpenWechat();
    if (pid <= 0) {
        std::cout << "open wechat error!" << std::endl;
        return -1;
    }

    while (!WXIsWechatAlive(pid)) {
        std::cout << ".";
        Sleep(1);
    }

    if (WXInitialize(pid) != ERROR_SUCCESS) {
        std::cout << "WXInitialize error!" << std::endl;
        return -1;
    }

    while (!WXIsWechatSDKOk(pid)) {
        std::cout << ".";
        Sleep(1);
    }

    std::cout << "superweixin initialize success!" << std::endl;

    WXAntiRevokeMsg(pid);

    std::cout << "start anti revoke msg, enter to unanti." << std::endl;

    getchar();

    WXUnAntiRevokeMsg(pid);

    WXSaveVoiceMsg(pid, L"c:\\wxmsg");

    std::cout << "start save voice msg, enter to stop." << std::endl;

    getchar();

    WXUnSaveVoiceMsg(pid);

    while (1) {

        getchar();

        WXSendTextMsg(pid, L"wxid_qoxxxxx", L"This wechatsdk msg");
    }
    return 0;
}

int main()
{
    printf("------------------------------------------------------------\n");
    printf("--------------- SuperWeChatPC电脑端超级微信-----------------\n");
    printf("--------------- 多开、防撤消、语音备份 ---------------------\n");
    printf("--------------- CopyRight (C) 2019 by Anhkgg ---------------\n");
    printf("----------- https://anhkgg.com 公众号：汉客儿 --------------\n");
    printf("------------------------------------------------------------\n\n");

    std::cout << "加载中..." << std::endl;

    DWORD pid = WXOpenWechat();
    if (pid <= 0) {
        std::cout << "打开微信失败，请检查是否已经安装微信!" << std::endl;
        getchar();
        return -1;
    }

    int max = 0;
    while (!WXIsWechatAlive(pid)) {
        std::cout << ".";
        Sleep(1);
        if (max++ > 60*60) {
            std::cout << "打开微信失败，超时未启动！" << std::endl;
            getchar();
            return -1;
        }
    }

    if (WXInitialize(pid) != ERROR_SUCCESS) {
        std::cout << "SuperWeChatPC初始化失败，请检查模块是否完整。<WeChatSDK.dll，WeChatSDKCore.dll，WeChatRc.dll，WeChatRs.dll>" << std::endl;
        getchar();
        return -1;
    }

    max = 0;
    while (!WXIsWechatSDKOk(pid)) {
        std::cout << ".";
        Sleep(1);
        if (max++ > 120 * 60) {
            getchar();
            std::cout << "SuperWeChatPC启动失败，请检查是否被杀毒软件屏蔽功能，请允许操作！" << std::endl;
            getchar();
            return -1;
        }
    }

    std::cout << std::endl;

    std::cout << "SuperWeChatPC初始化成功..." << std::endl;
    std::cout << "正在开启超级功能..." << std::endl;
    
    if (!WXAntiRevokeMsg(pid)) {
        std::cout << "防撤销功能已开启..." << std::endl;
    }
    //WXSaveVoiceMsg(pid, L"c:\\wxmsg");
    std::cout << "SuperWeChatPC启动成功..." << std::endl;

    max = 0;
    while (1) {
        if (max++ > 60*5) {
            break;
        }
        Sleep(1);
    }

    return 0;
}