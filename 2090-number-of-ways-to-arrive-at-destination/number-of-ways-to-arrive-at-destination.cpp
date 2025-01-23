class Solution {
public:
    const int MOD = 1e9+7;
    int GetCountPaths(int N,int Source,int Destination,unordered_map<int,vector<pair<int,int>>> &AdjList){
        vector<int> Ways(N,0); 
        Ways[Source]=1;
        vector<long long> Distance(N,LLONG_MAX);
        Distance[Source]=0;
        priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
        pq.push({0,Source});

        while(!pq.empty()){
            pair<long long,int> CurrentPair=pq.top();
            pq.pop();
            long long CurrentDistance=CurrentPair.first;
            int CurrentNode=CurrentPair.second;

            for(auto &AdjNodeWeightPair:AdjList[CurrentNode]){
                int AdjNode=AdjNodeWeightPair.first;
                long long AdjNodeWeight=AdjNodeWeightPair.second;

                if(CurrentDistance + AdjNodeWeight < Distance[AdjNode]){
                    Distance[AdjNode]=CurrentDistance + AdjNodeWeight;
                    pq.push({Distance[AdjNode],AdjNode});
                    Ways[AdjNode]=Ways[CurrentNode] % MOD;
                }
                else if(CurrentDistance + AdjNodeWeight == Distance[AdjNode]){
                    Ways[AdjNode]=(Ways[AdjNode]+Ways[CurrentNode]) % MOD;
                }
            }
        }
        return (Ways[Destination] % MOD) % MOD;
    }
    int countPaths(int n, vector<vector<int>>& roads) {
        unordered_map<int,vector<pair<int,int>>> AdjList;
        for(auto &Road:roads){
            int U = Road[0];
            int V = Road[1];
            int Time = Road[2];
            AdjList[U].push_back({V,Time});
            AdjList[V].push_back({U,Time});
        }
        int Source=0;
        int Destination=n-1;
        return GetCountPaths(n,Source,Destination,AdjList);
    }
};