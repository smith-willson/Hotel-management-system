# Hotel Management System

A console-based Hotel Management System written in C as a first-year university project. It demonstrates modular C programming, structures, arrays, input validation, date calculations, file handling, and CRUD operations.

## Features
- Admin login with a three-attempt limit and masked password input on Windows.
- Customer registration and automatic room assignment (15 rooms).
- Customer details lookup, update, and deletion.
- Room availability overview.
- Check-in/check-out validation and stay-duration calculation.
- Bill generation in PKR for Single and Double rooms.
- CSV persistence in `database/customers.csv`.

## Project structure
```text
Hotel-Management-System/
├── include/       # Header files
├── src/           # C implementation files
├── database/      # Runtime CSV data (created automatically)
├── main.c
├── README.md
└── .gitignore
```

## Requirements
- GCC (C11 compatible)
- Windows, Linux, or macOS

## Build
Run this command from the project root:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c src/*.c -o hotel
```

On Windows, run `hotel.exe`. On Linux/macOS, run `./hotel`.

## Demo login
| Field | Value |
|---|---|
| Username | `admin` |
| Password | `12345` |

These are demonstration credentials stored in the source code, not production-grade authentication.

## Notes
- The application supports 15 rooms and keeps each room number assigned to one saved customer record until that record is deleted.
- To keep the CSV format simple, text fields must not contain commas.
- The `database` folder is created automatically when saving records. Runtime customer data is excluded from Git.
- Room rates and service charges are fixed demonstration values in PKR and can be changed in `src/Customer.c`.

## Author
Muhammad Haseeb — Computer & Information Systems Engineering Student

GitHub: [smith-willson](https://github.com/smith-willson)
