#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#define MAX_LEVEL  10

using namespace std;
struct Node {
    int key;
    int value;
    vector<Node*> next;

    Node(int key, int val,int level) : key(key),value(val), next(level + 1, nullptr) {}
};

class SkipList {
private:
    Node* head;
    Node* tail;
    int currentLevel;

    int randLevel() {
        int level = 0;
        while (rand() % 2 == 0 && level < MAX_LEVEL) {
            level++;
        }
        return level;
    }

public:
    SkipList() : currentLevel(0) {
        head = new Node(-1,-1, MAX_LEVEL);
        tail = new Node(INT_MAX, -1,MAX_LEVEL);

        for (int i = 0; i <= MAX_LEVEL; i++) {
            head->next[i] = tail;
        }
    }

    Node* getHead() {
        return head;
    }

    Node* getTail() {
        return tail;
    }

    void insert(int key,int val) {
        vector<Node*> update(MAX_LEVEL + 1, nullptr);
        Node* current = head;

        for (int i = MAX_LEVEL; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0];
        if (current != nullptr && current->key == key) {
            cout << "Key " << key << " already exists. Skipping insertion." << endl;
            return;
        }

        int level = randLevel();
        if (level > currentLevel)
            currentLevel = level;

        Node* newNode = new Node(key,val, level);

        // Update pointers for all levels
        for (int i = 0; i <= level; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }

    bool search(int key) {
        Node* current = head;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != tail && current->next[i]->key < key) {
                current = current->next[i];
            }
        }

        current = current->next[0];
        return current != tail && current->key == key;
    }

    void remove(int key) {
        vector<Node*> update(currentLevel + 1, nullptr);
        Node* current = head;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->next[i] != tail && current->next[i]->key < key) {
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0];

        if (current != tail && current->key == key) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->next[i] != current)
                    break;
                update[i]->next[i] = current->next[i];
            }

            delete current;

            // Check if levels need to be decreased
            while (currentLevel > 0 && head->next[currentLevel] == tail) {
                currentLevel--;
            }
        }
    }

    void print() {
        for (int i = currentLevel; i >= 0; i--) {
            Node* current = head->next[i];
            cout << "Level " << i << ": ";
            while (current != tail) {
                cout << current->key <<" "<< current ->value<< ", ";
                current = current->next[i];
            }
            cout << '\n';
        }
    }

    ~SkipList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next[0];
            delete temp;
        }
    }
};

class Game {
private:
    SkipList players;

public:
    void addPlayer(int playerId, int score) {
        players.insert(playerId, score);
    }

    void removePlayer(int playerId) {
        if (players.search(playerId)) {
            players.remove(playerId);
            cout << "Player " << playerId << " removed." << '\n';
        } else {
            cout << "Player " << playerId << " not found." << '\n';
        }
    }

    void updateScore(int playerId, int newScore) {
        if (players.search(playerId)) {
            players.remove(playerId);
            players.insert(playerId, newScore);
            cout << "Player " << playerId << "'s score updated to " << newScore << "." << endl;
        } else {
            cout << "Player " << playerId << " not found." << endl;
        }
    }

    void printLeaderboard(int topN) {
        vector<pair<int, int>> playersScores;
        Node* current = players.getHead()->next[0];

        while (current != players.getTail()) {
            playersScores.push_back({current->key, current->value});
            current = current->next[0];
        }

        sort(playersScores.begin(), playersScores.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second > b.second;
             });

        cout << "Top " << topN << " Players by Score:" << endl;
        int count = 0;
        for (const auto& player : playersScores) {
            if (count >= topN) break;
            cout << "Player " << player.first << " - Score: " << player.second << endl;
            count++;
        }
    }


  
};

int main() {
    srand(time(0));
    Game game;

    game.addPlayer(1, 100);
    game.addPlayer(2, 200);
    game.addPlayer(5, 150);
    game.addPlayer(4, 500);

    game.updateScore(1, 150);
    game.updateScore(2, 250);
    game.updateScore(3, 75);

    game.printLeaderboard(3);

    game.removePlayer(2);

    game.printLeaderboard(3);

    return 0;
}
