#include<bits/stdc++.h>
using namespace std;

bool isValid(int x, int y, int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

int main() {

    int n, m;
    cin >> n >> m;
    char a[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    

    int neighbor_dx[] = {-1, 1, 0, 0,-1,1,-1,1};
    int neighbor_dy[] = {0, 0, -1, 1,1,-1,-1,1};
    int cnt=0;

    int x, y;
    cin >> x >> y;
    x--;y--;

    if (!isValid(x, y, n, m)) {
        cout << "no" << endl;
        return 0;
    }

    for (int i = 0; i < 8; i++) {
        int newX = x + neighbor_dx[i];
        int newY = y + neighbor_dy[i];
        if (!isValid(newX, newY, n, m)) {
            cnt++;
            continue;
        }

        if (a[newX][newY] == 'x') {
            cnt++;
        }
    }

    if(cnt==8) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}