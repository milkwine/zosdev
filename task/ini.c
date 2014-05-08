#include "api.h"
static void  ini();
static int cmd(char* buf,int len);
static int strequal(char* stra,char* strb);
static void ini(){
    clear();
    char c_info[]="info";
    char c_clear[]="clear";
    char c_ls[]="ls";
    while(1){
        char cmd_buf[50]={0};
        puts("$>");
        if(cmd(cmd_buf,50)!=-1){
            if(strequal(cmd_buf,c_info)){
                puts("os developed by MilkWine(2014).\n");
            }else if(strequal(cmd_buf,c_clear)){
                clear();
            }else if(strequal(cmd_buf,c_ls)){
                ls();
            }else{
                puts("command not found!\n");
            }
        }
    }
}
static int strequal(char* stra,char* strb){
    int i;
    for (i = 0; stra[i] && strb[i] ; i++) {
        if(stra[i]!=strb[i])return 0;
    }
    if(stra[i]!=strb[i])return 0;
    return 1;
}
static int cmd(char* buf,int len){
    int count=0;
    while(1){
        int i=0;
        char key_buf[9];
        key_buf[0] = 0;
        key_buf[1] = 0;
        key_buf[2] = 0;
        key_buf[3] = 0;
        key_buf[4] = 0;
        key_buf[5] = 0;
        key_buf[6] = 0;
        key_buf[7] = 0;
        key_buf[8] = 0;
        gets(key_buf,8);
        for (i = 0; key_buf[i]; i++) {

            if(key_buf[i] == '\n'){
                key_buf[i+1] = 0;
                i=-1;
                break;
            }else if(key_buf[i] == 0x08){   //backspace
                if(count>0){
                    backspace();
                    count--;
                }
                continue;
            }

            if( count < (len-1) )
              buf[count++] = key_buf[i];
            else{
                puts("\ncommand too long!\n");
                return -1;
            }
        }
        puts(key_buf);
        if(i==-1)break;
    }
    buf[count] = 0;
    return count;
}
