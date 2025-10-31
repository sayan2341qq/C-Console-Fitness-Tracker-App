#include "Ascii.h"
#include "string"
#include<iostream>
#include<iomanip>
#include<string>
#include <thread>
#include <chrono>
#include<cstring>
#include<Windows.h>
#include<stdio.h>
#include<fstream>
using namespace std;
using namespace ascii;
Ascii font = Ascii(amongus);

class User
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
	{
		age = agein;
		weight = wght;
		height = hgt;
		username = usern;
		password = pass;
		firstname = firstn;
		lastname = lastn;
	}
	void operator=(User& obj) {
		age = obj.age;
		weight = obj.weight;
		height = obj.height;
		username = obj.username;
		password = obj.password;
		firstname = obj.firstname;
		lastname = obj.lastname;
	}
	void Display(User obj)
	{
		int Choice;
		system("CLS");
		Ascii font = Ascii(amongus);
		font.print("INFOPORTAL");
		cout << endl;
		//cout << setw(95) << "+_+_+_INFORMATION PORTAL_+_+_+" << endl << endl;
		cout << "PERSONAL DETAILS: " << endl;
		cout << obj;
		cout << "Enter 1 to return to menu: ";
		cin >> Choice;
		while (Choice != 1)
		{
			cout << "Enter 1 only!Enter :";
			cin >> Choice;
		}
		//system("pause");
	}
	~User()
	{

	}
	friend ostream& operator << (ostream& os, User& obj)
	{
		os << "FIRST NAME : " << obj.firstname << endl;
		os << "LAST NAME : " << obj.lastname << endl;
		os << "PASSWORD : " << obj.password << endl << endl;
		os << "APP DETAILS: " << endl;
		os << "USERNAME : " << obj.username << endl;
		os << "AGE : " << obj.age << endl;
		os << "WEIGHT : " << obj.weight << endl;
		os << "HEIGHT: " << obj.height << endl << endl;
		return os;
	}
};

class Login
{
public:
	int usercount;
	User* users;
	User loginuser;
	Login()
	{
		usercount = 0;
		fstream file;
		file.open("Accounts.txt", ios::in);
		if (!file.is_open()) {
			file.close();
			file.open("Accounts.txt", ios::out);
			file.close();
			file.open("Accounts.txt", ios::in);
		}
		while (!file.eof()) {
			string temp;
			for (int i = 0; i < 7; i++) {
				getline(file, temp);
			}
			usercount++;
		}
		usercount -= 1;
		users = nullptr;
	}
	bool readfile() {  //reads the record of users into the object array users
		int age;
		float weight;
		float height;
		string username;
		string password;
		string firstname;
		string lastname;
		string temp;
		users = new User[usercount];
		fstream file;
		file.open("Accounts.txt", ios::in);
		if (!file.is_open()) {
			cout << "File not found\n";
			return false;
		}

		for (int i = 0; i < usercount; i++) {
			getline(file, username);               //username,password,firstname,lastname,age,weight,height
			getline(file, password);
			getline(file, firstname);
			getline(file, lastname);

			getline(file, temp);
			age = stoi(temp);
			getline(file, temp);
			weight = stof(temp);
			getline(file, temp);
			height = stof(temp);
			User obj(age, weight, height, username, password, firstname, lastname);
			users[i] = obj;
		}
		return true;
	}
	void LoginDisplay()
	{
		int Choice;
		Ascii font = Ascii(amongus);
		font.print("FITNESSAPP");
		cout << endl << endl << "1.LOGIN INTO EXISTING ACCOUNT." << endl;
		cout << "2.ADD ACCOUNT" << endl;
		cout << "3.EXIT" << endl;

		cout << "Enter Your Choice: " << endl;
		cin >> Choice;
		while (Choice < 1 || Choice>3)
		{
			cout << endl << "Enter Correct Choice: ";
			cin >> Choice;
		}
		if (Choice == 1)
		{
			cin.ignore();
			bool check = false;
			string name;
			string pass;
			system("CLS");
			while (check != true)
			{
				cout << "Enter your username:" << endl;
				cin >> name;
				cout << "Enter your password: " << endl;
				cin >> pass;
				loginuser = LoginAccount(name, pass, check);
			}


		}
		else if (Choice == 2)
		{
			system("CLS");
			cout << "Enter your first name: ";
			cin >> loginuser.firstname;
			cout << "Enter your last name: ";
			cin >> loginuser.lastname;
			cout << "Enter your user name: ";
			cin >> loginuser.username;
			cout << "Enter your password name: ";
			cin >> loginuser.password;
			cout << "Enter your age: ";
			cin >> loginuser.age;
			cout << "Enter your weight: ";
			cin >> loginuser.weight;
			cout << "Enter your height: ";
			cin >> loginuser.height;
			AddAccount(loginuser);

		}
		else
		{
			exit(0);
		}


	}
	void AddAccount(User& obj)
	{
		fstream file;
		file.open("Accounts.txt", ios::in);
		if (!file.is_open()) {
			cout << "File Not Found";
			return;
		}
		while (!file.eof()) {
			string temp;
			getline(file, temp);
			if (temp == obj.username) {
				cout << "Account Already Added";
				file.close();
				return;
			}
			for (int i = 0; i < 6; i++) {
				getline(file, temp);
			}

		}
		file.close();
		file.open("Accounts.txt", ios::app);
		file << obj.username << endl;
		file << obj.password << endl;
		file << obj.firstname << endl;
		file << obj.lastname << endl;
		file << obj.age << endl;
		file << obj.weight << endl;
		file << obj.height << endl;
		cout << "Account added successfully\n";
		file.close();

	}
	void updateTxt() {
		fstream file;
		file.open("Accounts.txt", ios::out);
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
	void UpdateInfo(string name) {
		int choice, index;
		string pass;
		float temp;

		int k = 1;
		while (k != 0)
		{
			system("CLS");

			//cout << setw(95) << "+_+_+_INFORMATION UPDATER_+_+_+" << endl << endl;
			Ascii font = Ascii(amongus);
			font.print("INFOUPDATER");
			cout << endl;
			cout << "1: UPDATE PASSWORD\n";
			cout << "2: UPDATE AGE\n";
			cout << "3: UPDATE WEIGHT\n";
			cout << "4: UPDATE HEIGHT\n";
			cin >> choice;
			for (int i = 0; i < usercount; i++) {
				if (users[i].username == name) {
					index = i;
					break;
				}
			}
			switch (choice) {
			case 1:
				cout << "Enter your original Password First: ";
				cin >> pass;
				if (pass == users[index].password) {
					cout << "Enter Your Updated PassWord: ";
					cin >> pass;
					users[index].password = pass;
					cout << "Updated!\n";
				}
				else {
					cout << "Wrong Password Entered , Password can not be updated \n";
				}
				break;


			case 2:
				cout << "Enter Your Updated Age: ";
				cin >> choice;
				users[index].age = choice;
				cout << "Updated!\n";
				break;
			case 3:
				cout << "Enter Your Updated Weight: ";
				cin >> temp;
				users[index].weight = temp;
				cout << "Updated!\n";

				break;
			case 4:
				cout << "Enter Your Updated Height: ";
				cin >> temp;
				users[index].height = temp;
				cout << "Updated!\n";
				break;

			}
			updateTxt();
			cout << "Enter 1 to change. 0 to go to menu: ";
			cin >> k;
		}
	}
	User& LoginAccount(string username1, string password1, bool& check)
	{
		User temp;
		readfile();
		for (int i = 0; i < usercount; i++) {
			//cout << users[i].username << " " << users[i].password << endl;
			if (users[i].username == username1 && users[i].password == password1) {
				check = true;
				return users[i];
			}
		}
		cout << endl << "You have entered the wrong password or username.Enter again: ";
		cout << endl;
		return temp;
		exit(0);
	}
	~Login()
	{
	}

};
class Progress
{
public:
	//ME Stufff
	int level;
	int size;
	Progress() {
		level = 0;
		size = 0;
	}
	void calculateProgress(int& ex) {
		if (ex / 100 >= 1 * level) {
			level++;
			size = ex % 100;
			ex = 0;
		}
		else {
			size = ex / 10;
		}
	}
	void DisplayProgress()
	{
		system("CLS");
		Ascii font = Ascii(amongus);
		font.print("PROGRESS");
		//cout << setw(90) << "_+_+_+_PROGRESS_+_+_+_" << endl << endl << endl << endl;
		int Choice;
		cout << endl;
		cout << "Your level is: " << level << endl;
		cout << "Your progress is: ";
		cout << "[ ";
		for (int i = 0; i < size / level; i++) {
			cout << "-" << " ";
		}
		cout << "]" << endl;
		cout << "Enter 1 to return to menu: ";
		cin >> Choice;
		while (Choice != 1)
		{
			cout << "Enter 1 only!Enter :";
			cin >> Choice;
		}
	}
	void loadProgress(string name) {
		string temp;
		fstream file;
		file.open("Progress.txt", ios::in);
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, temp);
				if (temp == name) {
					getline(file, temp);
					level = stoi(temp);
					getline(file, temp);
					size = stoi(temp);
				}
			}
		}
		else {  //incase new account or first time doing excerecise
			level = 0;
			size = 0;
		}
	}
};

