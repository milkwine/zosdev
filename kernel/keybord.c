#include "common.h"
#include "keybord.h"
#include "isr.h"
#include "monitor.h"
static u32 keymap[NR_SCAN_CODES * MAP_COLS] = {

/* scan-code			!Shift		Shift		E0 XX	*/
/* ==================================================================== */
/* 0x00 - none		*/	0,		0,		0,
/* 0x01 - ESC		*/	0,		0,		0,
/* 0x02 - '1'		*/	'1',		'!',		0,
/* 0x03 - '2'		*/	'2',		'@',		0,
/* 0x04 - '3'		*/	'3',		'#',		0,
/* 0x05 - '4'		*/	'4',		'$',		0,
/* 0x06 - '5'		*/	'5',		'%',		0,
/* 0x07 - '6'		*/	'6',		'^',		0,
/* 0x08 - '7'		*/	'7',		'&',		0,
/* 0x09 - '8'		*/	'8',		'*',		0,
/* 0x0A - '9'		*/	'9',		'(',		0,
/* 0x0B - '0'		*/	'0',		')',		0,
/* 0x0C - '-'		*/	'-',		'_',		0,
/* 0x0D - '='		*/	'=',		'+',		0,
/* 0x0E - BS		*/	0x08,	   0x08,	    0x08,
/* 0x0F - TAB		*/	0,		0,		0,
/* 0x10 - 'q'		*/	'q',		'Q',		0,
/* 0x11 - 'w'		*/	'w',		'W',		0,
/* 0x12 - 'e'		*/	'e',		'E',		0,
/* 0x13 - 'r'		*/	'r',		'R',		0,
/* 0x14 - 't'		*/	't',		'T',		0,
/* 0x15 - 'y'		*/	'y',		'Y',		0,
/* 0x16 - 'u'		*/	'u',		'U',		0,
/* 0x17 - 'i'		*/	'i',		'I',		0,
/* 0x18 - 'o'		*/	'o',		'O',		0,
/* 0x19 - 'p'		*/	'p',		'P',		0,
/* 0x1A - '['		*/	'[',		'{',		0,
/* 0x1B - ']'		*/	']',		'}',		0,
/* 0x1C - CR/LF		*/	'\n',		'\n',		'\n',
/* 0x1D - l. Ctrl	*/	CTRL,		CTRL,		CTRL,
/* 0x1E - 'a'		*/	'a',		'A',		0,
/* 0x1F - 's'		*/	's',		'S',		0,
/* 0x20 - 'd'		*/	'd',		'D',		0,
/* 0x21 - 'f'		*/	'f',		'F',		0,
/* 0x22 - 'g'		*/	'g',		'G',		0,
/* 0x23 - 'h'		*/	'h',		'H',		0,
/* 0x24 - 'j'		*/	'j',		'J',		0,
/* 0x25 - 'k'		*/	'k',		'K',		0,
/* 0x26 - 'l'		*/	'l',		'L',		0,
/* 0x27 - ';'		*/	';',		':',		0,
/* 0x28 - '\''		*/	'\'',		'"',		0,
/* 0x29 - '`'		*/	'`',		'~',		0,
/* 0x2A - l. SHIFT	*/	SHIFT,	SHIFT,	0,
/* 0x2B - '\'		*/	'\\',		'|',		0,
/* 0x2C - 'z'		*/	'z',		'Z',		0,
/* 0x2D - 'x'		*/	'x',		'X',		0,
/* 0x2E - 'c'		*/	'c',		'C',		0,
/* 0x2F - 'v'		*/	'v',		'V',		0,
/* 0x30 - 'b'		*/	'b',		'B',		0,
/* 0x31 - 'n'		*/	'n',		'N',		0,
/* 0x32 - 'm'		*/	'm',		'M',		0,
/* 0x33 - ','		*/	',',		'<',		0,
/* 0x34 - '.'		*/	'.',		'>',		0,
/* 0x35 - '/'		*/	'/',		'?',		0,
/* 0x36 - r. SHIFT	*/	SHIFT,	    SHIFT,	    SHIFT,
/* 0x37 - '*'		*/	'*',		'*',    	0,
/* 0x38 - ALT		*/	ALT,		ALT,  	ALT,
/* 0x39 - ' '		*/	' ',		' ',		0,
/* 0x3A - CapsLock	*/	0,	    0,	    0,
/* 0x3B - F1		*/	0,		0,		0,
/* 0x3C - F2		*/	0,		0,		0,
/* 0x3D - F3		*/	0,		0,		0,
/* 0x3E - F4		*/	0,		0,		0,
/* 0x3F - F5		*/	0,		0,		0,
/* 0x40 - F6		*/	0,		0,		0,
/* 0x41 - F7		*/	0,		0,		0,
/* 0x42 - F8		*/	0,		0,		0,
/* 0x43 - F9		*/	0,		0,		0,
/* 0x44 - F10		*/	0,		0,		0,
/* 0x45 - NumLock	*/	0,	    0,	    0,
/* 0x46 - ScrLock	*/	0,	    0,	    0,
/* 0x47 - Home		*/	0,	    0,		0,
/* 0x48 - CurUp		*/	0,		0,		0,
/* 0x49 - PgUp		*/  0,      0,      0,
/* 0x4A - '-'		*/  0,      0,      0,
/* 0x4B - Left		*/  0,      0,      0,
/* 0x4C - MID		*/  0,      0,      0,
/* 0x4D - Right		*/  0,      0,      0,
/* 0x4E - '+'		*/  0,      0,      0,
/* 0x4F - End		*/  0,      0,      0,
/* 0x50 - Down		*/  0,      0,      0,
/* 0x51 - PgDown	*/  0,      0,      0,
/* 0x52 - Insert	*/  0,      0,      0,
/* 0x53 - Delete	*/  0,      0,      0,
/* 0x54 - Enter		*/	0,		0,		0,
/* 0x55 - ???		*/	0,		0,		0,
/* 0x56 - ???		*/	0,		0,		0,
/* 0x57 - F11		*/	0,      0,		0,	
/* 0x58 - F12		*/	0,      0,		0,	
/* 0x59 - ???		*/	0,		0,		0,	
/* 0x5A - ???		*/	0,		0,		0,	
/* 0x5B - ???		*/	0,		0,		0,
/* 0x5C - ???		*/	0,		0,		0,
/* 0x5D - ???		*/	0,		0,		0,
/* 0x5E - ???		*/	0,		0,		0,	
/* 0x5F - ???		*/	0,		0,		0,
/* 0x60 - ???		*/	0,		0,		0,
/* 0x61 - ???		*/	0,		0,		0,	
/* 0x62 - ???		*/	0,		0,		0,	
/* 0x63 - ???		*/	0,		0,		0,	
/* 0x64 - ???		*/	0,		0,		0,	
/* 0x65 - ???		*/	0,		0,		0,	
/* 0x66 - ???		*/	0,		0,		0,	
/* 0x67 - ???		*/	0,		0,		0,	
/* 0x68 - ???		*/	0,		0,		0,	
/* 0x69 - ???		*/	0,		0,		0,	
/* 0x6A - ???		*/	0,		0,		0,	
/* 0x6B - ???		*/	0,		0,		0,	
/* 0x6C - ???		*/	0,		0,		0,	
/* 0x6D - ???		*/	0,		0,		0,	
/* 0x6E - ???		*/	0,		0,		0,	
/* 0x6F - ???		*/	0,		0,		0,	
/* 0x70 - ???		*/	0,		0,		0,	
/* 0x71 - ???		*/	0,		0,		0,	
/* 0x72 - ???		*/	0,		0,		0,	
/* 0x73 - ???		*/	0,		0,		0,	
/* 0x74 - ???		*/	0,		0,		0,	
/* 0x75 - ???		*/	0,		0,		0,	
/* 0x76 - ???		*/	0,		0,		0,	
/* 0x77 - ???		*/	0,		0,		0,	
/* 0x78 - ???		*/	0,		0,		0,	
/* 0x78 - ???		*/	0,		0,		0,	
/* 0x7A - ???		*/	0,		0,		0,	
/* 0x7B - ???		*/	0,		0,		0,	
/* 0x7C - ???		*/	0,		0,		0,	
/* 0x7D - ???		*/	0,		0,		0,	
/* 0x7E - ???		*/	0,		0,		0,
/* 0x7F - ???		*/	0,		0,		0
};

