#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * substring(char * s, int start, int n_chars) {
	char subbuff[n_chars+1];
	memcpy( subbuff, &s[start], n_chars );
	subbuff[n_chars] = '\0';
	return subbuff;
}


int main(int argc, char const *argv[])
{
	char * test = "Hello people!!!";
	// char * test2 = substring(test, 5, 6);
	char * test2 = test.substr(5, 6);
	printf("TEST2: %s", test2);
	return 0;
}