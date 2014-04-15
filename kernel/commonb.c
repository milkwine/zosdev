#include "common.h"
#include "monitor.h"

void memset( u8* dst, u8 val, u32 len){
    while( len-- ){
        *dst = val;
        dst++;
    }
}

void itoa(char* buf,int buf_len,int num){
  if(buf_len<11)return;
  int i=0,j=7;
  buf[i++]='0';
  buf[i++]='x';
  while(j>=0){
    int d=(num>>(4*j))& 0x0000000F;
    if(d<10){
      buf[i++]=d|0x30;
    }else{
      buf[i++]=(d-9)|0x40;
    }   
    j--;
  }
  buf[i]='\0';
}
