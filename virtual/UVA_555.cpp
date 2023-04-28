#include <iostream>
#include <algorithm>
using namespace std;

class Card
{
    friend ostream & operator << (ostream &os, const Card &rhs);
    friend bool operator < (const Card &lhs, const Card &rhs);
public:
    void Set(char s, char d);
private:
    char suit_ = ' ', digit_ = ' ';
    int num_ = 0;
};
// ------------------------------------------------------------------
void Card::Set(char s, char d)
{
    // TODO
    this->suit_ = s;
    this->digit_ = d;
}
// ------------------------------------------------------------------
bool operator < (const Card &lhs, const Card &rhs)
{
    // TODO
    int r, l;
    if(lhs.suit_ == rhs.suit_)
    {
        switch (lhs.digit_)
        {
            case 'A':
                l = 15;
                break;
            case 'K':
                l = 13;
                break;
            case 'Q':
                l = 12;
                break;
            case 'J':
                l = 11;
                break;
            case 'T':
                l = 10;
                break;
            default:
                l = lhs.digit_ - '0';
                break;
        }
        switch (rhs.digit_)
        {
            case 'A':
                r = 15;
                break;
            case 'K':
                r = 13;
                break;
            case 'Q':
                r = 12;
                break;
            case 'J':
                r = 11;
                break;
            case 'T':
                r = 10;
                break;
            default:
                r = rhs.digit_ - '0';
                break;
        }
        return (l < r);
    }
    switch (lhs.suit_)
    {
        case 'C':
            l = 1;
            break;
        case 'D':
            l = 2;
            break;
        case 'S':
            l = 3;
            break;
        case 'H':
            l = 4;
            break;
    }
    switch (rhs.suit_)
    {
        case 'C':
            r = 1;
            break;
        case 'D':
            r = 2;
            break;
        case 'S':
            r = 3;
            break;
        case 'H':
            r = 4;
            break;
    }
    return (l < r);
}
// ------------------------------------------------------------------
ostream & operator << (ostream &os, const Card &card)
{
    os << card.suit_ << card.digit_;
    return os;
}
// ------------------------------------------------------------------
int main()
{
    char start = ' ';
    while (cin >> start && start!='#')
    {
        constexpr char position[] = "NESW";
        constexpr size_t NumPeople = sizeof(position)-1;

        // determine the first player to get cards
        int j = 0;
        for (size_t i=0; i<NumPeople; i+=1)
        {
            if (position[i]==start)
            {
                j = (i+1)%NumPeople;
                break;
            }
        }

        // read in and distribute cards
        constexpr size_t NumCards = 13;
        Card cards[NumPeople][NumCards];
        for (size_t i=0; i<NumPeople*NumCards; i+=1)
        {
            char s, n;
            cin >> s >> n;
            cards[j][i/NumPeople].Set(s, n);
            j = (j+1)%NumPeople;
        }

        // sort cards of every player
        for (size_t i=0; i<NumPeople; i+=1)
        {
            sort(cards[i], end(cards[i]));
        }

        // find the first player to display
        for (size_t i=0; i<NumPeople; i+=1)
        {
            if (position[i]=='S')
            {
                j = i;
                break;
            }
        }

        // display cards of every player
        for (size_t t=0; t<NumPeople; t+=1, j=(j+1)%NumPeople)
        {
            cout << position[j] << ':';
            for (size_t i=0; i<NumCards; i+=1)
            {
                cout << ' ' << cards[j][i];
            }
            cout << endl;
        }
    }
}
/*
N
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
S
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
#
*/
