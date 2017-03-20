#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define RFOR(i, a, b) for (int i = (b)-1; i >= int(a); --i)
#define rep(i, n) FOR(i, 0, n)
#define rep1(i, n) FOR(i, 1, int(n) + 1)
#define rrep(i, n) RFOR(i, 0, n)
#define rrep1(i, n) RFOR(i, 1, int(n) + 1)
#define all(c) begin(c), end(c)

#define map unordered_map

template <typename T>
void __dump__(std::ostream &os, const T &first) {
    os << first;
}
template <typename First, typename... Rest>
void __dump__(std::ostream &os, const First &first, const Rest &... rest) {
    os << first << ", ";
    __dump__(os, rest...);
}
#define dump(...)                                         \
    do {                                                  \
        std::ostringstream os;                            \
        os << __LINE__ << ":\t" << #__VA_ARGS__ << " = "; \
        __dump__(os, __VA_ARGS__);                        \
        std::cerr << os.str() << std::endl;               \
    } while (0)

int main(){
    string END = "ksss";

    srand(time(0));
    vector<string> must;
    string w(4, '_');
    [&]{
        FOR(a, 'a', 'z' + 1){
            FOR(b, 'a', 'z' + 1){
                FOR(c, 'a', 'z' + 1){
                    FOR(d, 'a', 'z' + 1){
                        w[0] = a;
                        w[1] = b;
                        w[2] = c;
                        w[3] = d;
                        if (w <= END) {
                            must.push_back(w);
                        } else {
                            return;
                        }
                    }
                }
            }
        }
    }();

    map<string, set<int>> prfx_mp[4]; // prefix -> indicies of string
    map<string, set<int>> sffx_mp[4]; // suffix -> indicies of string
    rep(i, must.size()) {
        rep1(l, 3) {
            string &s = must[i];
            string prfx = s.substr(0, l);
            prfx_mp[l][prfx].insert(i);
            string sffx = s.substr(s.size() - l);
            sffx_mp[l][sffx].insert(i);
        }
    }

    set<int> not_used, used;
    rep (i, must.size()) not_used.insert(i);

    auto remove = [&](int idx) {
        auto &s = must[idx];
        rep1(i, 3) {
            auto a = [&](){
                string prfx = s.substr(0, i);
                assert(prfx_mp[i].count(prfx));
                assert(prfx_mp[i][prfx].count(idx));
                prfx_mp[i][prfx].erase(idx);
                if (prfx_mp[i][prfx].size() == 0) {
                    prfx_mp[i].erase(prfx);
                }
            };
            auto b = [&](){
                string sffx = s.substr(s.size() - i);
                assert(sffx_mp[i].count(sffx));
                assert(sffx_mp[i][sffx].count(idx));
                sffx_mp[i][sffx].erase(idx);
                if (sffx_mp[i][sffx].size() == 0) {
                    sffx_mp[i].erase(sffx);
                }            
            };
            if(rand() & 1) a(), b(); else b(), a();
        }
        assert(used.count(idx) == 0);
        assert(not_used.count(idx) == 1);
        used.insert(idx);
        not_used.erase(idx);
    };

    string ans = "zzzz";

    auto append = [&](int idx, int l) {
        string a = must[idx].substr(l);
        ans += a;
        remove(idx);
    };

    auto unshift = [&](int idx, int l) {
        string b = must[idx].substr(0, must[idx].size() - l);
        ans.insert(ans.begin(), all(b));
        remove(idx);
    };

    rep(i, must.size()) {
        if (i % 10000 == 0) {
            dump(ans);
            dump(i, ans.size(), must.size());
        }

        int added = false;

        int idx = *not_used.begin();
        string s = must[idx];

        if (ans.find(s) != string::npos) {
            append(idx, s.size());
        } else {
            rrep1(l, 3) {
                {
                    string sffx = ans.substr(ans.size() - l);
                    if (prfx_mp[l].count(sffx) != 0) {
                        int idx = *prfx_mp[l][sffx].begin();
                        append(idx, l);
                        added = true;
                        break;
                    }
                }
                {
                    string prfx = ans.substr(0, l);
                    if (sffx_mp[l].count(prfx) != 0) {
                        int idx = *sffx_mp[l][prfx].begin();
                        unshift(idx, l);
                        added = true;
                        break;
                    }
                }
            }
        }

        if (!added) {
            // append(idx, 0);
            if(rand() & 1) append(idx, 0); else unshift(idx, 0);
        }

        // dump(ans);
    }
    assert(used.size() == must.size());
    assert(not_used.size() == 0);
    dump(ans.size());
    cout << 1 << endl;
    cout << ans << endl;
}
