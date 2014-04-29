#ifndef KEYBORD_H
#define KEYBORD_H 1

void ini_keybord();
void keybord_read(u8* buf, int len);

/************************************************************************/
/*                          Macros Declaration                          */
/************************************************************************/
#define	KB_IN_BYTES	10	/* size of keyboard input buffer */
#define MAP_COLS	3	/* Number of columns in keymap */
#define NR_SCAN_CODES	0x80	/* Number of scan codes (rows in keymap) */

#define FLAG_BREAK	0x0080		/* Break Code			*/

/* Shift, Ctrl, Alt */
#define SHIFT	    0x80		/* L Shift	*/
#define CTRL		0x81        /* L Ctrl	*/
#define ALT		    0x82    	/* L Alt	*/


#endif
