#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include "avl.hpp"
using namespace std;
class User
{
public:
    string username;
    vector<string> friendos;
    Avl posts;
    User(string name)
    {
        username = name;
    }

    bool hasFriendo(string frnd)
    {
        int i = lower_bound(friendos.begin(), friendos.end(), frnd) - friendos.begin();
        return (i < friendos.size() && friendos[i] == frnd);
    }

    void addFriendoSorted(string frnd)
    {
        int i = lower_bound(friendos.begin(), friendos.end(), frnd) - friendos.begin();
        if (i == friendos.size() || friendos[i] != frnd)
        {
            friendos.insert(friendos.begin() + i, frnd);
        }
    }
};

class socialNet
{
    unordered_map<string, User *> users;
    long long globalTime = 0;

    User *getUser(string name)
    {
        auto it = users.find(name);
        if (it != users.end())
        {
            return it->second;
        }
        return nullptr;
    }

public:
    ~socialNet()
    {
        for (auto &pair : users)
        {
            delete pair.second;
        }
    }
    void addUser(string name)
    {
        string lowerName = name;
        for (auto &c : lowerName)
            c = tolower(c);
        if (lowerName.empty())
        {
            cout << "Error: Username cannot be empty.\n";
            return;
        }
        if (users.find(lowerName) != users.end())
        {
            cout << "Error: User with a similar name already exists\n";
            return;
        }
        users[lowerName] = new User(lowerName);
        cout << "User named '" << name << "' was added.\n";
    }

    void addFriendo(string user1, string user2)
    {
        string lower1 = user1;
        for (auto &c : lower1)
            c = tolower(c);
        string lower2 = user2;
        for (auto &c : lower2)
            c = tolower(c);
        User *u1 = getUser(lower1);
        User *u2 = getUser(lower2);

        if (lower1.empty() or lower2.empty())
        {
            cout << "Error: Usage: ADD FRIEND <user1> <user2>\n";
            return;
        }
        if (lower1 == lower2)
        {
            cout << "Error: Cannot add self as a friend\n";
            return;
        }
        if (!u1)
        {
            cout << "Error: User not found: " << user1 << "\n";
            return;
        }
        if (!u2)
        {
            cout << "Error: User not found: " << user2 << "\n";
            return;
        }
        if (u1->hasFriendo(lower2))
        {
            cout << "Error: " << user1 << " and " << user2 << " are already friends.\n";
            return;
        }
        u1->addFriendoSorted(lower2);
        u2->addFriendoSorted(lower1);
        cout << user1 << " & " << user2 <<" are now friends!\n";
    }

    void listFriendos(string name)
    {
        string lowerName = name;
        for (auto &c : lowerName)
            c = tolower(c);
        User *user = getUser(lowerName);
        if (!user)
        {
            cout << "Error: User not found: " << name << "\n";
            return;
        }
        if(user->friendos.size() == 0){
            cout << "No friends found for the user: " << name << "\n";
            return;
        }
        cout << "Friend list of " << name <<":\n";
        for (int i = 0; i < user->friendos.size(); i++)
        {
            cout << user->friendos[i];
            if (i + 1 < user->friendos.size())
                cout << " ";
        }
        cout << "\n";
    }

    void suggetions(string name, int N)
    {
        if (N < 0)
        {
            cout << "Error: Please enter a valid number for N.\n";
            return;
        }
        if (N == 0)
            return;
        string lowerName = name;
        for (auto &c : lowerName)
            c = tolower(c);
        User *user = getUser(lowerName);
        if (!user)
        {
            cout << "Error: User not found: " << name << "\n";
            return;
        }

        unordered_map<string, int> mutuals;
        unordered_map<string, bool> isFrnd;

        for (string frnd : user->friendos)
        {
            isFrnd[frnd] = true;
        }
        for (string frnd : user->friendos)
        {
            User *friendo = getUser(frnd);
            if (!friendo)
                continue;
            for (string ff : friendo->friendos)
            {
                if (ff == lowerName || isFrnd[ff])
                    continue;
                mutuals[ff]++;
            }
        }
        if(mutuals.size() == 0){
            cout << "No friend suggestions available for: "<<name<<"\n";
            return;
        }
        struct Suggn
        {
            string name;
            int mutualCount;
            Suggn(string n, int c) : name(n), mutualCount(c) {}
        };
        vector<Suggn> v;
        v.reserve(mutuals.size());
        for (auto &p : mutuals)
        {
            v.push_back(Suggn(p.first, p.second));
        }

        for (int i = 0; i < v.size(); i++)
        {
            int best = i;
            for (int j = i + 1; j < v.size(); j++)
            {
                bool high = false;
                if (v[j].mutualCount > v[i].mutualCount)
                    high = true;
                else if (v[j].mutualCount == v[i].mutualCount && v[j].name < v[i].name)
                    high = true;
                if (high)
                {
                    best = j;
                }
            }
            if (best != i)
            {
                swap(v[i], v[best]);
            }
        }
        int count = 0;
        cout << "Suggestions for "<<name<<" are listed below:\n";
        for (int i = 0; i < v.size() && count < N; i++)
        {
            cout << users[v[i].name]->username;
            count++;
            if (count < N && i + 1 < v.size())
                cout << " ";
        }
        cout << "\n";
    }

    void addPost(string name, string cont)
    {
        string lowerName = name;
        for (auto &c : lowerName)
            c = tolower(c);
        User *user = getUser(lowerName);
        if (!user)
        {
            cout << "Error: User not found: " << name << "\n";
            return;
        }
        long long timestamp = globalTime++;
        string lowerContent = cont;
        for (auto &c : lowerContent)
            c = tolower(c);
        cout << name << " added a new post!\n";
        user->posts.addPost(lowerContent, timestamp);
    }

    void recentPosts(string name, int N)
    {
        string lowerName = name;
        for (auto &c : lowerName)
            c = tolower(c);
        User *user = getUser(lowerName);
        if (!user)
        {
            cout << "Error: User not found: " << name << "\n";
            return;
        }
        if (N < -1)
        {
            cout << "Error: Please enter a valid number for N.\n";
            return;
        }
        cout << "Most Recent posts of "<<name<<" are listed:\n";
        user->posts.printPosts(N);
    }

    void DOS(string name1, string name2)
    {
        string lower1 = name1;
        for (auto &c : lower1)
            c = tolower(c);
        string lower2 = name2;
        for (auto &c : lower2)
            c = tolower(c);
        User *u1 = getUser(lower1);
        User *u2 = getUser(lower2);
        if (!u1)
        {
            cout << "Error: User not found: " << name1 << "\n";
            return;
        }
        if (!u2)
        {
            cout << "Error: User not found: " << name2 << "\n";
            return;
        }
        if (name1.empty() or name2.empty())
        {
            cout << "Error: Usage: DOS <user1> <user2>\n";
            return;
        }
        if (u1 == u2)
        {
            cout << 0 << "\n";
            return;
        }
        queue<pair<string, int>> q;
        unordered_map<string, bool> visited;
        q.push({lower1, 0});
        visited[lower1] = true;
        while (q.size())
        {
            auto p = q.front();
            q.pop();
            string currUser = p.first;
            int dist = p.second;
            User *curr = getUser(currUser);
            if (!curr)
                continue;
            for (int i = 0; i < curr->friendos.size(); i++)
            {
                string frnd = curr->friendos[i];
                if (visited[frnd])
                    continue;
                if (frnd == lower2)
                {
                    cout << dist + 1 << "\n";
                    return;
                }
                visited[frnd] = true;
                q.push({frnd, dist + 1});
            }
        }
        cout << -1 << "\n";
    }
};