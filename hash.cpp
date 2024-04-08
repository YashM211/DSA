//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function template for C++
#define ll long long int

ll quickhash(string s, ll p, ll mod)
{
    ll ans = (s[0] - 'a') + 1;
    for (int i = 1; i < s.size(); i++)
    {
        ans = ((ans * p + s[i] - 'a' + 1) % mod + mod) % mod;
    }
    return ans;
}

class hassh
{
private:
    vector<ll> phash;
    vector<ll> pk;
    ll mod;
    ll n;
    ll p;

public:
    hassh(string s, ll mmod, ll pp)
    {
        n = (ll)s.size();
        mod = mmod;
        p = pp;
        phash.resize(n);
        pk.resize(n);
    }

    void hasher(string s)
    {
        phash[0] = s[0] - 'a' + 1ll;
        pk[0] = 1;
        for (int i = 1; i < n; i++)
        {
            phash[i] = ((phash[i - 1] * p + s[i] - 'a' + 1) % mod + mod) % mod;
            pk[i] = ((pk[i - 1] * p) % mod + mod) % mod;
        }
    }

    ll gethash(int l, int r)
    {
        if (l == 0)
            return (phash[r]) % mod;
        else
            return ((phash[r] - phash[l - 1] * pk[r - l + 1]) % mod + mod) % mod;
    }

    ll getphash(int i)
    {
        return phash[i];
    }
};

class Solution
{
public:
    int search(string text, string pat)
    {
        // Your code goes here
        ll mod = 1e9 + 7;
        ll p = 31;
        ll pathashval = quickhash(pat, p, mod);
        // return pathashval;

        int wsize = pat.size();
        hassh texthash(text, mod, p);
        texthash.hasher(text);
        // cout<<pathashval<<endl;
        // cout<<texthash.gethash(8,9)<<endl;

        // for(int i=0 ; i<text.size() ; i++){
        //     cout<<texthash.getphash(i)<<endl;
        // }

        // cout<<texthash.getphash(9)<<" "<<texthash.getphash(8)<<" "<<texthash.getphash(7)<<endl;
        for (int i = 0; i + pat.size() - 1 < text.size(); i++)
        {
            // cout<<i<<" ";
            ll res = texthash.gethash(i, i + wsize - 1);
            if (res == pathashval)
            {
                return true;
            }
        }
        return false;
    }
};

//{ Driver Code Starts.

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        string x, y;
        cin >> x >> y;

        Solution ob;
        cout << ob.search(x, y) << "\n";
    }

    return 0;
}
// } Driver Code Ends