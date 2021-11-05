#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
#define maxm 6005
#define maxn 1010
#define inf 2147483647
#define maxw 13000
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define loop(i, a, b) for(int i = a; i >= b; i--)
#define sqr(x) ((x) * (x))

inline ll read() {
    ll s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {s = s * 10 + ch - '0'; ch = getchar();}
    return s * w;
}

/**
* ============================================================================
@Author:      Cool_Ball
@DateTime:    2021-11-04 21:03:38
* ============================================================================
*/

ll n;

//----------fraction start----------//
struct frac {
    ll up, down;
};

ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

frac add(frac a, frac b) {
    ll tmp1 = a.down * b.down, tmp2 = a.up * b.down + b.up * a.down;
    ll g = gcd(tmp1, tmp2);
    tmp1 /= g, tmp2 /= g;
    return frac{tmp2, tmp1};
}

frac subt(frac a, frac b) {
    ll tmp1 = a.down * b.down, tmp2 = a.up * b.down - b.up * a.down;
    ll g = gcd(tmp1, tmp2);
    tmp1 /= g, tmp2 /= g;
    if(tmp1 < 0) {
        tmp1 = abs(tmp1);
        tmp2 = -tmp2;
    }
    return frac{tmp2, tmp1};
}

frac mul(frac a, frac b) {
    ll tmp1 = a.down * b.down, tmp2 = a.up * b.up;
    ll g = gcd(tmp1, tmp2);
    tmp1 /= g, tmp2 /= g;
    return frac{tmp2, tmp1};
}

frac div(frac a, frac b) {
    ll tmp1 = a.down * b.up, tmp2 = a.up * b.down;
    ll g = gcd(tmp1, tmp2);
    tmp1 /= g, tmp2 /= g;
    return frac{tmp2, tmp1};
}
//----------fraction end----------//


//----------Guass Elimination start----------//
frac A[maxn][maxn];
ll exc = 0;
void Guass() {
    rep(i, 1, n) {
        //find largest pivot
        ll maxx = i;
        rep(j, i + 1, n) {
            if(abs(A[j][i].up * A[maxx][i].down) > abs(A[maxx][i].up * A[j][i].down)) {
                maxx = j;
            }
        }
        //row exhange
        if(maxx != i) {
            cout << "Switch the " << i << "-th row with the " << maxx << "-th row" << endl;
            rep(j, 1, n) {
                swap(A[i][j], A[maxx][j]);
            }
            exc++;
            rep(o, 1, n) {
                rep(p, 1, n) {
                    cout << A[o][p].up;
                    if(A[o][p].down != 1) cout << "/" << A[o][p].down;
                    cout << " ";
                }
                cout << endl;
            }
        }
        //Guass eliminated to upper triangular matrix
        rep(j, i + 1, n) {
            frac tmp = div(A[j][i] ,A[i][i]);
            cout << "Subtract the " << j << "-th row with " << tmp.up << "/" << tmp.down << " times of the " << i << "-th row." << endl;
            rep(k, i , n) {
                A[j][k] = subt(A[j][k], mul(A[i][k], tmp));
            }
        }
        if(i < n) {
            rep(o, 1, n) {
                rep(p, 1, n) {
                    cout << A[o][p].up;
                    if(A[o][p].down != 1) cout << "/" << A[o][p].down;
                    cout << " ";
                }
                cout << endl;
            }
        }
    }

    //output the determianat of the martix
    frac ans = frac{1, 1};
    rep(i, 1, n) {
        ans = mul(ans, A[i][i]);
    }
    printf("The determinant of the matrix is:\n");
    if(exc % 2 == 1 && ans.up != 0) cout << "-";
    cout << ans.up;
    if(ans.down != 1) cout << "/" << ans.down << endl;
    return;
}
//----------Guass Elimination end----------//

void inp() {
    printf("Please input the matrix(integer or fraction)\n");
    rep(i, 1, n) {
        rep(j, 1, n) {
            bool flag = false;
            string s;
            cin >> s;
            ll num = 0, w = 1;
            rep(k, 0, s.length() - 1) {
                if(s[k] == '/') {
                    flag = true;
                    A[i][j].up = w * num;
                    w = 1, num = 0;
                }
                if(s[k] == '-') w = -1;
                if(s[k] >= '0' && s[k] <= '9') num = num * 10 + s[k] - '0';
            }
            if(flag) A[i][j].down = w * num;
            else {
                A[i][j].up = w * num;
                A[i][j].down = 1;
            }
        }
    }
}

int main() {
    printf("Please input the matrix size(n*n)\n");
    n = read();
    inp();
    Guass();
    return 0;
}