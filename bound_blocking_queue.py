from threading import Semaphore
from collections import deque

class BlockingQueue:

    def __init__(self, n):
        self.queue = deque()
        self.n = n
        self.empty_space = Semaphore(n)
        self.filled_space = Semaphore(0)

    def enqueue(self, element):
        
        self.empty_space.acquire()
        self.queue.append(element)
        self.filled_space.release()

    def dequeue(self):

        self.filled_space.acquire()
        self.queue.popleft()
        self.empty_space.release()
        

    def size(self):
        
        return len(self.queue)

