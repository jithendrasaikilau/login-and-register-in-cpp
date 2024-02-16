#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
class User 
{
private:
    string username;
    string password;
public:
    User(string &name, string &pass)
    {
        username=name;
		password=pass;
    }
    string &getUsername() 
	{ 
	    return username; 
	}
    string &getPassword() 
	{ 
	   return password; 
	}
};
class login_and_register
{
public:
    void run();

private:
    void displayMenu();
    bool login();
    bool is_username_and_password_valid(string &username, string &password);
    bool checkCaptcha(string &captcha, string &user_captcha);
    string generateCaptcha();
    void register_user();
    bool is_username_valid(string &user);
    bool is_password_valid(string &pass);
    bool has_uppercase(const string &pass);
    bool has_lowercase(const string &pass);
    bool has_digit(const string &pass);
    bool has_special_character(const string &pass);
    bool is_username_already_exists(const string &user);
    bool is_password_already_exists(const string &pass);
    void forgot();
    void search_by_username();
    void search_by_password();
};

int main()
{
    login_and_register obj;
    obj.run();
    return 0;
}

void login_and_register::run()
{
    int choice;
    while (true)
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (login())
                break;
            else
                return;
        case 2:
            register_user();
            break;
        case 3:
            forgot();
            break;
        case 4:
            cout << "Thanks for using this program.\n\n";
            return;
        default:
            cout << "You've made a mistake. Try again.\n"<< endl;
            system("pause");
        }
    }
}

void login_and_register::displayMenu()
{
    system("CLS");
    cout << "              Welcome to login page        \n";
    cout << "1. LOGIN" << endl;
    cout << "2. REGISTER" << endl;
    cout << "3. FORGOT PASSWORD (or) USERNAME" << endl;
    cout << "4. Exit" << endl;
}

bool login_and_register::login()
{
    string user, pass;
    int tries = 3;
    int success = 0;
    while (tries && !success)
    {
        system("CLS");
        cout << "Please enter Username: ";
        cin >> user;
        cout << "Please enter Password: ";
        cin >> pass;
        string captcha = generateCaptcha();
        cout << "Captcha:" << captcha;
        string usr_captcha;
        cout << "\nEnter above CAPTCHA: ";
        cin >> usr_captcha;

        if (is_username_and_password_valid(user, pass))
        {
            if (checkCaptcha(captcha, usr_captcha))
            {
                cout << "\nHello, " << user << "\n<LOGIN SUCCESSFUL>\nThanks for logging in..\n";
                system("pause");
            }
            else
            {
                cout << "Captcha Invalid  !!!" << endl;
                system("pause");
            }
            success = 1;
            return true;
        }
        else
        {
            cout << "\nLOGIN ERROR\nPlease check your username and password\n\n";
            tries = tries - 1;
            if (tries > 0)
            {
                cout << "You have more " << tries << " chances only\n";
                system("pause");
            }
        }
    }
    if (tries < 1)
    {
        cout << "Your three chances are over program is exited!!!";
        return false;
    }
}

bool login_and_register::is_username_and_password_valid(string &username, string &password)
{
    ifstream file("database.txt");
    string u, p, e;
    while (file >> u >> p )
    {
        if (u == username && p == password)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool login_and_register::checkCaptcha(string &captcha, string &user_captcha)
{
    return captcha.compare(user_captcha) == 0;
}

string login_and_register::generateCaptcha()
{
    int n = 4;
    time_t t;
    srand((unsigned)time(&t));
    const char *chrs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string captcha = "";
    while (n)
    {
        captcha += chrs[rand() % 62];
        n--;
    }

    return captcha;
}

void login_and_register::register_user()
{
    system("CLS");
    string user, pass;
    cout << "Enter the username\n username must contain at least 8 characters: ";
    cin >> user;

    if (is_username_already_exists(user))
    {
        cout << "Username already exists. Please choose a different username.\n";
        system("pause");
        return;
    }

    cout << "Enter the password \n Password must contain at least 8 characters and should have one lowercase, one uppercase, one digit, one special character: \n";
    cin >> pass;

    if (is_password_already_exists(pass))
    {
        cout << "Password already exists. Please choose a different password.\n";
        system("pause");
        return;
    }


    if (is_username_valid(user) && is_password_valid(pass))
    {
        User newUser(user, pass);

        ofstream file("database.txt", ios::app);
        file << newUser.getUsername() << ' ' << newUser.getPassword() << endl;

        cout << "\nRegistration Successful\n";
        system("pause");
    }
    else
    {
        cout << "Enter credentials correctly\n";
        system("pause");
    }
}

bool login_and_register::is_username_already_exists(const string& user)
{
    ifstream file("database.txt");
    string u, p;
    while (file >> u >> p)
    {
        if (u == user)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool login_and_register::is_password_already_exists(const string& pass)
{
    ifstream file("database.txt");
    string u, p;
    while (file >> u >> p)
    {
        if (p == pass)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool login_and_register::is_username_valid(string &user)
{
    return user.length() >= 8;
}

bool login_and_register::is_password_valid(string &pass)
{
    return pass.length() >= 8 && has_uppercase(pass) && has_lowercase(pass) && has_digit(pass) && has_special_character(pass);
}

bool login_and_register::has_uppercase(const string &pass)
{
    for (int i = 0; i < pass.length(); i++)
    {
        if (isupper(pass[i]))
        {
            return true;
        }
    }
    return false;
}

bool login_and_register::has_lowercase(const string &pass)
{
    for (int i = 0; i < pass.length(); i++)
    {
        if (islower(pass[i]))
        {
            return true;
        }
    }
    return false;
}

bool login_and_register::has_digit(const string &pass)
{
    for (int i = 0; i < pass.length(); i++)
    {
        if (isdigit(pass[i]))
        {
            return true;
        }
    }
}
bool login_and_register::has_special_character(const string &pass)
{
    string specialChars = "!@#$%^&*()-_+=<>?{}[]|:;'',.~";
    for (int i = 0; i < pass.length(); i++)
    {
        if (specialChars.find(pass[i]) != string::npos)
        {
            return true;
        }
    }
    return false;
}

void login_and_register::forgot()
{
    system("CLS");
    int choice;
    cout << "1. Search your ID by username" << endl;
    cout << "2. Search your ID by password" << endl;
    cout << "3. Main menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        search_by_username();
        break;
    case 2:
        search_by_password();
        break;
    case 3:
        break;
    default:
        cout << "Sorry, you entered a wrong choice. Try again" << endl;
        break;
    }
}


void login_and_register::search_by_username()
{
    string username;
    cout << "Enter your username: ";
    cin >> username;

    ifstream file("database.txt");
    string u, p;
    while (file >> u >> p)
    {
        if (u == username)
        {
            cout << "\nHurray, account found\n";
            cout << "\nYour password is " << p << endl;
            system("pause");
            file.close();
            return;
        }
    }
    file.close();
    cout << "\nSorry, your userID is not found in our database\n";
    system("pause");
}

void login_and_register::search_by_password()
{
    string password;
    cout << "Enter the password: ";
    cin >> password;

    ifstream file("database.txt");
    string u, p;
    while (file >> u >> p )
    {
        if (p == password)
        {
            cout << "\nYour password is found in the database\n";
            cout << "Your ID is: " << u << endl;
            system("pause");
            file.close();
            return;
        }
    }
    file.close();
    cout << "Sorry, we cannot find your password in our database\n";
    system("pause");
}
