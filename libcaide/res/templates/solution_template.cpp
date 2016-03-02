#include <algorithm>
#include <iomanip>
#include <istream>
#include <map>
#include <numeric>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define INF 1000000000
#define Inf 1000000000000000000
#define EPS 1e-9
#define ALL(X) (X).begin(), (X).end()
#define RI(X) scanf("%d", &(X))
#define RII(X, Y) scanf("%d%d", &(X), &(Y))
#define RIII(X, Y, Z) scanf("%d%d%d", &(X), &(Y), &(Z))
#define DRI(X) int (X); scanf("%d", &X)
#define DRII(X, Y) int X, Y; scanf("%d%d", &X, &Y)
#define DRIII(X, Y, Z) int X, Y, Z; scanf("%d%d%d", &X, &Y, &Z)
#define RS(X) scanf("%s", (X))
#define CASET int ___T, case_n = 1; scanf("%d ", &___T); while (___T-- > 0)
#define MP make_pair
#define PB push_back
#define MS0(X) memset((X), 0, sizeof((X)))
#define MS1(X) memset((X), -1, sizeof((X)))
#define LEN(X) strlen(X)
#define PLL pair<long long,long long>
#define VPLL vector<pair<long long,long long> >
#define F first
#define S second
#define forin for(int i = 0;i < n;i++)

#define MOD 1000000007 // In order to make answer for long answer problems
#define OUT(X) cout << fixed << setprecision(X)  // Output with certain precision value

#define REP(i, N) for (int i = 0; i < (N); ++i)
#define REPP(i, A, B) for (int i = (A); i < (B); ++i)

using namespace std;
// Powered by caide (code generator, tester, and library code inliner)

typedef long long ll;

long long combin(long long n, long long r)
{
	long long ans = 1;
	for (int i = 0; i < r; i++)
	{
		ans *= n - i;
		ans /= i + 1;
	}
	return ans;
}

int gcd(int a, int b){ 
	return b == 0 ? a : gcd(b, a%b); 
}


class Solution {
public:
    void solve(std::istream& in, std::ostream& out) {
    }
};

void solve(std::istream& in, std::ostream& out)
{
    out << std::setprecision(12);
    Solution solution;
    solution.solve(in, out);
}
