#include <iostream>
#include "SlayViber.h"

using namespace std;

int main() {
    cout << "GENERATE TESTCASES..\n";
    cout << "\n=== Test 1: Default Constructor & Print ===\n";
    SlayViber user1;
    user1.print(); // user "userXXXXX" information: Followers: 0, Streaming: No, Registered: No, Restriction: No

    cout << "\n=== Test 2: Interactive Registration ===\n";
    user1.registration(); // user enters username/password, prints registration success
    user1.print(); // user "enteredUsername" information: Followers: 0, Streaming: No, Registered: Yes, Restriction: No

    cout << "\n=== Test 3: Already Registered User ===\n";
    SlayViber user2("Alice", "pass123", 10, false);
    user2.registration(); // User "Alice" is already registered.

    cout << "\n=== Test 4: Visiting Another User ===\n";
    SlayViber visitor("Bob", "passBob", 50, false);
    SlayViber target("Carol", "passCarol", 100, false);
    visitor.visit(target); // Bob visited Carol, user "Carol" info: Followers: 100, Streaming: No, Registered: Yes, Restriction: No
    cout << "Carol followers nowL: " << target.getFollowers() << endl;

    cout << "\n=== Test 5: Visiting Deleted User ===\n";
    SlayViber deletedUser("Dave", "pass", 20, false);
    deletedUser.deleteUser(); // User "Dave" deleted successfully.
    visitor.visit(deletedUser); // This account cannot visit another user because one of the accounts has been deleted.

    cout << "\n=== Test 6: Go Live & Follower Change ===\n";
    SlayViber liveUser("Eve", "pass", 200, false);
    liveUser.goLive(); // Eve is live now! Eve gained XXX followers OR Eve lost XXX followers
    liveUser.print(); // user "Eve" info updated with new followers

    cout << "\n=== Test 7: Go Live With Restriction ===\n";
    SlayViber restrictedUser("Frank", "pass", 50, true);
    restrictedUser.goLive(); // Frank is restricted and cannot go live.

    cout << "\n=== Test 8: Delete Registered User ===\n";
    SlayViber regUser("Grace", "pass", 10, false);
    regUser.deleteUser(); // User "Grace" deleted successfully.
    regUser.print(); // This user has been deleted.

    cout << "\n=== Test 9: Delete Unregistered User ===\n";
    SlayViber unregUser;
    unregUser.deleteUser(); // Cannot delete this user because he/she isnt registered.

    cout << "\n=== Test 10: Visiting Self ===\n";
    SlayViber selfUser("Henry", "pass", 5, false);
    selfUser.visit(selfUser); // Henry visited Henry, user "Henry" info: Followers: 5, Streaming: No, Registered: Yes, Restriction: No

    cout << "\n=== Test 11: Multiple Users & Visitors ===\n";
    SlayViber u1("Ira", "pass", 10, false); // Username exists, u1 -> invalid user
    SlayViber u2("Jack", "pass", 20, false);
    SlayViber u3("Kate", "pass", 15, false);
    u1.visit(u2); // invalid user
    u2.visit(u3); // Jack visited Kate, Kate info
    u3.visit(u1); // Kate visited Ira, Ira info

    cout << "\n=== Test 12: Print infos ===\n";
    u1.print(); // invalid user
    u2.print(); // user "Jack" info
    u3.print(); // user "Kate" info

    return 0;
}