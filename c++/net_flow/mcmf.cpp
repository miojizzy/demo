#include "mcmf.h"

bool MCMF::spfa(int source, int target){
    memset(vis, 0, sizeof(vis)); // 初始化0
    memset(flow,0x7f, sizeof(flow));//初始化为最大值 因为整条链路的流量由它的最小值来确定
    memset(cost, 0x7f, sizeof(cost));//初始化为最大值 因为要求的是最小的消耗
    vis[source] = 1;
    cost[source] = 0;
    last_point[target] = -1;

    while(!q.empty()) q.pop_front();
    q.push_back(source);

    while(!q.empty()){
        int now = q.pop_front();
        vis[now] = 0;
        for(int i = head[now]; i!=-1; i = edges[i].next){
            int from = now;
            int to = edgeds[i].to;
            if(edges[i].flow > 0 && cost[to] > cost[from]+edges[i].cost){
                cost[to] = cost[from]+edges[i].cost;
                last_point[to] = from;
                last_edge[to] = i;
                flow[i] = min(flow[from], edges[i].flow)
                if(vis[to] != 1){
                    vis[to] = 1;
                    q.push_back(to);
                }
            }
        }
    }
    return last_point[target] != -1;
}

void MCMF::mcmf(){
    while(!q.empty()) q.pop_front();
    memset(vis, 0, sizeof(vis));
    
    int now = target; 
    while(spfa(source, target)){
        edges[last_edge[now]].flow -= flow[now];
        edges[last_edge[now]^-1].flow += flow[now];
        now = last_point[now];
    }
}


void MCMF::init(vector<vector<int> >& edge_info){
    for(int i=0; i<edge_info.size(); ++i){

    }

    
}

void MCMF::get_result(){

}
