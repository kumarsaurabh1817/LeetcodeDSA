class Solution {
public:
    bool isValid(int newX,int newY,int M,int N){
        return ((newX >= 0 && newX < M) && (newY >= 0 && newY < N));
    }
    int GetShortestPath(int srcx,int srcy,int destx,int desty,vector<vector<int>> &Grid){
        int M=Grid.size();
        int N=Grid[0].size();
        vector<vector<int>> distance(M,vector<int> (N,INT_MAX));
        distance[srcx][srcy]=0;
        queue<pair<int,pair<int,int>>> q;
        q.push({0,{srcx,srcy}});
        int answer=0;
        vector<vector<int>> directions={{0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
        while(!q.empty()){
            pair<int,pair<int,int>> CurrentPair=q.front();
            q.pop();
            int currdist=CurrentPair.first;
            int currX=CurrentPair.second.first;
            int currY=CurrentPair.second.second;

            if(currX==destx && currY==desty){
                answer=currdist;
                break;
            }
            for(int index=0;index<8;index++){
                int newX=currX+directions[index][0];
                int newY=currY+directions[index][1];

                if(isValid(newX,newY,M,N) && Grid[newX][newY]==0){
                    if(distance[currX][currY] + 1 < distance[newX][newY]){
                        distance[newX][newY]=distance[currX][currY] + 1;
                        q.push({distance[newX][newY],{newX,newY}});
                    }
                }
            }
        }
        if(distance[destx][desty]==INT_MAX){
            return -1;
        }
        return answer+1;
    }
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int M=grid.size();
        int N=grid[0].size();
        if(grid[0][0]==1 || grid[M-1][N-1]==1){
            return -1;
        }
        return GetShortestPath(0,0,M-1,N-1,grid);
    }
};