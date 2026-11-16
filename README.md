Open-source Pet Tracker
==

The goal of this project is to develop a cat GPS tracker, open-source, more robust and much cheaper than the competition.

Objectives:
- [ ] Optional wifi connection (AP) to manage the device
- [ ] Optional bluetooth communication
- [ ] Optional GSM reporting
- [ ] Sleep modes where the device sleeps for X amount of time, wakes up and tries to report position, etc
- [ ] GPS tracking

# Usage

This project's developpement is managed exclusively by Nix:

- Use `direnv allow` (or `nix develop .#open-pet-tracker`) to enter a developpement shell with all of the required dependencies available (espressif idf, etc)
- Then to build:
  ```
  cmake -B build
  cmake --build build
  ```
- To flash:
  - Keep boot button pressed on the ESP32
  - Plug the USB cable
  - `cmake --build build --target flash`
