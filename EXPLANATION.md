# About this project — honest breakdown

This file explains what I built, what I understand, what AI helped with, and what I still need to learn. I think transparency matters more than appearing more senior than I am.

## What I built

- **Member management** — add members, list all members, find a member by ID
- **Contract management** — add contracts, list all contracts, list contracts belonging to a specific member
- **PostgreSQL persistence** — both members and contracts are stored in a real database, not in files
- **Repository pattern** — each business object has a repository class that handles its database access
- **Interactive CLI** — a simple menu loop in `main.cpp` that drives the application
- **Input validation** — the program doesn't crash when the user types unexpected input

## What I understand

### Why Member and Contract are separate classes
They represent different real-world things with different fields. A Member has a name and email; a Contract has a type, fee, and active flag. Keeping them in separate classes makes each one easier to extend later (for example, adding a phone number to Member doesn't touch Contract).

### How the foreign key links contracts to members
In the `contracts` table, `member_id` is defined as `REFERENCES members(id)`. This tells PostgreSQL that every contract must point to an existing member. If I try to insert a contract for a member ID that doesn't exist, the database refuses. This enforces the one-to-many relationship at the database level instead of relying on application code to check.

### How libpqxx sends parameterized SQL queries
Instead of building a SQL string by concatenation (which is vulnerable to SQL injection), I use `exec_params` with placeholders like `$1`, `$2`. The library safely substitutes the values when running the query. For example:
```cpp
txn.exec_params(
    "INSERT INTO members (id, first_name, last_name, email) VALUES ($1, $2, $3, $4)",
    m.id, m.firstName, m.lastName, m.email
);
```
This is safer and cleaner than string concatenation.

### Why main.cpp does not contain SQL directly
The repository classes (`MemberRepository`, `ContractRepository`) hide all database access behind methods like `addMember()` and `listAll()`. `main.cpp` only calls those methods. This means if I ever change the database (or move to a different storage), I only need to change the repository — not `main.cpp`. This is what the **repository pattern** does.

### How input validation prevents crashes
When `std::cin >> choice` expects a number but the user types letters, `cin` enters a failed state. Without handling this, the loop would spin uncontrollably. My code checks `std::cin.fail()`, clears the stream with `std::cin.clear()`, removes the bad input with `std::cin.ignore()`, and continues the loop cleanly.

### Why the build uses CMake
CMake is the standard build tool for C++ projects of any size. It figures out which files to compile, finds external libraries like libpqxx, and produces clean output. It also makes the project easier to build on different operating systems.

## What AI helped with

I used AI assistance throughout this project. Specifically:

- **Explaining C++ syntax and concepts** — for example, why headers and implementation files are split, what `const T&` means, how range-based for loops work
- **Debugging errors** — compiler messages can be cryptic; AI helped me read them and find the actual fix
- **Structuring the repository pattern** — I knew about it conceptually from my BCA studies, but AI helped me apply it cleanly in C++
- **Setting up libpqxx and PostgreSQL** — the initial wiring of CMake to find libpqxx, the connection setup, the transaction pattern
- **Improving the README and documentation**

## What I would do differently next time

- Spend more time on each concept before adding the next one. I sometimes added features faster than my full understanding could keep up.
- Use Git from day one (I added it only at the end). Tracking commits along the way would have helped me see my own progress.
- Write small tests for each new method instead of testing manually through the menu.

## What I still need to learn

- **Qt and QML** — the job posting that motivated this project mentions Qt, and I haven't touched it yet
- **Unit testing with GoogleTest** — testing patterns in C++
- **Connection pooling and production-grade error handling** — what real applications do under load


## Why I'm sharing all this

I'd rather be honest about my level than oversell. If I get an interview and someone asks me about a concept I claimed to know but don't really understand, that's much worse than being upfront about where I'm still learning. I'm a junior, I'm learning fast, and I'd rather be trusted than impressive.
