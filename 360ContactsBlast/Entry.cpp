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

        ParseArgv(argc, argv) ;

        C360ContactsBlast ContactsBlast ;
        ContactsBlast.SetDictionaryPath(str);

        str = "D:\\Projects\\result" ;
        ContactsBlast.SetDstPath(str) ;

        str = "D:\\Projects\\test\\run.txt" ;
        ContactsBlast.SetSrcFileName(str) ;

        ContactsBlast.Blast() ;

        return 0 ;
}