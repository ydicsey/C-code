// #pragma once
// #include<stdint.h>

// char *mystrchr(const char *s, int c);
// char *mystrrchr(const char *s, int c);
// size_t mystrspn(const char *s, const char *accept);
// size_t mystrcspn(const char *s, const char *reject);
// char *mystrpbrk(const char *s, const char *accept);
// char *mystrstr(const char *haystack , const char *needle);
// char *mystrtok(char *str, const char *delim);

#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
// The strtol() function converts the initial part of the string in nptr to a long integer value according to the
// given base, which must be between 2 and 36 inclusive, or be the special value 0.
// underflow occurs
// #define LONG_MIN 0x80000000
// overflow occurs
// #define LONG_MAX 0x7FFFFFFF
// In  both cases,  errno  is set to ERANGE.
int32_t isDigit(int32_t c)
{
    return (c >= '0' && c <= '9' ? 1 : 0);
}
int32_t isSpace(int32_t c)
{
    return ( c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v' ? 1 : 0);
}
int32_t isAlpha(int32_t c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? 1 : 0);
}
int32_t isUPalpha(int32_t c)
{
    return ((c >= 'A' && c <= 'Z') ? 1 : 0);
}
// long int mystrtol(const char *nptr, char **endptr , int base)
// {
//     // EINVAL (not in C99) The given base contains an unsupported value.
//     if(base > 36 || base < 0)
//     {
//         errno = EINVAL;
//     }
//     // start on 2022/2/27
//     uint8_t* s = (uint8_t*)nptr;
//     int32_t c, pos = 1;
//     uint32_t ans;
//     do{
//         c = *s++;
//     }while(isSpace(c));
//     if(c == '-')
//     {
//         pos = 0;
//         c = *s++;
//     }
//     else
//     {
//         pos = 1;
//         if (c == '+')
//             c = *s++;
//     }
//     if((base == 0 || base == 16) && c == 0 && (*s == 'x' || *s == 'X'))
//     {
//         base = 16;
//         *s++;
//         c = *s;
//         *s++;
//     }
//     if(base == 0)
//     {
//         if(c == '0')
//             base = 8;
//         else
//             base = 10;
//     }
//     if(base < 2 || base > 36)
//     {
//         errno = EINVAL;
//     }

