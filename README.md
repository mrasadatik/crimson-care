# CrimsonCare

## Description

CrimsonCare is a C project designed to provide a robust solution for blood management. This project is configured to support both Debug and Release builds.

## Course Information

-   **University:** East West University
-   **Course:** CSE207 - Data Structures
-   **Instructor:** <span style="display: inline-flex; justify-content: center; align-items: center; gap: 5px">Dr. Hasan Mahmood Aminul Islam (DHMAI) <a href="https://fse.ewubd.edu/computer-science-engineering/faculty-view/hasan.mahmood" target="_blank" style="background-color: white; border: none; padding: 1px; margin: 0;"><img src="./resources/assets/images/East-west-university-Logo-40px-mini-mini.png" alt="EWU Faculty View: DHMAI" height="20"></a></span>
-   **Teaching Assistant:** Abdullah Al Tamim

## Project Structure

```plaintext
|-- .editorconfig
|-- .gitignore
|-- CrimsonCare.cbp
|-- CrimsonCare.layout
|-- CrimsonCare.workspace
|-- Doxyfile
|-- LICENSE.md
|-- main.c
|-- Makefile
|-- README.md
|-- include
  |-- admin_manager.h
  |-- blood_manager.h
  |-- hospital_manager.h
  |-- misc.h
  |-- transaction_manager.h
|-- src
  |-- admin_manager.c
  |-- blood_manager.c
  |-- hospital_manager.c
  |-- misc.c
  |-- transaction_manager.c
|-- docs
|-- report
  |-- crimson-care-project-report.tex
  |-- docs
    |-- latex
|-- resources
  |-- db
  |-- assets
    |-- images
    |-- misc
      |-- cc.txt
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
    cd crimson-care
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

#### On Linux/Mac

##### Debug Build

To build the project in Debug mode, run the following command:

```bash
mkdir -p bin/Debug && gcc -Wall -Wextra -g3 -Iinclude main.c src/*.c -o bin/Debug/CrimsonCare
```

##### Release Build

To build the project in Release mode, run the following command:

```bash
mkdir -p bin/Release && gcc -Wall -Wextra -O3 -Iinclude main.c src/*.c -o bin/Release/CrimsonCare
```

#### On Windows

##### Debug Build

To build the project in Debug mode, run the following command:

```bash
mkdir -p bin/Debug && gcc -Wall -Wextra -g3 -mconsole -Iinclude main.c src/*.c -o bin/Debug/CrimsonCare.exe
```

##### Release Build

To build the project in Release mode, run the following command:

```bash
mkdir -p bin/Release && gcc -Wall -Wextra -O3 -mconsole -Iinclude main.c src/*.c -o bin/Release/CrimsonCare.exe
```

## Usage

To run the application, execute the compiled binary located in the `bin/Debug/` or `bin/Release/` directory, depending on the build configuration you chose.

Example:

**On Linux/Mac**

-   Debug Build:

    ```bash
    ./bin/Debug/CrimsonCare
    ```

-   Release Build:

    ```bash
    ./bin/Release/CrimsonCare
    ```

**On Windows**

-   Debug Build:

    ```bash
    bin\Debug\CrimsonCare.exe
    ```

-   Release Build:

    ```bash
    bin\Release\CrimsonCare.exe
    ```

## Contributors

-   Maysha Taskin Iqra (2023-1-60-152)
-   Sabiha Akter Chaity (2023-2-60-057)
-   Sumyya Tabassum (2023-3-60-351)
-   Arnab Saha (2021-3-60-201)
-   Md Shahoriyer Nadim (2023-3-60-189)
-   [Md Asaduzzaman Atik](https://github.com/mrasadatik) (2023-1-60-130)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.

## Acknowledgments

-   [Code::Blocks](http://www.codeblocks.org/) - The IDE used for this project.
-   [Doxygen](https://www.doxygen.nl/) - The documentation generator used for this project.
-   [Git](https://git-scm.com/) - The version control system used for this project.
-   [GitHub](https://github.com/) - The platform used to host the repository.
-   [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) - The specification used for commit messages.
-   [LaTeX (MikTeX)](https://miktex.org/) - The LaTeX distribution used to generate the report.
-   Stack Overflow Question: [how to show enter password in the form of Asterisks(\*) on terminal](https://stackoverflow.com/questions/25990966/how-to-show-enter-password-in-the-form-of-asterisks-on-terminal)
-   Stack Overflow Question: [How to display asterisk for input password in C++ using CLion](https://stackoverflow.com/questions/41652182/how-to-display-asterisk-for-input-password-in-c-using-clion)
-   Dev.to Post - [How to take hidden password from terminal in C/C++](https://dev.to/namantam1/how-to-take-hidden-password-from-terminal-in-cc-3ddd)
-   Report Writing Inspiration:
    -   [HeadBall Report](https://raw.githubusercontent.com/RujalAcharya/HeadBall/main/project_report.pdf)
    -   [Software Engineering Final Year Project Report](https://www.slideshare.net/judebwayo/software-engineering-final-year-project-report)
    -   [rvce-latex/Project-Report-Template](https://github.com/rvce-latex/Project-Report-Template/blob/main/Main.pdf)
