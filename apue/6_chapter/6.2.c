#include <stdio.h>
#include <pwd.h>
#include <string.h>

struct passwd* getpwnam_user(const char *name)
{
	struct passwd *ptr;

	setpwent();
	while((ptr = getpwent()) != NULL) {
		if(strcmp(name, ptr->pw_name) == 0)
			break;
	}
	endpwent();
	return ptr;
}

int main()
{
	struct passwd *pd = getpwnam_user("no");
	if(pd) {
		printf("user name: %s\n", pd->pw_name);
		printf("pw_passwd: %s\n", pd->pw_passwd);
		printf("user ID:   %d\n", pd->pw_uid);
		printf("user GID:  %d\n", pd->pw_gid);
		printf("pw_gecos:  %s\n", pd->pw_gecos);
		printf("dir        %s\n", pd->pw_dir);
		printf("pw_shell:  %s\n", pd->pw_shell);
	}

	return 0;
}