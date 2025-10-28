#include "SlayViber.h"

random_device SlayViber::rd;
set<string> SlayViber::usernames;

// Default constructor
SlayViber::SlayViber() { 
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(100000, 999999);
    username = string("user") + to_string(dis(gen));
}

// Parametric constructor
SlayViber::SlayViber(string username, string password, int followers, bool hasRestriction)
    : username(username), password(password), followers(followers),
    streaming(false), isRegistered(false), hasRestriction(hasRestriction) {
    if (usernames.count(username)) {
        cout << "Username exists!\n";
        invalid = 1;
        return; // <-- just exits constructor, still a new object exists
    }
    isRegistered = 1;
    usernames.insert(username);
}

// Prints all relevant information about this user
void SlayViber::print() const{
    if (invalid) { cout << "invalid user\n"; return; }
    if (deleted) {
        cout << "This user has been deleted.\n";
        return;
    }

    cout << "\nuser " << username <<" information:\n";
    cout << "Followers: " << followers << "\n";
    cout << "Streaming: " << (streaming ? "Yes" : "No") << "\n";
    cout << "Registered: " << (isRegistered ? "Yes" : "No") << "\n";
    cout << "Restriction: " << (hasRestriction ? "Yes" : "No") << "\n";
}

// Records that this user visited another SlayViber user and prints information about this user.
void SlayViber::visit(SlayViber& other) {
    if (invalid || other.invalid) { cout << "invalid user\n"; return; }
    if (this->deleted || other.deleted) {
        cout << "This account cannot visit another user because one of the"
            << " accounts has been deleted.\n";
        return;
    }
    // Add this user to the other user's visitors list
    other.visitors.push_back(this->username);

    // Print log about the visit
    cout << this->username << " visited " << other.username << "\n";

    // Print this user's information
    other.print();

    // // If the user visit themselves, do nothing after.
    if (this == &other) return;

    // Ask if visitor wants to follow
    char choice;
    cout << "Do you want to follow " << other.username << "? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        other.followers++;
        cout << "You are now following " << other.username << "! " << other.username << "'s Followers: " << other.followers << "\n";
    }
    else {
        cout << "You did not follow " << other.username << ".\n";
    }
}


// Register unregistered user
void SlayViber::registration() {
    if (invalid) { cout << "invalid user\n"; return; }
    if (deleted || isRegistered) {
        cout << (deleted ? "This user has been permanently deleted."
            : string("User ") + username + " is already registered.\n");
        return;
    }

    // Interactive register user
    string inputUsername;
    string inputPassword;
    cout << "Enter username: ";
    cin >> inputUsername;
    cout << "Enter password: ";
    cin >> inputPassword;

    // Check if username already exists
    if (usernames.count(inputUsername)) {
        cout << "Registration unsuccessfull. Username already taken! Try again.\n";
        return;
    }

    username = inputUsername;
    password = inputPassword;
    isRegistered = 1;
    usernames.insert(username);

    cout << "User \"" << username << "\" registered successfully!\n";
}

void SlayViber::goLive() {
    if (invalid) { cout << "invalid user\n"; return; }
    if (deleted) {
        cout << "This user has been deleted.\n";
        return;
    }

    if (streaming) {
        cout << username << " is already live!\n";
        return;
    }

    if (hasRestriction) {
        cout << username << " is restricted and cannot go live.\n";
        return;
    }

    streaming = true;
    cout << username << " is live now!\n";

    mt19937 gen(rd());

    // Decide increase or decrease: 0 = decrease, 1 = increase
    uniform_int_distribution<int> incOrDec(0, 1);
    bool increase = incOrDec(gen);

    int originalFollowers = followers;

    if (increase) {
        // Increase 5% - 40%
        uniform_int_distribution<int> dist(5, 40);
        int percent = dist(gen);
        int add = followers * percent / 100;
        followers += add;
        cout << username << " gained " << add << " followers (" << percent << "%)!\n";
    }
    else {
        // Decrease 0% - 30%
        uniform_int_distribution<int> dist(0, 30);
        int percent = dist(gen);
        int sub = followers * percent / 100;
        followers -= sub;
        cout << username << " lost " << sub << " followers (" << percent << "%)!\n";

        // Check if drop > 25%
        if (percent > 25) {
            hasRestriction = true;
            streaming = false;
            cout << username << " has been restricted due to large follower loss!\n";
        }
    }
}

// Deletes the user permanentlty, cant re-register, but the username will be accesible to toher
void SlayViber::deleteUser() {
    if (invalid) { cout << "invalid user\n"; return; }
    if (deleted || !isRegistered) {
        cout << (deleted ? "This user has already been deleted."
            : "Cannot delete this user because he/she isnt registered.\n");
        return;
    }

    visitors.clear();
    deleted = 1;
    usernames.erase(username);
    cout << "User " << this->username << " deleted successfully.\n";
}

// Getters
string SlayViber::getUsername() const { return username; }
int SlayViber::getFollowers() const { return followers; }
bool SlayViber::getRestrictionStatus() const { return hasRestriction; }
bool SlayViber::isDeleted() const { return deleted; }

// Setters (controlled)
void SlayViber::setFollowers(int f) { followers = f; }
void SlayViber::setRestrictionStatus(bool r) { hasRestriction = r; }