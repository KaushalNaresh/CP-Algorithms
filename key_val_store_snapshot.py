class KeyValurStore:

    def __init__(self):
        self.store = {}
        self.version = 0

    def get(self, key, snapshot_id):
        
        if key not in self.store:
            return None
        
        history = self.store[key]

        lb, ub = 0, len(history)
        while lb < ub:

            mid = (lb+ub)//2
            if self.store[mid][0] == snapshot_id:
                lb = mid+1
            else:
                ub = mid

        return self.store[lb-1][1]

    def takeSnapshot(self):
        
        snapshot_id = self.version
        self.version += 1

        return snapshot_id

    def put(self, key, value):
        
        if key not in self.store:
            self.store[key] = [[self.version, value]]
        
        self.store[key].append([self.version, value])
        return None

    def deleteSnapshot(self, snapshot_id):
        pass