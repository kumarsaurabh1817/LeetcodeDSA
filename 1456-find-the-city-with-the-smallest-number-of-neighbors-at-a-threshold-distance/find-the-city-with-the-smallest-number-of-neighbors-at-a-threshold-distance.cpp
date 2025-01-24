class Solution {
public:
    int GetTheCity(int N,vector<vector<int>> &Edges,int Limit){
        vector<vector<int>> DistanceAdjMatrix(N,vector<int>(N,1e9));
        for(auto &Edge:Edges){
            int U=Edge[0];
            int V=Edge[1];
            int Wt=Edge[2];
            DistanceAdjMatrix[U][V]=Wt;
            DistanceAdjMatrix[V][U]=Wt;
        }
        for(int i=0;i<N;i++){
            DistanceAdjMatrix[i][i]=0;
        }
        for(int k=0;k<N;k++){
            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    DistanceAdjMatrix[i][j]=min(DistanceAdjMatrix[i][j],DistanceAdjMatrix[i][k]+DistanceAdjMatrix[k][j]);
                }
            }
        }
        int CountMin=N+1;
        int CityIndex=-1;
        for(int i=0;i<N;i++){
            int Count=0;
            for(int j=0;j<N;j++){
                if(j != i && DistanceAdjMatrix[i][j] <= Limit){
                    Count++;
                }
            }
            if(Count < CountMin){
                CountMin=Count;
                CityIndex=i;
            }
            else if(Count == CountMin){
                CityIndex=i;
            }
        }
        return CityIndex;
    }
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        return GetTheCity(n,edges,distanceThreshold);
    }
};