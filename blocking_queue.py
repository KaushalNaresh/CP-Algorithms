from threading import Condition, Lock, Thread
from typing import Callable

class BlockingQueue:

    def __init__(self, capacity):

        self._items = []
        self._cap = capacity
        self._closed = False

        self._lock = Lock()
        self._not_full = Condition(self._lock)
        self._not_empty = Condition(self._lock)

    def get(self):

        with self._not_empty:

            while not self._items:
                self._not_empty.wait()
            
            item = self._items.pop(0)
            self._not_full.notify()

            return item
        
    def put(self, x):

        with self._not_full:

            while len(self._items) == self._cap:
                self._not_full.wait()
            
            self._items.append(x)
            self._not_empty.notify()

        return None
    
    def close(self):
        with self._lock:
            self._closed = True
            self._not_empty.notify_all()
            self._not_full.notify_all()
    

class ThreadingPool:

    def __init__(self, num_threads):

        self.n = num_threads
        self._queue = BlockingQueue()
        self._lock = Lock()
        self._stop = False

        self._threads = [Thread(target=self._worker) for _ in num_threads]

        for thread in self._threads:
            thread.start()

    def sumbit(self, job: Callable[[], None]) -> bool:

        with self._lock:
            if self._stop:
                return False
            self._queue.put(job)
            return True

    def _worker(self) -> None:

        while True:

            job = self._queue.get()

            if not job:
                return None
            
            with self._lock:
                if self._stop:
                    continue 
            
            try:
                job()
            except Exception as ex:

                with self._lock:
                    if not self._stop:
                        self._stop = True
                        self._queue.close()
    
    def shutdown(self):

        with self._lock:
            self._stop = True
        self._queue.close()

        for t in self._threads:
            t.join()



def run_tasks(getDependentTasks, num_threads: int = 4) -> None:

    threadPool = ThreadingPool(num_threads=num_threads)

    roots = getDependentTasks(None)
    graph = {}
    in_deg = {}
    seen = set()
    queue = list(roots)

    for r in roots:
        in_deg[r] = 0

    ## Graph discovery
    while queue:

        node = queue.pop(0)
        if node in seen:
            continue

        seen.add(node)
        children = list(getDependentTasks(node))

        graph[node] = children

        for child in children:
            if child in in_deg:
                in_deg[child] += 1
            queue.append(child)

    total= len(seen)

    if total == 0:
        threadPool.shutdown()

    lock = Lock()
    done_cv = Condition(lock)
    completed = 0

    def submit_task(task):

        def job():
            nonlocal completed
            task.doWork()

            with done_cv:
                completed += 1
                for child in graph[task]:
                    in_deg[child] -= 1
                    if in_deg[child] == 0:
                        submit_task(child)
                done_cv.notify_all()
        threadPool.submit(job)

    with done_cv:
        for t, d in in_deg.items():
            if d == 0:
                submit_task(t)
        
        if completed < total:
            done_cv.wait()

    threadPool.shutdown()

