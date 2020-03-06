#include <iostream>
#include <unordered_map>

#define _MAX_NUM_  1001

using namespace std;

int man[_MAX_NUM_][_MAX_NUM_];
int to_propose[_MAX_NUM_];
int woman[_MAX_NUM_][_MAX_NUM_];
int woman_hus[_MAX_NUM_];
int n, queue[1000001], fr, re;
unordered_map<string, int> mm;
unordered_map<string, int> wm;
string mname[_MAX_NUM_];
string wname[_MAX_NUM_];

int main() {
    cin >> n;
    int wm_cnt = 0;
    fr = 0, re = 0;
    for(int i = 0; i < n; i++) {
        woman_hus[i] = -1;
        to_propose[i] = 0;
    }
    // man preference list input
    for(int i = 0; i < n; i++) {
        string name;
        cin >> name;
        mm[name] = i;
        mname[i] = name;
        for(int j = 0; j < n; j++) {
            string w_name;
            cin >> w_name;
            if(wm.find(w_name) == wm.end()) {
                wname[wm_cnt] = w_name;
                wm[w_name] = wm_cnt++;
            }
            man[i][j] = wm[w_name];
        }
    }
    // woman preference list input
    for(int i = 0; i < n; i++) {
        string name;
        cin >> name;
        int _index = wm[name];
        for(int j = 0; j < n; j++) {
            string m_name;
            cin >> m_name;
            woman[_index][mm[m_name]] = j;
        }
    }
    // printf("%d %d", wm["han"], wm["wang"]);

    for(int i = 0; i < n; i++) {
        queue[re++] = i;
    }

    // while the queue is not empty
    while(fr != re) {
        //dequeue
        int man_num = queue[fr++];
        int proposee = man[man_num][to_propose[man_num]];
        //propose
        if(woman_hus[proposee] == -1) {
            //wm not paired
            woman_hus[proposee] = man_num;
        }else {
            //wm has been proposed
            if(woman[proposee][man_num] < woman[proposee][woman_hus[proposee]]) {
                // the current proposor is prefered
                queue[re++] = woman_hus[proposee];
                woman_hus[proposee] = man_num;
            }else {
                queue[re++] = man_num;
            }
        }
        to_propose[man_num]++;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(woman_hus[j] == i) {
                cout << mname[i] << " " << wname[j] << endl;
            }
        }
    }
}