#include "shell.h"
/**
 * variable_expansion - Expand variables in the buffer
 * @b: buffer structure
 * @envp: Enviorn structure
 * Description: Expands variables from input of $VALUE.
 * 				$? = Last return value.
 *				$$ = Process ID.
 *				$VALUE = Any enviormental variable. Deletes if found none.
 */
void variable_expansion(buffer *b, env_t *envp, int retrn_value)
{
	char *hold;
	int index, offset;

	offset = index = 0;
	while ((index = _strstr_int(b->buf + b->bp + offset, "$")) >= 0)
	{
		index += offset;
		offset = index + 1;
		if (b->buf[b->bp + index + 1] == '?')
		{
			hold = _itoa(retrn_value);
			buffer_word_erase(b, b->bp + index);
			buffer_insert(b, hold, b->bp + index);
			_free(hold);
		}
		else if (b->buf[b->bp + index + 1] == '$')
		{
			buffer_word_erase(b, b->bp + index);
			// insert PID at b->bp + index
		}
		else if (!_is_whitespace(b->buf[b->bp + index + 1]))
		{
			hold = rm_vname(envp, b->buf + b->bp + index + 1, b->size);
			buffer_word_erase(b, b->bp + index);
			if (hold != NULL)
				buffer_insert(b, hold, b->bp + index);
		}
	}
}
