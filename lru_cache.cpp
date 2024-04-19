class node{
    public:
	int key, val;
	node* next, *prev;
	node(int key, int val){
        this->key = key;
        this->val = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};



class LRUCache {
public:

    node *head, *tail;
	unordered_map<int, node*> map;
	int capacity;

    LRUCache(int capacity) {
        this->capacity = capacity;
		this->head = nullptr;
		this->tail = nullptr;
    }

    node* deleteNode(node* curr){
        node *prev_node = nullptr, *next_node = nullptr;
        if(curr->prev != nullptr)
            prev_node = curr->prev;
        if(curr->next != nullptr)
            next_node = curr->next;
        
        curr->next = nullptr;
        curr->prev = nullptr;

        if(prev_node != nullptr)
            prev_node->next = next_node;
        else
            this->head = next_node;

        if(next_node != nullptr)
            next_node->prev = prev_node;
        else
            this->tail = prev_node;

        return curr;
    }

    void updateHead(node* curr){
        if(this->head == nullptr){
            this->head = curr;
            this->tail = curr;
        }
        else{
            node* temp = this->head;
            this->head = curr;
            curr->next = temp;
            if(temp)
                temp->prev = this->head;
        }
    }
    
    int get(int key) {
        if(this->map.find(key) == this->map.end()){
            return -1;
        }
        else{
            node* delete_node = this->deleteNode(this->map[key]);
            this->updateHead(delete_node);
            return delete_node->val;
        }

    }
    
    void put(int key, int val) {
        if(this->map.size() < this->capacity){
            if(map.find(key) == this->map.end()){
                node* new_node = new node(key, val);
                map[key] = new_node;
                this->updateHead(new_node);
            }
            else{
                node* deleted_node = this->deleteNode(this->map[key]);
                deleted_node->val = val;
                this->updateHead(deleted_node);
            }
        }
        else{
            if(this->map.find(key) == this->map.end()){
                node* deleted_node = this->deleteNode(this->tail);
                this->map.erase(deleted_node->key);
                node* new_node = new node(key, val);
                map[key] = new_node;
                updateHead(new_node);
            }
            else{
                node* deleted_node = this->deleteNode(this->map[key]);
                deleted_node->val = val;
                updateHead(deleted_node);
            }	
        }
    }
};