#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream> 
#include <cstdlib> 
#include <ctime>   
#include <Windows.h> 
#include <vector>
#include <tuple>
#include <limits>
#include <stdexcept>

using namespace std;

// --- Utility Function for Centered Headers ---
void print_header(const string& text) {
    int screen_width = 80; // Standard console width for centering
    int padding = (screen_width - text.length()) / 2;
    cout << "\n";
    cout << setw(padding + text.length()) << setfill('=') << "" << setfill(' ') << endl;
    cout << setw(padding) << "" << "** " << text << " **" << endl;
    cout << setw(padding + text.length()) << setfill('=') << "" << setfill(' ') << endl;
    cout << "\n";
}

// Forward Declaration
class User;

// --- Progress Class ---
class Progress {
public:
    int level;
    int size;
    int experience; 

    Progress() : level(0), size(0), experience(0) {}

    void calculateProgress(const string& username) {
        // Experience to next level: 100 * (level + 1)
        int exp_needed = 100 * (level + 1);
        while (experience >= exp_needed) {
            level++;
            experience -= exp_needed;
            exp_needed = 100 * (level + 1); // Update next level requirement
        }
        // Size represents progress towards the CURRENT level (out of 10 for display)
        size = (experience * 10) / exp_needed;
        if (size > 10) size = 10; // Cap at 10 for a simple bar display
        saveProgress(username);
    }

    void DisplayProgress() {
        int Choice;
        system("CLS");
        print_header("PROGRESS");
        
        // Calculate progress needed for current level
        int exp_needed = 100 * (level + 1);
        int exp_current_level = experience;

        cout << "Your **level** is: " << level << endl;
        cout << "Experience: " << exp_current_level << " / " << exp_needed << endl;
        cout << "Your progress is: ";
        
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << "#"; // Use '#' instead of '=' for the bar
        }
        for (int i = size; i < 10; i++) {
            cout << " ";
        }
        cout << "] " << size * 10 << "%" << endl;


