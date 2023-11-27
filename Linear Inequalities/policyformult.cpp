#include <bits/stdc++.h>
 #include <ext/pb_ds/assoc_container.hpp>
 using namespace std;
 using namespace __gnu_pbds;
 // Policy based data structure
 template<class T> using oset=tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 typedef long long ll;
 typedef unsigned long long ull;
 typedef long double lld;
 #define pb push_back
 #define ppb pop_back
 #define mp make_pair
 #define pii pair<ll,ll>
 #define rep(i,st,en) for(ll i=st;i<en;i++)
 #define vi vector<ll>
 #define vii vector<pii>
 #define all(x) x.begin(),x.end()
 #define rall(x) x.rbegin(),x.rend()
 #define eb emplace_back
 #define yes cout<<"YES"<<endl; return;
 #define no cout<<"NO"<<endl; return;
 #define flus fflush(stdout);
 
 #define fin cerr<<endl;
 #define ff first
 #define ss second
 #define np next_permutation
 #define inf 1e18
 #define mod 1000000007
 #define N 200009
 #define PI 3.14159265358979323846
 #define minpq priority_queue <ll, vector<ll>, greater<ll>>
 #define maxpq priority_queue<ll>
 void sout(){
     cout<<endl;
 }
 template <typename T,typename... Types>
 void sout(T var1,Types... var2){
     cout<<var1<<" ";
     sout(var2...);
 }
 
 
 
 #ifndef ONLINE_JUDGE
 #define gin(x) cerr << #x <<" "; _print(x); cerr << endl;
 #else
 #define gin(x)
 #endif
 
 void _print(ll t) {cerr << t;}
 void _print(int t) {cerr << t;}
 void _print(string t) {cerr << t;}
 void _print(char t) {cerr << t;}
 void _print(lld t) {cerr << t;}
 void _print(double t) {cerr << t;}
 void _print(ull t) {cerr << t;}
 
 template <class T, class V> void _print(pair <T, V> p);
 template <class T> void _print(vector <T> v);
 template <class T> void _print(set <T> v);
 template <class T, class V> void _print(map <T, V> v);
 template <class T> void _print(multiset <T> v);
 template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
 template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
 template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
 template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
 template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
 
 map<string , vi > range1;
 map<string , vi > range2;
 
 void extract_from_statements(string statement)
 {
       if(statement[0] == 'S') return ;
       string fir_attri = "";
       bool fir_neg = false;
       int n = statement.size();
       int ind1 = -1;
       for(int i = 0 ; i < n ; i++ )
       {
               if(statement[i] == '-')
                {
                  fir_neg = true;
                  continue;
                }
             if(statement[i] == '>' || statement[i] == ' ' || statement[i] == '<')
              {
                ind1 = i ;
                break;
              }
             fir_attri += statement[i];
       }
       gin(fir_attri)
       int st = -1;
       for(int i = ind1 ; i < n ; i++ )
       {
              if(statement[i] == ',')
                {
                  st = i ;
                  break;
                }
       }
       
       
       bool gtr = false , gtrEq  = false;
       
       if(statement[ind1 + 1] == '=')
       {
          gtrEq = true;
          ind1 += 2;
       }
       else
       {
            gtr = true;
            ind1 += 1;
       }
       string firr = "";
       for(int ii = ind1  ; ii < st ; ii++)
       {
              firr += statement[ii];
       }
       
       while(firr.back() == ' ')firr.pop_back();
       
       reverse(all(firr));
       
      while(firr.back() == ' ')firr.pop_back();
       
        reverse(all(firr));
     
      gin(firr)
       
       bool sec_neg = false;
       int ind2 = -1;
       st++;
      string sec_attri = "";
      while(st < n && statement[st] == ' ')
      {
         st++;
      }
      for(int i = st ; i < n ; i++ )
       {
             
               if(statement[i] == '-')
                {
                  sec_neg = true;
                  continue;
                }
             if(statement[i] == '>' || statement[i] == ' ' || statement[i] == '<')
              {
                ind2 = i ;
                break;
              }
             sec_attri += statement[i];
       }
       gin(sec_attri);
       
       if(gtr)
       {
             ind2++;
       }
       else
       {
           ind2+=2;
       }
      string secc = "";
     
      for(int ii = ind2 ; ii < n ; ii++)
      {
             if(statement[ii] == '-')continue;
             secc += statement[ii];
      }
     
        while(secc.back() == ' ')secc.pop_back();
       
       reverse(all(secc));
       
      while(secc.back() == ' ')secc.pop_back();
      range1[fir_attri].push_back( stoi(firr) );
      range2[fir_attri].push_back( stoi(secc) );
 }
 
 bool find_crt()
 {
        string inp = "";
        ifstream ReadFile("LIinputpolicy.txt");
        getline (ReadFile, inp);


        // gin(inp)
        int n = inp.size();
        bool st = false;
        string firr = "";
        int st_ind = -1;
        for(int i = 0  ; i < n ; i++)
        {
              if(inp[i] == '+')
                {
                   st_ind = i ;
                  break;
                }
              if(st) firr += inp[i] ;
              if(inp[i] == '-')
              {
                  continue;
              }
              if(inp[i] == '(')
              {
                  st = true;
              }
        }
        while(firr.back() == ' ') firr.pop_back();
        reverse(all(firr));
        while(firr.back() == ' ') firr.pop_back();
        reverse(all(firr));
        gin(firr)
        st_ind++;
       
        string ssec = "";
        for(int i = st_ind ; i < n ;i++)
        {
              if(inp[i] == ')')break;
              ssec += inp[i];
        }
       
         while(ssec.back() == ' ') ssec.pop_back();
        reverse(all(ssec));
        while(ssec.back() == ' ') ssec.pop_back();
        reverse(all(ssec));
       
        gin(ssec)
       
       
       
        int iind = -1;
        for(int i = 0 ; i < n;i++)
        {
            if(inp[i] == '>')
            {
                
                  iind  = i;
                  break;
            }
        }
  
        bool ggrt = false , ggrtEq = false ;
       
        if(inp[iind + 1] == '=')
        {
                ggrtEq = true;
                iind += 2;
        }
        else
        {
           ggrt = true;
           iind++;
        }
        string nnum = "";
        for(int i = iind ; i < n ; i++)
        {
             if(inp[i] == '-')continue;
             nnum += inp[i];
        }
       
          while(nnum.back() == ' ') nnum.pop_back();
        reverse(all(nnum));
        while(nnum.back() == ' ') nnum.pop_back();
        reverse(all(nnum));
       
        gin(nnum)
       
        for(auto &it : range1)
        {
           sort(all(it.ss));
        }
        for(auto &it : range2)
        {
           sort(all(it.ss));
        }
       
        if(inp[0] == '-')
        {
           if(ggrt)
            {
               return ( range2[firr].back() + range2[ssec].back()  < stoi(nnum) );
            }
            else
            {
                 return ( range2[firr].back() + range2[ssec].back()  <= stoi(nnum) );
            }
        }
        else
        {
             if(ggrt)
            {
               return ( range1[firr].back() + range1[ssec].back()  > stoi(nnum) );
            }
            else
            {
                 return ( range1[firr].back() + range1[ssec].back()  >= stoi(nnum) );
            }
        }
        return true;
 }
 
 
 void solve(){
  vector<string>statements;
 
 
 
  string myText;
 
  ifstream MyReadFile("LIinputstates.txt");

    while (getline (MyReadFile, myText)) {
      statements.push_back(myText);
      }
      for(auto it : statements)
      {
         extract_from_statements(it);
      }
      gin(range1)
      gin(range2)
      // gin(statements)
     
      if(  find_crt() )
      {
            cout<<"SAT"<<endl;
      }
      else
      {
           cout<<"UNSAT"<<endl;
      }
     
   
 }
 
int main() {
    // Input in line 319 states and line 187 policy
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Redirect output to a file
    #ifndef ONLINE_JUDGE
    freopen("LIpolicyoutput.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif

    solve();

    return 0;
}