//     uint32_t overflow = pos? LONG_MAX : -(uint32_t)LONG_MIN;
//     uint32_t lim = overflow % base;
//     overflow /= (uint32_t)base;
//     int32_t i = 0, j = 0;
//     for(;; c = *s++)
//     {
//         if(isDigit(c))
//         {
//             c -= '0';
//         }
//         else if (c >= 'A' && c <= 'Z')
//             c -= 'A' - 10;
//         else if (c >= 'a' && c <= 'z')
//             c -= 'a' - 10;
//         else
//             break;
//         if(c >= base)
//         {
//             break;
//         }
//         if (i < 0 || j > overflow || (j == overflow && c > lim))
//             i = -1;
//         else 
//         {
//             i = 1;
//             j *= base;
//             j += c;
//         }
//         if (i < 0) {
//                 j = pos ? LONG_MAX : LONG_MIN;
//                 errno = ERANGE;
//         } else if (!pos)
//                 j = -j;
//         if (endptr != 0)
//                 *endptr = (char *) (i ? (s - 1) : nptr);
//         return (j);
//     }
// }
char *mystrchr(const char *s, int c)
{
    if (NULL == s)
    {
        return NULL;
    }
    if ((c > 255) || (c < 0))
    {
        return NULL;
    }
    uint8_t* i;
    for (i = (uint8_t*)s; *i != 0; i++)
    {
        if(*i == c)
        {
            return i;
        }
    }
    return NULL;
}
char *mystrrchr(const char *s, int c)
{
    if (NULL == s)
    {
        return NULL;
    }
    if ((c > 255) || (c < 0))
    {
        return NULL;
    }
    uint8_t* i;
    for(i = (uint8_t*)s; *i != 0; i++);
    for (; i != (uint8_t*)s; i--)
    {
        if(*i == c)
        {
            return i;
        }
    }
    return NULL;
}
size_t mystrspn(const char *s, const char *accept)
{
    if (NULL == s || NULL == accept)
    {
        return 0;
    }
    size_t count = 0;
    // uint8_t* i;
    // for (i = s; *i != 0; i++)
    // {
    //     if (NULL == mystrchr(accept, *i))
    //     {
    //         break;
    //     }
    //     count ++;
    // }
    while(s[count] && mystrchr(accept, s[count]))
    {
        count++;
    }
    return count;
}
size_t mystrcspn(const char *s, const char *reject)
{
    if (NULL == s || NULL == reject)
    {
        return 0;
    }
    size_t count = 0;

    while(s[count] && (NULL == mystrchr(reject, s[count])))
    {
        count++;
    }
    return count;
}
char *mystrpbrk(const char *s, const char *accept)
{
    if (NULL == s || NULL == accept)
    {
        return NULL;
    }
    uint8_t* i = (uint8_t*)s;
    while(*i && (NULL == mystrchr(accept, *i)))
    {
        i++;
    }
    return i;
}
// 返回haystack中首次出現needle的地址
char *mystrstr(const char *haystack , const char *needle)
{
    if (NULL == haystack || NULL == needle)
    {
        return NULL;
    }
    // uint8_t* i = haystack;
    uint8_t* j = (uint8_t*)needle;
    // uint8_t *ptr = mystrchr(i, *j);
    uint8_t *ptr = mystrchr(haystack, *j);
    uint8_t *hayptr = ptr;
    if(NULL == ptr)
    {
        return NULL;
    }
    
    for(; *j != 0; j++)
    {
        if(*ptr == *j)
        {
            ptr++;
        }
    }
    if(*j == 0)
    {
        return hayptr;
    }
    if(*ptr == 0)
    {
        return NULL;
    }

    return NULL;
}
char *mystrtok(char *str, const char *delim)
{
    static char *backup = NULL;
    if(str == NULL && (str = backup) == NULL)
    {
        return NULL;
    }
    // uint8_t* ptr;
    // uint8_t* temp;
    // for(ptr = str; *ptr != 0; ptr++)
    // {
    //     for(temp = (uint8_t*)delim; *temp != 0; temp++)
    //     {
    //         if(*ptr == *temp)
    //         {
    //             backup = ptr + 1;
    //             if(*ptr - *str == 0)
    //             {
    //                 str = backup;
    //                 break;
    //             }
    //             *ptr = '\0';
    //             return str;
    //         }
    //     }
    // }
    // return NULL;
    str += mystrspn(str, delim);
    if(*str == 0)
    {
       backup = str;
       return NULL;
    }
    uint8_t *end = str + mystrcspn(str, delim);
    if(*end == 0)
    {
       backup = end;
       return str;
    }
    *end = '\0';
    backup = end + 1;
    return str;
}
// start 3/1/2022
int mystrncmp (const char *s1, const char *s2, size_t n)
{
    if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*(uint8_t *)s1 - *(uint8_t *)--s2);
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}
size_t mystrlen(const char *str)
{
    uint8_t* i;
    size_t len = 0;
    for (i = (uint8_t*)str; *i != 0; i++)
    {
       len++; 
    }
    return len;
}
// https://android.googlesource.com/platform/bionic/+/ics-mr0/libc/string/strncpy.c
char *mystrncpy(char *dst, const char *src, size_t n)
{
	if (n != 0) {
		char *d = dst;
		const char *s = src;
		do {
			if ((*d++ = *s++) == 0) {
				/* NUL pad the remaining n-1 bytes */
				while (--n != 0)
					*d++ = 0;
				break;
			}
		} while (--n != 0);
	}
	return (dst);
}
// https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
int mystrsplit(char ***pppList , int *pCounter , const char *pStr, const char *pSeparator)
{
    uint8_t** output;
    uint8_t* slow;
    uint8_t* fast;
    int32_t count = 0, n = 0;
    
    if(NULL == pSeparator)
    {
        uint8_t spaceTable[] = " \f\n\r\t\v";
        fast = (uint8_t*)pStr;

        do
        {
            fast += mystrspn(fast, spaceTable);
            // printf("\nfast = %s\n", fast);
            if(isSpace(*(fast + 1)) || *(fast + 1) == 0)
            {
                count++;
            }
            fast++;
            // printf("\ncount = %d\n", count);
        } while (*fast);

        *pCounter = count;
        output = malloc(count * sizeof(char*));
        count = 0;
        fast = (uint8_t*)pStr;
        slow = (uint8_t*)pStr;

        if(!output)
            return -1;

        do
        {
            // printf("\nstrspn = %ld\n", mystrspn(fast, spaceTable));
            if(mystrspn(fast, spaceTable))
            {
                fast += mystrspn(fast, spaceTable);
                slow = fast;
                n = 0;
                // printf("\n1.n = %d\n", n);
                // printf("\n2.fast = %s\n", fast);
                // printf("\n3.slow = %s\n", slow);
            }
            else
            {
                n++;
                // printf("\n4.n = %d\n", n);
                if(isSpace(*(fast + 1)) || *(fast + 1) == 0)
                {
                    char *temp = malloc(n * sizeof(char));
                    mystrncpy(temp, slow, n);
                    // printf("\n5.n = %d\n", n);
                    // printf("\n6.temp = %s\n", temp);
                    output[count++] = temp;
                }
                fast++;
            }
        } while (*fast);

        *pppList = (char**)output;
        return 0;
    }


    for(fast = (uint8_t*)pStr; *fast != 0; fast++)
    {
        if(*fast == pSeparator[0] && (0 == mystrncmp(fast, pSeparator, mystrlen(pSeparator))))
        {
            count++;
        }
    }

    *pCounter = count + 1;
    output = malloc(*pCounter * sizeof(char*));
    count = 0;

    if(!output)
        return -1;

    for(fast = (uint8_t*)pStr, slow = (uint8_t*)pStr; *fast != 0; fast++)
    {
        if(*fast == pSeparator[0] && (0 == mystrncmp(fast, pSeparator, mystrlen(pSeparator))))
        {
            char *temp = malloc(n * sizeof(char));
            mystrncpy(temp, slow, n);
            output[count++] = temp;
            n = -1;
            slow = fast + mystrlen(pSeparator);
            fast += mystrlen(pSeparator) - 1;
        }
        n++;
        // if(*(fast + 1) == 0)
        // {
        //     char *temp = malloc(n * sizeof(char));
        //     mystrncpy(temp, slow, n);
        //     output[count++] = temp;
        //     n = -1;
        //     slow = fast + mystrlen(pSeparator);
        //     fast += mystrlen(pSeparator) - 1;
        // }
    }
    if(*pCounter != count)
    {
        printf("\nn = %d\n", n);
        char *temp = malloc(n * sizeof(char));
        mystrncpy(temp, slow, n);
        output[count++] = temp;
    }
    *pppList = (char**)output;
    *pCounter = count;
    return 0;
}
