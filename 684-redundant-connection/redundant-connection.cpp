class DisjointSet{
    public:
    vector<int> Rank;
    vector<int> Parent;
    vector<int> Size;
    
    DisjointSet(int n){
        Rank.resize(n+1,0);
        Parent.resize(n+1);
        Size.resize(n+1,1);
        for(int i=0;i<n+1;i++){
            Parent[i]=i;
        }
    }

    int FindUltimateParent(int Node){
        if(Node == Parent[Node]){
            return Node;
        }
        Parent[Node]=FindUltimateParent(Parent[Node]);
        return Parent[Node];
    }
    void UnionByRank(int U,int V){
        int ULP_U=FindUltimateParent(U);
        int ULP_V=FindUltimateParent(V);
        if(ULP_U == ULP_V){
            return;
        }
        if(Rank[ULP_U] < Rank[ULP_V]){
            Parent[ULP_U]=ULP_V;
        }
        else if(Rank[ULP_U] > Rank[ULP_V]){
            Parent[ULP_V]=ULP_U;
        }
        else{
            Parent[ULP_V]=ULP_U;
            Rank[ULP_U]++;
        }
    }
    void UnionBySize(int U,int V){
        int ULP_U=FindUltimateParent(U);
        int ULP_V=FindUltimateParent(V);
        if(ULP_U == ULP_V){
            return;
        }
        if(Size[ULP_U] < Size[ULP_V]){
            Parent[ULP_U]=ULP_V;
        }
        else{
            Parent[ULP_V]=ULP_U;
            Size[ULP_U] += Size[ULP_V];
        }
    }
};
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> answer(2);
        int n=edges.size();
        DisjointSet ds(n);
        for(int i=0;i<edges.size();i++){
            int U=edges[i][0];
            int V=edges[i][1];
            if(ds.FindUltimateParent(U)==ds.FindUltimateParent(V)){
                answer[0]=U;
                answer[1]=V;
            }
            else{
                ds.UnionBySize(U,V);
            }
        }
        return answer;
    }
};