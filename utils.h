#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char * newString(int len) {
	char * x = (char*)malloc(len);
	return x;
}

char * intToString(int x) {
	char * result = newString(10);
	sprintf(result,"%d",x);
	return result;
}


void toUpper(char * str) {
	char * p = str;
	while (*p) {
		*p = toupper(*p);
		p++;
	}
}

char * readString(char * msg) {
	char * x = newString(128);
	printf(msg);
	scanf(" %s",x);
	return x;
}

int readInt(char * msg) {
	int x;
	printf(msg);
	scanf("%d",&x);
	return x;
}

