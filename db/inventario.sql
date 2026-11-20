CREATE TABLE IF NOT EXISTS components (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    type TEXT NOT NULL,
    quantity INTEGER NOT NULL DEFAULT 0,
    location TEXT,
    purchase_date TEXT,
    minimum_quantity INTEGER NOT NULL DEFAULT 0,
    notes TEXT
);
