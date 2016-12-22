#include "shell.h"
/**
 * hsh_cd - builtin command hsh_cd, mimics cd
 * @arg_list: argumenet list given by user, generally gives which directory
 * to change to
 * @envp: environemental variable linked list to get current working direcoty
 * and also to update the variables PWD and OLDPWD
 * @buf_size: size to create our buffer for path
 * Return: 0 on success and 1 on failure
 */
int hsh_cd(char **arg_list, env_t *envp, int buf_size)
{
	char *path, *buff, *pwd;
	int n, m, l;

	path = safe_malloc(sizeof(char) * buf_size), _memset(path, '\0', buf_size);
	buff = safe_malloc(sizeof(char) * buf_size), _memset(buff, '\0', buf_size);
	pwd = safe_malloc(sizeof(char) * buf_size), _memset(pwd, '\0', buf_size);
	getcwd(pwd, buf_size);
	if (arg_list[1] != NULL)
		n = _strcmp(arg_list[1], "~"), m = _strcmp(arg_list[1], "-");
	if (arg_list[1] == NULL || n == 0)
		path = rm_vname(envp, "HOME=", buf_size), l = chdir(path);
	else if (arg_list[1] != NULL && m == 0)
	{
		path = rm_vname(envp, "OLDPWD=", buf_size), l = chdir(path);
		_write(path), _write("\n");
	}
	else if (arg_list[1][0] == '/')
		l = chdir(arg_list[1]);
	else
	{
		getcwd(buff, buf_size);
		_strcat(buff, "/");
		_strcat(buff, arg_list[1]);
		l = chdir(buff);

	}
	if (l < 0)
	{
		write(0, "Error: no such file or directory\n", 33);
		return (2);
	}
	else
	{
		getcwd(buff, buf_size);
		update_env(envp, "OLDPWD=", pwd, buf_size);
		update_env(envp, "PWD=", buff, buf_size);
	}
	return (0);
}

/**
 * hsh_cd_help - builtin help printout for cd
 * Return: Always 0
 */
int hsh_cd_help(void)
{
	/* Maybe write more here, actualy help printout is a book */
	_write("cd usage: cd DIR\n    Change the current directory to DIR.\n");
	return (0);
}
