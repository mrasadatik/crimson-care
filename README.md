# CrimsonCare

## Description

CrimsonCare is a C project designed to provide a robust solution for blood management. This project is configured to support both Debug and Release builds.

## Project Structure

```bash
|-- .gitignore
|-- CrimsonCare.cbp
|-- CrimsonCare.depend
|-- CrimsonCare.layout
|-- main.c
|-- README.md
|-- include
  |-- .gitkeep
  |-- admin_manager.h
  |-- blood_manager.h
  |-- hospital_manager.h
  |-- transaction_manager.h
|-- src
  |-- .gitkeep
  |-- admin_manager.c
  |-- blood_manager.c
  |-- hospital_manager.c
  |-- transaction_manager.c
|-- resources
  |-- db
```

## Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/CrimsonCare.git
   cd CrimsonCare
   ```

2. **Open the project in Code::Blocks:**

   - Open Code::Blocks IDE.
   - Go to `File` -> `Open...` and select `CrimsonCare.cbp`.

3. **Build the project:**
   - Select the desired build target (Debug or Release).
   - Click on the `Build` button or press `F9`.

## Usage

To run the application, execute the compiled binary located in the `bin/Debug/` or `bin/Release/` directory, depending on the build configuration you chose.

## Contributors

-

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Code::Blocks](http://www.codeblocks.org/) - The IDE used for this project.
