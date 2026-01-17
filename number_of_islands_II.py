class UF:

    def __init__(self, m, n):
        self.parent = [[-1 for j in range(n)] for i in range(m)]
        self.rank = [[1]*n for _ in range(m)]
    
    def union(self, r1, c1, r2, c2):

        root1 = self.find(r1, c1)
        root2 = self.find(r2, c2)
        if root1 == root2: 
            return False
        
        r1r, c1r = root1
        r2r, c2r = root2
        
        if self.rank[r1r][c1r] == self.rank[r2r][c2r]:
            self.parent[r1r][c1r] = root2
            self.rank[r2r][c2r] += 1
        elif self.rank[r1r][c1r] < self.rank[r2r][c2r]:
            self.parent[r1r][c1r] = root2
        elif self.rank[r1r][c1r] > self.rank[r2r][c2r]:
            self.parent[r2r][c2r] = root1
        
        return True

    def find(self, r, c):

        if self.parent[r][c] == [r, c]:
            return [r, c]
        
        self.parent[r][c] = self.find(self.parent[r][c][0], self.parent[r][c][1])
        return self.parent[r][c]

class Solution:

    def findNumberOfIslands(self, m, n, positions) -> list:

        uf = UF(m, n)
        ans = []
        count = 0

        for r, c in positions:
            uf.parent[r][c] = [r, c]
            count += 1
            for neigh_r, neigh_c in [[-1, 0], [0, 1], [1, 0], [0, -1]]:
                n_r, n_c = r+neigh_r, c+neigh_c
                if n_r >= 0 and n_r < m and n_c >= 0 and n_c < n and uf.parent[n_r][n_c] != -1:
                    if uf.union(r, c, n_r, n_c):
                        count -= 1
            
            ans.append(count)

        return ans
    
# Test cases for Number of Islands II (positions added over time)
# Each test is: (m, n, positions, expected_counts)

tests = [
    # 1) Sample
    (3, 3, [[0,0],[0,1],[1,2],[2,1]], [1, 1, 2, 3]),

    # 2) Single cell
    (1, 1, [[0,0]], [1]),

    # 3) Two separate islands then a bridge cell connects them into one
    # after: (0,0)=1, (0,2)=2, (0,1) bridges -> 1
    (1, 3, [[0,0],[0,2],[0,1]], [1, 2, 1]),

    # 4) Four neighbors around center then center connects all (big merge)
    # (0,1)=1, (1,0)=2, (1,2)=3, (2,1)=4, center (1,1) connects all -> 1
    (3, 3, [[0,1],[1,0],[1,2],[2,1],[1,1]], [1, 2, 3, 4, 1]),

    # 5) Line growth that stays one island throughout
    (1, 5, [[0,0],[0,1],[0,2],[0,3],[0,4]], [1, 1, 1, 1, 1]),

    # 6) Diagonal additions never touch (each new one forms a new island)
    (3, 3, [[0,0],[1,1],[2,2]], [1, 2, 3]),

    # 7) Complex merges + duplicates
    # add (0,0)=1
    # add (0,1) connects ->1
    # add (1,2)=2
    # add (1,1) connects to (0,1) and (1,2) ->1
    # add (1,1) duplicate ->1
    # add (2,1) connects ->1
    (3, 3, [[0,0],[0,1],[1,2],[1,1],[1,1],[2,1]], [1, 1, 2, 1, 1, 1]),

    # 8) Two components in a 2x3, then connect via (1,1)
    # (0,0)=1, (0,2)=2, (1,2) connects to (0,2) =>2, (1,1) connects to (1,2) only =>2,
    # (0,1) connects left+right =>1
    (2, 3, [[0,0],[0,2],[1,2],[1,1],[0,1]], [1, 2, 2, 2, 1]),
]

# Optional quick runner (assuming Solution().findNumberOfIslands exists)
def run_tests():
    sol = Solution()
    for idx, (m, n, pos, exp) in enumerate(tests, 1):
        out = sol.findNumberOfIslands(m, n, pos)
        assert out == exp, f"Test {idx} failed: got {out}, expected {exp}"
    print("All tests passed!")

run_tests()

