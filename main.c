#include <stdio.h>
#include <string.h>

#include "my_string_functions.h"
#include "minunit.h"
int tests_run = 0;

FILE *inStream = NULL;
FILE *inStreamEmpty = NULL;
FILE *outStream = NULL;

/* Move 'cursor' to beginning of file */
void reset_file_position(FILE *file)
{
	fseek(file, 0, 0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                 Preconditons for test functions:                        *
 * 1. Each file 'cursor' is at beginning (when a function alters the file  *
 * cursor, it needs to reset the file position)                            *
 * 2. Each stream is open and in it's default state (inStream files: "r"   *
 * and outStream files: "w"). If a funtion changes the state, it resets    *
 * it when done.                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static char* test_fgets() 
{
	char s[25] = "", s2[5] = "", s3[5] = "";
	
	/* Base case: test non-empty file (file text < n) */
	my_fgets(s, 24, inStream); 
	mu_assert("fgets error, s != 'file text'", strcmp(s, "file text") == 0);

	/* Edge case 1: test against overflow (file text > n) */
	reset_file_position(inStream);
	my_fgets(s2, 4, inStream);
	// check first five characters of inStream (size of s2)
	mu_assert("fgets error, overflow", strcmp(s2, "file") == 0); 
	reset_file_position(inStream);

	/* Edge case 2: test empty file */
	my_fgets(s3, 24, inStreamEmpty);
	mu_assert("fgets error, reading empty file", strcmp(s3, "") == 0);
		
	return 0;
}

static char* test_fputs()
{
	char s[18] = "This is some text", s2[5] = "";

	/* Base case: non-empty string. Write text to file then read it back 
	and check if it's the same. */
	my_fputs(s, outStream);
	outStream = fopen("output.txt", "r");
	fgets(s, 18, outStream);
	mu_assert("fputs error, ", strcmp(s, "This is some text") == 0);

	/* Edge case: empty string. Check if MY_EOF is returned. */
	reset_file_position(outStream);	
	outStream = fopen("output.txt", "w");
	mu_assert("fputs error2, ", my_fputs(s2, outStream) == MY_EOF);

	return 0;
}

static char* test_fgetc()
{
	/* Case 1: not at end of file. */
	int char1 = my_fgetc(inStream);
	mu_assert("fgetc error, case 1", char1 == 'f');
	reset_file_position(inStream);

	/* case 2: end of file */
	int char2 = my_fgetc(inStreamEmpty);
	mu_assert("fgetc error, case 2", char2 == MY_EOF);

	return 0;
}

static char* test_fputc()
{
	/* Case 1: non-empty file */
	mu_assert("fptc error, case 1", my_fputc('z', outStream) == (int) 'z');

	return 0;
}

static char* test_gets()
{
	/* Case 1: non empty string */
	char str[9];
	printf("Enter string 'rand str'\n");
	my_gets(str);
	mu_assert("gets error, case 1", strcmp(str, "rand str") == 0);

	/* case 2: empty string */
	char str2[3];
	printf("Enter an empty string (press enter)\n");
	my_gets(str2);
	mu_assert("gets error, case 2", strcmp(str2, "") == 0);

	return 0;
}

static char* test_getchar()
{
	/* case 1: */
	printf("enter the char 'g'\n");
	mu_assert("getchar error, case 1", my_getchar() == 'g');

	return 0;
}

/* strcpy doesn't check for overflow (strncpy does) */
static char* test_strcpy()
{
	/* case 1: (dest > src)  */
	char src[12] = "hello world", dest[20];
	my_strcpy(dest, src);
	mu_assert("strcpy error, case 1", strcmp(src, dest) == 0);

	/* case 2: empty string */
	char src2[6] = "", dest2[20] = "hello";
	my_strcpy(dest2, src2);
	mu_assert("strcpy error, edge case 2", strcmp(dest2, "") == 0);

	return 0;
}

/* Check first two cases from strcpy, then check for overflow */
static char* test_strncpy()
{
	/* case 1: (dest > src)  */
	char src[12] = "hello world", dest[20];
	my_strcpy(dest, src);
	mu_assert("strcpy error, case 1", strcmp(src, dest) == 0);

	/* case 2: empty string */
	char src2[6] = "", dest2[20] = "hello";
	my_strcpy(dest2, src2);
	mu_assert("strcpy error, edge case 2", strcmp(dest2, "") == 0);

	/* case 3: overflow. (src > dest) */
	char src3[10] = "some word", dest3[5], src4[10] = "some word", dest4[5];
	my_strncpy(dest3, src3, 5);
	strncpy(dest4, src4, 5);
	mu_assert("strcpy error, edge case 3", strcmp(dest3, dest4) == 0);
}

static char* test_strcat()
{
	/* case 1: non empty strings */
	char src[] = " world", dest[25] = "hello";
	my_strcat(dest, src);
	mu_assert("strcat error, case 1", strcmp(dest, "hello world") == 0);
	
	/* case 2: empty string */
	char src2[] = "", dest2[25] = "hello";
	my_strcat(dest2, src2);
	mu_assert("strcat error, case 1", strcmp(dest2, "hello") == 0);

	return 0;
}

static char* test_strncat()
{
	/* case 1: non empty string: copy entire src */
	char src[] = " world", dest[25] = "hello";
	my_strncat(dest, src, 6);
	mu_assert("strncat error, case 1", strcmp(dest, "hello world") == 0);

	/* case 2: non empty string: copy substring of src */
	char src2[] = " world", dest2[25] = "hello";
	my_strncat(dest2, src2, 4);
	mu_assert("strncat error, case 2", strcmp(dest2, "hello wor") == 0);

	return 0;
}

static char* test_strcmp()
{
	/* case 1: same strings */
	char *s1 = "rand", *s2 = "rand";
	mu_assert("strcmp error, case 1", my_strcmp(s1, s2) == 0);

	/* case 2: empty strings */
	char *s3 = "", *s4 = "";
	mu_assert("strcmp error, case 2", my_strcmp(s3, s4) == 0);

	/* case 3: s1 < s2*/
	char *s5 = "abc", *s6 = "abxy";
	mu_assert("strcmp error, case 3", my_strcmp(s5, s6) == -1);

	/* case 4: s1 > s2 */
	char *s7 = "abx", *s8 = "abc";
	mu_assert("strcmp error, case 4", my_strcmp(s7, s8) == 1);

	return 0;
}

static char* test_strncmp()
{
	/* case 1: same strings */
	char *s1 = "abx", *s2 = "abx";
	mu_assert("strcmp error, case 1", my_strncmp(s1, s2, 3) == 0);

	/* case 2: same strings, compare substring */
	char *s3 = "abc", *s4 = "a";
	mu_assert("strcmp error, case 2", my_strncmp(s3, s4, 1) == 0);

	/* case 3: different strings, compare all chars */
	char *s5 = "rand word", *s6 = "rand worz";
	mu_assert("strcmp error, case 3", my_strncmp(s5, s6, 9) == -1);

	/* case 4: different string, compare substring s1 < s1 */
	char *s7 = "rand a", *s8 = "rand z";
	mu_assert("strcmp error, case 4", my_strncmp(s7, s8, 6) == -1);

	/* case 5: different string, compare substring s1 > s1 */
	char *s9 = "some tezt", *s10 = "some tect";
	mu_assert("strcmp error, case 5", my_strncmp(s9, s10, 8) == 1);
}

static char* test_strlen()
{
	/* case 1: size > 0 */
	char *str = "A random string";
	mu_assert("strlen error, case 1", strlen(str) == 15);

	/* case 2: empty string */
	char str2[10];
	mu_assert("strlen error, case2", strlen(str2) == my_strlen(str2));
}

static char* all_tests() 
{
	mu_run_test(test_fgets);
	mu_run_test(test_fputs);
	mu_run_test(test_strcpy);
	mu_run_test(test_strncpy);
	mu_run_test(test_strcat); 
	mu_run_test(test_strncat);
	mu_run_test(test_strlen);
	mu_run_test(test_strcmp);
	mu_run_test(test_strncmp);
	mu_run_test(test_fgetc);
	mu_run_test(test_fputc);
	mu_run_test(test_gets);
	mu_run_test(test_getchar);
	return 0;
}

int main(int argc, char **argv) 
{
	inStream = fopen("input.txt", "r");
	inStreamEmpty = fopen("empty_file.txt", "r");
	outStream = fopen("output.txt", "w");
	
	char *result = all_tests();

	result != 0 ? printf("%s\n", result) : printf("ALL TESTS PASSED\n");
	printf("Tests run: %d\n", tests_run);

	fclose(inStream);
	fclose(inStreamEmpty);
	fclose(outStream);

	/* Test puts, and putchar (can't use mu_assert to verify correct output) */
	printf("\nputs and putchar test\n");

	my_puts("rand");
	my_puts("");
	my_puts("str");

	my_putchar('a');

	return result != 0;
}
