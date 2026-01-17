"""
Docstring for count_number_of_words_with_given_prefix

Input: str = [ "apk", "app", "apple", "arp", "array" ], pre = "ap" 
Output: 3 
"""

class TrieNode:

    def __init__(self, is_word=False):
        self.is_word = is_word
        self.children = [None for _ in range(26)]
        self.count = 0 ## Stores count of words with this prefix

class Trie:

    def __init__(self):
        self.root = TrieNode()
    
    def add_word(self, word):

        curr_node = self.root

        for char in word:

            if not curr_node.children[ord(char)-ord('a')]:
                curr_node.children[ord(char)-ord('a')] = TrieNode()
            curr_node = curr_node.children[ord(char)-ord('a')]
            curr_node.count += 1
        
        curr_node.is_word = True
    
    def count_words(self, prefix):

        curr_node = self.root

        for char in prefix:
            if curr_node.children[ord(char)-ord('a')]:
                curr_node = curr_node.children[ord(char)-ord('a')]
            else:
                return 0
        
        return curr_node.count


trie = Trie()
words = ["apk", "app", "apple", "arp", "array"]

for word in words:
    trie.add_word(word)

print(trie.count_words("array"))