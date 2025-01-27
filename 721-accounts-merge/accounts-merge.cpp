class Disjoint_Set{
  public:
  vector<int> rank;
  vector<int> parent;
  vector<int> size;

  Disjoint_Set(int n){
    rank.resize(n+1,0);
    size.resize(n+1,1);
    parent.resize(n+1);
    for(int i=0;i<=n;i++){
      parent[i]=i;
    }
  }

  int Find_Ultimate_Parent(int node){
    if(node==parent[node]){
      return node;
    }
    else{
      return parent[node]=Find_Ultimate_Parent(parent[node]);
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
    vector<vector<string>> MergeAccountDetails(vector<vector<string>> &Accounts){
        const int N=Accounts.size();
        Disjoint_Set ds(N);
        unordered_map<string,int> HashMap;
        for(int index=0;index<Accounts.size();index++){
            vector<string> &CurrentAccount=Accounts[index];
            for(int i=1;i<CurrentAccount.size();i++){
                string Email=CurrentAccount[i];
                if(HashMap.find(Email) == HashMap.end()){
                    HashMap[Email]=index;
                }
                else{
                    ds.Union_By_Size(HashMap[Email],index);
                }
            }
        }
        vector<string> MergedMails [N];
        for(auto Current:HashMap){
            string Email=Current.first;
            int Node=Current.second;
            int ULPNode=ds.Find_Ultimate_Parent(Node);
            MergedMails[ULPNode].push_back(Email);
        }

        vector<vector<string>> answer;
        for(int i=0;i<N;i++){
            if(MergedMails[i].empty()){
                continue;
            }
            sort(MergedMails[i].begin(),MergedMails[i].end());
            vector<string> temp;
            temp.push_back(Accounts[i][0]);
            for(int index=0;index<MergedMails[i].size();index++){
                temp.push_back(MergedMails[i][index]);
            }
            answer.push_back(temp);
        }

        return answer;
    }
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        return MergeAccountDetails(accounts);
    }
};