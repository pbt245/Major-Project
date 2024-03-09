#include "study_in_pink1.h"

bool readFile(
    const string &filename,
    int &HP1,
    int &HP2,
    int &EXP1,
    int &EXP2,
    int &M1,
    int &M2,
    int &E1,
    int &E2,
    int &E3)
{
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open())
    {
        ifs >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
        return true;
    }
    else
    {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Extra functions
void clamphp(int &hp)
{
    if (hp > 666)
        hp = 666;
    if (hp < 0)
        hp = 0;
}

void clampexp(int &exp)
{
    if (exp > 600)
        exp = 600;
    if (exp < 0)
        exp = 0;
}

void clampm(int &m)
{
    if (m > 3000)
        m = 3000;
    if (m < 0)
        m = 0;
}

// Task 1
int firstMeet(int &exp1, int &exp2, int e1)
{
    // TODO: Complete this function
    clampexp(exp1), clampexp(exp2);
    int D;
    if (e1 < 0 || e1 > 99)
        return -99;
    if ((0 <= e1) && (e1 <= 3))
    {
        if (e1 == 0)
            exp2 = exp2 + 29;
        else if (e1 == 1)
            exp2 = exp2 + 45;
        else if (e1 == 2)
            exp2 = exp2 + 75;
        else
            exp2 = exp2 + 29 + 45 + 75;
        clampexp(exp2);

        D = e1 * 3 + exp1 * 7;
        if (D % 2 == 0)
        {
            // if ((D == 0) || (D % 200 == 0))
            //     exp1 = exp1 + (D / 200);
            // else
            //     exp1 = exp1 + (D / 200) + 1;
            exp1 += ceil(D / 200.0);
        }
        else
            exp1 = exp1 - (D / 100);
        clampexp(exp1);
    }

    else if (e1 <= 99)
    {
        if (e1 <= 19)
            exp2 = exp2 + ceil(e1 / 4.0 + 19);
        else if (e1 <= 49)
            exp2 = exp2 + ceil(e1 / 9.0 + 21);
        else if (e1 <= 65)
            exp2 = exp2 + ceil(e1 / 16.0 + 17);
        else if (e1 <= 79)
        {
            exp2 = exp2 + ceil(e1 / 4.0 + 19);
            clampexp(exp2);
            if (exp2 > 200)
                exp2 = exp2 + ceil(e1 / 9.0 + 21);
        }
        else
        {
            exp2 = exp2 + ceil(e1 / 4.0 + 19);
            clampexp(exp2);
            exp2 = exp2 + ceil(e1 / 9.0 + 21);
            clampexp(exp2);
            if (exp2 > 400)
            {
                exp2 = exp2 + ceil(e1 / 16.0 + 17);
                exp2 = ceil(exp2 * 1.15);
                clampexp(exp2);
            }
        }
        clampexp(exp2);

        exp1 = exp1 - e1;
        clampexp(exp1);
    }

    return exp1 + exp2;
}

// Task 2

// defining function used for the iteration in events road 2
void eventInRoad2(int &HP1, int &EXP1, int &M1, int mm, int E2)
{
    // buy food
    clamphp(HP1);
    clampexp(EXP1);
    clampm(M1);
    if (HP1 < 200)
    {
        HP1 = ceil(HP1 * 130 / 100.0);
        M1 = M1 - 150;
    }
    else
    {
        HP1 = ceil(HP1 * 110 / 100.0);
        M1 = M1 - 70;
    }
    clamphp(HP1);
    clampm(M1);
    if (E2 % 2 != 0 && mm > 2 * M1)
        return;
    if (E2 % 2 == 0 && M1 == 0)
        return;

    // transportation
    if (EXP1 < 400)
    {
        M1 = M1 - 200;
        EXP1 = ceil(EXP1 * 113 / 100.0);
    }
    else
    {
        M1 = M1 - 120;
        EXP1 = ceil(EXP1 * 113 / 100.0);
    }
    clamphp(HP1);
    clampm(M1);
    if (E2 % 2 != 0 && mm > 2 * M1)
        return;
    if (E2 % 2 == 0 && M1 == 0)
        return;

    // homeless
    if (EXP1 < 300)
    {
        M1 = M1 - 100;
        EXP1 = ceil(EXP1 * 90 / 100.0);
    }
    else
    {
        M1 = M1 - 120;
        EXP1 = ceil(EXP1 * 90 / 100.0);
    }
    clampexp(EXP1);
    clampm(M1);
}

int traceLuggage(int &HP1, int &EXP1, int &M1, int E2)
{
    // TODO: Complete this function

    clamphp(HP1);
    clampm(M1);
    clampexp(EXP1);
    if (E2 < 0 || E2 > 99)
        return -99;

    // Road 1
    int S = 0;
    while (S * S <= EXP1)
        S++;                                     // greatest S  < EXP1;
    if (EXP1 - (S - 1) * (S - 1) < S * S - EXP1) // S nearest EXP1
        S = S - 1;                               // else S = S

    double P1;
    if (EXP1 >= S * S)
        P1 = 1;
    else
        P1 = ((double)EXP1 / S / S + 80) / 123;

    // Road 2
    int mm = M1; // money at the moment
    if (M1 != 0)
    {
        if (E2 % 2 != 0)
        {
            while (M1 * 2 >= mm)
                eventInRoad2(HP1, EXP1, M1, mm, E2 % 2);
        }
        else
            eventInRoad2(HP1, EXP1, M1, mm, E2 % 2);
    }
    HP1 = ceil(HP1 * 83 / 100.0);
    EXP1 = ceil(EXP1 * 117 / 100.0);
    clamphp(HP1);
    clampexp(EXP1);

    S = 0;
    while (S * S <= EXP1)
        S++;                                     // greatest S  < EXP1;
    if (EXP1 - (S - 1) * (S - 1) < S * S - EXP1) // S nearest EXP1
        S = S - 1;
    double P2;
    if (EXP1 >= S * S)
        P2 = 1;
    else
        P2 = ((double)EXP1 / S / S + 80) / 123;

    // Road 3
    int P[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    double P3;
    if (E2 < 10)
        P3 = P[E2] / 100.0;
    else
        P3 = P[(E2 % 10 + E2 / 10) % 10] / 100.0;
    if (P1 == 1 && P2 == 1 && P3 == 1)
        EXP1 = ceil(EXP1 * 75 / 100.0);
    else
    {
        double P4 = (P1 + P2 + P3) / 3;
        if (P4 < 0.5)
        {
            HP1 = ceil(HP1 * 85 / 100.0);
            EXP1 = ceil(EXP1 * 115 / 100.0);
        }
        else
        {
            HP1 = ceil(HP1 * 90 / 100.0);
            EXP1 = ceil(EXP1 * 120 / 100.0);
        }
    }

    clamphp(HP1);
    clampexp(EXP1);
    clampm(M1);

    return HP1 + EXP1 + M1;
}

// Task 3
int sherlockCo(int table[10][10], int r, int c)
{
    int i = 0, j = 0;
    int ans = table[r][c];

    if (c - r >= 0)
    {
        i = 0;
        j = c - r;
    }
    else if (c - r < 0)
    {
        i = r - c;
        j = 0;
    }

    while (i < 10 && j < 10)
    {
        ans = max(ans, table[i][j]);
        i++;
        j++;
    }

    if (c + r > 9)
    {
        i = c + r - 9;
        j = 9;
    }
    else if (c + r <= 9)
    {
        i = 0;
        j = c + r;
    }

    while (i < 10 && j >= 0)
    {
        ans = max(ans, table[i][j]);
        i++;
        j--;
    }
    return ans;
}

int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3)
{
    // TODO: Complete this function
    // change array taxi -> different name table
    if (E3 < 0 || E3 > 99)
        return -99;
    clamphp(HP1);
    clampexp(EXP1);
    clamphp(HP2);
    clampexp(EXP2);

    int table[10][10];

    // (a,b) is meetpoint
    int a = 0;
    int b = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            table[i][j] = (E3 * j + i * 2) * (i - j);
            if (table[i][j] > E3 * 2)
                a++;
            if (table[i][j] < -E3)
                b++;
        }
    }

    while (a > 9)
        a = (a / 10) + (a % 10);
    while (b > 9)
        b = (b / 10) + (b % 10);

    int atMeetpoint = abs(sherlockCo(table, a, b));

    if (atMeetpoint >= abs(table[a][b]))
    {
        EXP1 = ceil(EXP1 * 112 / 100.0);
        EXP2 = ceil(EXP2 * 112 / 100.0);
        HP1 = ceil(HP1 * 110 / 100.0);
        HP2 = ceil(HP2 * 110 / 100.0);
        clamphp(HP1);
        clampexp(EXP1);
        clamphp(HP2);
        clampexp(EXP2);
        return atMeetpoint;
    }

    EXP1 = ceil(EXP1 * 88 / 100.0);
    EXP2 = ceil(EXP2 * 88 / 100.0);
    HP1 = ceil(HP1 * 90 / 100.0);
    HP2 = ceil(HP2 * 90 / 100.0);
    clamphp(HP1);
    clampexp(EXP1);
    clamphp(HP2);
    clampexp(EXP2);

    return table[a][b];
}

