#include "String.h"

// 1. default constructor
String::String() : str_(new char[1]()), size_(0), capacity_(0) 
{
    str_[0] = '\0';
}
// 2. copy constructor
String::String(const String& other) : str_(new char[other.capacity_ +1]()), size_(other.size_), capacity_(other.capacity_)
{
    my_strlcpy(this->str_, this->capacity_ +1, other.c_str(), this->size_);
}
// 3. constructor with one parameter with type const char *
String::String(const char* source) : str_(new char[my_strlen(source) +1]()), size_(my_strlen(source)), capacity_(my_strlen(source))
{
    my_strlcpy(this->str_, this->capacity_ +1, source, this->size_);
}
// 4. destructor
String::~String()
{
    // str_ would not be a nullptr
    delete[] this->str_;
    this->size_ = 0;
    this->capacity_ = 0;
}
// 5. size()
size_t String::size() const { return size_; };
size_t String::capacity() const { return capacity_; };
// 6. c_str()
const char* String::c_str() const { return str_; }
// 7. operator []
char& String::operator[](size_t pos)
{
    return this->str_[pos];
}
const char& String::operator[](size_t pos) const
{
    return this->str_[pos];
}
// 8. operator +=
String& String::operator+= (const String& str)
{
    for(size_t i = 0; i < str.size_; ++i)
    {
        *this += str[i];
    }
    return *this;
}
String& String::operator+= (const char* s)
{
    size_t len = my_strlen(s);
    for(size_t i = 0; i < len; ++i)
    {
        *this += s[i];
    }
    return *this;
}
String& String::operator+= (char c)
{
    // push_back
    if(this->size_ == this->capacity_)
    {
        size_t newCapacity = this->capacity_ == 0 ? 15 : this->capacity_*2;
        // reserve
        // avoid leak of memory
        char *tmp = new char[newCapacity +1]();
        my_strlcpy(tmp, newCapacity +1, this->str_, this->size_);
        delete[] this->str_;
        this->str_ = tmp;
        this->capacity_ = newCapacity;
    }
    this->str_[this->size_] = c;
    this->str_[++this->size_] = '\0';
    return *this;
}
// 9. clear()
void String::clear()
{
    // if(nullptr == this->str_)
    // {
    //     return;
    // }
    this->str_[0] = '\0';
    this->size_ = 0;
}
// 10. operator =
// pass by value => call a copy constructer
String& String::operator=(String ref) 
{
    // if(this != &ref)
    // {
    //     this->clear();
    //     this->operator+=(ref);
    //     return *this;
    // }
    // return *this; 

    // Copy and Swap
    this->swap(ref);
    return *this;
}
String& String::operator=(const char* ref) 
{
    this->clear();
    this->operator+=(ref);
    return *this;
}
String& String::operator=(char c) 
{
    this->clear();
    this->operator+=(c);
    return *this;
}
// 11. swap()
void String::swap(String& src)
{
    std::swap(this->size_, src.size_);
    std::swap(this->capacity_, src.capacity_);
    std::swap(this->str_, src.str_);
}

// strcpy avoid stopping at \0, and append a \0 at the end of string 
void String::my_strlcpy(char *dst, size_t dstsize, const char* src, size_t count)
{
    if(nullptr != src)
    {
        size_t len = 0;
        // while(++len < dstsize && *src)
        while(count && ++len < dstsize)
        {
            *dst++ = *src++;
            --count;
        }
        if(len <= dstsize)
        {
            *dst = 0;
        }
    }
}
size_t String::my_strlen(const char *src) const
{
    size_t len = 0;
    while(*src != '\0')
    {
        ++src;
        ++len;
    }
    return (len);
}

// A. relational operators (<, >, <=, >=, ==, !=)
bool operator< (const String& lhs, const String& rhs)
{
    size_t idx = std::min(lhs.size(), rhs.size());
    for(size_t i = 0; i < idx; ++i)
    {
        if(lhs[i] != rhs[i])
        {
            return (lhs[i] < rhs[i]);
        }
    }
    // 直到字串結束都一樣，以長度為準
    return (lhs.size() < rhs.size());
}
bool operator== (const String& lhs, const String& rhs)
{
    if(lhs.size() != rhs.size())
    {
        return false;
    }
    else 
    {
        for(size_t i = 0; i < lhs.size(); ++i)
        {
            if(lhs[i] != rhs[i])
            {
                return false;
            }
        }
    }
    return true;
}
bool operator<= (const String& lhs, const String& rhs)
{
    return ((lhs < rhs) || (lhs == rhs));
}
bool operator> (const String& lhs, const String& rhs)
{
    return (! (lhs <= rhs));
}
bool operator>= (const String& lhs, const String& rhs)
{
    return (! (lhs < rhs));
}
bool operator!= (const String& lhs, const String& rhs)
{
    return (! (lhs == rhs));
}
// B. operator <<, >>
std::ostream& operator<< (std::ostream& os, const String& str)
{
    for(size_t i = 0; i < str.size(); ++i)
    {
        os << str[i];
    }
    return os;
}
std::istream& operator>> (std::istream& is, String& str)
{
    str.clear();
    char ch;
    while(ch = is.get(), !isspace(ch))
    {
        str += ch;
    }
    return is;
}
// C. operators +
String operator+ (const String& rhs, const String& lhs)
{
    String tmp(rhs);
    tmp += lhs;
    return tmp;
}