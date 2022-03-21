# hw0201 mymatch
```c
int mymatch(char ***pppList , const char *pStr, const char *pPattern);
```
- **how to use?**
```c
char str[] = "basse ace ache ae aaae baaae ace";
char **pppList;
int32_t i, count = mymatch(&pppList, str, "a*e");
printf("%d\n", count);
for( i=0; i<count; i++ ) 
{
	printf("pattern match: %s\n", pppList[i]);
}
return 0;
```
- **output**
```c
5
pattern match: ace
pattern match: ache
pattern match: ae
pattern match: aaae
pattern match: ace
```

# hw0202 IEEE 754
- a program for the user to input a double floating-point number and display the number as sign, exponent, fraction.