// Task 4
bool isSpecialChar(char c)
{
    return c == '@' || c == '#' || c == '%' || c == '$' || c == '!';
}

int checkPassword(const char *s, const char *email)
{
    string password = s;
    string email1 = email;
    // Check password length
    if (password.length() < 8)
        return -1;
    if (password.length() > 20)
        return -2;

    // Extract username from email
    string username;
    int pos = 0;
    while (pos < email1.length() && email1[pos] != '@')
    {
        username = username + email1[pos];
        pos++;
    }

    // Check if username exists in password
    int found = password.find(username);
    if (found != -1)
        return -(300 + found);

    // Check for consecutive three similar characters
    for (int i = 0; i < password.length() - 2; i++)
    {
        if (password[i] == password[i + 1] && password[i] == password[i + 2])
            return -(400 + i);
    }

    // Check for presence of special characters
    bool hasSpecialChar = false;
    for (char c : password)
    {
        if (isSpecialChar(c))
        {
            hasSpecialChar = true;
            break;
        }
    }
    if (!hasSpecialChar)
        return -5;

    // Check for invalid characters
    for (int i = 0; i < password.length(); i++)
    {
        char c = password[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || isSpecialChar(c)))
            return i;
    }

    // Password meets all criteria
    return -10;
}

// Task 5

