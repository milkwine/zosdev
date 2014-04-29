#include "common.h"
#include "monitor.h"

void memset( u8* dst, u8 val, u32 len){
    while( len-- ){
        *dst = val;
        dst++;
    }
}

void itoia(char* buf, int buflen, int num){

    int last = buflen-1;
    int i;
    do{
        i = num % 10;
        num /= 10;
        buf[last--] = '0' + i;
    }while(num && last>=0);

    for (i = 0; i < buflen-last-1; i++) {
        buf[i] = buf[i+last+1];
    }

    buf[buflen-last-1] = 0;

}

void itoha(char* buf,int buf_len,int num){
  if(buf_len<11)return;
  int i=0,j=7;
  buf[i++]='0';
  buf[i++]='x';
  while(j>=0){
    int d=(num>>(4*j))& 0x0000000F;
    if(d!=0)
      break;
    j--;
  }
  if(j<0)buf[i++]=0|0x30;
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
