/**
 * hsh_alias_help - builtin help printout for alias
 *
 * Return: always 0
 */
int hsh_alias_help(void)
{
	_write("alias usage: alias [KEY[=VALUE]]\n    Prints out all known");
	_write(" aliases. If used with key value pair, sets or modifies alias");
	return (0);
}