// find which passwords (TheMost) appear most frequently in arr_pwds
struct Password
{
    int len;
    int pos;
    int count;
};

int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    string arr_pwds1[10000];
    for (int i = 0; i < num_pwds; i++)
    {
        arr_pwds1[i] = arr_pwds[i];
    }
    Password pwds[10000] = {0};
    for (int i = 0; i < num_pwds; i++)
    {
        pwds[i].pos = i;
        pwds[i].len = arr_pwds1[i].size();
        for (int j = 0; j < num_pwds; j++)
        {
            if (arr_pwds1[i] == arr_pwds1[j] && i > j)
            {
                pwds[i].count = -1;
                break;
            }
            if (arr_pwds1[i] == arr_pwds1[j])
                pwds[i].count++;
        }
    }
    for (int i = 0; i < num_pwds - 1; i++)
    {
        for (int j = 0; j < num_pwds - i - 1; j++)
        {
            if (pwds[j].count > pwds[j + 1].count)
                swap(pwds[j], pwds[j + 1]);
            else if (pwds[j].count == pwds[j + 1].count)
            {
                if (pwds[j].len > pwds[j + 1].len)
                    swap(pwds[j], pwds[j + 1]);
                else if (pwds[j].len == pwds[j + 1].len)
                {
                    if (pwds[j].pos < pwds[j + 1].pos)
                        swap(pwds[j], pwds[j + 1]);
                }
            }
        }
    }
    return pwds[num_pwds - 1].pos;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
