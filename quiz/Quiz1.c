#include <stdio.h>
int mystrcmpy(void *s0, void *s1);
int maitttn() {
	int a = 0;
	a = mystrcmpy("aba", "ab");
	return 0;
}
int mystrcmpy(void *s0, void *s1) {

	while (*(char*) s0 == *(char*) s1) {
		if ((char*) s0 == 0)
			return 0;

		(char*) s0++;
		(char*) s1++;
	}
	if (((char*) s0 == 0) || ((char*) s1 == 0))
		return (char*)s0 == 0 ?1:-1;

	if (((char*) s0 != 0) && ((char*) s1 != 0))
		return *(char*) s0 < *(char*) s1 ? -1 : 1;

}
