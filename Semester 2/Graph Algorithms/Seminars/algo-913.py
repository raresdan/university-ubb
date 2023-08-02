import graph
import wgc
import heapq

def bfs1(g, s):
    '''Executes a Breadth-First Search in graph g starting from vertex s.
    Returns a dictionary where the keys are all the accessible vertices from s
    and the value for a vertex x is the shortest walk from s to x as a list of vertices
    '''
    queue = [s]
    walks = {s:[s]}
    while len(queue) != 0 :
        vertex = queue.pop(0)
        for outbound in g.parseNOut(vertex):
            if outbound not in walks:
                walks[outbound] = walks[vertex] + [outbound]
                queue.append(outbound)
        #print(vertex, " ", walks)
    return walks    

def shortest_path1(g, s, t):
    '''Computes the shortest (min length) walk from vertex s to vertex t in graph g.
    Returns the list of vertices along the walk. Returns None if no walk exists.
    '''
    walks = bfs1(g, s)
    if t not in walks.keys():
        return None
    return walks[t]

def min_path_dijkstra(g, cost, s, t):
    '''Computes the min cost walk from s to t in graph g with the costs given in 'cost'.
    'cost' must be a dictionary taking pairs of vertices (x,y) as keys and with the values being the costs.
    Returns the walk as a list of vertices, or None if no path exists.
    '''
    dist = {s:0}
    prev = {s:None}
    priority_q = []
    heapq.heappush(priority_q, (0, s))
    
    while len(priority_q) and t:
        current_distance, current_vertex = heapq.heappop(priority_q)
        if current_vertex == t:
            break
        if current_distance > dist[current_vertex]:
            #print(f'skipping {current_vertex}')
            continue
        
        for neighbour in g.parseNOut(current_vertex):
            if neighbour not in dist.keys() or dist[current_vertex] + cost[(current_vertex, neighbour)] < dist[neighbour]:
                dist[neighbour] = dist[current_vertex] + cost[(current_vertex, neighbour)]
                prev[neighbour] = current_vertex
                heapq.heappush(priority_q, (dist[neighbour], neighbour))
        
        print(f'current vertex: {current_vertex}, distance: {dist}, queue: {priority_q}')
    
    if t not in dist.keys():
        return None
    walk = []
    vertex = t
    while vertex != s:
        walk.append(vertex)
        #for neighbour in g.parseNIn(vertex):
        #    if neighbour in dist.keys() and dist[neighbour] == dist[vertex] - cost[(neighbour, vertex)]:         
        #        vertex = neighbour
        #        break
        vertex = prev[vertex]
                
    walk.append(s)
    walk.reverse()
    return walk
    
def min_path_dp(g, cost, s, t):
    # d[k][x] = cost of min cost walk from s to x of lenght = k
    #     if no such walk exists, then x will not be a key in d[k]
    d = [{x:float('inf') for x in g.parseX()}]
    d[0][s] = 0
    for k in range(1, len(g.parseX())*2):
        curr_dist = d[-1]
        next_dist = {x:float('inf') for x in g.parseX()}
        for x in g.parseX():
            for y in g.parseNIn(x):
                if next_dist[x] > curr_dist[y] + cost[y,x]:
                    next_dist[x] = curr_dist[y] + cost[y,x]
        d.append(next_dist)
    print(d)
    best_k = None
    for k in range(len(d)):
        if best_k is None or d[k][t] < d[best_k][t]:
            best_k = k
    print(f"len={best_k}, cost={d[best_k][t]}")
    walk = []
    while best_k > 0:
        walk.append(t)
        for p in g.parseNIn(t):
            if d[best_k-1][p] + cost[p,t] == d[best_k][t]:
                t = p
                best_k -= 1
                break
    walk.append(s)
    walk.reverse()
    return walk

def shortest1():
    g = graph.create_small_graph(graph.GraphWithInNbh)
    print(shortest_path1(g, 5, 2))

def shortest_wgc():
    g = wgc.WolfGoatCabbageGraph()
    s = g.start()
    t = g.dest()
    print(shortest_path1(g, s, t))

def shortest_big():
    g = graph.create_random_graph(100000, 200000, graph.GraphWithInNbh)
    print(shortest_path1(g, 0, 1))
    walks = bfs1(g, 0)
    print(len(walks))
    max_dist = None
    for v in walks:
        if max_dist is None or max_dist < len(walks[v]):
            max_dist = len(walks[v])
    print(max_dist)

def test_dijkstra():
    g, cost = graph.create_small_graph_with_costs(graph.GraphWithInNbh)
    print(min_path_dijkstra(g, cost, 1, 4))

def test_min_path_dp():
    g, cost = graph.create_small_graph_with_costs(graph.GraphWithInNbh)
    print(min_path_dp(g, cost, 1, 4))

if __name__ == "__main__":
    test_min_path_dp()
