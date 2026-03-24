
#include <iostream>
#include <string>
#include <limits>
#include "Media.h"
#include "Podcast.h"
#include "Song.h"
#include "LinkedList.h"

// Utility function to safely get string input
std::string getLineInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    // Clear any preceding newline characters from the buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    return input;
}

// Utility function to safely get integer input
int getIntInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

// === 6. Main Program Loop ===
int main() {
    // Instantiate the templated list with Song* (for Phase 1)
    // The structure is ready to be instantiated with Media* later
    LinkedList<Song> myPlaylist;  // Stores Song* pointers
    int choice = 0;

    std::cout << "Welcome to the Playlist Manager Starter Program (Templated Circular Edition)!" << std::endl;

    // Demonstrate initial insertion of various media types
    myPlaylist.insert(new Song("Bohemian Rhapsody", "Queen", 355));
    myPlaylist.insert(new Song("Stairway to Heaven", "Led Zeppelin", 482));
    myPlaylist.insert(new Song("Imagine", "John Lennon", 183));

    do {
        std::cout << "\n--- Menu ---" << std::endl;
        std::cout << "1. Add a new Song" << std::endl;
        std::cout << "2. Add a new Podcast" << std::endl;
        std::cout << "3. Display Playlist" << std::endl;
        std::cout << "4. Play Current Media Item" << std::endl;
        std::cout << "5. Play Next (Circular)" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting." << std::endl;
            choice = 6;
        }

        switch (choice) {
            case 1: { // Add Song
                // Collect user input for a new Song
                std::string title = getLineInput("Enter Song Title: ");
                std::string artist = getLineInput("Enter Artist Name: ");
                int duration = getIntInput("Enter duration in seconds: ");

                // Create the Song object dynamically and insert it as Song*
                myPlaylist.insert(new Song(title, artist, duration));
                std::cout << "[Song added successfully!]" << std::endl;
                break;
            }
            case 2: { // Add Podcast
                std::string title = getLineInput("Enter Podcast Episode Title: ");
                std::string host = getLineInput("Enter Host Name: ");
                int episodeNum = getIntInput("Enter Episode Number: ");

                // For Phase 1, we're using LinkedList<Song>, so Podcasts cannot be added yet
                // This will be enabled in later phases when we switch to LinkedList<Media*>
                std::cout << "[Note: Podcasts will be available when using LinkedList<Media*>]" << std::endl;
                std::cout << "[Creating and storing as Song for demonstration...]" << std::endl;

                // Temporary: Store as Song for Phase 1
                std::string combinedTitle = title + " (Podcast Episode)";
                myPlaylist.insert(new Song(combinedTitle, host, episodeNum * 60)); // Rough duration conversion
                std::cout << "[Item added as Song for Phase 1 demonstration!]" << std::endl;
                break;
            }
            case 3:
                myPlaylist.displayList();
                break;
            case 4:
                myPlaylist.playCurrent();
                break;
            case 5:
                myPlaylist.playNext();  // New circular play method
                break;
            case 6:
                std::cout << "Exiting Playlist Manager..." << std::endl;
                break;
            default:
                std::cout << "Invalid menu choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 6);

    // The LinkedList destructor is called automatically when 'myPlaylist' goes out of scope
    return 0;
}