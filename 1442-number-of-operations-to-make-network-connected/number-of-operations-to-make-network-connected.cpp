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
    int makeConnected(int n, vector<vector<int>>& connections) {
        Disjoint_Set ds(n);
        int ExtraEdge=0;
        for(int i=0;i<connections.size();i++){
            int U=connections[i][0];
            int V=connections[i][1];
            if(ds.Find_Ultimate_Parent(U) != ds.Find_Ultimate_Parent(V)){
                ds.Union_By_Size(U,V);
            }
            else{
                ExtraEdge++;
            }
        }
        int count=0;
        for(int i=0;i<n;i++){
            if(ds.Find_Ultimate_Parent(i)==i){
                count++;
            }
        }
        if(ExtraEdge >= count-1){
            return count-1;
        }
        return -1;
    }
};