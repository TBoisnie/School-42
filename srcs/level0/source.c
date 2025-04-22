#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char **argv, const char **envp)
{
	char * args[2];
	int uid;
	int gid;

	if ( atoi(argv[1]) == 423 )
	{
		args[0] = (char *)strdup("/bin/sh");
		args[1] = 0;
		gid = getegid();
		uid = geteuid();
		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);
		execv("/bin/sh", args);
	}
	else
	{
		fwrite("No !\n", 1, 5, stderr);
	}

	return 0;
}
