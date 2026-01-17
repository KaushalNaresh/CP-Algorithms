from collections import deque

def find_root_bfs(n, edges, colors, pattern):
    """
    colors: list like ["R","B","W",...]
    pattern: list like ["R","B","W","R","B","W"] (period p)
    """
    p = len(pattern)

    g = [[] for _ in range(n)]
    for u, v in edges:
        g[u].append(v)
        g[v].append(u)

    deg = [len(g[i]) for i in range(n)]

    def valid_root(r: int) -> bool:
        # Root must have <= 2 children in rooted orientation
        if deg[r] > 2:
            return False

        dist = [-1] * n
        q = deque([r])
        dist[r] = 0

        while q:
            u = q.popleft()
            # level-color constraint
            if colors[u] != pattern[dist[u] % p]:
                return False

            for v in g[u]:
                if dist[v] == -1:
                    dist[v] = dist[u] + 1
                    q.append(v)

        return True

    for r in range(n):
        if valid_root(r):
            return r
    return -1
