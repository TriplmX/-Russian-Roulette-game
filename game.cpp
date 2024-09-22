#include <iostream>
#include <string>
#include <thread>
#include <exception>
#include <typeinfo>
using namespace std;

int inputHandler() {
    string cinC;
    getline(cin, cinC);
    if (cinC.length() != 1 || !isdigit(cinC[0]))
        return -1;
    int value = cinC[0] - '0';
    return value;
}
bool isIntType(const std::type_info& type) {
    return type == typeid(int);
}

class Player {
    string _name;
    unique_ptr<int> _exp = make_unique<int>(0);;
    unique_ptr<int> _numOfRoundsPlayed = make_unique<int>(0);
public:
    Player(const char* name) {
        setName(name);
    }
    ~Player() {}

    friend void operator++ (Player& obj) {
        obj.incrementPlayedRounds();
    }
    friend void operator+= (Player& obj, int exp) {
        if (exp >= 0) {
            obj.setExp(exp);
        }
    }

    void operator= (string newName) {
        setName(newName.c_str());
    }

    Player& operator= (const Player& otherPlayer) {
        if (this != &otherPlayer) {
            setName(otherPlayer.getName().c_str());
            setRoundsForCopyCases(otherPlayer.getRounds());
            setExp(otherPlayer.getExp());
        }
        return *this;
    }

    friend ostream& operator<< (ostream& COUT, const Player& obj) {
        obj.coutStatus();
        return COUT;
    }
    string getName() const { return _name; }
    int getExp() const { return *_exp; }
    int getRounds() const { return *_numOfRoundsPlayed; }

protected:
    void coutStatus() const {
        cout << "  * Name: " << getName() << endl;
        cout << "  * * Exp: " << getExp() << endl;
        cout << "  * * * Number of played rounds: " << getRounds() << endl;

    }
    void setName(const char* name) {
        _name = name;
    }
    void setExp(int exp = 0) {
        if (exp != 0) {
            *_exp += exp;
        }
        else {
            *_exp = exp;
        }
    }
    void setRoundsForCopyCases(int rounds) {
        *_numOfRoundsPlayed = rounds;
    }
    void incrementPlayedRounds() {
        (*_numOfRoundsPlayed)++;
    }


};

class Game {
    Player _player;
    string _info = "this is the info";
    const string _title = "RUSSIAN ROULLETE 2";
    bool _isGameActive = true;
    bool _isSpecialUnlocked = false;

public:
    Game(string name) : _player(name.c_str()) {
        //titleScreen();
        mainMenu();
    }

    friend ostream& operator<< (ostream& COUT, const Game& obj) {
        cout << obj._info << endl;

        return COUT;
    }

    void saveSystem() {

    }

