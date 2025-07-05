# ATM Simulation with Secure SHA-256 Hashing

A C++ implementation of an ATM simulation system with secure password hashing using custom SHA-256 algorithm.

## Features

- Complete SHA-256 implementation
- Bank account management (create, deposit, withdraw)
- Transaction history logging
- Secure password storage (hashed, not plaintext)
- File-based persistence

🔒 Why SHA-256?
To ensure password security, raw passwords are never stored or compared in plaintext. Instead, they are hashed using the SHA-256 algorithm. This prevents reverse engineering of passwords in case of data breaches and promotes security best practices.
