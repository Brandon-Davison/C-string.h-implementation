#include "my_string_functions.h"

char* my_fgets(char *s, int n, FILE *stream)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		char c = fgetc(stream);
		if (c == '\n' || c == EOF) 
			break;
		*(s + i) = c;
	}
	*(s + i) = '\0';
	return s;
}

int my_fputs(const char *s, FILE *stream)
{	
	if (*s != NULL)
	{
		int i = 0;
		if (stream != NULL)
		{
			while (*(s + i) != '\0')
			{
				fputc(*(s + i), stream);
				++i;
			}
			return i;
		}
	}
	return MY_EOF;
}

int my_fgetc(FILE *stream)
{
	int c = getc(stream);
	return c == EOF ? MY_EOF : c;
}

int my_fputc(int c, FILE *stream)
{
	int a = fputc(c, stream);
	return a == EOF ? MY_EOF : c;
}

char *my_gets(char *s)
{	
	int i;
	for (i = 0; *(s + i) != '\n'; ++i)
	{	
		int temp = getchar();
		if (temp == '\n')
			break;
		*(s + i) = temp;
	}
	*(s + i) = '\0';
	return s;
}

int my_puts(const char *s)
{
	int i;
	for (i = 0; *(s + i) != '\0'; ++i)
	{
		my_putchar(*(s + i));
	}
	my_putchar('\n');
	return i == 0 ? 0 : i + 1;
}

int my_getchar(void)
{
	return getchar();
}

int my_putchar(int c)
{
	return putchar(c);
}

char *my_strcpy(char *destination, const char *source)
{
	*destination = *source;
	return *source ? my_strcpy(++destination, ++source) : destination;
}

// precondition: n < sizeof destination and source
char *my_strncpy(char *destination, const char *source, int n)
{
	for (int i = 0; i < n; ++i)
		*destination ? (*(destination + i) = *(source + i)) : ((*destination) = '\0');
	return destination;
}

// precondition: both strings aren't empty
char *my_strcat(char *destination, const char *source)
{
	int n = my_strlen(source), offset = my_strlen(destination);
			
	for (int i = 0; i < n; ++i)
		*(destination + i + offset) = *(source + i);
	return destination;
}

char *my_strncat(char *destination, const char *source, int n)
{
	int offset = my_strlen(destination);

	for (int i = 0; i < n; ++i)
		*(destination + i + offset) = *(source + i);
	return destination;
}

int my_strcmp(const char *s1, const char *s2)
{
	int i = 0;
	while (*(s1 + i) != '\0' && *(s2 + i) != '\0')
	{
		if (*(s1 + i) < *(s2 + i))      return -1;
		else if (*(s1 + i) > *(s2 + i)) return 1;
		++i;
	}
	return 0;
}

int my_strncmp(const char *s1, const char *s2, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (*(s1 + i) < *(s2 + i))      return -1;
		else if (*(s1 + i) > *(s2 + i)) return 1;
	}
	return 0;
}

int my_strlen(const char *s)
{
	int len = 0;
	while (*(s + len) != '\0')
	{
		++len;
	}
	return len;
}
