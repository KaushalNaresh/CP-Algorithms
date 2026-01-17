import heapq

def keth_smallest(arr, k, m):

    pq = []
    heapq.heapify(pq)

    if len(arr) <= m:
        i = 0
        for numb in arr:
            heapq.heappush((numb, i), pq)
            i += 1
        return [pq[-1]]
    
    for i in range(len(arr)):
        heapq.heappush((arr[i], i))
        if i == m-1:
            break
    
    lptr = 0, rptr = m-1

    while rptr < len(arr):
        count = 0

        while count < k-1 and pq[-1]:

