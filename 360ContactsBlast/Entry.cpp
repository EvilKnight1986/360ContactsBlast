#include "DES2.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char g_szSrcFileName[MAX_PATH] = {0} ;
char g_szDstPath[MAX_PATH]         = {0} ;
char g_szKeyFileName[MAX_PATH] = {0} ;

int DecodeDes(char *FileBuf, int nSize, char *pKey)
{
        FILE *fpDst;
        CString szSrcPath,szDstPath,szKey1,szKey2;
        char buff[8] = {0};
        long fileSize = 0,hasDone = 0;
        char uKey[16] = {0xE0, 0x9D, 0x3D, 0xC8, 0xC9, 0x32, 0x90, 0x24, 0xFE, 0x92, 0xE3, 0x55, 0x41, 0x19, 0x5E, 0xFF
        };

        if((fpDst = fopen(szDstPath.GetBuffer(),"wb")) == NULL)
        {
                MessageBox("打不开目的文件!","错误",MB_OK | MB_ICONERROR);
                return;
        }

        fseek(fpSrc,0,SEEK_SET);
        fseek(fpSrc,0,SEEK_END);
        fileSize = ftell(fpSrc);
        rewind(fpSrc);

        //myDES->InitializeKey(szKey1.GetBuffer(),0);

        myDES->InitializeKey(szKey2.GetBuffer(),1);
        while(!feof(fpSrc))
        {
                memset(buff,0,8);
                fread(buff,sizeof(char),8,fpSrc);
                //D(key0)-E(key1)-D(key0)
                myDES->DecryptData(buff, 0);
                myDES->EncryptData(myDES->GetPlaintext(), 1);
                myDES->DecryptData(myDES->GetCiphertextInBytes(), 0);
                fwrite(myDES->GetPlaintext(),sizeof(char),8,fpDst);
                hasDone += 8;
        }
        fclose(fpSrc);
        fclose(fpDst);
}


int ParseArgv(int argc, char ** argv)
{
        return 0 ;
}

int main(int argc, char** argv)
{
        system("title 360备份联系人数据包爆破") ;

        ParseArgv(argc, argv) ;

        return 0 ;
}