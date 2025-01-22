class Solution {
public:
    bool isValid(int newX,int newY,int M,int N){
        if((newX >= 0 && newX < M) && (newY >= 0 && newY < N)){
            return true;
        }
        else{
            return false;
        }
    }
    int GetMinimumEffortPath(int srcx,int srcy,int destx,int desty,vector<vector<int>> &Heights){
        int M = Heights.size();
        int N = Heights[0].size();
        vector<vector<int>> Effort(M,vector<int> (N,INT_MAX));
        Effort[srcx][srcy]=0;
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;
        pq.push({0,{srcx,srcy}});
        int answer=0;
        vector<vector<int>> directions={{0,1},{0,-1},{-1,0},{1,0}};
        while(!pq.empty()){
            pair<int,pair<int,int>> CurrentPair=pq.top();
            pq.pop();
            int CurrentEffort=CurrentPair.first;
            int currX=CurrentPair.second.first;
            int currY=CurrentPair.second.second;

            if(currX==destx && currY==desty){
                answer=CurrentEffort;
                break;
            }

            for(int index=0;index<4;index++){
                int newX=currX+directions[index][0];
                int newY=currY+directions[index][1];

                if(isValid(newX,newY,M,N)){
                    int NewEffort = abs(Heights[newX][newY]-Heights[currX][currY]);
                    int Max_NewCurrEffort=max(CurrentEffort,NewEffort);
                    if(Max_NewCurrEffort < Effort[newX][newY]){
                        Effort[newX][newY]=Max_NewCurrEffort;
                        pq.push({Effort[newX][newY],{newX,newY}});
                    }
                }
            }
        }       
        return answer; 
    }
    int minimumEffortPath(vector<vector<int>>& heights) {
        int M = heights.size();
        int N = heights[0].size();
        int srcx=0;
        int srcy=0;
        int destx=M-1;
        int desty=N-1;
        return GetMinimumEffortPath(srcx,srcy,destx,desty,heights);
    }
};