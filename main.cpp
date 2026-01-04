#include <iostream>
#include <sstream>
#include "graph.hpp"
using namespace std;

int main()
{
    socialNet X;
    string Line;

    while (getline(cin, Line))
    {
        if (Line.empty())
            continue;

        while(!Line.empty() && Line[0]==' '){
            Line.erase(Line.begin());
        }
        
        stringstream ss(Line);
        string cmd;
        ss >> cmd;

        // Adding a User
        if (cmd == "ADD_USER")
        {
            string name;
            if (!(ss >> name))
            {
                cout << "Error: Please Enter a username\n";
                continue;
            }
            X.addUser(name);
        }
        // Adding a friendo
        else if (cmd == "ADD_FRIEND")
        {
            string name1, name2;
            if (!(ss >> name1 >> name2))
            {
                cout << "Error: Usage: ADD_FRIEND <username1> <username2>\n";
                continue;
            }
            X.addFriendo(name1, name2);
        }
        // Adding a post
        else if (cmd == "ADD_POST")
        {
            string name;
            if (!(ss >> name))
            {
                cout << "Error: Usage: ADD_POST <username> <post_content>\n";
                continue;
            }
            string content;
            getline(ss, content);
            // removing the leading spaces from front of the post content
            while (!content.empty() and content[0] == ' ')
                content.erase(content.begin());

            if (content.empty())
            {
                cout << "Error: Post content cannot be empty\n";
                continue;
            }

            X.addPost(name, content);
        }
        // Listing friendos
        else if (cmd == "LIST_FRIENDS")
        {
            string name;
            ss >> name;
            if (name.empty())
            {
                cout << "Error: Usage: LIST_FRIENDS <username>\n";
                continue;
            }
            X.listFriendos(name);
        }
        // Suggesting good friendos
        else if (cmd == "SUGGEST_FRIENDS")
        {
            string name;
            int N;
            ss >> name >> N;
            if (name.empty() or !ss)
            {
                cout << "Error: Usage: SUGGEST_FRIENDS <username> <N>\n";
                continue;
            }
            X.suggetions(name, N);
        }
        // DOS between two users
        else if (cmd == "DEGREES_OF_SEPARATION")
        {
            string name1, name2;
            ss >> name1 >> name2;
            if (name1.empty() or name2.empty())
            {
                cout << "Error: Usage: DEGREES_OF_SEPARATION <username1> <username2>\n";
                continue;
            }
            X.DOS(name1, name2);
        }
        // Output most recent posts
        else if (cmd == "OUTPUT_POSTS")
        {
            string name;
            int N;
            ss >> name >> N;
            if (name.empty() or !ss)
            {
                cout << "Error: Usage: OUTPUT_POSTS <username> <N>\n";
                continue;
            }
            X.recentPosts(name, N);
        }
        //EXIT command
        else if (cmd == "EXIT")
        {
            cout << "Exiting...\n";
            break;
        }
        else
            cout << "Invalid Command\n";
    }
}