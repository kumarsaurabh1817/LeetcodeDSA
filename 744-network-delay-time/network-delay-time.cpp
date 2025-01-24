class Solution {
public:
    int GetMinTime(int StartNode,int N,unordered_map<int,vector<pair<int,int>>> &AdjList){
        vector<int> Time(N+1,INT_MAX);
        Time[StartNode]=0;
        Time[0]=-1;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,StartNode});

        while(!pq.empty()){
            pair<int,int> CurrentPair=pq.top();
            pq.pop();
            int CurrentTime=CurrentPair.first;
            int CurrentNode=CurrentPair.second;

            for(auto AdjNodeWeightPair:AdjList[CurrentNode]){
                int AdjNode=AdjNodeWeightPair.first;
                int AdjNodeWeight=AdjNodeWeightPair.second;

                if(CurrentTime+AdjNodeWeight < Time[AdjNode]){
                    Time[AdjNode]=CurrentTime+AdjNodeWeight;
                    pq.push({Time[AdjNode],AdjNode});
                }
            }
        }
        int MinTime=0;
        for(int i=1;i<N+1;i++){
            // if(Time[i]==INT_MAX){
            //     return -1;
            // }
            MinTime=max(Time[i],MinTime);
        }
        return MinTime == INT_MAX ? -1 : MinTime;
    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int,vector<pair<int,int>>> AdjList;
        for(int i=0;i<times.size();i++){
            vector<int> &Current=times[i];
            int Source=Current[0];
            int Target=Current[1];
            int TimeTaken=Current[2];
            AdjList[Source].push_back({Target,TimeTaken});
        }
        return GetMinTime(k,n,AdjList);
    }
};