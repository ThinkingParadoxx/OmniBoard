#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dfs(vector<vector<int>> &grid, int sr, int sc, int dr, int dc, vector<vector<bool>> &vis)
{
    if (sr == dr && sc == dc)
    {
        vector<pair<int, int>> v;
        v.push_back({dr, dc});
        return v;
    }
    if (sr >= 17 sr < 0 sc >= 19 sc < 0 grid[sr][sc] == 1 || vis[sr][sc])
    {
        vector<pair<int, int>> out;
        return out;
    }
    int delr[] = {0, 0, -1, 1, -1, -1, 1, 1};
    int delc[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    vis[sr][sc] = true;
    vector<pair<int, int>> out;
    int mini = INT_MAX;
    for (int i = 0; i < 8; i++)
    {
        int nr = sr + delr[i];
        int nc = sc + delc[i];
        vector<pair<int, int>> ans = dfs(grid, nr, nc, dr, dc, vis);
        if (ans.size() > 0 && ans.size() < mini)
        {
            out = ans;
            mini = ans.size();
        }
    }
    if (out.size() == 0)
    {
        vector<pair<int, int>> temp;
        return temp;
    }
    vis[sr][sc] = false;
    out.push_back({sr, sc});
    return out;
}
int main()
{
    vector<vector<int>> grid = {{0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                                {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}};
    vector<vector<bool>> vis(17, vector<bool>(19, false));
    grid[13][7] = 0;
    vector<pair<int, int>> ans = dfs(grid, 16, 3, 13, 7, vis);
    grid[13][7] = 1;
    grid[16][3] = 0;
    cout << ans.size() << endl;
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].first << "," << ans[i].second << endl;
    }
}