/**
 * _strstr_int - finds the first occurence of the substring needle
 * in the string haystack
 * @haystack: string to search
 * @needle: string to find
 * Return: index to the beginning of the located substring
 */


int _strstr_int(char *haystack, char *needle)
{
	int i;

	i = 0;
     while (*haystack != '\0')
     {
          char *beginning = haystack;
          char *pattern = needle;

          while (*pattern == *haystack && *pattern != '\0'
                 && *haystack != '\0')
          {
               haystack++;
               pattern++;
          }
          if (*pattern == '\0')
               return (i);
          haystack = beginning + 1;
		i++;
     }
     return (-1);
}
