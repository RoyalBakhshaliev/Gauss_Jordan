#include <iostream>
using namespace std;

const int MAX = 100;

void pechat(int stroki, int stolbcy, double matrica[MAX][MAX]) {
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbcy; j++) {
            cout << matrica[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool est_v_massive(int massiv[], int razmer, int znachenie) {
    for (int i = 0; i < razmer; i++) {
        if (massiv[i] == znachenie)
            return true;
    }
    return false;
}

int main() {
    int stroki, stolbcy;
    cout << "Vvedite kolichestvo strok: ";
    cin >> stroki;
    cout << "Vvedite kolichestvo stolbcov: ";
    cin >> stolbcy;

    double matrica[MAX][MAX];
    double rezultat[MAX][MAX];

    cout << "Vvedite elementy matricy (v tom chisle svobodnye chleny)" << endl;
    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbcy; j++) {
            cin >> matrica[i][j];
            rezultat[i][j] = matrica[i][j];
        }
    }

    cout << endl << "Vvedennaya matrica:" << endl;
    pechat(stroki, stolbcy, matrica);

    int stroki_vedushie[MAX];
    int stolbcy_vedushie[MAX];
    int kolichestvo_vedushih = 0;

    for (int col = 0; col < stolbcy - 1; col++) {
        for (int row = 0; row < stroki; row++) {
            if (kolichestvo_vedushih < stroki &&
                !est_v_massive(stroki_vedushie, kolichestvo_vedushih, row) &&
                matrica[row][col] != 0) {

                int vedushaya_stroka = row;
                int vedushiy_stolbec = col;
                stroki_vedushie[kolichestvo_vedushih] = row;
                stolbcy_vedushie[kolichestvo_vedushih] = col;
                kolichestvo_vedushih++;

                double opornyy = matrica[vedushaya_stroka][vedushiy_stolbec];

                for (int i = 0; i < stroki; i++) {
                    for (int j = 0; j < stolbcy; j++) {
                        if (i == vedushaya_stroka) {
                            rezultat[i][j] = matrica[i][j] / opornyy;
                        }
                        else if (j == vedushiy_stolbec) {
                            rezultat[i][j] = 0;
                        }
                        else {
                            rezultat[i][j] = matrica[i][j] -
                                (matrica[i][vedushiy_stolbec] * matrica[vedushaya_stroka][j]) / opornyy;
                        }
                    }
                }

                cout << "Sleduyushchaya iteraciya:" << endl;
                pechat(stroki, stolbcy, rezultat);

                for (int i = 0; i < stroki; i++)
                    for (int j = 0; j < stolbcy; j++)
                        matrica[i][j] = rezultat[i][j];
            }
        }
    }

    bool net_resheniya = false;
    bool beskonechno = false;

    for (int i = 0; i < stroki; i++) {
        int nuley = 0;
        for (int j = 0; j < stolbcy; j++) {
            if (matrica[i][j] == 0)
                nuley++;
        }
        if (nuley == stolbcy - 1 && matrica[i][stolbcy - 1] != 0) {
            cout << "Sistema nesovmestna (net resheniy)" << endl;
            net_resheniya = true;
        }
        if (nuley == stolbcy) {
            cout << "Beskonechnoe chislo resheniy (lineynaya zavisimost)" << endl;
            beskonechno = true;
        }
    }

    if (beskonechno) {
        cout << "Uproshchennaya matrica:" << endl;
        pechat(stroki, stolbcy, matrica);
    }

    if (stolbcy - stroki >= 2)
        cout << "Beskonechnoe chislo resheniy" << endl;

    if (!net_resheniya) {
        cout << "Reshenie sistemy uravneniy:" << endl;
        for (int i = 0; i < stroki; i++) {
            bool pervyy_chlen = false;
            for (int j = 0; j < stolbcy; j++) {
                if (matrica[i][j] != 0 && j != stolbcy - 1) {
                    if (pervyy_chlen)
                        cout << " + ";
                    cout << matrica[i][j] << "*x" << j + 1;
                    pervyy_chlen = true;
                }
                else if (j == stolbcy - 1) {
                    cout << " = " << matrica[i][j];
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
