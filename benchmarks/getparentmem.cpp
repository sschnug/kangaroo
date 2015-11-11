#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main(void)
{
	char tBuff[50u], tUnit; double tMem;
	sprintf(tBuff, "pmap %d | tail -1 | awk \'{print $2;}\'", getppid());
	system(tBuff);
	return 0;
}
