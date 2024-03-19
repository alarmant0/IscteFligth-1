**IscteFLight**

IscteFLight is a simple flight management system implemented in Bash. It allows users to perform various tasks related to flight booking, checking flight status, registering passengers, and navigating through a user-friendly menu interface.

**Features**

- **Compra Bilhetes (`compra_bilhete.sh`):** This script allows users to purchase flight tickets by providing necessary details such as departure city, destination city, date, and passenger information.

- **Estado Voos (`estado_voos.sh`):** With this script, users can check the status of flights by entering the flight number or other relevant details.

- **Menu (`menu.sh`):** The main menu script provides users with options to access different functionalities of the system such as purchasing tickets, checking flight statuses, registering passengers, and viewing statistics.

- **Regista Passageiro (`regista_passageiro.sh`):** This script enables users to register passenger information for future reference or ticket booking purposes.

- **Statistics (`stats.sh`):** This script provides statistical information about flights, such as the number of tickets sold, revenue generated, etc.

**How to Use**

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/alarmant0/IscteFligth
   ```

2. **Navigate to the Project Directory and give execute permissions:**
   ```bash
   cd IscteFLight
   chmod +x compra_bilhete.sh estado_voos.sh menu.sh regista_passageiro.sh stats.sh
   ```

3. **Run the Scripts:**
   - To purchase tickets:
     ```bash
     ./compra_bilhetes.sh
     ```
   - To check flight statuses:
     ```bash
     ./estado_voos.sh
     ```
   - To access the main menu:
     ```bash
     ./menu.sh
     ```
   - To register a passenger:
     ```bash
     ./regista_passageiro.sh
     ```
   - To view statistics:
     ```bash
     ./stats.sh
     ```

4. **Follow the On-Screen Prompts:**
   Each script will prompt you for necessary information to complete the desired action. Follow the instructions provided in the terminal.

**Requirements**

- Bash (Bourne Again SHell) interpreter.
- Linux or macOS operating system (may work on Windows with WSL or Cygwin).

**License**

[MIT License](LICENSE)

