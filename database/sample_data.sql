-- Example data for testing OpenGym

INSERT INTO members (id, first_name, last_name, email) VALUES
    (1, 'Akshay', 'Amin', 'akshay@example.com'),
    (2, 'Anna', 'Schmidt', 'anna.schmidt@example.com'),
    (3, 'Lukas', 'Mueller', 'lukas.m@example.com');

INSERT INTO contracts (id, member_id, type, monthly_fee, active) VALUES
    (100, 1, 'Premium', 49.99, true),
    (101, 1, 'Personal Training', 120.00, true),
    (102, 2, 'Basic', 29.99, true),
    (103, 3, 'Basic', 29.99, false);
