#include<bits/stdc++.h>
using namespace std;string t;main(){int n;cin>>t>>n;int a[n];puts(t==string(t.rbegin(),t.rend())?"Y":"N");for(int&v:a)cin>>v;sort(a,a+n);for(int v:a)cout<<v<<' ';}