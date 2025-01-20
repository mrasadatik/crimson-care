# CrimsonCare

## Description

CrimsonCare is a C project designed to provide a robust solution for blood management. This project is configured to support both Debug and Release builds.

## Course Information

-   **University:** East West University
-   **Course:** CSE207 - Data Structures
-   **Instructor:** <span style="display: inline-flex; justify-content: center; align-items: center; gap: 5px">Dr. Hasan Mahmood Aminul Islam (DHMAI) <a href="https://fse.ewubd.edu/computer-science-engineering/faculty-view/hasan.mahmood"><img src="https://raw.githubusercontent.com/mrasadatik/mrasadatik/refs/heads/main/.storage/graphics/ewu/logo/East-west-university-Logo-40px-min-mini.png" alt="EWU Faculty View: DHMAI" height="20"></a></span>
-   **Teaching Assistant:** Abdullah Al Tamim

## Project Structure

```
|-- .editorconfig
|-- .gitignore
|-- CrimsonCare.cbp
|-- CrimsonCare.layout
|-- LICENSE
|-- main.c
|-- Makefile
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
  |-- .gitkeep
  |-- db
    |-- .gitkeep
```

## Installation and Build

### Prerequisites

-   <details>
    <summary>GCC Compiler</summary>

    **Description**: The GNU Compiler Collection (GCC) is a standard compiler for C and C++.

    **Installation**:

    -   <details>
        <summary>Windows</summary>

        **MinGW Installation**:

        1.  Download the MinGW installer from the [MinGW-w64 project](https://sourceforge.net/projects/mingw/files/latest/download).
        2.  Choose the appropriate version for your system (32-bit or 64-bit).
        3.  Run the installer.
        4.  Once installed, add the MinGW `bin` directory to your system PATH..
        5.  Verify the installation by opening Command Prompt and running:
            ```bash
            gcc --version
            ```
            You should see the version of GCC installed.

        </details>

    -   <details>
        <summary>Linux</summary>

        **Ubuntu/Debian**:

        ```bash
          sudo apt update
          sudo apt install build-essential
        ```

        **Fedora**:

        ```bash
          sudo dnf groupinstall "Development Tools"
        ```

        </details>

    -   <details>
        <summary>macOS</summary>

        **macOS**: Install Xcode Command Line Tools:

        ```bash
        xcode-select --install
        ```

        </details>

    </details>

-   <details>
    <summary>Git</summary>

    -   **Description**: A version control system to manage source code.
    -   **Installation**: Download and install Git from the [official Git website](https://git-scm.com/downloads). Follow the installation instructions for your operating system.
    </details>

-   <details>
    <summary>Code::Blocks IDE (Optional)</summary>

    -   **Description**: An open-source Integrated Development Environment (IDE) for C/C++ programming.
    -   **Installation**: If you prefer using an IDE, download and install Code::Blocks from the [official website](https://www.codeblocks.org/downloads/binaries/). Choose the version that includes the MinGW compiler (typically labeled as "codeblocks-XX.XXmingw-setup.exe").

    </details>

### Clone the repository

1. **Clone the repository:**

    ```bash
    git clone https://github.com/mrasadatik/crimson-care.git
    cd crimson-care-main
    ```

### Build for Code::Blocks IDE

2. **Open the project in Code::Blocks:**

    - Open Code::Blocks IDE.
    - Go to `File` -> `Open...` and select `CrimsonCare.cbp`.

3. **Build the project:**
    - Select the desired build target (Debug or Release).
    - Click on the `Build` button or press `F9`.

### Build for Command Line (Using Make)

#### On Linux/Mac

##### Default Build

To build both Debug and Release versions, run:

```bash
make
```

<details>
<summary>More options</summary>

##### Debug Build

To build only the Debug version, run:

```bash
make debug
```

##### Release Build

To build only the Release version, run:

```bash
make release
```

</details>

#### On Windows

##### Default Build

To build both Debug and Release versions, run:

```bash
mingw32-make
```

<details>
<summary>More options</summary>

##### Debug Build

To build only the Debug version, run:

```bash
mingw32-make debug
```

##### Release Build

To build only the Release version, run:

```bash
mingw32-make release
```

</details>

### Build for Command Line (Without Make)

#### Debug Build

To build the project in Debug mode, run the following command:

```bash
mkdir -p bin/Debug && gcc -o bin/Debug/CrimsonCare src/*.c -I include -g3 -mconsole -static
```

#### Release Build

To build the project in Release mode, run the following command:

```bash
mkdir -p bin/Release && gcc -o bin/Release/CrimsonCare src/*.c -I include -O3 -mconsole -static
```

## Usage

To run the application, execute the compiled binary located in the `bin/Debug/` or `bin/Release/` directory, depending on the build configuration you chose.

Example:

-   Debug Build:

    ```bash
    ./bin/Debug/CrimsonCare.exe
    ```

-   Release Build:

    ```bash
    ./bin/Release/CrimsonCare.exe
    ```

## Contributors

-   Maysha Taskin Iqra (2023-1-60-152)
-   Sabiha Akter Chaity (2023-2-60-057)
-   Sumyya Tabassum (2023-3-60-351)
-   Arnab Saha (2021-3-60-201)
-   Md Shahoriyer Nadim (2023-3-60-189)
-   [Md Asaduzzaman Atik](https://github.com/mrasadatik) (2023-1-60-130)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

-   [Code::Blocks](http://www.codeblocks.org/) - The IDE used for this project.
-   Stack Overflow Question: [how to show enter password in the form of Asterisks(\*) on terminal](https://stackoverflow.com/questions/25990966/how-to-show-enter-password-in-the-form-of-asterisks-on-terminal)
