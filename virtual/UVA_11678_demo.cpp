#include <iostream>
#include <set>
using namespace std;

int main() {
    int A, B, n;
    while (cin >> A >> B){
        if (A == 0 && B == 0) break;
        set <int> stA, stB, st;
        for (int i = 0; i < A; i++){
            cin >> n;
            stA.insert(n);
            st.insert(n);
        }
        for (int i = 0; i < B; i++){
            cin >> n;
            stB.insert(n);
            st.insert(n);
        }
        cout << "\n" << min(st.size() - stA.size(), st.size() - stB.size()) << "\n";        
    }
    return 0;
}