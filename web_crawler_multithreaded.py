from typing import List
from queue import Queue
import threading

class Solution:
    def crawl(self, startUrl: str, htmlParser: 'HtmlParser') -> List[str]:
        host = startUrl.split('/')[2]

        q = Queue()
        q.put(startUrl)

        visited = set([startUrl])
        visited_lock = threading.Lock()

        def worker():
            while True:
                url = q.get()
                if url is None:
                    q.task_done()
                    return

                for nxt in htmlParser.getUrls(url):
                    if nxt.split('/')[2] != host:
                        continue
                    with visited_lock:
                        if nxt in visited:
                            continue
                        visited.add(nxt)
                    q.put(nxt)

                q.task_done()

        # Start a small pool
        num_threads = 4
        threads = [threading.Thread(target=worker) for _ in range(num_threads)]
        for t in threads:
            t.start()

        # Wait until all reachable URLs are processed
        q.join()

        # Stop workers
        for _ in range(num_threads):
            q.put(None)
        for t in threads:
            t.join()

        return list(visited)
