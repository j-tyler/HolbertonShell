#include "shell.h"
/**
 * hsh_cd - builtin command hsh_cd, mimics cd
 * @arg_list: argumenet list given by user, generally gives which directory
 * to change to
 * @envp: environemental variable linked list to get current working direcoty
 * and also to update the variables PWD and OLDPWD
 * @buf_size: size to create our buffer for path
 */
int hsh_cd(char **arg_list, env_t *envp, int buf_size)
{
	char *path;
	char buff[buf_size], pwd[buf_size];
	int n;

	path = safe_malloc(sizeof(char) * buf_size);
	memset(path, '\0', buf_size);
	memset(pwd, '\0', buf_size);
	memset(buff, '\0', buf_size);
	getcwd(pwd, buf_size);
	if (arg_list[1] == NULL || (n = strcmp(arg_list[1], "~")) == 0)
	{
		path = rm_vname(envp, "HOME=", buf_size);
		n = chdir(path);
	}
	else if (arg_list[1] != NULL && ((n = strcmp(arg_list[1], "-")) == 0))
	{
		path = rm_vname(envp, "OLDPWD=", buf_size);
		n = chdir(path);
	}
	else
	{
		getcwd(buff, buf_size);
		strcat(buff,"/");
		strcat(buff, arg_list[1]);
		n = chdir(buff);

	}
	if (n < 0)
		printf("Error: no such file or directory\n");
	else
	{
		getcwd(buff, buf_size);
		update_env(envp, "OLDPWD=", pwd);
		update_env(envp, "PWD=", buff);
	}
	return (0);
}

/**
 * hsh_cd_help - builtin help printout for cd
 */
int hsh_cd_help(void)
{
	/* Maybe write more here, actualy help printout is a book */
	write(STDOUT_FILENO,
	"cd usage: cd DIR\n    Change the current directory to DIR.\n", 58);
	return (0);
}