class Excercises :public Progress  //ME Stufff
{
	//ME Stufff    
	string* exercises;
	int experience;
	int* types;
public:

	//ME Stufff
	Excercises()
	{
		experience = 0;
		exercises = new string[8];
		exercises[0] = "Planks";
		exercises[1] = "Pushups";
		exercises[2] = "Crunches";
		exercises[3] = "Squats";
		exercises[4] = "PullUps";
		exercises[5] = "JumpingJacks";
		exercises[6] = "MountainClimbers";
		exercises[7] = "SidePlanks";

		//can put diff exps here
		types = new int[8];
		types[0] = 100;
		types[1] = 50;
		types[2] = 25;
		types[3] = 10;
		types[4] = 10;
		types[5] = 10;
		types[6] = 10;
		types[7] = 10;
	}
	void DisplayEx(int& l, int& s)
	{
		int Choice = 0;
		while (Choice != 9)
		{
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("WORKOUTS");
			cout << endl;
			/*cout << setw(90) << "_+_+_+_WORKOUTS_+_+_+_" << endl << endl << endl << endl;*/
			cout << "1.  Planks" << endl;
			cout << "2.  Pushups" << endl;
			cout << "3.  Crunches" << endl;
			cout << "4.  Squats" << endl;
			cout << "5.  PullUps" << endl;
			cout << "6.  Jumping Jacks" << endl;
			cout << "7.  Mountain climbers" << endl;
			cout << "8.  Side Planks" << endl;
			cout << "9.  RETURN TO MENU" << endl << endl;
			cout << "Enter Your Choice: ";
			cin >> Choice;
			while (Choice < 1 || Choice>9)
			{
				cout << endl << "Enter Correct Choice: ";
				cin >> Choice;
			}
			if (Choice == 1)
			{

				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("PLANKS");
				//cout << setw(90) << "_+_+_+_PLANKS_+_+_+_" << endl << endl << endl << endl;
				cout << endl;
				cout << "-> Select a position where you can extend your whole body length." << endl <<
					"-> Using an exercise mat will give you enough padding to be " <<
					"comfortable on all fours." << endl;
				cout << "-> Begin in the plank position, face down with your forearms and toes on the floor." << endl
					<< "-> Your elbows are directly under your shoulders and your forearms are facing forward." << endl
					<< "-> Your head is relaxed and you should be looking at the floor." << endl;
				cout << "-> Engage your abdominal muscles, drawing your navel toward your spine." << endl;
				cout << "-> Keep your torso straight and rigid and your body in a "
					<< "straight line " << endl
					<< "-> This is the neutral spine position." << endl << "-> Ensure your shoulders are down, "
					<< "not creeping up toward your ears." << endl << "-> Your heels should be over the balls of your feet. " << endl;
				cout << "-> Hold this position for 10 seconds. Release to floor. " << endl;
				cout << "-> Over time work up to 30, 45, or 60 seconds." << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				cout << endl;
				while (option == 1)
				{
					doExercise(0, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;
				}
			}
			else if (Choice == 2)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("PUSHUPS");
				//cout << setw(90) << "_+_+_+_Pushups_+_+_+_" << endl << endl << endl << endl;
				cout << endl;
				cout << "-> To do a push-up you are going to get on the floor on all fours" << endl <<
					"-> position your hands slightly wider than your shoulders. ";
				cout << "-> Don't lock out the elbows; keep them slightly bent." << endl
					<< "-> Extend your legs back so you are balanced on your hands and toes, your feet hip-width apart. " << endl
					<< "-> Once in this position, here is how you will do a push-up." << endl;
				cout << "-> Contract your abs and tighten your core by pulling your belly button toward your spine. " << endl;
				cout << "-> Inhale as you slowly bend your elbows and lower yourself to the floor, until your elbows are at a 90-degree angle." << endl;
				cout << "-> Exhale while contracting your chest muscles and pushing back up through your hands, returning to the start position. " << endl;
				cout << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				cout << endl;
				while (option == 1)
				{
					doExercise(1, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;
				}
			}
			else if (Choice == 3)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("CRUNCHES");
				//cout << setw(90) << "_+_+_+_Crunches_+_+_+_" << endl << endl << endl << endl;
				cout << endl;
				cout << "-> Lie down on the floor on your back and bend your knees. " << endl;
				cout << "-> place your hands behind your head or across your chest. " << endl;
				cout << "-> Some people find that crossing the arms over the chest helps them avoid pulling on the neck. " << endl;
				cout << "-> Brace your core. " << endl;
				cout << "-> Crunch your ribs toward your pelvis using your abdominal muscles to initiate and complete the movement." << endl;
				cout << "-> Exhale as you come up and keep your neck straight, chin up." << endl;
				cout << "-> Hold at the top of the movement for a few seconds, breathing continuously." << endl;
				cout << "-> Lower slowly back down, but don't relax all the way." << endl;
				cout << "-> Repeat for 15 to 20 repetitions with perfect form for each rep" << endl;
				cout << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				cout << endl;
				while (option == 1)
				{
					doExercise(2, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;
				}
			}
			else if (Choice == 4)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("SQUATS");
				//cout << setw(90) << "_+_+_+_Squats_+_+_+_" << endl << endl << endl << endl;
				cout << endl;

				cout << "-> Stand with feet about hip or shoulder-width apart. " << endl;
				cout << "-> If using a chair, place it behind you and stand in front of it. Tighten your abs" << endl;
				cout << "-> Bend the knees and slowly squat towards the chair. " << endl;
				cout << "-> Send the hips back, while keeping the head up and the torso straight. You can extend the arms if that helps with balance " << endl;
				cout << "-> Pause here, or sit briefly on the chair." << endl;
				cout << "-> Then contract the glutes to lift up out of the chair and begin extending the legs." << endl;
				cout << "-> Extend the legs fully until you're back to standing position, but don't lock the knees." << endl;
				cout << "-> Repeat this for 1�3 sets of 10�16 repetitions." << endl;
				cout << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				cout << endl;
				while (option == 1)
				{
					doExercise(3, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;

				}
			}
			else if (Choice == 5)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("PULLUPS");
				//cout << setw(90) << "_+_+_+_PullUps_+_+_+_" << endl << endl << endl << endl;
				cout << endl;
				cout << "-> Stand below the bar with your feet shoulder width apart. " << endl;
				cout << "-> Jump up and grip the bar with an overhand grip about shoulder width apart." << endl;
				cout << "-> Fully extend your arms so you are in a dead hang." << endl;
				cout << "-> Bend your knees and cross your ankles for a balanced position. Take a breath at the bottom." << endl;
				cout << "-> Exhale while pulling yourself up so your chin is level with the bar. Pause at the top." << endl;
				cout << "-> Lower yourself (inhaling as you go down) until your elbows are straight." << endl;
				cout << "-> Repeat the movement without touching the floor." << endl;
				cout << "-> Complete the number of repetitions your workout requires." << endl;
				cout << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				cout << endl;
				while (option == 1)
				{
					doExercise(4, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;
				}
			}
			else if (Choice == 6)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("JumpJacks");
				//cout << setw(87) << "_+_+_+_Jumping Jacks (with step)_+_+_+_" << endl << endl << endl << endl;
				cout << endl;
				cout << "-> You may want to start with the step at its lowest position if you're trying it for the first time. " << endl;
				cout << "-> If you feel discomfort or pain, avoid this exercise." << endl;
				cout << "-> Stand facing a step or platform and jump up onto it with both feet." << endl;
				cout << "-> Jump back down to the floor, or step down to the floor if jumping feels unsafe or uncomfortable." << endl;
				cout << "-> Perform a jumping jack on the floor and, after you jump the feet back together, jump back onto the step." << endl;
				cout << "-> Continue alternating a jump on the step and a jumping jack." << endl;
				cout << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				cout << endl;
				while (option == 1)
				{
					doExercise(5, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;
				}
			}
			else if (Choice == 7)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("CLIMBERS");
				//cout << setw(90) << "_+_+_+_Mountain climbers_+_+_+_" << endl << endl << endl << endl;
				cout << endl;
				cout << "-> Get into a plank position, making sure to distribute your weight evenly between your hands and your toes. " << endl;
				cout << "-> Check your form�your hands should be about shoulder-width apart, back flat, abs engaged, and head in alignment." << endl;
				cout << "-> Pull your right knee into your chest as far as you can." << endl;
				cout << "-> Switch legs, pulling one knee out and bringing the other knee in." << endl;
				cout << "-> Keep your hips down and run your knees in and out as far and as fast as you can." << endl;
				cout << "-> Alternate inhaling and exhaling with each leg change." << endl;
				cout << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				cout << endl;
				while (option == 1)
				{
					doExercise(6, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;
				}
			}

			else if (Choice == 8)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("SIDEPLANKS");
				//cout << setw(90) << "_+_+_+_Side Planks_+_+_+_" << endl << endl << endl << endl;
				cout << endl;
				cout << "-> Ensure your head is directly in line with your spine. Your left arm can be aligned along the left side of your body." << endl;
				cout << "-> Engage your abdominal muscles, drawing your navel toward your spine." << endl;
				cout << "-> Lift your hips and knees from the mat while exhaling. Your torso is straight in line with no sagging or bending. Hold the position." << endl;
				cout << "-> After several breaths, inhale and return to the starting position. The goal should be to hold as long as you can easily" << endl;
				cout << "-> Change sides and repeat." << endl;
				cout << endl;
				cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
				int option;
				cin >> option;
				while (option < 1 || option>2)
				{
					cout << "Enter again! : ";
					cin >> option;
				}
				while (option == 1)
				{
					doExercise(7, l, s);
					cout << endl;
					cout << endl << "1.START TIMER \n2.GO BACK \n\n" << "Enter your choice: ";
					cin >> option;
					cout << endl;
					while (option < 1 || option>2)
					{
						cout << "Enter again! : ";
						cin >> option;
					}
					cout << endl;
				}
			}
			else
			{
				continue;
			}
		}
	}

