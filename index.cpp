#include <bits/stdc++.h>
#include <conio.h>
#include <iostream>
using namespace std;

class Voter
{
public:
    string name;
    int age;
    string state;
    int voterId;
    int party;
    Voter *next;

    Voter(string name, int age, string state, int voterId, int party)
    {
        this->name = name;
        this->age = age;
        this->state = state;
        this->voterId = voterId;
        this->party = party;
        next = NULL;
    }
};

class VoterFunctions
{
public:
    Voter *head = NULL;
    Voter *tail = NULL;

    void InitializeFromDataFile(const string &filename)
    {
        ifstream inFile(filename);

        if (inFile.is_open())
        {
            string name, state;
            int age, voterId, party;

            while (inFile >> name >> age >> state >> voterId >> party)
            {
                Insert(name, age, state, voterId, party);
            }

            inFile.close();
        }
        else
        {
            cout << "Error: Unable to open the file." << endl;
        }
    }

    void Insert(string name, int age, string state, int voterId, int party)
    {
        Voter *temp = new Voter(name, age, state, voterId, party);

        if (head == NULL)
        {
            head = tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = tail->next;
        }
    }

    void Display()
    {
        Voter *temp = head;

        while (temp != NULL)
        {
            cout << "\033[1;36mName:\033[0m " << temp->name << endl;
            cout << "\033[1;36mAge:\033[0m " << temp->age << endl;
            cout << "\033[1;36mState:\033[0m " << temp->state << endl;
            cout << "\033[1;36mVoter ID:\033[0m " << temp->voterId << endl;

            switch (temp->party)
            {
            case 1:
                cout << "\033[1;32mVoted for: BJP\033[0m";
                break;

            case 2:
                cout << "\033[1;34mVoted for: AAP\033[0m";
                break;

            case 3:
                cout << "\033[1;35mVoted for: Congress\033[0m";
                break;

            case 4:
                cout << "\033[1;33mVoted for: SVP\033[0m";
                break;

            case 5:
                cout << "\033[1;37mNOTA\033[0m";
                break;

            default:
                cout << "\033[1;31mNo valid option selected\033[0m";
                break;
            }
            cout << endl
                 << endl;
            temp = temp->next;
        }
    }

    bool CheckId(int Id)
    {
        Voter *temp = head;

        while (temp != NULL)
        {
            if (temp->voterId == Id)
            {
                return false;
            }

            temp = temp->next;
        }
        return true;
    }

    void SaveToFile()
    {
        ofstream outFile("initial_data.txt", ios::app);
        if (outFile.is_open())
        {
            Voter *temp = head;

            while (temp != NULL)
            {
                outFile << temp->name << " " << temp->age << " " << temp->state << " " << temp->voterId << " " << temp->party << endl;
                temp = temp->next;
            }

            outFile.close();
            cout << "Voter information saved successfully." << endl;
        }
        else
        {
            cout << "Error: Unable to save voter information to the file." << endl;
        }
    }

    int count()
    {
        int cnt = 0;
        Voter *temp = head;

        while (temp != NULL)
        {
            cnt++;
            temp = temp->next;
        }

        return cnt;
    }

    void WinningParty()
    {

        cout << endl
             << endl;
        const int PARTIES = 5;
        int partyVotes[PARTIES] = {0};

        Voter *temp = head;

        while (temp != NULL)
        {
            if (temp->party >= 1 && temp->party <= PARTIES)
            {
                partyVotes[temp->party - 1]++;
            }
            temp = temp->next;
        }

        cout << "Vote Results:" << endl;

        for (int i = 0; i < PARTIES; ++i)
        {
            switch (i + 1)
            {
            case 1:
                cout << "BJP: ";
                break;
            case 2:
                cout << "AAP: ";
                break;
            case 3:
                cout << "Congress: ";
                break;
            case 4:
                cout << "SVP: ";
                break;
            case 5:
                cout << "NOTA: ";
                break;
            default:
                break;
            }

            cout << partyVotes[i] << " votes" << endl;
        }

        int maxVotesIndex = 0;

        for (int i = 1; i < PARTIES; ++i)
        {
            if (partyVotes[i] > partyVotes[maxVotesIndex])
            {
                maxVotesIndex = i;
            }
        }

        switch (maxVotesIndex + 1)
        {
        case 1:
            cout << "BJP is currently winning!" << endl;
            break;
        case 2:
            cout << "AAP is currently winning!" << endl;
            break;
        case 3:
            cout << "Congress is currently winning!" << endl;
            break;
        case 4:
            cout << "SVP is currently winning!" << endl;
            break;
        case 5:
            cout << "NOTA is currently winning!" << endl;
            break;
        default:
            break;
        }
    }

