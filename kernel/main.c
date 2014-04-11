#include "common.h"
#include "monitor.h"

void main(){

	m_clear();
	char ch = 'a';
	while(1){

		m_putc( ch, SUC );
		ch = ch >= 'z' ? 'a' : ch + 1;

	}

}
