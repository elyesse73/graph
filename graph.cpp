#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

class Graph
{
private:
    std::unordered_map<std::string, std::stack<std::pair<std::string, double>>> graph;

public:
    void addEdge(std::string a, std::string b, double c)
    {
        graph[a].push({b, c});
    };
    void printGraph()
    {
        for (auto e : graph)
        {
            auto f = e.second;
            while (!f.empty())
            {
                std::cout << "Arête " << e.first << " -> ";
                auto x = f.top();
                std::cout << x.first << " : " << x.second;
                f.pop();
                std::cout << "," << std::endl;
            };
        }
    };
    auto operator<<(Graph G)
    {
        G.printGraph();
    };
    void visit(std::vector<std::string> &visited, std::string h)
    {
        auto it = std::find(visited.begin(), visited.end(), h);
        if (it == visited.end())
        {
            visited.push_back(h);
            auto f = graph[h];
            while (!f.empty())
            {
                auto x = f.top();
                std::cout << h << "->" << x.first << ":" << x.second << std::endl;
                visit(visited, x.first);
                f.pop();
            };
        };
    };
    void dfsr()
    {
        std::vector<std::string> visited;
        for (auto e : graph)
        {
            visit(visited, e.first); // version récursive
        };
    };
    void dfsi2()
    {
        std::vector<std::string> visited;
        std::stack<std::string> tovisit;
        for (auto e : graph)
        {
            tovisit.push(e.first);
            while (!tovisit.empty())
            {
                auto t = tovisit.top();
                auto it = std::find(visited.begin(), visited.end(), t);
                if (it == visited.end())
                {
                    visited.push_back(t);
                    auto f = graph[t];
                    while (!f.empty())
                    {
                        auto x = f.top();
                        std::cout << t << "->" << x.first << ":" << x.second << std::endl;
                        tovisit.push(x.first);
                        f.pop();
                    };
                };
                tovisit.pop();
            };
        };
    }
    void dfsi()
    {
        std::vector<std::string> visited;
        std::stack<std::string> tovisit;
        for (auto e : graph)
        {
            tovisit.push(e.first);
            while (!tovisit.empty())
            {
                auto t = tovisit.top();
                auto f = graph[t];
                visited.push_back(t);
                while (!f.empty())
                {
                    auto x = f.top();
                    auto it = std::find(visited.begin(), visited.end(), x.first);
                    if (it == visited.end())
                    {
                        std::cout << t << "->" << x.first << ":" << x.second << std::endl;
                        tovisit.push(x.first);
                    };
                    f.pop();
                };
                tovisit.pop();
            };
        };
    };
    void bfs()
    {
        std::vector<std::string> visited;
        std::queue<std::string> tovisit;
        for (auto e : graph)
        {
            tovisit.push(e.first);
            while (!tovisit.empty())
            {
                auto t = tovisit.front();
                auto f = graph[t];
                while (!f.empty())
                {
                    auto it = std::find(visited.begin(), visited.end(), t);
                    if (it == visited.end())
                    {
                        visited.push_back(t);
                        auto x = f.top();
                        std::cout << t << "->" << x.first << ":" << x.second << std::endl;
                        tovisit.push(x.first);
                    };
                    f.pop();
                };
                tovisit.pop();
            };
        };
    };
};
int main()
{
    Graph g;
    g.addEdge("Paris", "Lyon", 100);
    g.addEdge("Paris", "Marseille", 150);
    g.addEdge("Lyon", "Nice", 80);
    g.addEdge("Marseille", "Nice", 70);
    g.addEdge("Nice", "Paris", 200);
    g.printGraph();
    // std::cout << g << std::endl;
    std::cout << "Parcours en profondeur récursif :" << std::endl;
    g.dfsr();
    std::cout << "Parcours en largeur :" << std::endl;
    g.dfsi2();
    std::cout << "Parcours en profondeur itératif :" << std::endl;
    g.bfs();
    return 0;
};