import heapq

class GPUCredits:

    def __init__(self):
        self.user_credits = {}

    def grant(self, user: str, t: int, amount: int, expiry_time: int):

        self._remove_expired_times(t)
        
        heap = self.user_credits[user]
        heapq.heappush(heap, (expiry_time, amount))

    def use(self, user: str, amount: int, t: int):

        self._remove_expired_times(t, user)

        heap = self.user_credits[user]

        while heap or amount > 0:
            if heap[0][1] <= amount:
                amount -= heap[0][1]
                heapq.heappop(heap)
            else:
                left_over = heap[0][1] - amount
                amount = 0
                heapq.heappush(heap, (heap[0][0], left_over))

    def transfer(self, from_user, to_user, amount, t):

        self._remove_expired_times(t, from_user)

        from_user_heap = self.user_credits[from_user]
        to_user_heap = self.user_credits[to_user]

        while from_user_heap and amount > 0:
            timestamp, curr_amount = heapq.heappop(from_user_heap)
            if curr_amount < amount:
                amount -= curr_amount
                heapq.heappush(to_user_heap, (timestamp, curr_amount))
            else:
                leftover = curr_amount-amount
                heapq.heappush(from_user_heap, leftover)
                heapq.heappush(to_user_heap, (timestamp, amount))
                amount = 0
            

    def get_balance(self, user: str, t: int):

        self._remove_expired_times(t, user)

        return sum([block[1] for block in self.user_credits[user]])

    def _remove_expired_times(self, t: int, user: str):

        heap = self.user_credits[user]

        while heap and heap[0][0] < t:
            heapq.heappop(heap)





import heapq

class GPUCredits:

    def __init__(self):
        self.user_credits = {}

    def grant(self, user: str, t: int, amount: int, expiry_time: int):
        if user not in self.user_credits:
            self.user_credits[user] = []

        self._remove_expired_credits(t, user)
        heapq.heappush(self.user_credits[user], (expiry_time, amount))

    def use(self, user: str, amount: int, t: int) -> bool:
        if user not in self.user_credits:
            self.user_credits[user] = []
        
        self._remove_expired_credits(t, user)

        heap = self.user_credits[user]
        total_balance = self.get_balance(user, t)

        if total_balance < amount:
            return False  

        while amount > 0:
            expiry, curr_amount = heapq.heappop(heap)
            if curr_amount <= amount:
                amount -= curr_amount
            else:
                heapq.heappush(heap, (expiry, curr_amount - amount))
                amount = 0
        return True

    def transfer(self, from_user: str, to_user: str, amount: int, t: int) -> bool:
        if from_user not in self.user_credits:
            self.user_credits[from_user] = []

        if to_user not in self.user_credits:
            self.user_credits[to_user] = []

        self._remove_expired_credits(t, from_user)

        from_user_heap = self.user_credits[from_user]
        to_user_heap = self.user_credits[to_user]

        total_balance = self.get_balance(from_user, t)
        if total_balance < amount:
            return False  

        while amount > 0:
            expiry, curr_amount = heapq.heappop(from_user_heap)
            if curr_amount <= amount:
                heapq.heappush(to_user_heap, (expiry, curr_amount))
                amount -= curr_amount
            else:
                heapq.heappush(from_user_heap, (expiry, curr_amount - amount))
                heapq.heappush(to_user_heap, (expiry, amount))
                amount = 0
        return True

    def get_balance(self, user: str, t: int) -> int:
        if user not in self.user_credits:
            self.user_credits[user] = []

        self._remove_expired_credits(t, user)

        return sum(amount for _, amount in self.user_credits[user])

    def _remove_expired_credits(self, t: int, user: str):
        heap = self.user_credits[user]
        while heap and heap[0][0] <= t:
            heapq.heappop(heap)







class TimeMap:

    def __init__(self):
        self.map = {}

    def set(self, key: str, value: str, timestamp: int) -> None:
        if key not in self.map:
            self.map[key] = [[timestamp, value]]
        else:
            self.map[key].append([timestamp, value])

    def get(self, key: str, timestamp: int) -> str:

        if key not in self.map:
            return ""

        values = self.map[key]
        res = -1
        lptr, rptr = 0, len(values)-1

        while lptr <= rptr:
            mid = lptr + (rptr-lptr)//2

            if values[mid][0] <= timestamp:
                res = values[mid][1]
                lptr = mid+1
            else:
                rptr = mid-1

        return res if res != -1 else ""