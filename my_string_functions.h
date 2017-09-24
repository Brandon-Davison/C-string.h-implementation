#ifndef MY_STRING_FUNCTIONS_H
#define MY_STRING_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#define MY_EOF -1

/* 
 * at most, 1 less than n from stream into s. If successful, 
 * append NULL char, return s. Otherwise, return NULL
 */
char* my_fgets(char *s, int n, FILE *stream);

/*
 * Writes s to the output specified by stream. If the function is successful,
 * then it returns the number of characters written to the output;
 * otherwise it returns MY_EOF (i.e. for cases where stream does
 * not point any where yet). Make sure you #define MY_EOF as -1
 */
int my_fputs(const char *s, FILE *stream);

/*
 * Reads the next character from the input pointed to by stream.
 * If the input is at the end of file or a processing error 
 * occurs return MY_EOF; otherwise return the integer 
 * representation of the character read.
 */
int my_fgetc(FILE *stream);

/*
 * Writes the character c (converted to a character) to the 
 * output specified by stream. If the write is successful the 
 * ascii value of the character is returned; otherwise MY_EOF 
 * is returned.
 */
int my_fputc(int c, FILE *stream);

/*
 * Reads characters from stdin into the array pointed to by s 
 * until a newline is encountered. The newline character is NOT 
 * kept at the end of the array pointed to by s. A null character
 * is written to the end of string s. The function returns s.
 */
char *my_gets(char *s);

/*
 * Writes the string pointed to by s to stdout. The function 
 * appends a newline to the output. The function returns the 
 * number of characters written to the output.
 */
int my_puts(const char *s);

/*
 * Returns the ascii value of the next character read from stdin.
 */
int my_getchar(void);

/*
 * writes character c to stdout. The character c is returned.
 */
int my_putchar(int c);

/*
 * Copies all characters in the array pointed to by source 
 * into the array pointed to by destination. The null character 
 * is also copied. The function returns destination.
 */
char *my_strcpy(char *destination, const char *source);

/*
 * Copies no more than n characters from the string pointed to
 * by source into the array pointed to by destination. The 
 * function does not copy any characters past a null character. 
 * If the string pointed to by source is less than n characters, 
 * null characters are appended to the end of the array pointed
 * to by destination until n characters have been written.
 */
char *my_strncpy(char *destination, const char *source, int n);

/*
 * This function appends a copy of the string pointed to by 
 * source (including the null character) to the end of the 
 * string pointed to by destination. The append overwrites 
 * the null character at the end of destination. The string
 * pointed to by destination is returned.
 */
char *my_strcat(char *destination, const char *source);

/*
 * This function appends no more than n characters from the string 
 * pointed to by source to the end of the array pointed to by 
 * destination. The null character is appended to the end of the result.
 * The destination pointer is returned.
*/
char *my_strncat(char *destination, const char *source, int n);

/*
 * This function compares the string pointed to by s1 to the 
 * string pointed to by s2. If the string pointed to by s1 comes
 * before the string pointed to by s2 in dictionary ordering,
 * then -1 is returned. If the string pointed to by s1 is the 
 * same as the string pointed to by s2, then 0 is returned 
 * (the compare function is case sensitive). Otherwise 1 is
 *  returned.
 * s1 < s1: -1
 * s1 == w2: 0
 * s1 > s2:  1
 */
int my_strcmp(const char *s1, const char *s2);

/*
 * This function compares no more than n characters (characters 
 * following a null character are not compared) from the string 
 * pointed to by s1 to the string pointed to by s2. If the string
 * pointed to by s1 comes before the string pointed to by s2 in 
 * dictionary ordering, then -1 is returned. If the string pointed 
 * to by s1 is the same as the string pointed to by s2, then 0 is 
 * returned (the compare function is case sensitive). Otherwise 1 
 * is returned.
 * s1 < s1: -1
 * s1 == w2: 0
 * s1 > s2:  1
 */
int my_strncmp(const char *s1, const char *s2, int n);

/*
 * This function returns the length of the string pointed to
 * by s. The computation of length does NOT include the null character.
 */
int my_strlen(const char *s);

#endif
