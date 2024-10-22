#include <bits/stdc++.h>
#include <sstream>
#include <fstream>

using namespace std;

int match1 = 1;
int mismatch1 = -1;
int gap = -2;

int score(char a, char b) {
    if (a == b) {
        return match1;
    } else if (a == '-' || b == '-') {
        return gap;
    } else {
        return mismatch1;
    }
}

pair<int, string> GlobalAlignment(string s1, string s2) {
    int Ls1 = s1.length();
    int Ls2 = s2.length();

    int arr[Ls1 + 1][Ls2 + 1]{};
    char Carr[Ls1 + 1][Ls2 + 1]{};

    for (int i = 0; i <= Ls1; i++) {
        arr[i][0] = i * gap;
        Carr[i][0] = 'U'; // Gap in sequence 1 (Up)
    }

    for (int j = 0; j <= Ls2; j++) {
        arr[0][j] = j * gap;
        Carr[0][j] = 'L'; // Gap in sequence 2 (Left)
    }

    for (int i = 1; i <= Ls1; i++) {
        for (int j = 1; j <= Ls2; j++) {
            int matchScore = arr[i - 1][j - 1] + score(s1[i - 1], s2[j - 1]);
            int gapInSeq1 = arr[i - 1][j] + gap;
            int gapInSeq2 = arr[i][j - 1] + gap;

            arr[i][j] = max({matchScore, gapInSeq1, gapInSeq2});
            if (matchScore == arr[i][j]) {
                Carr[i][j] = 'M';
            } else if (gapInSeq1 == arr[i][j]) {
                Carr[i][j] = 'U';
            } else if (gapInSeq2 == arr[i][j]) {
                Carr[i][j] = 'L';
            }
        }
    }

    string ASeq1 = "";
    string ASeq2 = "";
    int i = Ls1;
    int j = Ls2;

    while (i > 0 && j > 0) {
        switch (Carr[i][j]) {
            case 'M':
                ASeq1 = s1[i - 1] + ASeq1;
                ASeq2 = s2[j - 1] + ASeq2;
                i--;
                j--;
                break;
            case 'U':
                ASeq1 = s1[i - 1] + ASeq1;
                ASeq2 = '-' + ASeq2;
                i--;
                break;
            case 'L':
                ASeq1 = '-' + ASeq1;
                ASeq2 = s2[j - 1] + ASeq2;
                j--;
                break;
        }
    }

    while (i > 0) {
        ASeq1 = s1[i - 1] + ASeq1;
        ASeq2 = '-' + ASeq2;
        i--;
    }
    
    while (j > 0) {
        ASeq1 = '-' + ASeq1;
        ASeq2 = s2[j - 1] + ASeq2;
        j--;
    }

    return {arr[Ls1][Ls2], ASeq1 + "\n" + ASeq2};
}

int main() {
    ifstream file1 ; 
    file1.open("file1.txt");
    stringstream buffer1 ;
    buffer1 << file1.rdbuf();
    string s1;
    s1=buffer1.str();
     ifstream file2 ; 
    file2.open("file2.txt");
    stringstream buffer2 ;
    buffer2 << file2.rdbuf();
    string s2;
    s2=buffer2.str();
    

    pair<int, string> finalresult = GlobalAlignment(s1, s2);

    int Score = finalresult.first;
    string ASeq1 = finalresult.second.substr(0, finalresult.second.find("\n"));
    string ASeq2 = finalresult.second.substr(finalresult.second.find("\n") + 1);

    cout << "Alignment Score: " << Score << "\n";
    cout << "Aligned Sequence 1: " << ASeq1 << "\n";
    cout << "Aligned Sequence 2: " << ASeq2 << "\n";

    return 0;
}
