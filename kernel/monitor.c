#include "monitor.h"
#include "common.h"

u16* video = (u16*) 0xB8000;
u8 cur_x = 0;
u8 cur_y = 0;

static void delay(){

    int i,j;
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 100; j++) {
        }
    }

}

static void move_cursor(){
    // The screen is 80 characters wide...
    u16 cursorLocation = cur_y * 80 + cur_x;
    out_byte(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    out_byte(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    out_byte(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    out_byte(0x3D5, cursorLocation);      // Send the low cursor byte.

}

static void scroll(){

	if ( cur_y >= 25 ) {

        int i;
        for (i = 0*80; i < 24*80; i++)
        {     //0~39 40~78
              //80~119 120~159
              if((i/40)%2==0)
              video[i] = video[i+80];
        }   

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {   
            if((i/40)%2==0)
              video[i] = BLANK;
        }   
        // The cursor should now be on the last line.
        cur_y = 24;
	}
}


void m_clear(){

    int i;
    for (i = 0; i < 80*25; i++) {
        video[i] = (u16) 0x20|15<<8;
    }

    cur_x = 0;
    cur_y = 0;

}

void m_putc(char ch, u16 color){
	
	if( ch == '\n' ){

		cur_x = 0;
		cur_y ++;

	}else if( ch != 0 ){

		u16* location = video + (cur_y * 80 + cur_x);
		*location = color | ch ;
		cur_x++;

	}

	if(cur_x >= 40){
		cur_y++;
		cur_x = 0;
	}

	move_cursor();
	scroll();
	//delay();

}

void m_write(char* str, u16 color){

	while( *str ){

		m_putc( *str, color );
		str++;

	}

}

void m_putint( u32 num ){
    char buf[11];
    itoia(buf, 11, num);
    m_write( buf, SUC );
}
void m_puthex( u32 num ){

	char buf[11];
	itoha( buf, 11, num );
	m_write( buf, SUC );
}

void m_printf(const char* format,...){
    u32 addr = (u32)&format;
    addr += sizeof(char*);

    while(*format){

        if(*format == '%'){
            format++;
            if(*format == 'x'){
                m_puthex(*(u32*)addr);
                addr+=sizeof(int);
                format++;
                continue;
            }else if(*format == 'd'){
                m_putint(*(u32*)addr);
                addr+=sizeof(int);
                format++;
                continue;
            }
            format--;
        }
        m_putc(*format,INFO);
        format++;
    }

}
