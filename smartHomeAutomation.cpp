
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Device states
    bool lightsOn = false;
    bool fanOn = false;
    bool autoMode = true;

    // Initial temperature and device power ratings (in watts)
    double temperature = 22.0;
    const double fanPower = 75.0;
    const double lightsPower = 20.0;

    int choice;

    // Display the menu until the user chooses to exit
    do {
        cout << "\n===== SMART HOME SYSTEM =====\n";
        cout << "1. Toggle lights\n";
        cout << "2. Toggle fan\n";
        cout << "3. Set temperature\n";
        cout << "4. Toggle automatic mode\n";
        cout << "5. View system status\n";
        cout << "6. Estimate power consumption\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";

        // Validate the user's menu input
        if (!(cin >> choice)) {
            cout << "Please enter a valid number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                // Turn the lights on or off
                lightsOn = !lightsOn;

                cout << "Lights are now "
                     << (lightsOn ? "ON" : "OFF") << ".\n";
                break;

            case 2:
                // Allow manual fan control only when auto mode is disabled
                if (!autoMode) {
                    fanOn = !fanOn;

                    cout << "Fan is now "
                         << (fanOn ? "ON" : "OFF") << ".\n";
                } else {
                    cout << "Disable automatic mode first.\n";
                }
                break;

            case 3:
                // Update the room temperature
                cout << "Enter temperature (0-50 C): ";

                if (!(cin >> temperature)) {
                    cout << "Invalid temperature.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    temperature = 22.0;
                    break;
                }

                // Keep the temperature within a reasonable range
                if (temperature < 0 || temperature > 50) {
                    cout << "Temperature out of range.\n";
                    temperature = 22.0;
                    break;
                }

                // Automatically control the fan based on temperature
                if (autoMode) {
                    fanOn = (temperature >= 28.0);
                }

                cout << "Temperature updated.\n";
                break;

            case 4:
                // Switch automatic temperature control on or off
                autoMode = !autoMode;

                // Adjust the fan immediately when automatic mode is enabled
                if (autoMode) {
                    fanOn = (temperature >= 28.0);
                }

                cout << "Automatic mode: "
                     << (autoMode ? "ON" : "OFF") << ".\n";
                break;

            case 5:
                // Display the current state of the system
                cout << "\n--- SYSTEM STATUS ---\n";
                cout << "Lights: "
                     << (lightsOn ? "ON" : "OFF") << "\n";
                cout << "Fan: "
                     << (fanOn ? "ON" : "OFF") << "\n";
                cout << "Temperature: "
                     << temperature << " C\n";
                cout << "Automatic mode: "
                     << (autoMode ? "ON" : "OFF") << "\n";
                break;

            case 6: {
                // Calculate the combined power of active devices
                double power = 0.0;

                if (lightsOn) {
                    power += lightsPower;
                }

                if (fanOn) {
                    power += fanPower;
                }

                // Display power in watts and estimated hourly energy in kWh
                cout << fixed << setprecision(1);
                cout << "Current power consumption: "
                     << power << " W\n";
                cout << "Estimated energy for 1 hour: "
                     << power / 1000.0 << " kWh\n";
                break;
            }

            case 0:
                cout << "Shutting down Smart Home System.\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
