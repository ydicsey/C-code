# 1. Another Character Encoding
- user type *EXIT* to quit this program.
# 2. Replacement
- The keywords and the new word should be colored.
# 3. My String Library v1
```c
long int mystrtol(const char *nptr, char **endptr , int base);
```
- NOT FINISHED YET
# 4. My String Library v2
```c
char *mystrchr(const char *s, int c);
char *mystrrchr(const char *s, int c);
size_t mystrspn(const char *s, const char *accept);
size_t mystrcspn(const char *s, const char *reject);
char *mystrpbrk(const char *s, const char *accept);
char *mystrstr(const char *haystack , const char *needle);
char *mystrtok(char *str, const char *delim);
```
# 5. Split
- **how to use?**
```c
char str[] = "  a bb   c      eee";
char **pppList;
int count;
// NULL means spilt by space char: " \f\n\r\t\v"
mystrsplit(&pppList, &count, str5, NULL);
printf("\nsplit.count = %d\n", count);
for( i=0; i<count; i++ ) 
{
	printf("str: %s\n", pppList[i]);
}
return 0;
```
- **output**
```c
split.count = 4
str: a
str: bb
str: c
str: eee
```
- this function can also split by "," or ",," and something like that, means users can split by more than one char
- **NULL** means spilt by space char: " \f\n\r\t\v"