        cout << "\nEnter 1 to return to menu: ";
        if (!(cin >> Choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        while (Choice != 1) {
            cout << "Enter 1 only! Enter: ";
            if (!(cin >> Choice)) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void loadProgress(const string& username) {
        fstream file("Progress.txt", ios::in);
        string temp;
        bool found = false;

        if (file.is_open()) {
            while (getline(file, temp)) {
                if (temp == username) {
                    found = true;
                    if (getline(file, temp)) experience = stoi(temp);
                    if (getline(file, temp)) level = stoi(temp);
                    if (getline(file, temp)) size = stoi(temp);
                    break;
                }
                for (int i = 0; i < 3 && !file.eof(); ++i) {
                    getline(file, temp);
                }
            }
            file.close();
        }

        if (!found) {
            level = 0;
            size = 0;
            experience = 0;
            saveProgress(username);
        }
    }

    void saveProgress(const string& username) {
        vector<tuple<string, int, int, int>> progress_records;
        fstream file_in("Progress.txt", ios::in);
        string temp;
        bool user_found = false;

        if (file_in.is_open()) {
            while (getline(file_in, temp)) {
                string uname = temp;
                int exp = 0, lvl = 0, sz = 0;

                if (uname == username) {
                    user_found = true;
                    exp = experience;
                    lvl = level;
                    sz = size;
                    for (int i = 0; i < 3 && !file_in.eof(); ++i) getline(file_in, temp);
                } else {
                    try {
                        if (getline(file_in, temp)) exp = stoi(temp);
                        if (getline(file_in, temp)) lvl = stoi(temp);
                        if (getline(file_in, temp)) sz = stoi(temp);
                    } catch (...) {
                        // Handle conversion errors gracefully
                    }
                }
                progress_records.emplace_back(uname, exp, lvl, sz);
            }
            file_in.close();
        }

        if (!user_found) {
            progress_records.emplace_back(username, experience, level, size);
        }

        fstream file_out("Progress.txt", ios::out | ios::trunc); 
        for (const auto& record : progress_records) {
            file_out << get<0>(record) << endl;
            file_out << get<1>(record) << endl;
            file_out << get<2>(record) << endl;
            file_out << get<3>(record) << endl;
        }
        file_out.close();
    }
};

// --- User Class ---
class User : public Progress 
{
public:
    int age;
    float weight;
    float height;
    string username;
    string password;
    string firstname;
    string lastname;

    User(int agein = 0, float wght = 0, float hgt = 0, string usern = "", string pass = "", string firstn = "", string lastn = "")
        : age(agein), weight(wght), height(hgt), username(std::move(usern)), password(std::move(pass)), firstname(std::move(firstn)), lastname(std::move(lastn)) {}

    void operator=(const User& obj) {
        age = obj.age;
        weight = obj.weight;
        height = obj.height;
        username = obj.username;
        password = obj.password;
        firstname = obj.firstname;
        lastname = obj.lastname;
        // NOTE: Progress members (level, size, experience) are NOT copied here, 
        // as they are loaded/saved separately via the file system for the active user.
    }

    void Display() {
        int Choice;
        system("CLS");
        print_header("USER INFOPORTAL");
        cout << "PERSONAL DETAILS: " << endl;
        cout << (*this); 
        cout << "Enter 1 to return to menu: ";
        if (!(cin >> Choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        while (Choice != 1) {
            cout << "Enter 1 only! Enter: ";
            if (!(cin >> Choice)) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    friend ostream& operator<<(ostream& os, const User& obj) {
        os << "  First Name : " << obj.firstname << endl;
        os << "  Last Name : " << obj.lastname << endl;
        os << "  Password : " << obj.password << endl << endl;
        os << "APP DETAILS: " << endl;
        os << "  Username : " << obj.username << endl;
        os << "  Age : " << obj.age << endl;
        os << "  Weight : " << obj.weight << " kg" << endl;
        os << "  Height: " << obj.height << " cm" << endl << endl;
        return os;
    }
};

// --- Excercises Class ---
class Excercises
{
private:
    string* exercises;
    int* types; 

public:
    Excercises() {
        exercises = new string[8]{
            "Planks", "Pushups", "Crunches", "Squats",
            "PullUps", "JumpingJacks", "MountainClimbers", "SidePlanks"
        };

        types = new int[8]{
            100, 50, 25, 10, 10, 10, 10, 10
        };
    }

    ~Excercises() {
        delete[] exercises;
        delete[] types;
    }

    void doExercise(int index, User& currentUser) {
        system("CLS");
        cout << "You are doing exercise **" << exercises[index] << "**" << endl;

        int durationInSeconds = 5; 

        auto start = std::chrono::steady_clock::now();

        while (true) {
            auto end = std::chrono::steady_clock::now();
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

            if (elapsed_seconds.count() >= durationInSeconds) {
                cout << "Exercise **" << exercises[index] << "** completed!" << endl;
                break;
            }

            int remainingSeconds = durationInSeconds - elapsed_seconds.count();
            cout << "Time remaining: " << remainingSeconds << " seconds  \r"; 

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        cout << endl; 

        currentUser.experience += types[index];
        currentUser.calculateProgress(currentUser.username); 

        cout << "Gained **" << types[index] << "** experience points. Current Level: " << currentUser.level << endl;
        system("pause");
    }

    void DisplayEx(User& currentUser); 
    void cutomizeexcercise(User& currentUser);
    void bonusachievements(int level);
    void motivation();
};


// --- Login Class ---
class Login {
public:
    int usercount;
    User* users;
    int loggedInUserIndex = -1; 

    Login() : usercount(0), users(nullptr) {
        fstream file("Accounts.txt", ios::in);
        if (!file.is_open()) {
            file.close();
            ofstream out_file("Accounts.txt"); 
            out_file.close();
            file.open("Accounts.txt", ios::in);
        }

        string temp;
        while (getline(file, temp)) {
            for (int i = 0; i < 6 && getline(file, temp); ++i); 
            usercount++;
        }
        file.close();
        
        if (usercount > 0) {
            readfile();
        }
    }

    ~Login() {
        delete[] users;
    }

    bool readfile() {
        if (usercount == 0) return true; 

        delete[] users; 
        users = new User[usercount];

        fstream file("Accounts.txt", ios::in);
        if (!file.is_open()) {
            cout << "Error: Accounts.txt not found\n";
            return false;
        }

        for (int i = 0; i < usercount; i++) {
            string username, password, firstname, lastname, age_str, weight_str, height_str;

            if (!getline(file, username) || 
                !getline(file, password) || 
                !getline(file, firstname) || 
                !getline(file, lastname) || 
                !getline(file, age_str) || 
                !getline(file, weight_str) || 
                !getline(file, height_str)) {
                cout << "Error reading user record " << i + 1 << ". File might be corrupted.\n";
                return false;
            }

            try {
                int age = stoi(age_str);
                float weight = stof(weight_str);
                float height = stof(height_str);
                User obj(age, weight, height, username, password, firstname, lastname);
                users[i] = obj;
            } catch (const exception& e) {
                cout << "Data conversion error for user " << username << ": " << e.what() << endl;
                return false;
            }
        }
        file.close();
        return true;
    }

    void LoginDisplay(User& tempUser) {
        int Choice = 0;
        system("CLS");
        print_header("FITNESS APP LOGIN");
        cout << "1. **LOGIN** INTO EXISTING ACCOUNT." << endl;
        cout << "2. **ADD ACCOUNT** (Sign Up)" << endl;
        cout << "3. **EXIT**" << endl;

        cout << "Enter Your Choice: " << endl;
        if (!(cin >> Choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Choice = 0; 
        }

        while (Choice < 1 || Choice > 3) {
            cout << endl << "Enter Correct Choice (1-3): ";
            if (!(cin >> Choice)) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Choice = 0;
            }
        }

        if (Choice == 1) {
            bool check = false;
            string name, pass;
            system("CLS");
            print_header("ACCOUNT LOGIN");
            while (!check) {
                cout << "Enter your username: ";
                cin >> name;
                cout << "Enter your password: ";
                cin >> pass;
                loggedInUserIndex = LoginAccount(name, pass, check);
            }
            tempUser = users[loggedInUserIndex];
            tempUser.loadProgress(tempUser.username); 
        } else if (Choice == 2) {
            system("CLS");
            print_header("NEW ACCOUNT SIGNUP");
            cout << "Enter your first name: ";
            cin >> tempUser.firstname;
            cout << "Enter your last name: ";
            cin >> tempUser.lastname;
            cout << "Enter your user name: ";
            cin >> tempUser.username;
            cout << "Enter your password: ";
            cin >> tempUser.password;
            cout << "Enter your age: ";
            cin >> tempUser.age;
            cout << "Enter your weight (kg): ";
            cin >> tempUser.weight;
            cout << "Enter your height (cm): ";
            cin >> tempUser.height;
            AddAccount(tempUser);
            loggedInUserIndex = usercount - 1; 
            tempUser.loadProgress(tempUser.username); 
        } else {
            exit(0);
        }
    }

    void AddAccount(User& obj) {
        fstream file_in("Accounts.txt", ios::in);
        string temp;
        
        if (file_in.is_open()) {
            while (getline(file_in, temp)) {
                if (temp == obj.username) {
                    cout << "Account with this username already exists!\n";
                    file_in.close();
                    return;
                }
                for (int i = 0; i < 6 && getline(file_in, temp); ++i); 
            }
            file_in.close();
        }

        fstream file_app("Accounts.txt", ios::app);
        file_app << obj.username << endl;
        file_app << obj.password << endl;
        file_app << obj.firstname << endl;
        file_app << obj.lastname << endl;
        file_app << obj.age << endl;
        file_app << obj.weight << endl;
        file_app << obj.height << endl;
        file_app.close();

        cout << "Account added successfully!\n";
        
        usercount++;
        User* new_users = new User[usercount];
        for (int i = 0; i < usercount - 1; ++i) {
            new_users[i] = users[i];
        }
        new_users[usercount - 1] = obj;
        delete[] users;
        users = new_users;
        system("pause");
    }

    void updateTxt() {
        fstream file("Accounts.txt", ios::out);
        for (int i = 0; i < usercount; i++) {
            file << users[i].username << endl;
            file << users[i].password << endl;
            file << users[i].firstname << endl;
            file << users[i].lastname << endl;
            file << users[i].age << endl;
            file << users[i].weight << endl;
            file << users[i].height << endl;
        }
        file.close();
    }

    void UpdateInfo(User& currentUser) {
        int choice;
        string pass;
        float temp;
        int k = 1;

        while (k != 0) {
            system("CLS");
            print_header("INFO UPDATER");
            cout << "1: UPDATE PASSWORD\n";
            cout << "2: UPDATE AGE\n";
            cout << "3: UPDATE WEIGHT (kg)\n";
            cout << "4: UPDATE HEIGHT (cm)\n";
            cout << "0: BACK TO MENU\n";
            cin >> choice;

            if (choice == 0) break;

            if (loggedInUserIndex == -1) {
                cout << "Error: No user logged in.\n";
                system("pause");
                break;
            }

            switch (choice) {
            case 1:
                cout << "Enter your current Password First: ";
                cin >> pass;
                if (pass == currentUser.password) {
                    cout << "Enter Your Updated PassWord: ";
                    cin >> pass;
                    currentUser.password = pass;
                    users[loggedInUserIndex].password = pass;
                    cout << "Password Updated!\n";
                } else {
                    cout << "Wrong Password Entered.\n";
                }
                break;
            case 2:
                cout << "Enter Your Updated Age: ";
                cin >> choice;
                currentUser.age = choice;
                users[loggedInUserIndex].age = choice;
                cout << "Age Updated!\n";
                break;
            case 3:
                cout << "Enter Your Updated Weight: ";
                cin >> temp;
                currentUser.weight = temp;
                users[loggedInUserIndex].weight = temp;
                cout << "Weight Updated!\n";
                break;
            case 4:
                cout << "Enter Your Updated Height: ";
                cin >> temp;
                currentUser.height = temp;
                users[loggedInUserIndex].height = temp;
                cout << "Height Updated!\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
            updateTxt();
            cout << "Enter 1 to change more. **0** to go to menu: ";
            cin >> k;
        }
    }

    int LoginAccount(const string& username, const string& password, bool& check) {
        for (int i = 0; i < usercount; i++) {
            if (users[i].username == username && users[i].password == password) {
                check = true;
                return i; 
            }
        }
        cout << endl << "You have entered the wrong password or username. Try again." << endl;
        check = false;
        return -1;
    }
};

// --- Excercises Methods (Definitions) ---
void Excercises::DisplayEx(User& currentUser) {
    int Choice = 0;
    while (Choice != 9) {
        system("CLS");
        print_header("WORKOUTS");
        for (int i = 0; i < 8; ++i) {
            cout << i + 1 << ".  " << exercises[i] << endl;
        }
        cout << "9.  **RETURN TO MENU**" << endl << endl;
        cout << "Enter Your Choice: ";
        cin >> Choice;

        while (Choice < 1 || Choice > 9) {
            cout << endl << "Enter Correct Choice (1-9): ";
            cin >> Choice;
        }

        if (Choice >= 1 && Choice <= 8) {
            int option = 0;
            while (option != 2) {
                system("CLS");
                print_header(exercises[Choice - 1]);
                cout << "Instructions for **" << exercises[Choice - 1] << "**:\n";
                // Simplified instructions for clean output
                cout << "-> Follow the form guidelines carefully.\n";
                cout << "-> The timer will run for 5 seconds for a quick demo.\n\n";

                cout << "1. **START TIMER** \n2. **GO BACK** \n\n" << "Enter your choice: ";
                cin >> option;
                while (option < 1 || option > 2) {
                    cout << "Enter again! : ";
                    cin >> option;
                }
                cout << endl;

                if (option == 1) {
                    doExercise(Choice - 1, currentUser);
                }
            }
        }
    }
}

void Excercises::cutomizeexcercise(User& currentUser) {
    system("CLS");
    int size, size1, choice;
    print_header("CUSTOMIZER");
    cout << "1.Customize\n2.Back to menu\n ";
    cout << "Enter your choice: ";
    cin >> choice;
    while (choice > 2 || choice < 1) {
        cout << "Enter correct one: ";
        cin >> choice;
    }
    while (choice != 2) {
        system("CLS");
        cout << "Enter the number of excercises you want to add (1-10): ";
        cin >> size;
        int input;
        int* arr = new int[size];
        for (int i = 0; i < size; i++) {
            system("CLS");
            print_header("CUSTOMIZE YOUR WORKOUT");
            for (int j = 0; j < 8; ++j) {
                cout << j << ".  " << exercises[j] << endl;
            }
            cout << "Enter Your Choice (0-7 for exercise selection): ";
            cin >> input;
            while (input < 0 || input > 7) {
                cout << "Enter correct input: ";
                cin >> input;
            }
            arr[i] = input;
        }
        cout << "Enter how many times you want to repeat this customized plan: ";
        cin >> size1;
        cout << "Press any key when ready: ";
        system("pause");
        system("CLS");
        for (int i = 0; i < size1; i++) {
            for (int j = 0; j < size; j++) {
                doExercise(arr[j], currentUser);
            }
        }
        delete[] arr;
        cout << "Customized workout complete!\n";
        cout << "Enter 2 to exit or any other to redo: ";
        cin >> choice;
    }
}

void Excercises::bonusachievements(int level) {
    system("CLS");
    print_header("BONUS ACHIEVEMENTS");
    string arr[10] = {
        "Fit Fusion: Level 1", "Sweat Squad: Level 2", "Strength Surge: Level 3",
        "Cardio Crusher: Level 4", "Mindful Milestone: Level 5", "Endurance Elite: Level 6",
        "Nutrition Ninja: Level 7", "Flexibility Fanatic: Level 8", "Pace Setter: Level 9",
        "Transformation Titan: Level 10"
    };
    cout << "**UNLOCKED ACHIEVEMENTS!**\n";
    for (int i = 0; i < level && i < 10; i++) {
        cout << "-> " << arr[i] << endl;
    }
    cout << "\n**LOCKED ACHIEVEMENTS!**\n";
    for (int i = level; i <= 9; i++) {
        cout << "-> " << arr[i] << endl;
    }
    cout << endl;
    system("pause");
}

void Excercises::motivation() {
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 11); // Bright Cyan for quotes
    int index = rand() % 10 + 1; 

    system("CLS");
    print_header("DAILY MOTIVATION");

    cout << "MOTIVATION OF THE DAY!" << endl;
    if (index == 1) cout << "\"You are never too old to set another goal or to dream a new dream.\" - C.S. Lewis" << endl << endl;
    else if (index == 2) cout << "\"Strength doesn't come from what you can do. It comes from overcoming the things you once thought you couldn't.\" - Rikki Rogers" << endl << endl;
    else if (index == 3) cout << "It's not about perfect. It's about effort. And when you bring that effort every single day,\nthat's where transformation happens. That's how change occurs.\" - Jillian Michaels" << endl << endl;
    else if (index == 4) cout << "\"You miss 100 % of the shots you don't take.\" - Wayne Gretzky" << endl << endl;
    else if (index == 5) cout << "\"The secret of getting ahead is getting started.\" - Mark Twain" << endl << endl;
    else if (index == 6) cout << "\"When life gives you lemons, make lemonade. When it gives you weights, lift them.\"" << endl << endl;
    else if (index == 7) cout << "\"Success isn't always about greatness. It's about consistency. Consistent hard work leads to success. Greatness will come.\"- Dwayne Johnson" << endl << endl;
    else if (index == 8) cout << "\"Believe in yourself and all that you are. Know that there is something inside you that is greater than any obstacle.\" - Christian D. Larson" << endl << endl;
    else if (index == 9) cout << "\"The only way to do great work is to love what you do.\" - Steve Jobs" << endl << endl;
    else cout << "\"The future belongs to those who believe in the beauty of their dreams.\" - Eleanor Roosevelt" << endl << endl;
    
    SetConsoleTextAttribute(console_color, 14); 
    system("pause");
}

// --- DietRecipes Class ---
class DietRecipes {
public:
    void recipeBreakfast(int i) {
        system("CLS");
        
        switch (i) {
        case 1:
            print_header("SCRAMBLED EGGS RECIPE");
            cout << "\nIngredients:\n  * olive oil\n  * 2 cups spinach\n  * 6 grape tomatoes\n  * 2 large eggs\n  * 1 tablespoon water\n  * salt and pepper, to taste\n";
            cout << "\n**INSTRUCTIONS**\n";
            cout << "1. Drizzle olive oil into a nonstick skillet over medium heat. Add spinach and tomatoes and cook until the spinach just begins to wilt. Whisk together eggs and water until foamy. Pour eggs into skillet.\n";
            cout << "2. Do not stir the eggs until the sides begin to set. Gently pull the eggs toward the center of the skillet, allowing uncooked egg mixture to fill the edges.\n";
            cout << "3. Continue until no visible uncooked eggs remain. Remove from heat immediately to prevent overcooking.\n";
            cout << "4. Salt and pepper to taste and serve.\n";
            break;
        case 2:
            print_header("GREEK YOGURT RECIPE");
            cout << "\nIngredients:\n  * 1 cup Greek yogurt\n  * 1/2 cup mixed berries\n  * 1/4 cup almonds\n  * Sweetener (optional)\n";
            cout << "\n**INSTRUCTIONS**\n";
            cout << "1. Combine yogurt, sweetener, almonds, and berries in a bowl. Mix gently and enjoy.\n";
            break;
        case 3:
            print_header("OATMEAL WITH CHIA");
            cout << "\nIngredients:\n  * 1/2 cup rolled oats\n  * 1 cup water\n  * 1 tablespoon chia seeds\n  * 1/2 banana, sliced\n";
            cout << "\n**INSTRUCTIONS**\n";
            cout << "1. Combine oats and water in a microwave-safe bowl. 2. Microwave on high for 2 minutes. 3. Stir in chia seeds and banana slices. 4. Let sit for 5 minutes before eating." << endl;
            break;
        case 4:
            print_header("AVOCADO TOAST");
            cout << "\nIngredients:\n  * 1/2 avocado\n  * 1 slice whole grain bread\n  * salt and pepper, to taste\n";
            cout << "\n**INSTRUCTIONS**\n";
            cout << "1. Toast whole grain bread until golden brown. 2. Mash avocado and spread on toast. 3. Season with salt and pepper to taste." << endl;
            break;
        case 5:
            print_header("GREEN PROTEIN SMOOTHIE");
            cout << "\nIngredients:\n  * 1 cup kale\n  * 1/2 banana\n  * 1 scoop protein powder\n  * 1 cup water/milk\n";
            cout << "\n**INSTRUCTIONS**\n";
            cout << "1. Combine all ingredients in a blender. 2. Blend until smooth." << endl;
            break;
        default:
            cout << "Invalid recipe choice.\n";
            break;
        }
        int choice;
        cout << "\nPress any number to go back: ";
        cin >> choice;
    }

    void DisplayRecipes() {
        int Choice = 0;
        while (Choice != 6) {
            system("CLS");
            print_header("DIET RECIPES MENU");

            cout << "**BREAKFAST RECIPES:**\n";
            cout << "1. Scrambled Eggs with Spinach\n";
            cout << "2. Greek Yogurt with Berries\n";
            cout << "3. Oatmeal with Chia Seeds\n";
            cout << "4. Avocado Toast\n";
            cout << "5. Green Protein Smoothie\n";
            cout << "6. **RETURN TO MENU**\n\n";

            cout << "Enter Your Choice (1-6): ";
            cin >> Choice;

            if (Choice >= 1 && Choice <= 5) {
                recipeBreakfast(Choice);
            } else if (Choice != 6) {
                cout << "Invalid choice. Please try again.\n";
                system("pause");
            }
        }
    }
};

// --- Main Application Loop ---
void MainMenu(Login& loginSystem, User& currentUser) {
    int Choice;
    Excercises ex;
    DietRecipes dr;

    while (true) {
        system("CLS");
        print_header("FITNESS APP MAIN MENU");
        cout << "Welcome, **" << currentUser.firstname << "**!" << endl << endl;

        cout << "1. View User Information" << endl;
        cout << "2. Update User Information" << endl;
        cout << "3. View Workouts" << endl;
        cout << "4. Customized Workout Plan" << endl;
        cout << "5. View Progress" << endl;
        cout << "6. View Achievements" << endl;
        cout << "7. View Diet Recipes" << endl;
        cout << "8. Daily Motivation" << endl;
        cout << "9. **LOGOUT**" << endl;
        cout << "Enter Your Choice: ";
        cin >> Choice;

        while (Choice < 1 || Choice > 9) {
            cout << "Enter Correct Choice (1-9): ";
            cin >> Choice;
        }

        switch (Choice) {
        case 1:
            currentUser.Display();
            break;
        case 2:
            loginSystem.UpdateInfo(currentUser);
            break;
        case 3:
            ex.DisplayEx(currentUser);
            break;
        case 4:
            ex.cutomizeexcercise(currentUser);
            break;
        case 5:
            currentUser.DisplayProgress();
            break;
        case 6:
            ex.bonusachievements(currentUser.level);
            break;
        case 7:
            dr.DisplayRecipes();
            break;
        case 8:
            ex.motivation();
            break;
        case 9:
            currentUser.saveProgress(currentUser.username); 
            cout << "Logging out. Goodbye!\n";
            system("pause");
            return;
        default:
            break;
        }
    }
}

int main() {
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 14); 

    srand(static_cast<unsigned int>(time(nullptr)));

    Login loginSystem;
    User currentUser; 

    // Initial Login/Signup loop
    while (loginSystem.loggedInUserIndex == -1) {
        loginSystem.LoginDisplay(currentUser);
        if (loginSystem.loggedInUserIndex != -1) {
            MainMenu(loginSystem, currentUser);
            loginSystem.loggedInUserIndex = -1; 
        }
    }

    return 0;
}