static u8 keybuf[KB_IN_BYTES];
static u8 e0 = 0;
static u8 shift = 0;
static int p_in=0;
static int p_out=0;

static void push(char ch){
    int p = p_in+1 == KB_IN_BYTES ? 0 : p_in+1;
    if(p==p_out)return;
    keybuf[p_in] = ch; 
    p_in = p;
    //m_printf("%c",ch);
}
static char get(){
    if(p_out == p_in)return 0;
    char ch = keybuf[p_out];
    p_out = p_out+1 == KB_IN_BYTES ? 0 : p_out+1;
    return ch; 
}


static void keybord_callback(registers_t* regs){
    u8 code = in_byte(0x60);
    //m_printf("\nscnacode:%x ",code);

    if( code == 0xE0 || code == 0xE1 ){
        e0 = 1;
        return;
    }

    if(!(code & FLAG_BREAK)){ //make code
        //m_printf("break code:%d",keymap[code*3+0]);
        u8 ch;
        if(e0){
            ch = keymap[code*3+2];
        }else if(shift){
            ch = keymap[code*3+1];
        }else{
            ch = keymap[code*3+0];
        }
        switch(ch){
            case 0:
                {break;}
            case SHIFT:
                {shift=1;break;}
            case CTRL:
                {break;}
            case ALT:
                {break;}
            default:
                {push(ch);break;}
        }

    }else{                  //breka code
        code&=0x7F;
        u8 ch;
        if(e0){
            ch = keymap[code*3+2];
        }else if(shift){
            ch = keymap[code*3+1];
        }else{
            ch = keymap[code*3+0];
        }
        switch(ch){
            case 0:
                {break;}
            case SHIFT:
                {shift=0;break;}
            case CTRL:
                {break;}
            case ALT:
                {break;}
            default:
                {break;}
        }
    }
}
void keybord_read(u8* buf, int len){
    disable_int(); 

    char ch=0;
    int i=0;
    while((ch=get())!=0 && i<len){
        buf[i++] = ch;
    }
}
void ini_keybord(){
   register_interrupt_handler(IRQ1, &keybord_callback);
}
