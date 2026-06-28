# OpenGym

A C++ gym management application with PostgreSQL persistence. Built as a hands-on project to refresh and modernize my C++ and database skills for backend developer roles in the DACH region.

## About this project

I studied C, C++, and PostgreSQL during my Bachelor of Computer Applications, and I wanted to bring those skills back into active shape while job-searching for analyst and junior developer positions in Germany. OpenGym is a small but functional gym management system that models the kind of domain real fitness studio software deals with — members, contracts, relationships, and persistence.

The project gave me a chance to apply academic foundations in a modern, production-style C++ context: C++20, the CMake build system, the repository pattern, and direct integration with PostgreSQL via libpqxx. The focus is on clean architecture and clear separation between business objects, persistence, and the user interface.

## Features

- Add, list, search, and manage gym members
- Add, list, and filter contracts (with foreign-key relationship to members)
- Query contracts by member ID (one-to-many relationship)
- Robust input validation (handles bad input without crashing)
- PostgreSQL persistence — data survives between sessions
- Interactive CLI menu

## Tech stack

- **Language:** C++20
- **Build system:** CMake
- **Database:** PostgreSQL 16
- **DB client library:** libpqxx 8
- **Platform:** macOS (clang++); should build on Linux with minimal/no changes

## Architecture
The two **Repository** classes encapsulate all database access. `main.cpp` knows nothing about SQL — it just calls `addMember(...)`, `listAll()`, `findById(...)`. This separation makes it trivial to swap the storage layer.

## Database schema

```sql
CREATE TABLE members (
    id INTEGER PRIMARY KEY,
    first_name VARCHAR(100) NOT NULL,
    last_name VARCHAR(100) NOT NULL,
    email VARCHAR(200) NOT NULL
);

CREATE TABLE contracts (
    id INTEGER PRIMARY KEY,
    member_id INTEGER NOT NULL REFERENCES members(id),
    type VARCHAR(100) NOT NULL,
    monthly_fee NUMERIC(10, 2) NOT NULL,
    active BOOLEAN NOT NULL
);
```

The `member_id` foreign key enforces the relationship at the database level — a contract cannot reference a non-existent member.

## How to build and run

### Prerequisites (macOS)

```bash
brew install cmake postgresql@16 libpqxx pkg-config
brew services start postgresql@16
```

### Create the database

```bash
createdb opengym
psql opengym -c "CREATE TABLE members (id INTEGER PRIMARY KEY, first_name VARCHAR(100) NOT NULL, last_name VARCHAR(100) NOT NULL, email VARCHAR(200) NOT NULL); CREATE TABLE contracts (id INTEGER PRIMARY KEY, member_id INTEGER NOT NULL REFERENCES members(id), type VARCHAR(100) NOT NULL, monthly_fee NUMERIC(10, 2) NOT NULL, active BOOLEAN NOT NULL);"
```

### Build

```bash
mkdir -p build
cd build
cmake ..
make
```

### Run

```bash
./opengym
```

## What this project reinforced

Returning to C++ after working in analyst-focused roles, a few things stood out:

- **Header vs. implementation separation** is enforced by the language and pays off as the project grows
- **Modern CMake** is essential for any non-trivial C++ codebase; it abstracts platform differences cleanly
- **The repository pattern** lets the rest of the application be storage-agnostic — switching from file persistence to PostgreSQL touched only two files
- **`const` and references (`const T&`)** are not optional politeness; they're how modern C++ communicates intent and enforces correctness at compile time
- **libpqxx + parameterized queries** make safe database access ergonomic and prevent SQL injection

## What's next

- **Qt / QML GUI** to replace the CLI menu — natural extension of the existing layer separation
- Additional entities (Courses, Check-ins, Invoices)
- Unit tests with GoogleTest
- Connection pooling for production-style robustness

## Author

[Akshay Amin](https://github.com/Akshayamin13) — Bachelor of Computer Applications graduate, currently based in Oldenburg, Germany, with an MBA in General Technology Management (Data Science focus). Actively job-searching for analyst and junior developer roles in the DACH region.
