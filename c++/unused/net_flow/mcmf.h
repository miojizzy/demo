
class MCMF{
public:
    static const int MAX_POINT_CNT;
    static const int MAX_EDGE_CNT;

    struct EdgeNode{
        int next, to, flow, cost;
    };
    typedef struct EdgeNode Edge;

    void init();

    void get_result();

private:
    bool spfa();
    void mcmf();
    int n, m;
//    int point2edge_list[MAX_POINT_CNT];
    int head[MAX_POINT_CNT];
    Edge edges[MAX_EDGE_CNT];

    int last_point[MAX_POINT_CNT];
    int last_edge[MAX_POINT_CNT];
    int flow[MAX_POINT_CNT];
    int cost[MAX_POINT_CNT];
    int vis[MAX_POINT_CNT];
    Queue<int> q;
    

};

