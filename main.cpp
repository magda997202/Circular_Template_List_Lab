/* Name: Magda Hussein
* Date: 03/23/2026
 * Program:  Implementing a Circular List
 * Assignment: Circular Linked List Lab - Media Player Playlist
 */

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
    // Instantiate the templated list with Song* (for Phase 1 and 2)
    LinkedList<Song> myPlaylist;
    int choice = 0;

    std::cout << "Welcome to the Circular Playlist Manager!" << std::endl;
    std::cout << "Demonstrating circular linked list with wrap-around functionality.\n" << std::endl;

    // Demonstrate initial insertion with circular behavior
    std::cout << "Creating initial playlist with 3 songs:" << std::endl;
    myPlaylist.insert(new Song("Bohemian Rhapsody", "Queen", 355));
    myPlaylist.insert(new Song("Stairway to Heaven", "Led Zeppelin", 482));
    myPlaylist.insert(new Song("Imagine", "John Lennon", 183));
    std::cout << "[3 songs added to circular playlist]\n" << std::endl;

    do {
        std::cout << "\n--- Circular Playlist Menu ---" << std::endl;
        std::cout << "1. Add a new Song" << std::endl;
        std::cout << "2. Add a new Podcast (will be stored as Song for Phase 2)" << std::endl;
        std::cout << "3. Display Playlist" << std::endl;
        std::cout << "4. Play Current Media Item" << std::endl;
        std::cout << "5. Play Next (Circular - wraps around)" << std::endl;
        std::cout << "6. Reset to Beginning" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Exiting." << std::endl;
            choice = 7;
        }

        switch (choice) {
            case 1: { // Add Song
                std::string title = getLineInput("Enter Song Title: ");
                std::string artist = getLineInput("Enter Artist Name: ");
                int duration = getIntInput("Enter duration in seconds: ");

                myPlaylist.insert(new Song(title, artist, duration));
                std::cout << "[Song added successfully to circular playlist!]" << std::endl;
                break;
            }
            case 2: { // Add Podcast (for Phase 2 demonstration)
                std::string title = getLineInput("Enter Podcast Episode Title: ");
                std::string host = getLineInput("Enter Host Name: ");
                int episodeNum = getIntInput("Enter Episode Number: ");

                // For Phase 2, we store as Song since LinkedList<Song> is being used
                std::string combinedTitle = title + " (Podcast Ep." + std::to_string(episodeNum) + ")";
                myPlaylist.insert(new Song(combinedTitle, host, episodeNum * 60));
                std::cout << "[Podcast added as song for circular playlist demonstration!]" << std::endl;
                break;
            }
            case 3:
                myPlaylist.displayList();
                break;
            case 4:
                std::cout << "\n[Playing current item:] ";
                myPlaylist.playCurrent();
                break;
            case 5:
                std::cout << "\n[Playing next item with circular wrap-around:]" << std::endl;
                myPlaylist.playNext();
                break;
            case 6:
                myPlaylist.resetCurrent();
                std::cout << "[Current position reset to beginning of playlist]" << std::endl;
                break;
            case 7:
                std::cout << "Exiting Circular Playlist Manager..." << std::endl;
                break;
            default:
                std::cout << "Invalid menu choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 7);

    // The LinkedList destructor is called automatically when 'myPlaylist' goes out of scope
    return 0;
}