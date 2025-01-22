class Solution {
public:
    int GetCheapestFlight(int Source,int Destination,int k,unordered_map<int,list<pair<int,int>>> &AdjList,int N){
        vector<int> Cost(N,INT_MAX);
        Cost[Source]=0;
        queue<pair<int,int>> q;
        q.push({Source,0});
        int steps=0;
        while(!q.empty() && steps <= k){
            int size=q.size();
            for(int i=0;i<size;i++){
                pair<int,int> CurrentPair=q.front();
                q.pop();
                int CurrentNode=CurrentPair.first;
                int CurrentCost=CurrentPair.second;

                for(auto &AdjNodeWeightPair:AdjList[CurrentNode]){
                    int AdjNode=AdjNodeWeightPair.first;
                    int AdjNodeWeight=AdjNodeWeightPair.second;

                    if(Cost[CurrentNode]!=INT_MAX && CurrentCost+AdjNodeWeight < Cost[AdjNode]){
                        Cost[AdjNode]=CurrentCost +AdjNodeWeight;
                        q.push({AdjNode,Cost[AdjNode]});
                    }
                }
            }
            steps++; 
        }
        return Cost[Destination]==INT_MAX ? -1 : Cost[Destination];
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int,list<pair<int,int>>> AdjList;
        for(int i=0;i<flights.size();i++){
            int A = flights[i][0];
            int B = flights[i][1];
            int Cost = flights[i][2];
            AdjList[A].push_back({B,Cost});
        }
        return GetCheapestFlight(src,dst,k,AdjList,n);
    }
};