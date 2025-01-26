class Disjoint_Set{
    public:
    vector<int> parent;
    vector<int> rank;
    vector<int> size;

    Disjoint_Set(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
        }
    }
    int Find_Ultimate_Parent(int Node){
        if(Node==parent[Node]){
            return Node;
        }
        else{
            parent[Node]=Find_Ultimate_Parent(parent[Node]);
            return parent[Node];
        }
    }
    void Union_By_Rank(int u,int v){
        int ULP_u=Find_Ultimate_Parent(u);
        int ULP_v=Find_Ultimate_Parent(v);
        if(ULP_u==ULP_v){
            return;
        }
        if(rank[ULP_u]<rank[ULP_v]){
            parent[ULP_u]=ULP_v;
        }
        else if(rank[ULP_u]>rank[ULP_v]){
            parent[ULP_v]=ULP_u;
        }
        else{
            parent[ULP_v]=ULP_u;
            rank[ULP_u]++;
        }
    }
    void Union_By_Size(int u,int v){
        int ULP_u=Find_Ultimate_Parent(u);
        int ULP_v=Find_Ultimate_Parent(v);
        if(ULP_u==ULP_v){
            return;
        }
        if(size[ULP_u]<size[ULP_v]){
            parent[ULP_u]=ULP_v;
            size[ULP_v]+=size[ULP_u];
        }
        else{
            parent[ULP_v]=ULP_u;
            size[ULP_u]+=size[ULP_v];
        }
    }
};
class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        Disjoint_Set ds(n);
        for(int i=0;i<edges.size();i++){
            int A = edges[i][0];
            int B = edges[i][1];
            if(ds.Find_Ultimate_Parent(A) != ds.Find_Ultimate_Parent(B)){
                ds.Union_By_Size(A,B);
            }
        }
        vector<int> temp;
        for(int i=0;i<n;i++){
            if(ds.Find_Ultimate_Parent(i)==i){
                temp.push_back(ds.size[i]);
            }
        }
        long long answer=0;
        for(int i=0;i<temp.size()-1;i++){
            answer += ((long long)temp[i] * ((long long)n-(long long)temp[i]));
            n-=temp[i];
        }
        return answer;
    }
};