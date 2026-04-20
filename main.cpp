#include <bits/stdc++.h>
using namespace std;
vector<string> b = {"rnbqkbnr", "pppppppp", "........", "........", "........", "........", "PPPPPPPP", "RNBQKBNR"};
bool W(char c) { return isupper((unsigned char)c); }
bool I(int r, int c) { return r >= 0 && r < 8 && c >= 0 && c < 8; }
int V(char c)
{
    switch (tolower(c))
    {
    case 'p':
        return 1;
    case 'n':
    case 'b':
        return 3;
    case 'r':
        return 5;
    case 'q':
        return 9;
    case 'k':
        return 99;
    default:
        return 0;
    }
}
pair<int, int> K(const vector<string> &g, bool w)
{
    char k = w ? 'K' : 'k';
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (g[r][c] == k)
                return {r, c};
    return {-1, -1};
}
void P()
{
    cout << "\n +-----------------+\n";
    for (int r = 0; r < 8; r++)
    {
        cout << 8 - r << "| ";
        for (char x : b[r])
            cout << (x == '.' ? "  " : string(1, x) + " ");
        cout << "|\n";
    }
    cout << " +-----------------+\n   a b c d e f g h\n\n";
}
int E(const vector<string> &g)
{
    int s = 0;
    for (auto &r : g)
        for (char c : r)
            if (c != '.')
                s += W(c) ? V(c) : -V(c);
    return s;
}
bool A(const vector<string> &g, int r, int c, bool w)
{
    int d = w ? -1 : 1;
    if (I(r + d, c - 1) && g[r + d][c - 1] == (w ? 'P' : 'p'))
        return 1;
    if (I(r + d, c + 1) && g[r + d][c + 1] == (w ? 'P' : 'p'))
        return 1;
    int n[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}}, k[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}, r1[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, b1[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (auto &m : n)
        if (I(r + m[0], c + m[1]) && g[r + m[0]][c + m[1]] == (w ? 'N' : 'n'))
            return 1;
    for (auto &m : k)
        if (I(r + m[0], c + m[1]) && g[r + m[0]][c + m[1]] == (w ? 'K' : 'k'))
            return 1;
    for (auto &m : r1)
    {
        int x = r, y = c;
        while (I(x += m[0], y += m[1]))
        {
            char p = g[x][y];
            if (p == '.')
                continue;
            if (W(p) == w && (tolower(p) == 'r' || tolower(p) == 'q'))
                return 1;
            break;
        }
    }
    for (auto &m : b1)
    {
        int x = r, y = c;
        while (I(x += m[0], y += m[1]))
        {
            char p = g[x][y];
            if (p == '.')
                continue;
            if (W(p) == w && (tolower(p) == 'b' || tolower(p) == 'q'))
                return 1;
            break;
        }
    }
    return 0;
}
vector<pair<string, vector<string>>> M(const vector<string> &g, bool w)
{
    vector<pair<string, vector<string>>> m;
    auto add = [&](int fr, int fc, int tr, int tc, char p = 0)
    {if(!I(tr,tc))return;char x=g[fr][fc],t=g[tr][tc];if(t!='.'&&W(t)==w)return;auto h=g;h[fr][fc]='.';h[tr][tc]=p?p:x;auto [kr,kc]=K(h,w);if(!A(h,kr,kc,!w)){string s; s+=char('a'+fc); s+=char('8'-fr); s+=char('a'+tc); s+=char('8'-tr); if(p)s+=tolower(p); m.push_back({s,h});} };
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
        {
            char p = g[r][c];
            if (p == '.' || W(p) != w)
                continue;
            int d = w ? -1 : 1;
            switch (tolower(p))
            {
            case 'p':
            {
                int nr = r + d;
                if (I(nr, c) && g[nr][c] == '.')
                {
                    add(r, c, nr, c, (nr == 0 || nr == 7) ? (w ? 'Q' : 'q') : 0);
                    if ((w && r == 6) || (!w && r == 1))
                    {
                        int nr2 = r + 2 * d;
                        if (g[nr2][c] == '.')
                            add(r, c, nr2, c);
                    }
                }
                for (int dc : {-1, 1})
                {
                    int nc = c + dc;
                    if (I(nr, nc) && g[nr][nc] != '.' && W(g[nr][nc]) != w)
                        add(r, c, nr, nc, (nr == 0 || nr == 7) ? (w ? 'Q' : 'q') : 0);
                }
                break;
            }
            case 'n':
            {
                int a[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
                for (auto &m : a)
                    add(r, c, r + m[0], c + m[1]);
                break;
            }
            case 'b':
            case 'r':
            case 'q':
            {
                int x[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}, s = tolower(p) == 'b' ? 0 : tolower(p) == 'r' ? 4
                                                                                                                                                    : 0,
                    e = tolower(p) == 'b' ? 4 : tolower(p) == 'r' ? 8
                                                                  : 8;
                for (int i = s; i < e; i++)
                {
                    int dr = x[i][0], dc = x[i][1], rr = r + dr, cc = c + dc;
                    while (I(rr, cc))
                    {
                        if (g[rr][cc] == '.')
                            add(r, c, rr, cc);
                        else
                        {
                            if (W(g[rr][cc]) != w)
                                add(r, c, rr, cc);
                            break;
                        }
                        rr += dr;
                        cc += dc;
                    }
                }
                break;
            }
            case 'k':
            {
                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++)
                        if (dr || dc)
                            add(r, c, r + dr, c + dc);
                break;
            }
            }
        }
    return m;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool w = 1;
    for (;;)
    {
        P();
        auto m = M(b, w);
        if (m.empty())
        {
            auto [kr, kc] = K(b, w);
            if (A(b, kr, kc, !w))
                cout << (w ? "Black" : "White") << " wins by checkmate.\n";
            else
                cout << "Stalemate.\n";
            break;
        }
        if (w)
        {
            cout << "move: ";
            string s;
            getline(cin, s);
            for (auto &ch : s)
                ch = tolower(ch);
            if (s == "q")
                break;
            auto it = find_if(m.begin(), m.end(), [&](auto &z)
                              { return z.first == s; });
            if (it == m.end())
            {
                cout << "illegal\n";
                continue;
            }
            b = it->second;
        }
        else
        {
            auto it = min_element(m.begin(), m.end(), [](auto &a, auto &c)
                                  { return E(a.second) < E(c.second); });
            b = it->second;
            cout << "computer: " << it->first << "\n";
        }
        w = !w;
    }
}
