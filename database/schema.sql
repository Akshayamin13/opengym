-- OpenGym database schema

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
