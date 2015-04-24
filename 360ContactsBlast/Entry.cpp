#include "C360ContactsBlast.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char g_szSrcFileName[MAX_PATH] = {0} ;
char g_szDstPath[MAX_PATH]         = {0} ;
char g_szKeyFileName[MAX_PATH] = {0} ;

int ParseArgv(int argc, char ** argv)
{
        return 0 ;
}

int main(int argc, char** argv)
{
        system("title 360备份联系人数据包爆破") ;
        string str = "D:\\Projects\\test\\passwd.txt" ;
        char szBuffer[260] = {0} ;

        C360ContactsBlast ContactsBlast ;

        // 输入字典路径
        do 
        {
                printf("请输入字典文件路径: ") ;
                scanf("%s", szBuffer) ;
                str = szBuffer ;
        } while (! ContactsBlast.SetDictionaryPath(str));
        
        // 设置解密成功文件存储路径
        // 其实只是存一个成功的密码
        //do 
        //{
        //        printf("请输入解密成功密码存放目录: ") ;
        //        scanf("%s", szBuffer) ;
        //        str = szBuffer ;
        //} while (! ContactsBlast.SetDstPath(str));


        // 设置解密成功文件存储路径
        // 其实只是存一个成功的密码
        do 
        {
                printf("设置360 contacts数据包文件的路径: ") ;
                scanf("%s", szBuffer) ;
                str = szBuffer ;
        } while (! ContactsBlast.SetSrcFileName(str));

        ContactsBlast.Blast() ;

        system("pause") ;
        return 0 ;
}