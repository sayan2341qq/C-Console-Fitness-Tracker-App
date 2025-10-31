C++ Console Fitness Tracker App

A simple, console-based fitness tracking application developed in C++. This app allows users to create an account, log workouts (simulated by a 5-second timer), track progress via an experience/level system, view diet recipes, and manage personal information.

The application utilizes object-oriented programming (OOP) principles, including classes like User, Progress, Login, Excercises, and DietRecipes, to manage different aspects of the fitness journey. User and progress data are persisted using local text files (Accounts.txt and Progress.txt).

---

Features

* User Authentication: Secure login and sign-up with data stored in Accounts.txt.
* Progress Tracking: Users gain experience points for completing exercises.
    * Experience points are converted into a Level and a visible progress bar (size).
    * Progress is persisted in Progress.txt.
* Workout Management:
    * View and start 8 pre-defined Workouts (e.g., Planks, Pushups).
    * Workouts are simulated with a 5-second timer.
    * Customized Workout Plan feature to sequence multiple exercises and repeat them.
* User Information: View and update personal details (age, weight, height, password).
* Achievements: Unlock Bonus Achievements based on the user's level.
* Diet & Motivation: Access simple Diet Recipes and a Daily Motivation quote.

---

Tech Stack

* Language: C++
* Libraries/Headers: <iostream>, <fstream>, <string>, <thread>, <chrono>, <vector>, <tuple>, and <Windows.h> (for console manipulation like system("CLS") and text coloring).
* Design: Object-Oriented Programming (OOP) with class inheritance (User inherits from Progress).

---

Getting Started

Prerequisites

* A C++ compiler (e.g., g++ or Microsoft Visual C++).
* The project is designed for Windows environments due to the use of:
    * #include <Windows.h>
    * system("CLS") (Clear screen command for Windows)
    * system("pause") (Awaits a key press, specific to Windows console)

Compilation and Run

1. Save the Code: Save the entire C++ source code into a single file named fitness_app.cpp.
2. Compile: Open your terminal or command prompt and compile the file.
    g++ fitness_app.cpp -o fitness_app.exe
    (Note: If using Visual Studio, you can compile and run directly within the IDE.)
3. Run: Execute the compiled program.
    ./fitness_app.exe

The application will create the necessary data files (Accounts.txt and Progress.txt) automatically upon first run or sign-up.

---

File Structure (Internal)

| File Name | Purpose | Format |
| Accounts.txt | Stores all user registration data (username, password, first name, last name, age, weight, height). | Each user record occupies 7 lines, with one data point per line. |
| Progress.txt | Stores the progress data for each user (experience, level, size). | Each user progress record occupies 4 lines: username, experience, level, size. |

---

Application Structure (Classes)

| Class | Purpose | Key Methods |
| User | Stores personal user details and displays them. Inherits from Progress. | Display(), Overloaded operator<< for output. |
| Progress | Manages the user's experience (XP), level, and progress bar size. | calculateProgress(), DisplayProgress(), loadProgress(), saveProgress(). |
| Login | Handles user authentication, file I/O for accounts, and user info updates. | LoginDisplay(), AddAccount(), LoginAccount(), UpdateInfo(). |
| Excercises | Defines exercises, handles workout initiation, and updates user XP. | doExercise(), DisplayEx(), cutomizeexcercise(), bonusachievements(), motivation(). |
| DietRecipes | Provides simple, hard-coded healthy meal instructions. | recipeBreakfast(), DisplayRecipes(). |

---

Key Code Highlights

Experience Calculation Logic (in Progress::calculateProgress)

The app uses a simple formula for leveling up:

XP Needed for Next Level = 100 * (Current Level + 1)

The progress bar size (out of 10) is calculated as:

Size = (Current Experience / XP Needed for Next Level) * 10

Threading for Workout Timer (in Excercises::doExercise)

The workout simulation uses standard C++ concurrency features for a non-blocking timer display:

auto start = std::chrono::steady_clock::now();
// ...
std::this_thread::sleep_for(std::chrono::milliseconds(1000));

This ensures the user sees a real-time countdown while the program is "busy" simulating the exercise.

---

Contribution

This project is a great foundational piece for a console application. Feel free to fork the repository and expand on it! Potential improvements could include:

* Improved Error Handling: More robust input validation for age, weight, and height.
* Refactor File I/O: Use a more structured format (like CSV or JSON) for data files instead of line-by-line reading.
* Cross-Platform Compatibility: Remove Windows.h dependencies and replace system("CLS") with a cross-platform alternative.
* More Recipes/Workouts: Expand the hard-coded lists.