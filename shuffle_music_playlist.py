from collections import defaultdict
import heapq

class Song:

    def __init__(self, name, artist):
        self.name = name
        self.artist = artist

class Playlist:

    def __init__(self):
        self.playlist = []
        self.freqMap = defaultdict(list)

    def addSong(self, song: Song) -> None:
        self.playlist.append(song)
        self.freqMap[song.artist].append(song)

    def _shuffle(self) -> list[Song]:
        
        # No adjacent song should belong to same artist
        pq = []

        for k, v in self.freqMap.items():
            heapq.heappush(pq, [-len(v), k]) # max heap [count left, artist]
        
        prev_artist = None
        ans = []
        while pq:
            top_count, top_artist = heapq.heappop(pq)
            top_count += 1

            ans.append(self.freqMap[top_artist][-1])
            self.freqMap[top_artist].pop()

            if prev_artist:
                heapq.heappush(pq, [-len(self.freqMap[prev_artist]), prev_artist])

            if top_count:
                prev_artist = top_artist
            else:
                prev_artist = None
        
        if prev_artist and len(self.freqMap[prev_artist]) > 0:
            return []
        elif prev_artist:
            ans.append(self.freqMap[prev_artist][-1])
            return ans
        else:
            return ans


def print_playlist(label, songs):
    print(f"\n{label}")
    if not songs:
        print("Result: [] (impossible or empty)")
        return
    print("Result:", ", ".join([f"[{s.name} {s.artist}]" for s in songs]))

def verify_no_adjacent_same_artist(songs):
    for i in range(1, len(songs)):
        if songs[i].artist == songs[i-1].artist:
            return False
    return True

def run_case(case_name, song_tuples):
    pl = Playlist()
    for name, artist in song_tuples:
        pl.addSong(Song(name, artist))

    ans = pl._shuffle()
    print_playlist(case_name, ans)

    if ans:
        ok = verify_no_adjacent_same_artist(ans)
        print("No-adjacent constraint satisfied:", ok)
    else:
        print("No-adjacent constraint satisfied: N/A (no arrangement returned)")


# ------------------------------------------------------------
# Test Case 1: Empty playlist
run_case(
    "TC1: Empty playlist",
    []
)

# Test Case 2: Single song
run_case(
    "TC2: Single song",
    [("s1", "A")]
)

# Test Case 3: All unique artists (always possible)
run_case(
    "TC3: All unique artists",
    [("s1", "A"), ("s2", "B"), ("s3", "C"), ("s4", "D")]
)

# Test Case 4: Balanced duplicates (possible)
# A:2, B:2
run_case(
    "TC4: Balanced duplicates (A:2, B:2)",
    [("a1", "A"), ("a2", "A"), ("b1", "B"), ("b2", "B")]
)

# Test Case 5: One artist slightly more frequent but still possible
# A:2, B:1, C:1  => max_count=2, N=4, ceil(N/2)=2 (possible)
run_case(
    "TC5: Slightly dominant artist but possible (A:2, B:1, C:1)",
    [("a1", "A"), ("a2", "A"), ("b1", "B"), ("c1", "C")]
)

# Test Case 6: Dominant artist makes it impossible
# A:3, B:1 => max_count=3, N=4, ceil(N/2)=2 (impossible)
run_case(
    "TC6: Impossible (A:3, B:1)",
    [("a1", "A"), ("a2", "A"), ("a3", "A"), ("b1", "B")]
)

# Test Case 7: Larger feasible mix
# A:3, B:2, C:2, D:1 => N=8, ceil(N/2)=4, max_count=3 (possible)
run_case(
    "TC7: Larger feasible mix (A:3, B:2, C:2, D:1)",
    [("a1", "A"), ("a2", "A"), ("a3", "A"),
     ("b1", "B"), ("b2", "B"),
     ("c1", "C"), ("c2", "C"),
     ("d1", "D")]
)

# Test Case 8: Exactly at the feasibility boundary
# A:4, B:3, C:1 => N=8, ceil(N/2)=4, max_count=4 (possible boundary)
run_case(
    "TC8: Boundary feasible (A:4, B:3, C:1)",
    [("a1", "A"), ("a2", "A"), ("a3", "A"), ("a4", "A"),
     ("b1", "B"), ("b2", "B"), ("b3", "B"),
     ("c1", "C")]
)
