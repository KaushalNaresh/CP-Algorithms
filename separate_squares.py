class Solution:

    def areaBelow(self, mid, squares):

        area_below = 0.0

        for _, y, l in squares:

            if y >= mid:
                continue
            if y+l <= mid:
                area_below += l*l
            else:
                area_below += (mid-y)*l
        
        return area_below
    
    
    def separateSquares(self, squares):

        lo, hi, total = float("inf"), float("-inf"), 0.0

        for _, y, l in squares:
            lo = min(lo, y)
            hi = max(hi, y+l)
            total += l*l

        for i in range(80):

            mid = (lo + hi)/2.0

            if self.areaBelow(mid, squares) < total/2.0:
                lo = mid
            else:
                hi = mid

        return hi

def run_tests(sol):
    tests = [
        ("single fractional", [[0,0,1]], 0.5),
        ("two stacked", [[0,0,1],[0,1,1]], 1.0),
        ("plateau gap", [[0,0,2],[0,10,2]], 2.0),
        ("mixed sizes", [[0,0,3],[0,3,1]], 5.0/3.0),
        ("upper square fractional", [[0,0,1],[0,5,2]], 5.75),
        ("duplicate overlap", [[0,0,2],[0,0,2],[0,0,2]], 1.0),
        ("small span", [[0,0.2,0.4]], 0.4),
        ("boundary top", [[0,0,2],[0,2,2]], 2.0),
    ]

    for name, squares, exp in tests:
        try:
            out = sol.separateSquares(squares)
        except Exception as e:
            out = f"EXCEPTION: {e}"
        print(name, "expected:", exp, "got:", out)

run_tests(Solution())
