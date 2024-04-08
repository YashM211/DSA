#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((ll)x.size())
#define all(a) (a).begin(), (a).end()

const ll MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

class sgt{
    private:
        vector<int>segtree;
    
    public:
        sgt(ll n){
            segtree.resize(4*n+1);
        }

        void build(ll index , ll low , ll high , vector<ll>&arr){
            if(low==high){
                segtree[index] = arr[low];
                return;
            }
            ll mid = (low+high)/2;
            build(2*index , low , mid , arr);
            build(2*index+1 , mid+1 , high , arr);

            segtree[index] = segtree[2*index] + segtree[2*index+1];
        }

        void update(ll index , ll low , ll high , ll pos, ll val){
            if(low==high ){
                segtree[index] = val;
                return;
            }

            ll mid = (low + high)/2;

            if(pos<=mid){
                update(2*index , low , mid , pos,val);
            }
            else{
                update(2*index+1 , mid+1 , high , pos,val);
            }

            segtree[index] = segtree[2*index]+ segtree[2*index+1];
        }

        ll getSum(ll index , ll low , ll high , ll lq , ll rq){
            //No Overlap
            if(low>rq || high<lq) return 0;

            //Complete Overlap
            if(low>=lq && high<=rq){
                return segtree[index];
            }

            //Partial Overlap
            ll mid = (low+high)/2;
            ll left = getSum(2*index , low , mid , lq,rq);
            ll right = getSum(2*index+1 , mid+1 , high , lq,rq);

            return left+right;
        }

        ll getroot(){
            return segtree[1];
        }
};

void helper(){
    ll n,q;
    cin>>n>>q;
    vector<ll>arr(n);
    for(ll i=0 ; i<n ; i++){
        cin>>arr[i];
    }
    // arr.insert(arr.begin() , -1e8);
    sgt t(n);
    t.build(1,0,n-1,arr);
    // cout<<t.getroot()<<endl<<endl;
    while(q--){
        ll typ;
        cin>>typ;
        // cout<<typ<<endl;
        if(typ==1){
            ll pos , val;
            cin>>pos>>val;
            // cout<<val;
            t.update(1,0,n-1,pos-1,val);
            // cout<<val<<endl;
        }
        else{
            ll lq,rq;
            cin>>lq>>rq;
            // cout<<lq;
            ll sum = t.getSum(1,0,n-1,lq-1,rq-1);
            cout<<sum<<endl;
        }
    }
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll tc = 1;
    // cin >> tc;
    for (ll t = 1; t <= tc; t++)
    {
        // cout << "Case #" << t << ": ";
        helper();
    }
}