	//ME Stufff
	void doExercise(int index, int& lvl, int& s)
	{
		system("CLS");
		cout << "You are doing exercise " << exercises[index] << endl;
		//change based on userInfo or the exercise itself
		int durationInSeconds = 5;

		auto start = std::chrono::steady_clock::now();

		while (true)
		{
			auto end = std::chrono::steady_clock::now();
			auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

			if (elapsed_seconds.count() >= durationInSeconds)
			{
				cout << "Exercise " << exercises[index] << " completed!" << endl;
				break;
			}

			int remainingSeconds = durationInSeconds - elapsed_seconds.count();
			{
				cout << "Time remaining: " << remainingSeconds << " seconds" << endl;
			}

			// Sleep for a short interval to reduce CPU usage
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		experience += types[index];
		calculateProgress(experience);
		lvl = level;
		s = size;
	}
	void cutomizeexcercise(int& l, int& s)
	{
		system("CLS");
		int size, size1, choice;
		Ascii font = Ascii(amongus);
		font.print("CUSTOMIZER");
		cout << endl;
		//cout << setw(90) << "_+_+_+_CUSTOMIZE MENU_+_+_+_" << endl << endl << endl << endl;
		cout << "1.Customize\n2.Back to menu\n ";
		cout << "Enter your choice: ";
		cin >> choice;
		while (choice > 2 || choice < 1)
		{
			cout << "Enter correct one: ";
			cin >> choice;
		}
		while (choice != 2)
		{
			system("CLS");
			cout << "Enter the number of excercises you want to add(1-10): ";
			cin >> size;
			int input;
			int* arr = new int[size];
			for (int i = 0; i < size; i++)
			{
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("CUSTOMIZE");
				cout << endl;
				//cout << setw(90) << "_+_+_+_CUSTOMIZE YOUR WORKOUT_+_+_+_" << endl << endl << endl << endl;
				cout << "0.  Planks" << endl;
				cout << "1.  Pushups" << endl;
				cout << "2.  Crunches" << endl;
				cout << "3.  Squats" << endl;
				cout << "4.  PullUps" << endl;
				cout << "5.  Jumping Jacks" << endl;
				cout << "6.  Mountain climbers" << endl;
				cout << "7.  Side Planks" << endl;
				cout << "8.  RETURN TO MENU" << endl << endl;
				cout << "Enter Your Choice: ";
				cin >> input;
				while (input < 0 || input>8)
				{
					cout << "Enter correct input: ";
					cin >> input;
				}
				arr[i] = input;
			}
			cout << "Enter how many times you want to repeat this customized plan: ";
			cin >> size1;
			cout << "Enter any button when ready: ";
			system("pause");
			system("CLS");
			for (int i = 0; i < size1; i++)
			{
				for (int j = 0; j < size; j++)
				{
					doExercise(arr[j], l, s);
				}
			}
			cout << "Enter 2 to exit or any other to redo: ";
			cin >> choice;
		}
	}
	void bonusachievements(int level)
	{
		system("CLS");
		Ascii font = Ascii(amongus);
		font.print("BONUS");
		cout << endl;
		//cout << setw(90) << "_+_+_+_BONUS ACHIEVEMENTS_+_+_+_" << endl << endl << endl << endl;
		string arr[10];
		arr[0] = "Fit Fusion:Level 1";
		arr[1] = "Sweat Squad:Level 2";
		arr[2] = "Strength Surge:Level 3";
		arr[3] = "Cardio Crusher:Level 4";
		arr[4] = "Mindful Milestone:Level 5";
		arr[5] = "Endurance Elite:Level 6";
		arr[6] = "Nutrition Ninja:Level 7";
		arr[7] = "Flexibility Fanatic:Level 8";
		arr[8] = "Pace Setter:Level 9";
		arr[9] = "Transformation Titan:Level 10";
		cout << "UNLOCKED ACHIEVEMENTS!\n";
		for (int i = 0; i < level; i++)
		{
			cout << "-> " << arr[i] << endl;
		}
		cout << endl << endl << "LOCKED ACHIEVEMENTS!\n";
		for (int i = level; i <= 9; i++)
		{
			cout << "-> " << arr[i] << endl;
		}
		cout << endl;
	}
	void motivation()
	{
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 11);
		int index;
		srand(time(NULL));
		index = rand() % 10 + 1;
		cout << "MOTIVATION OF THE DAY!" << endl;
		if (index == 1)
		{
			cout << """You are never too old to set another goal or to dream a new dream.""C.S.�Lewis" << endl << endl;
		}
		else if (index == 2)
		{
			cout << """Strength doesn't come from what you can do. It comes from overcoming the things you once thought you couldn't."" - Rikki Rogers" << endl << endl;
		}
		else if (index == 3)
		{
			cout << "It's not about perfect. It's about effort. And when you bring that effort every single day,\nthat's where transformation happens. That's how change occurs."" - Jillian Michaels" << endl << endl;
		}
		else if (index == 4)
		{
			cout << "You miss 100 % of the shots you don't take."" - Wayne Gretzky" << endl << endl;
		}
		else if (index == 5)
		{
			cout << """The secret of getting ahead is getting started."" - Mark Twain" << endl << endl;
		}
		else if (index == 6)
		{
			cout << """When life gives you lemons, make lemonade.When it gives you weights, lift them.""" << endl << endl;
		}
		else if (index == 7)
		{
			cout << """Success isn't always about greatness. It's about consistency. Consistent hard work leads to success. Greatness will come.""- Dwayne Johnson" << endl << endl;
		}
		else if (index == 8)
		{
			cout << """Believe in yourself and all that you are. Know that there is something inside you that is greater than any obstacle."" - Christian D.Larson" << endl << endl;
		}
		else if (index == 9)
		{
			cout << """The only way to do great work is to love what you do."" - Steve Jobs" << endl << endl;
		}
		else
		{
			cout << """The future belongs to those who believe in the beauty of their dreams."" - Eleanor Roosevelt" << endl << endl;
		}
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 14);
	}
};
class DietRecipes
{
public:
	void recipeBreakfast(int i) {
		if (i == 1) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "olive oil\n2 cups spinach\n6 grape tomatoes\n"
				<< "2 large eggs\n1 tablespoon water\nsalt and pepper, to taste\n";
			font1.print("INSTRUCTIONS");
			cout << endl;				cout << "\n1.Drizzle olive oil into a nonstick skillet over medium heat.\n"
				<< " Add spinach and tomatoes and cook until the spinach just begins to wilt.\n"
				<< " Meanwhile, whisk together eggs and water until foamy. Pour eggs into skillet with spinach.\n";
			cout << "\n2.Do not stir the eggs until the sides have begun to turn a lighter shade than the rest of\n";
			cout << "the eggs and have begun to gently pull away from the buttered edges of the pan. Using a silicon\n";
			cout << "spatula or a wooden spoon, gently pull the eggs toward the center of the skillet, bringing largen\n ";
			cout << "curds with you as you do so. The edges here you pulled the eggs toward the center will quickly fill\n with uncooked egg mixture\n";
			cout << "\n3.Continue to pull the curds toward the center of the entire skillet and gently stir the eggs\n"
				<< "until there are no more visible uncooked eggs. Stir eggs gently and remove from heat. Be sure \n"
				<< "not to leave eggs on the heat too long as they can quickly overcook and become dry and rubbery.\n";
			cout << "\n4.Salt and pepper to taste and serve immediately.\n";
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 2) {
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 cup Greek yogurt\n1/2 cup mixed berries\n1/4 cup almonds\n";
			cout << "\n1.one cup plain Greek yogurt\n"
				<< "2.one packet Truvia or other stevia-based sweetener\n"
				<< "3.one handful raw or dry-roasted almonds\n"
				<< "4.one handful berries of your choice\n"
				<< "5.one/4 cup granola (optional)\n";
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 3) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1/2 cup rolled oats\n1 cup water\n1 tablespoon chia seeds"
				<< "\n1/2 banana, sliced\n";
			font1.print("INSTRUCTIONS");
			cout << endl;					cout << "\n1.Combine oats and water in a microwave-safe bowl.\n"
				<< "2.Microwave on high for 2 minutes.\n"
				<< "3.Stir in chia seeds and banana slices.\n"
				<< "4.Let sit for 5 minutes before eating." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 4) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1/2 avocado\n1 slice whole grain bread\nsalt and pepper, to taste\n";
			font1.print("INSTRUCTIONS");
			cout << endl;					cout << "\n1.Toast whole grain bread until golden brown.\n"
				<< "2.Mash avocado and spread on toast.\n"
				<< "3.Season with salt and pepper to taste." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 5) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 cup kale\n1/2 banana\n1 scoop protein powder\n1 cup water\n";
			font1.print("INSTRUCTIONS");
			cout << endl;
			cout << "\n1.Combine kale, banana, protein powder, and water in a blender.\n"
				<< "2.Blend until smooth.\n"
				<< "3.Serve immediately." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else {
			system("CLS");
			cout << "\nRecipie not found\n";
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
	}
	void recipeLunch(int i) {
		if (i == 1) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 cup quinoa\n1 cup mixed vegetables\n1/4 cup tahini\n1 lemon\n";
			font1.print("INSTRUCTIONS");
			cout << endl;
			cout << "\n1.Cook quinoa according to package instructions.\n"
				<< "2.Steam mixed vegetables until tender.\n"
				<< "3.Whisk together tahini and lemon juice to make dressing.\n"
				<< "4.Toss quinoa and vegetables with dressing." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 2) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 chicken breast\n1 cup broccoli\n1/2 cup brown rice\n";
			font1.print("INSTRUCTIONS");
			cout << endl;
			cout << "\n1.Grill chicken breast until cooked through.\n"
				<< "2.Steam broccoli until tender.\n"
				<< "3.Cook brown rice according to package instructions.\n"
				<< "4.Serve chicken, broccoli, and rice together." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 3) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 cup lentils\n1 slice whole grain bread\n";
			font1.print("INSTRUCTIONS");
			cout << endl;
			cout << "\n1.Cook lentils according to package instructions.\n"
				<< "2.Toast whole grain bread until golden brown.\n"
				<< "3.Serve lentils with toast." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 4) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 can tuna\n1/2 cup lettuce\n1 whole wheat tortilla\n";
			font1.print("INSTRUCTIONS");
			cout << endl;
			cout << "\n1.Drain tuna and mix with mayonnaise or Greek yogurt.\n"
				<< "2.Lay out tortilla and top with tuna mixture and lettuce.\n"
				<< "3.Roll up tortilla and slice in half." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 4) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 block tofu\n1 cup broccoli\n1/2 cup brown rice\n";
			font1.print("INSTRUCTIONS");
			cout << endl;
			cout << "\n1.Cut tofu into cubes and stir-fry until golden brown.\n"
				<< "2.Steam broccoli until tender.\n"
				<< "3.Cook brown rice according to package instructions.\n"
				<< "4.Serve tofu, broccoli, and rice together." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else {
			system("CLS");
			cout << "\nRecipie not found\n";
		}
	}
	void recipeDinner(int i) {
		if (i == 1) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;

			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 salmon fillet\n1 cup asparagus\n1/2 cup quinoa\n";
			font1.print("INSTRUCTIONS");
			cout << endl;
			cout << "\n1.Bake salmon fillet in the oven until cooked through.\n"
				<< "2.Steam asparagus until tender.\n"
				<< "3.Cook quinoa according to package instructions.\n"
				<< "4.Serve salmon, asparagus, and quinoa together." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 2) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 cup mixed vegetables\n1/2 cup whole wheat couscous\n";
			font1.print("INSTRUCTIONS");
			cout << endl;					cout << "\n1.Thread mixed vegetables onto skewers and grill until tender.\n"
				<< "2.Cook whole wheat couscous according to package instructions.\n"
				<< "3.Serve skewers and couscous together." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 3) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 pound ground turkey\n1 can mixed beans\n1 cup side salad\n";
			font1.print("INSTRUCTIONS");
			cout << endl;					cout << "\n1.Brown ground turkey in a skillet.\n"
				<< "2.Add mixed beans and simmer until heated through.\n"
				<< "3.Serve turkey chili with side salad." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 4) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "2 bell peppers\n1 pound lean ground turkey\n1/2 cup brown rice\n";
			font1.print("INSTRUCTIONS");
			cout << endl;					cout << "\n1.Cut tops off bell peppers and remove seeds.\n"
				<< "2.Stuff peppers with cooked ground turkey and brown rice.\n"
				<< "3.Bake in the oven until peppers are tender." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else if (i == 5) {
			system("CLS");
			Ascii font = Ascii(amongus);
			Ascii font1 = Ascii(amongus);
			font.print("RECIPE");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Ingredients_+_+_+_" << endl << endl << endl << endl;
			cout << "1 block tofu\n1 cup broccoli\n1/2 cup brown rice noodles\n";
			font1.print("INSTRUCTIONS");
			cout << endl;					cout << "\n1.Cut tofu into cubes and stir-fry until golden brown.\n"
				<< "2.Steam broccoli until tender.\n"
				<< "3.Cook brown rice noodles according to package instructions.\n"
				<< "4.Serve tofu, broccoli, and noodles together." << endl;
			int choice;
			cout << "Enter any number to go back: ";
			cin >> choice;
		}
		else {
			system("CLS");
			cout << "\nRecipie not found\n";
		}
	}
	void displayBreakfasts() {
		int option;
		do {
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("BREAKFAST");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Diet Breakfast Recipes_+_+_+_" << endl << endl << endl << endl;
			cout << "1. Scrambled Eggs with Spinach and Tomatoes\n";
			cout << "2. Greek Yogurt with Berries and Almonds\n";
			cout << "3. Oatmeal with Chia Seeds and Banana Slices\n";
			cout << "4. Avocado Toast with Whole Grain Bread\n";
			cout << "5. Smoothie with Kale, Banana, and Protein Powder\n";
			cout << "do you want to see a recipe? (-1 to exit)\n";
			cin >> option;
			system("CLS");
			if (option == 1) {
				recipeBreakfast(option);
			}
			else if (option == 2) {
				recipeBreakfast(option);
			}
			else if (option == 3) {
				recipeBreakfast(option);
			}
			else if (option == 4) {
				recipeBreakfast(option);
			}
			else if (option == 5) {
				recipeBreakfast(option);
			}
		} while (option != -1);
	}

	void displayLunches() {
		int option;
		do {
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("LUNCH");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Diet Lunch Recipes_+_+_+_" << endl << endl << endl << endl;
			cout << "1. Quinoa Salad with Mixed Vegetables and Lemon-Tahini Dressing\n";
			cout << "2. Grilled Chicken Breast with Steamed Broccoli and Brown Rice\n";
			cout << "3. Lentil Soup with Whole Grain Bread\n";
			cout << "4. Tuna Salad Wrap with Lettuce and Whole Wheat Tortilla\n";
			cout << "5. Veggie Stir-fry with Tofu and Brown Rice\n";
			cout << "do you want to see a recipe? (-1 to exit)\n";
			cin >> option;
			if (option == 1) {
				recipeLunch(option);
			}
			else if (option == 2) {
				recipeLunch(option);
			}
			else if (option == 3) {
				recipeLunch(option);
			}
			else if (option == 4) {
				recipeLunch(option);
			}
			else if (option == 5) {
				recipeLunch(option);
			}
		} while (option != -1);
	}

	void displayDinners() {
		int option;
		do {
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("DINNER");
			cout << endl;

			//cout << setw(90) << "_+_+_+_Diet Dinner Recipes_+_+_+_" << endl << endl << endl << endl;
			cout << "1. Baked Salmon with Asparagus and Quinoa\n";
			cout << "2. Grilled Vegetable Skewers with Whole Wheat Couscous\n";
			cout << "3. Turkey Chili with Mixed Beans and Side Salad\n";
			cout << "4. Stuffed Bell Peppers with Lean Ground Turkey and Brown Rice\n";
			cout << "5. Stir-fried Tofu with Broccoli and Brown Rice Noodles\n";
			cout << "do you want to see a recipe? (-1 to exit)\n";
			cin >> option;
			if (option == 1) {
				recipeDinner(option);
			}
			else if (option == 2) {
				recipeDinner(option);
			}
			else if (option == 3) {
				recipeDinner(option);
			}
			else if (option == 4) {
				recipeDinner(option);
			}
			else if (option == 5) {
				recipeDinner(option);
			}
		} while (option != -1);
	}
	void DisplayRecipe()
	{
		int Choice = 0;
		while (Choice != 4)
		{
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("DIETRECIPES");
			cout << endl;
			//cout << setw(90) << "_+_+_+_Diet Recipes_+_+_+_" << endl << endl << endl << endl;
			cout << "1. BREAKFAST RECIPES" << endl;
			cout << "2. LUNCH RECIPES" << endl;
			cout << "3. DINNER RECIPES" << endl;
			cout << "4. Back to Menu";
			cout << endl << endl << "Enter you choice: ";
			cin >> Choice;
			while (Choice > 4 || Choice < 1)
			{
				cout << "Enter correct option: ";
				cin >> Choice;
			}
			if (Choice == 1)
			{
				displayBreakfasts();
			}
			else if (Choice == 2)
			{
				displayLunches();
			}
			else if (Choice == 3)
			{
				displayDinners();
			}
		}
	}
};
class WaterTracker
{
public:
	void DisplayWater(float w)
	{
		int choice = 1;
		float water = 0;
		float waterIntake = 35 * w;
		while (choice != 0)
		{
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("WATERTRACKER");
			//cout << setw(90) << "_+_+_+_Water Tracker_+_+_+_" << endl << endl << endl << endl;
			cout << endl << endl << "Recommended Intake: " << waterIntake << " Weight: " << w << endl << endl;
			while (water <= 0)
			{
				cout << "Enter correct amount(ml): ";
				cin >> water;
			}
			if (water < waterIntake - 500)
			{
				cout << "You need to drink more water" << endl;
			}
			else if (water >= waterIntake - 500 && water <= waterIntake + 500)
			{
				cout << "You are drinking enough water" << endl;
			}
			else if (water > waterIntake + 500)
			{
				cout << "You are drinking too much water" << endl;
			}
			cout << endl << endl << "Enter 0 to go back to menu or else to repeat: ";
			cin >> choice;
		}
	}
};
class BMRChecker
{
public:
	void DisplayBMR(float weight, float height, int age)
	{
		system("CLS");
		int c;
		Ascii font = Ascii(amongus);
		font.print("BMRTRACKER");
		cout << endl;
		//cout << setw(90) << "_+_+_+_BMR TRACKER_+_+_+_" << endl << endl << endl << endl;
		cout << "1.Male \n2.Female\n\nEnter your choice: ";
		cin >> c;
		while (c < 1 || c>2)
		{
			cout << "Enter the correct option: ";
			cin >> c;
		}
		cout << endl;
		if (c == 2)
			cout << "Your ""Female"" BMR is: " << 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age) << endl << endl;
		else if (c == 1)
			cout << "Your ""Male"" BMR is: " << 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age) << endl << endl;
		cout << "Enter any number to go back: ";
		cin >> c;
		cout << endl;
	}

};
class BMIChecker
{
public:
	void DisplayBMI()
	{
		float weight, height;
		system("CLS");
		Ascii font = Ascii(amongus);
		font.print("BMRCALC.");
		cout << endl;
		//cout << setw(80) << "_+_+_+_BMI CALCULATOR+_+_+_" << endl << endl << endl << endl;
		cout << "ENTER YOUR WEIGHT: ";
		cin >> weight;
		cout << "ENTER YOUR HEIGHT(in meter): ";
		cin >> height;
		float bmi;
		bmi = weight / (height * height);
		cout << endl << endl << "WEIGHT(kg): " << weight << endl << endl << "HEIGHT(m): " << height << endl << endl << "BMI SCORE: " << bmi << "\t";
		if (bmi < 18)
		{
			cout << "YOU ARE UNDERWEIGHT!";
		}
		else if (bmi > 18 && bmi < 25)
		{
			cout << "YOU ARE IN YOUR WEIGHT RANGE!";
		}
		else
		{
			cout << "YOU ARE OVERWEIGHT!";
		}
		int choice;
		cout << endl << endl << "Enter any number to go back: ";
		cin >> choice;
		cout << endl << endl;
	}
	void BMItrack(float weight, float height, int age)
	{
		//cout<<weight<<" "<<height<<" "<<age<<endl;
		int choice;
		double BMI = weight / (height * height / 10000);
		system("CLS");
		Ascii font = Ascii(amongus);
		font.print("BMITRACKER");
		cout << endl;
		//cout << setw(90) << "_+_+_+_BMI TRACKER+_+_+_" << endl << endl << endl << endl;
		cout << endl << endl << "WEIGHT: " << weight << endl << endl << "HEIGHT: " << height << endl << endl << "BMI SCORE: " << BMI << "\t";
		cout << endl;
		if (BMI < 18.5)
		{
			cout << "Underweight" << endl;
		}
		else if (BMI >= 18.5 && BMI <= 24.9)
		{
			cout << "Normal Weight" << endl;
		}
		else if (BMI >= 25 && BMI <= 29.9)
		{
			cout << "Overweight" << endl;
		}
		else if (BMI >= 30)
		{
			cout << "Obese" << endl;
		}
		cout << endl << endl << "Enter any number to go back: ";
		cin >> choice;
		cout << endl << endl;
	}

};
class Menu :virtual public User, public Login, public Excercises, public BMIChecker, public BMRChecker
	, DietRecipes, public WaterTracker
{
public:
	Menu()
	{
		LoginDisplay();
		system("CLS");

	}
	virtual void Display()
	{

		int Choice = 0;
		loadProgress(loginuser.username);
		while (Choice != 11)
		{
			system("CLS");
			Ascii font = Ascii(amongus);
			font.print("MENU");
			cout << endl;
			//cout << setw(80) << "_+_+_+_MENU_+_+_+_" << endl << endl << endl;
			motivation();
			cout << "1.  Excercises" << endl;
			cout << "2.  Diet Recipies" << endl;
			cout << "3.  Water Tracker" << endl;
			cout << "4.  BMI Tracker + Calculator" << endl;
			cout << "5.  BMR Checker" << endl;
			cout << "6.  Progress" << endl;
			cout << "7.  UserInformation" << endl;
			cout << "8.  InformationUpdater" << endl;
			cout << "9.  Bonus Achievement" << endl;
			cout << "10. LogOut" << endl << endl;
			cout << "Enter Your choice: ";
			cin >> Choice;
			while (Choice < 1 || Choice>10)
			{
				cout << endl << "Enter Correct Choice: ";
				cin >> Choice;
			}
			if (Choice == 1)
			{
				int choices;
				system("CLS");
				Ascii font = Ascii(amongus);
				font.print("EXCERCISE");
				cout << endl;
				//cout << setw(80) << "_+_+_+_EXCERCISE MENU_+_+_+_" << endl << endl << endl << endl;
				cout << "1.Customize a plan and run it!\n2.Manual Excercise\n3.Back to Menu" << endl;
				cout << "Choose your choice: ";
				cin >> choices;
				while (choices > 3 || choices < 1)
				{
					cout << "Enter correct choice: ";
					cin >> choices;
				}
				if (choices == 1)
				{
					cutomizeexcercise(level, size);
				}
				else if (choices == 2)
				{
					DisplayEx(level, size);
				}
			}
			else if (Choice == 2)
			{
				DisplayRecipe();
			}
			else if (Choice == 3)
			{
				DisplayWater(loginuser.weight);
			}
			else if (Choice == 4)
			{
				int c = 0;

				while (c != 4)
				{
					system("CLS");
					Ascii font = Ascii(amongus);
					font.print("BMIMENU");
					cout << endl;
					//cout << setw(80) << "_+_+_+_BMI TRACKER AND CALCULATOR_+_+_+_" << endl << endl << endl << endl;
					cout << "1.  BMI TRACKER(YOUR ACCOUNT)" << endl;
					cout << "2.  BMI CALCULATOR" << endl;
					cout << "3.  BACK TO MENU" << endl << endl;

					cout << "Enter your option: ";
					cin >> c;
					while (c > 3 || c < 1)
					{
						cout << endl << "Enter the correct option: ";
						cin >> c;
					}
					if (c == 2)
					{
						DisplayBMI();
					}
					else  if (c == 1)
					{
						BMItrack(loginuser.weight, loginuser.height, loginuser.age);
					}
					else
					{
						break;
					}
				}

			}
			else if (Choice == 5)
			{
				DisplayBMR(loginuser.weight, loginuser.height, loginuser.age);
			}
			else if (Choice == 6)
			{
				DisplayProgress();
			}
			else if (Choice == 7)
			{
				User::Display(loginuser);
			}
			else if (Choice == 8)
			{
				UpdateInfo(loginuser.username);
			}
			else if (Choice == 9)
			{
				int temp;
				bonusachievements(level);
				cout << "Enter any number to go back: ";
				cin >> temp;
			}
			else
			{
				system("CLS");
				addProgress();
				LoginDisplay();
			}
		}
	}
	void addProgress() {
		int count; //counts each line from the file is read
		fstream file;
		bool flag = false;
		file.open("Progress.txt", ios::in);
		if (!file.is_open()) {
			file.close();
			file.open("Progress.txt", ios::out);
			file.close();
			file.open("Progress.txt", ios::in);
			flag = true;
		}
		while (!file.eof() && !flag) {
			count = 0;
			string temp;
			getline(file, temp);
			count++;
			if (temp == loginuser.username) {
				count--;
				//update progress if progress already exists
				file.close();
				file.open("Progress.txt", ios::in);
				fstream tempfile;
				tempfile.open("temp.txt", ios::out);
				for (int i = 0; i < count; i++) {
					getline(file, temp);
					tempfile << temp;
				}
				tempfile << loginuser.username << endl;
				tempfile << level << endl;
				tempfile << size << endl;
				getline(file, temp);//reading unwanted lines... to skip reading the old progress
				getline(file, temp);
				getline(file, temp);
				while (!file.eof()) {
					getline(file, temp);
					tempfile << temp << endl;
				}
				file.close();
				tempfile.close();
				tempfile.open("temp.txt", ios::in);
				file.open("Progress.txt", ios::out);
				while (!tempfile.eof()) {
					getline(tempfile, temp);
					file << temp << endl;
				}
				return;
			}
			getline(file, temp); //read to skip the unecessary information
			getline(file, temp);
			count = count + 2;
		}
		file.close();
		file.open("Progress.txt", ios::app);
		file << loginuser.username << endl;
		file << level << endl;
		file << size << endl;
		cout << "Progress added successfully\n";
		file.close();
	}
};
int main()
{
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 900);
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 14);
	Menu app;
	app.Display();
	return 0;
}
