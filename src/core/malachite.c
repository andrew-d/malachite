#include <stdio.h>

static char* code = "foo = 123\nbar=444\n";
extern void parse(char*);

int main(void) {
	parse(code);
	return 0;
}