    ~Game()
    {
        cout << "  Thank you for playing!\n\n";
    }
private:
    void incorrectInputWarning() {
        system("cls");
        cout << "\n  I N C O R R E C T  I N P U T !\n\n\n";
        cout << "  * Press any key to try again... ";
        cin.get();
    }
    void titleScreen() {
        system("cls");
        cout << "\n\n\n\n                                                   ";
        for (int i = 0; i < _title.length(); i++)
        {
            cout << _title[i];
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        cout << "\n\n                                             * Press any key to continue * \n";

        cin.get();
    }

    void mainMenu() {
        do
        {
            int menuSelection;
            do
            {
                system("cls");
                cout << "  | W E L C O M E " << _player.getName() << "!\n\n";
                cout << "    [1] [ P L A Y ] \n";
                cout << "    [2] [ O P T I O N S ] \n";
                cout << "    [3] [ E X I T ] \n\n";
                cout << "  | Y o u r  i n p u t: ";
                menuSelection = inputHandler();
                if (menuSelection < 1 || menuSelection > 3) {
                    incorrectInputWarning();
                }
            } while (menuSelection < 1 || menuSelection > 3);
            system("cls");
            switch (menuSelection)
            {
            case 1: play();
                break;
            case 2: settings();
                break;
            case 3: exitTheGame();
                break;
            default:break;
            }
        } while (_isGameActive);
    }

    void play() {
        int playSelection;
        int debugCode = 9;
        int maxValueForPlaySection;
        do
        {
            do
            {
                maxValueForPlaySection = 2 + _isSpecialUnlocked;
                cout << "  ||| Stats for " << _player.getName() << " -> EXP: " << _player.getExp()
                    << " | Rounds played: " << _player.getRounds() << " |||\n\n";
                cout << "    [1] [ S T A R T ] \n";
                cout << "    [2] [ B A C K ] \n";
                if (_isSpecialUnlocked)
                    cout << "    [3] [ H A R D C O R E ] \n";
                cout << "\n";
                cout << "  | Y o u r  i n p u t: ";
                cout << "\n\n  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
                    << "   R U L E S: You have [3 - 5] slots for bullets in the chamber, yet there is only one bullet.\n   You must guess in which chamber the bullet is not.\n"
                    << "   Every round gives you the amount of EXP based on the index of the round and the multiplier.\n   In that fashion, round [ten] will give you [10] exp on [EASY] difficulty.\n"
                    << "   Your stats will be tracked and if you collect [100] exp, you will unlock a special [GAME MODE]\n"
                    << "   Remember! - If you die, you lose your earned exp, but you can always back out!\n";
                cout << "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
                std::cout << "\033[10A";  // Move cursor up 9 lines
                std::cout << "\033[24C";  // Move cursor 24 spaces right
                playSelection = inputHandler();
                if ((playSelection < 1 || playSelection > maxValueForPlaySection) && playSelection != debugCode)
                    incorrectInputWarning();
                system("cls");
            } while ((playSelection < 1 || playSelection > maxValueForPlaySection) && playSelection != debugCode);
            if (playSelection == debugCode)
                _isSpecialUnlocked = true;
            if (playSelection == 1)
                gameplay();
            if (playSelection == 3)
                specialGameplay();

        } while (playSelection != 2);
    }


    void settings() {
        int settingsSelection;
        do
        {
            do
            {
                cout << "  | O P T I O N S |||| \n\n";
                cout << "    [1] [ C H A N G E  Y O U R  N A M E ] \n";
                cout << "    [2] [ G O  B A C K ] \n\n";
                cout << "  | Y o u r  i n p u t: ";
                settingsSelection = inputHandler();
                if (settingsSelection < 1 || settingsSelection > 2) {
                    incorrectInputWarning();
                }
            } while (settingsSelection < 1 || settingsSelection > 2);
            if (settingsSelection == 1) {
                string tempNewName;
                system("cls");
                cout << "  * E n t e r  n e w  n a m e  or  '0'  t o  a b o r t : ";
                getline(cin, tempNewName);
                if (tempNewName[0] != '0') {
                    _player = tempNewName;
                    cout << "\n   N A M E  S U C C E S S F U L L Y  C H A N G E D !  P r e s s  a n y  k e y . . .\n";
                    cin.get();
                }
                system("cls");
            }
        } while (settingsSelection != 2);
    }

    void exitTheGame() {
        int exitInput;
        do
        {
            cout << "   ARE YOU SURE YOU WANT TO EXIT?\n";
            cout << "    [1] [ Y E S ] \n";
            cout << "    [2] [ N O ] \n\n";
            cout << "    | Y o u r  i n p u t: ";
            exitInput = inputHandler();
            if (exitInput < 1 || exitInput> 2)
            {
                incorrectInputWarning();
            }
        } while (exitInput < 1 || exitInput> 2);
        if (exitInput == 1)
            _isGameActive = false;
    }

    void gameplay() {
        int* c_exp = new int(0), * c_rounds = new int(0);
        int* const minBulletNum = new int(1);
        int* const maxBulletNum = new int();
        int* choice = new int();
        int* bulletPosition = new int();
        int* dif = new int();
        int* multiplier = new int();
        do
        {
            cout << " * Choose your difficulty: \n";
            cout << "   * [1] E A S Y - 5 chambers, multiplier x1\n";
            cout << "   * [2] H A R D - 3 chambers, multiplier x2\n";
            cout << "   * YOUR CHOICE: ";
            *dif = inputHandler();
            if (*dif < 1 || *dif> 2)
                incorrectInputWarning();
            system("cls");
        } while (*dif < 1 || *dif> 2);
        if (*dif == 1) {
            *maxBulletNum = 5;
            *multiplier = 1;
        }
        else {
            *maxBulletNum = 3;
            *multiplier = 2;
        }

        do
        {
            *bulletPosition = rand() % *maxBulletNum + 1;
            do
            {
                cout << "  [*] Current difficulty: " << (*maxBulletNum == 5 ? "[EASY]" : "[HARD]") << endl;
                cout << "  | Current EXP gained: " << *c_exp << endl;
                cout << "  | Current Rounds played: " << *c_rounds << endl;
                cout << "  * The BULLET is in one the [" << *maxBulletNum
                    << "] chambers(1 - " << *maxBulletNum << "), choose wisely, or ENTER '0' to[BACK OUT]: ";
                *choice = inputHandler();
                if ((*choice < *minBulletNum || *choice > *maxBulletNum) && *choice != 0) {
                    incorrectInputWarning();
                    system("cls");
                }
            } while ((*choice < *minBulletNum || *choice > *maxBulletNum) && *choice != 0);
            if (*choice == *bulletPosition) {
                deathScreen();
                *c_exp = 0;
                *c_rounds = 0;
            }
            else {
                if (*choice != 0) {
                    cout << "\n\n\n  * Y O U  S U R V I V E D ! - - > Press any key to continue...";
                    (*c_rounds)++;
                    *c_exp += *c_rounds * (*multiplier);
                }
                else
                    cout << "\n\n\n  * I T  W A S  A  G O O D  R U N ! - - > Press any key to continue...";
                cin.get();
            }
            if (*choice == 0)
                saveStats(*c_exp, *c_rounds);
            system("cls");
        } while (*choice != 0);
        delete c_exp;
        delete c_rounds;
        delete minBulletNum;
        delete maxBulletNum;
        delete choice;
        delete bulletPosition;
        delete dif;
        delete multiplier;
    }

    void deathScreen() {
        system("cls");
        cout << "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
        cout << "  *  *  *  *  *  *  Y  O  U    D  I  E  D  *  *  *  *  *  *  *  *\n\n";
        cout << "  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n";
        cout << "  Press any key to continue...";
        cin.get();
    }

    void saveStats(int expEarned, int roundsPlayed) {
        for (int i = 0; i < roundsPlayed; i++)
        {
            ++_player;
        }
        _player += expEarned;
    };

    void specialGameplay() {
        cout << "Special Gameplay...\n";
        cin.get();
        system("cls");
    }
};


string preStartDetailTaker() {
    string temp;
    cout << "  * What is your name: \n    ";
    getline(cin, temp);
    return temp;
}

int main()
{
    srand(time(NULL));

    Game* game = new Game(preStartDetailTaker());

    delete game;

    return 0;
}

