// Simulating std::string
#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <ctype.h>

class String
{
public:
    // 1. default constructor
    String();
    // 2. copy constructor
    String(const String& other);
    // 3. constructor with one parameter with type const char *
    String(const char* source);
    // 4. destructor
    ~String();
    // 5. size()
    size_t size() const;
    size_t capacity() const;
    // 6. c_str()
    const char* c_str() const;
    // 7. operator []
    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;
    // 8. operator +=
    String& operator+= (const String& str);
    String& operator+= (const char* s);
    String& operator+= (char c);
    // 9. clear()
    void clear();
    // 10. operator =
    String& operator=(String ref);
    String& operator=(const char* ref);
    String& operator=(char c);
    // 11. swap()
    void swap(String& src);
private:
    char *str_ = nullptr;
    size_t size_ = 0, capacity_ = 0;
    // strcpy avoid stopping at \0, and append a \0 at the end of string 
    void my_strlcpy(char *dst, size_t dstsize, const char* src, size_t count);
    size_t my_strlen(const char *src) const;
};
// A. relational operators (<, >, <=, >=, ==, !=)
bool operator< (const String& lhs, const String& rhs);
bool operator== (const String& lhs, const String& rhs);
bool operator<= (const String& lhs, const String& rhs);
bool operator> (const String& lhs, const String& rhs);
bool operator>= (const String& lhs, const String& rhs);
bool operator!= (const String& lhs, const String& rhs);
// B. operator <<, >>
std::ostream& operator<< (std::ostream& os, const String& str);
std::istream& operator>> (std::istream& is, String& str);
// C. operators +
String operator+ (const String& rhs, const String& lhs);

#endif