    void DeleteVoter(int voterId)
    {
        Voter *current = head;
        Voter *previous = nullptr;

        while (current != nullptr && current->voterId != voterId)
        {
            previous = current;
            current = current->next;
        }

        if (current != nullptr)
        {
            if (previous != nullptr)
            {

                previous->next = current->next;
            }
            else
            {

                head = current->next;
            }

            SaveToFile();

            delete current;

            cout << "Voter with ID " << voterId << " has been successfully deleted." << endl;
        }
        else
        {
            cout << "Voter with ID " << voterId << " not found." << endl;
        }
    }

    void printHeading()
    {
        system("CLS");

        cout << "\033[1;32m========================================================================================================================================================================================================\033[0m" << endl;
        cout << "\033[1;32m\t\t\t\t\t\t\t\t\t\t\t\t\033[1;32mV  O  T  I  N  G    S  Y  S  T  E  M\033[0m" << endl;
        cout << "\033[1;32m========================================================================================================================================================================================================\033[0m" << endl;
    }
};

void printMenu()
{
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t===== Voting System Menu =====\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\033[1;36m1. Cast a Vote\033[0m\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\033[1;36m2. See Winning Party\033[0m\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\033[1;36m3. See Total Number of Votes Casted\033[0m\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\033[1;36m4. Delete a voter by ID\033[0m\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\033[1;36m5. Exit\033[0m\n";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\tEnter your choice (1-5): ";
}

bool authenticateUser()
{
    string username, password;
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\n\t\t\t\t\t\t\t\t================================ Login ================================" << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your username: ";
    cin >> username;

    cout << "\t\t\t\t\t\t\t\t\t\t\tEnter your password: ";
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == 13)
            break;
        password.push_back(ch);
        cout << '*';
    }

    cin.ignore();

    return (username == "DSP" && password == "MyDSP1");
}

int isValidSudoku(const vector<vector<char>> &A)
{
    unordered_map<char, int> mp;
    for (vector<char> s : A)
    {
        for (int i = 0; i < 9; i++)
        {
            if (s[i] == '.')
                continue;
            if (mp.count(s[i]) != 0)
            {
                // cout<<"A|";
                return 0;
            }
            mp[s[i]]++;
        }
        mp.clear();
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (A[j][i] == '.')
                continue;
            if (mp.count(A[j][i]) != 0)
            {
                // cout<<"B|";
                return 0;
            }
            mp[A[j][i]]++;
        }
        mp.clear();
    }
    vector<vector<int>> vv = {{0, 0}, {0, 3}, {0, 6}, {3, 0}, {3, 3}, {3, 6}, {6, 0}, {6, 3}, {6, 6}};
    for (auto v : vv)
    {
        for (int i = v[0]; i < v[0] + 3; i++)
        {
            for (int j = v[1]; j < v[1] + 3; j++)
            {
                if (A[i][j] == '.')
                    continue;
                if (mp.count(A[i][j]) != 0)
                {
                    // cout<<"C|";
                    return 0;
                }
                mp[A[i][j]]++;
            }
        }
        mp.clear();
    }
    return 1;
}

void recur(vector<vector<int>> &sp, int depth, int blank, vector<vector<char>> A, vector<vector<char>> &ans)
{
    if (!ans.empty())
        return;
    if (depth == blank)
    {
        ans = A;
        return;
    }
    else if (depth < blank)
    {
        int c1 = sp[depth][0];
        int c2 = sp[depth][1];
        for (int i = 1; i <= 9; i++)
        {
            A[c1][c2] = (char)('0' + i);
            if (isValidSudoku(A) == 0)
                continue;
            recur(sp, depth + 1, blank, A, ans);
        }
    }
}

void solveSudoku(vector<vector<char>> &A)
{
    int blank = 0;
    vector<vector<int>> sp;
    vector<vector<char>> ans;
    for (int j = 0; j < 9; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            if (A[j][i] == '.')
            {
                blank++;
                sp.push_back({j, i});
            }
        }
    }
    recur(sp, 0, blank, A, ans);
    A = ans;
}

char form[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
string n1, n2;
char token = 'x';
bool draw = false;
int digit;
int row, column;
string coloredToken(char token)
{
    if (token == 'x')
    {
        return "\033[1;31mX\033[0m";
    }
    else if (token == '0')
    {
        return "\033[1;34mO\033[0m";
    }
    else
    {
        return string(1, token);
    }
}

void printBoard()
{
    cout << "\n";
    cout << " " << coloredToken(form[0][0]) << " | " << coloredToken(form[0][1]) << " | " << coloredToken(form[0][2]) << "\n";
    cout << "___|___|___\n";
    cout << "   |   |   \n";
    cout << " " << coloredToken(form[1][0]) << " | " << coloredToken(form[1][1]) << " | " << coloredToken(form[1][2]) << "\n";
    cout << "___|___|___\n";
    cout << "   |   |   \n";
    cout << " " << coloredToken(form[2][0]) << " | " << coloredToken(form[2][1]) << " | " << coloredToken(form[2][2]) << "\n";
    cout << "   |   |   \n";
}

void getPlayerInput()
{
    if (token == 'x')
    {
        cout << n1 << " please enter the digit of the place you want to place your token: ";
    }
    if (token == '0')
    {
        cout << n2 << " please enter the digit of the place you want to place your token: ";
    }
    cin >> digit;

    if (digit < 1 || digit > 9)
    {
        cout << "Invalid input! Please enter a number between 1 and 9." << endl;
        getPlayerInput();
    }
    else
    {
        row = (digit - 1) / 3;
        column = (digit - 1) % 3;
    }

    if (form[row][column] != 'x' && form[row][column] != '0')
    {
        if (token == 'x')
        {
            form[row][column] = 'x';
            token = '0';
        }
        else
        {
            form[row][column] = '0';
            token = 'x';
        }
    }
    else
    {
        cout << "This space is already filled. Please choose another position." << endl;
        getPlayerInput();
    }
}

bool checkWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (form[i][0] == form[i][1] && form[i][0] == form[i][2] || form[0][i] == form[1][i] && form[0][i] == form[2][i])
        {
            return true;
        }
    }
    if (form[0][0] == form[1][1] && form[0][0] == form[2][2] || form[0][2] == form[1][1] && form[0][2] == form[2][0])
    {
        return true;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (form[i][j] != 'x' && form[i][j] != '0')
            {
                return false;
            }
        }
    }
    draw = true;
    return false;
}

int main()
{
    bool runProgram = true;

    while (runProgram)
    {
        system("CLS");

        cout << "\n\n\033[1;35m********************************************************************************************************************************************************************************************************\033[0m" << endl;
        cout << "\033[1;35m                                                                       G  A  M  E  S     A  N  D     V  O  T  I  N  G     S  Y  S  T  E  M  \033[0m" << endl;
        cout << "\033[1;35m********************************************************************************************************************************************************************************************************\033[0m" << endl;

        cout << "\n\n\033[1;32mPress Enter to continue...\033[0m";
        cin.get();
        cin.ignore();

        system("CLS");

        bool isAuthenticated = authenticateUser();

        system("CLS");

        if (isAuthenticated)
        {
            int choice;
            bool runProgramChoice = true;

            while (runProgramChoice)
            {
                cout << "\n\n\033[1;33m================= Main Menu =====================\033[0m" << endl;
                cout << "\033[1;36m1. Play Sudoku\033[0m" << endl;
                cout << "\033[1;36m2. Play Tic Tac Toe\033[0m" << endl;
                cout << "\033[1;36m3. Vote for a Political Party\033[0m" << endl;
                cout << "\033[1;36m4. Exit\033[0m" << endl;
                cout << "\033[1;33m===================================================\033[0m" << endl;
                cout << "\033[1;36mEnter your choice: \033[0m";
                cin >> choice;

                switch (choice)
                {
                case 1:
                {

                    vector<vector<char>> A1 = {
                        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

                    vector<vector<char>> A2 = {
                        {'8', '.', '.', '.', '.', '.', '.', '.', '.'},
                        {'.', '.', '3', '6', '.', '.', '.', '.', '.'},
                        {'.', '7', '.', '.', '9', '.', '2', '.', '.'},
                        {'.', '5', '.', '.', '.', '7', '.', '.', '.'},
                        {'.', '.', '.', '.', '4', '5', '7', '.', '.'},
                        {'.', '.', '.', '1', '.', '.', '.', '3', '.'},
                        {'.', '.', '1', '.', '.', '.', '.', '6', '8'},
                        {'.', '.', '8', '5', '.', '.', '.', '1', '.'},
                        {'.', '9', '.', '.', '.', '.', '4', '.', '.'}};

                    solveSudoku(A1);

                    cout << "Solved Sudoku - Test Case 1:" << endl;
                    for (int i = 0; i < 9; ++i)
                    {
                        for (int j = 0; j < 9; ++j)
                        {
                            if (A1[i][j] == '.')
                                cout << "\033[1;37m. \033[0m";
                            else
                                cout << "\033[1;32m" << A1[i][j] << " \033[0m";

                            if (j == 2 || j == 5)
                                cout << "\033[1;33m| \033[0m";
                        }
                        cout << endl;
                        if (i == 2 || i == 5)
                            cout << "\033[1;33m------+-------+------\033[0m" << endl;
                    }

                    solveSudoku(A2);

                    cout << "\nSolved Sudoku - Test Case 2:" << endl;
                    for (int i = 0; i < 9; ++i)
                    {
                        for (int j = 0; j < 9; ++j)
                        {
                            if (A2[i][j] == '.')
                                cout << "\033[1;37m. \033[0m";
                            else
                                cout << "\033[1;32m" << A2[i][j] << " \033[0m";

                            if (j == 2 || j == 5)
                                cout << "\033[1;33m| \033[0m";
                        }
                        cout << endl;
                        if (i == 2 || i == 5)
                            cout << "\033[1;33m------+-------+------\033[0m" << endl;
                    }
                }
                break;

                case 2:
                    cout << "Enter the name of the first player: ";
                    cin.ignore();
                    getline(cin, n1);

                    cout << "Enter the name of the second player: ";
                    getline(cin, n2);

                    cout << n1 << " is player 1, so he/she will play with '\033[1;31mX\033[0m'." << endl;
                    cout << n2 << " is player 2, so he/she will play with '\033[1;34mO\033[0m'." << endl;

                    while (!checkWinner())
                    {
                        printBoard();
                        if (checkWinner())
                        {
                            break;
                        }
                        getPlayerInput();
                        printBoard();
                    }

                    cout << "\nGame Over!\n";

                    if (token == 'x' && !draw)
                    {
                        cout << n2 << " is the winner with '\033[1;34mO\033[0m'!" << endl;
                    }
                    else if (token == '0' && !draw)
                    {
                        cout << n1 << " is the winner with '\033[1;31mX\033[0m'!" << endl;
                    }
                    else
                    {
                        cout << "It's a tie!" << endl;
                    }

                    break;
                case 3:
                {
                    VoterFunctions V;

                    V.count();

                    V.printHeading();

                    V.InitializeFromDataFile("initial_data.txt");

                    bool continueVoting = true;

                    while (continueVoting)
                    {
                        printMenu();

                        int choice;
                        cin >> choice;

                        cout << endl
                             << endl;

                        switch (choice)
                        {
                        case 1:
                        {
                            cin.ignore();
                            cout << "Enter your Name: ";
                            string name;
                            getline(cin, name);

                            cout << "Enter your age: ";
                            int age;
                            cin >> age;

                            if (age < 18)
                            {
                                cout << "People less than 18 years of age cannot vote!" << endl;
                                break;
                            }

                            cin.ignore();
                            cout << "Enter your state: ";
                            string state;
                            getline(cin, state);

                            cout << "Enter your voterId: ";
                            int voterId;
                            cin >> voterId;

                            bool chk = V.CheckId(voterId);

                            if (!chk)
                            {
                                cout << "\033[1;31mError: Your vote could not be processed. The Voter ID you provided has already been registered and used to cast a vote in this election. Please ensure you are using the correct Voter ID and try again!\033[0m" << endl;
                                break;
                            }

                            cout << "Press 1 for BJP \nPress 2 for AAP \nPress 3 for Congress \nPress 4 for SVP \nPress 5 for NOTA \nYour Answer: ";
                            int party;
                            cin >> party;

                            V.Insert(name, age, state, voterId, party);
                            cout << endl
                                 << endl;
                            // V.Display();

                            V.SaveToFile();
                            break;
                        }

                        case 2:
                            V.WinningParty();
                            break;

                        case 3:
                            cout << "Total Number of Votes Casted: " << V.count() << endl;
                            break;

                        case 4:
                        {
                            cout << "Enter the Voter ID to delete: ";
                            int voterIdToDelete;
                            cin >> voterIdToDelete;

                            V.DeleteVoter(voterIdToDelete);
                            break;
                        }

                        case 5:
                            continueVoting = false;
                            break;

                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                            break;
                        }
                    }

                    break;
                }

                case 4:
                    cout << "\n\n\t\t\t\t\t\t\t\t\t\033[1;31mTHANK YOU FOR USING OUR PROGRAM!\033[0m" << endl;
                    exit(0);

                default:
                    cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
                }

                cout << "\n\033[1;36mDo you want to run another program? (1 for Yes, 0 for No): \033[0m";
                cin >> runProgramChoice;
            }
        }
        else
        {
            cout << "\n\033[1;31mAuthentication failed. Exiting...\033[0m" << endl;
            runProgram = false;
        }

        cout << "\n\033[1;36mDo you want to run another set of programs? (1 for Yes, 0 for No): \033[0m";
        cin >> runProgram;
    }

    return 0;
}
