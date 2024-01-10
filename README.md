# Workshop Part Inventory System

Welcome to the Workshop Part Inventory System! This system is designed to help you manage and keep track of electronic workshop parts efficiently.

## Features

### Local hosted, single-user database system!

### 1. Search Part

- Shows detailed information about a specific part, including:
  - Part ID
  - Part Name
  - Manufacturer
  - Manufacturer ID
  - Website ordered from
  - Part Cost
  - Inventory value

### 2. Update Part

#### Part Info

- Update the following details:
  - Part Name
  - Manufacturer
  - Manufacturer ID
  - Website Ordered From
  - Part Cost

#### Quantity

- Add or remove quantity for a specific part.

### 3. Add Part

- Add a new part to the inventory with the following details:
  - Part ID
  - Part Name
  - Manufacturer
  - Manufacturer ID
  - Website Ordered From
  - Part Cost

### 4. Remove Part

- Remove a part from the inventory by providing the Part ID. Includes deletion confirmation.

### 5. View Inventory

- Shows detailed information about every part in the inventory, including:
  - Part ID
  - Part Name
  - Part Cost

## Advantages of Local Database
 
- **No worries about server setup or maintenance!**
  - No need to set up and maintain a separate database hosting server.
  - Just download and run!
  
- **No security fears!**
  - Eliminates security concerns by removing the need to host your database on a server with public network exposure.

## Getting Started

To get started with the Workshop Part Inventory System, follow these steps:

1. Clone the repository to your local machine.
2. Build the project, for this there are three options:
   - Linux:
      1. Navigate to build/
      2. Run the 'makefile'
   - Windows:
      1. Navigate to build/
      2. Run the 'build_it.bat' file
   - Visual Studio 2022 IDE Build
      1. Navigate to build/visual_studio2022/
      2. Open the Application.sln with Visual Studio 2022
      3. Set the 'Solution Configuration' to release (This is the gray dropdown box under the 'Debug' toolbar option
      4. Under the 'Build' toolbar click 'Build Solution'
3. Depending on the method used in Step 2 the .exe file will be found under the following:
   - Linux: bin/
   - Windows: bin/
   - Visual Studio 2022: bin/visual_studio/Release/
     - If there is no Release folder but instead a Debug folder, redo Step 2 in the Release solution configuration.
4. Save a shortcut to the .exe on the Desktop or your preferred location.
5. Run the application.

## Usage

1. Navigate to the desired feature.
2. Follow the prompts or input fields to perform actions.

## Contributions

Contributions are welcome! If you have any suggestions, improvements, or bug fixes, feel free to submit a pull request.

## License

This project is licensed under the [GNU General Public License (GPL)](LICENSE).

Happy managing your workshop parts!
