#include<bits/stdc++.h>
using namespace std;

int const N = 101;
struct node
{
    int dur,left,right;

}arr[N];

vector <int> V[N],V2[N],ans,path;
int color[N];
int color2[N];
int mx;

int cnt =1;
void DFS(int u)
{
    color[u] = 1;
    int n = V[u].size();
    for(int i=n-1;i>=0;i--)
    {
        int v = V[u][i];
        if(color[v]==0)
            DFS(v);
    }
    ans.push_back(u);
}

void topologicalSort(int n)
{
    ans.clear();
    for(int i=n;i>=1;i--)
    {
        if(color[i]==0)
            DFS(i);
    }
    reverse(ans.begin(),ans.end());
}

void DFS2(int u)
{
    color2[u] = 1;
    path.push_back(u);
    if(arr[u].right==mx)
    {
        cout<<"Path "<<cnt++<<": ";
        for(int j =0;j<path.size();j++)
            cout<<"T"<<path[j]<<" ";
        cout<<endl;
    }

    for(int i=0;i<V[u].size();i++)
    {
        int v = V[u][i];
        if(color2[v]==0 && arr[v].right== arr[v].left )
        {
             DFS2(v);
        }
    }
    path.pop_back();
}

int main()

{
    //input
    int n,E;
    cin>>n>>E;

    for( int i=0;i<E;i++)
    {
        int u,v;
        cin>>u>>v;
        V[u].push_back(v);
        V2[v].push_back(u);
    }

    for(int i=1;i<=n;i++)
    {
        cin>>arr[i].dur;
    }

    //sort //optional // for printing lexicographically smallest
    for(int i=1;i<=n;i++)
    {
        sort(V[i].begin(),V[i].end());
    }

    //top sort
    topologicalSort(n);

    //calculate left
    for(int i=0;i<n;i++)
    {
        int maax = 0;
        int j = ans[i];
        for(int k = 0;k<V2[j].size();k++)
        {
            maax = max(arr[V2[j][k]].left,maax);
        }
        arr[j].left = maax+arr[j].dur;
    }

    //calculate right
    for(int i=n-1;i>=0;i--)
    {
        int miin = INT_MAX;
        int j = ans[i];
        for(int k = 0;k<V[j].size();k++)
        {
            miin = min(arr[V[j][k]].right-arr[V[j][k]].dur,miin);
        }

        arr[j].right = miin;
        if(arr[j].right==INT_MAX)
            arr[j].right = arr[j].left;

        mx= max(arr[j].right,mx);
    }

    //output
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        int j = ans[i];
        cout<<"T"<<ans[i]<<" "<<arr[j].dur<<endl;
        cout<<arr[j].left<<" "<<arr[j].right<<endl;
        cout<<endl;
    }

    //path print
    for(int i=0;i<n;i++)
    {
        int j = ans[i];
        memset(color2,0,sizeof(color2));
        path.clear();
        if(arr[j].right== arr[j].left && V2[j].size()==0)
           DFS2(j);
    }

    return 0;
}

/*
12
15
1 2
2 3
2 6
3 4
4 7
5 6
6 7
6 8
6 9
7 10
8 10
9 10
6 11
10 12
11 12
7
12
5
10
5
6
12
10
15
20
10
15
*/




