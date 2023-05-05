#include <bits/stdc++.h>
#include "kdt.h"
using namespace std;
const int N = 62;
using dataset = vector<pair<Point<N>, double>>;
void readdata(ifstream &fin, dataset &wow)
{
    double s;
    while (fin >> s)
    {
        double id;
        vector<double> ar;
        ar.emplace_back(s);
        for (int i = 1; i < N; i++)
        {
            fin >> s;
            ar.emplace_back(s);
        }
        fin >> id;
        wow.emplace_back(ar, id);
    }
}
int main()
{
    ifstream fin1,fin2;
    fin1.open("D:\\train_emtion.txt", ios::in);
    if (!fin1.is_open())
    {
        cout << "data not found\n";
        return 1;
    }
    dataset train;
    readdata(fin1, train);
    dataset query;
    fin2.open("D:\\test_emtion.txt");
    if (!fin1.is_open())
    {
        cout << "data not found\n";
        return 1;
    }
    readdata(fin2,query);
    KDTree<N, double> kd(train);
    cout << "build complete\n";
    for (int i = 1; i <= 45; i+= 2)
    {
        int res = 0;
        for (auto &[poi, name] : query)
            res += kd.KNNvalue(poi, i) == name;
        cout << "K = " << i << "  " << res * 1.0 / query.size() * 100 << "%\n";
    }
    return 0;
}
