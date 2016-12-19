/**
 * variable_expansion - Expand variables in the buffer
 * @b: buffer structure
 * @envp: Enviorn structure
 */
void variable_expansion(buffer *b, env_t *envp, int retrn_value)
{
	char *hold;
	int index;
	// if $$ in b->buf, replace with PID
	// if $? in b->buf, replace with retrn_value
	// if $ in b->buf, search word after $ in env
	while ((index = _strstr_int(b->buf + b->bp, "$")) > 0)
	{
		if (b->buf[b->bp + index + 1] == '?')
		{
			hold = _itoa(retrn_value);
			buffer_word_erase(b, b->bp + index);
			buffer_insert(b, hold, b->bp + index);
			_free(hold);
		}
		else if (b->buf[b->bp + index + 1] == '$')
		{
			// replace with PID
		}
		else
		{
			hold = rm_vname(envp, b->buf[b->bp + index + 1], b->size);
			buffer_word_erase(b, b->bp + index);
			if (hold != NULL)
				buffer_insert(b, hold, b->bp + index)
		}
	}
}
