## Not correct solution I was not supposed to use priority queue

import heapq

def Solution(t, capacity, recharge):

    pq = []
    n = len(capacity)
    curr_time, count = 0, 0

    for i in range(n):
        heapq.heappush(pq, [curr_time, i])

    while t > 0:

        time, idx = heapq.heappop(pq)

        if time > curr_time:
            return -1
        
        t -= capacity[idx]

        if t >= 0:
            count += 1
        
        curr_time += capacity[idx]
        heapq.heappush(pq, [curr_time+recharge[idx], idx])

    return count