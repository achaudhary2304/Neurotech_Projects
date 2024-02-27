#include <bits/stdc++.h>

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
    string s1 = "ABCEEF";
    string s2 = "ABCF";

    pair<int, string> alignmentResult = GlobalAlignment(s1, s2);

    int alignmentScore = alignmentResult.first;
    string alignedSequence1 = alignmentResult.second.substr(0, alignmentResult.second.find("\n"));
    string alignedSequence2 = alignmentResult.second.substr(alignmentResult.second.find("\n") + 1);

    cout << "Alignment Score: " << alignmentScore << "\n";
    cout << "Aligned Sequence 1: " << alignedSequence1 << "\n";
    cout << "Aligned Sequence 2: " << alignedSequence2 << "\n";

    return 0;
}