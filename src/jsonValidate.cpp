#include "jsonValidate.hpp"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <iostream>   
#include <sstream>    
#include <bits/stdc++.h>

void readallTextFromJson()
{
    // Variable to store each line from the file
    std::string line;

    // Read each line from the file and print it
    while (getline(jsonFile_, line)) 
    {
        // Process each line as needed
        allText_ = allText_.append(line);
    }
}

static std::vector<std::string> split(std::string str, char delimiter)
{
  // Using str in a string stream
    std::stringstream ss(str);
    std::vector<std::string> res;
    std::string token;
    while (getline(ss, token, delimiter)) {
        res.push_back(token);
    }
    return res;
}


JsonValidate::JsonValidate(const std::string& pathToFile)
{
    jsonFile_ = std::ifstream(pathToFile.c_str());
    allText_ = readAllTextFromJson(); // Needs jsonFile_ after
}

void JsonValidate::decomposeJson()
{
    // Remove all occurrences of ' ' in text
    allText_.erase( remove(allText_.begin(), allText_.end(), ' '), allText_.end());

    // Remove the carachter 0 and size - 1
    allText_.erase(allText_.begin(), allText_.begin() + 1);
    allText_.pop_back();

    // Split by comma to have keyValues
    wordsSplited_ = split(allText_, ',');
    
    for(auto const& keyValue : wordsSplited_)
    {        
        std::size_t found = keyValue.find(":");

        if (found == std::string::npos)
            continue;

        keyValues_.insert({keyValue.substr(0,found - 1), keyValue.substr(found + 1)});

    }
}

// Fonction qui retourne l'etat de validité des virgules
bool JsonValidate::checkCommaValidity() const
{
    for(const auto& word : wordsSplited_)
    {
        if(word == "")
        {
            return false;
        }
    }
    return true;
}

// Fonction qui retourne l'etat de validité des accolades
bool JsonValidate::checkAccoladeValidaty() const 
{
    int compt = 0;

    for(auto const& c : allText_)
    {
        if(c == '{')
            compt++;
        
        else if(c == '}')
        {
            if(compt <= 0)
                return false;

            else
                compt--;
        }
    }
    return (compt == 0);
}

// Fonction qui retourne l'etat de validité des brackets
bool JsonValidate::checkBracketsValidaty() const
{
        int compt = 0;

    for(auto const& c : allText_)
    {
        if(c == '[')
            compt++;
        
        else if(c == ']')
        {
            if(compt <= 0)
                return false;

            else
                compt--;
        }
    }
    return (compt == 0);
}

// #include <iostream>
// #include <vector>
// #include <queue>
// using namespace std;

// // BFS for single connected component
// vector<int> bfs(vector<vector<int>>& adj) {
//     int V = adj.size();
//     vector<bool> visited(V, false);
//     vector<int> res;
    
//     queue<int> q;
    
//     int src = 0;
//     visited[src] = true;
//     q.push(src);

//     while (!q.empty()) {
//         int curr = q.front();
//         q.pop();
//         res.push_back(curr);

//         // visit all the unvisited
//         // neighbours of current node
//         for (int x : adj[curr]) {
//             if (!visited[x]) {
//                 visited[x] = true;
//                 q.push(x);
//             }
//         }
//     }
    
//     return res;
// }

// void addEdge(vector<vector<int>>& adj, int u, int v) {
//     adj[u].push_back(v);
//     adj[v].push_back(u);
// }

// int main() {
//     int V = 5;
//     vector<vector<int>> adj(V);
    
//     // creating adjacency list
//     addEdge(adj, 1, 2);
//     addEdge(adj, 1, 0);
//     addEdge(adj, 2, 0);
//     addEdge(adj, 2, 3);
//     addEdge(adj, 2, 4);

//     vector<int> res = bfs(adj);

//     for (int i : res)
//         cout << i << " ";
// }
