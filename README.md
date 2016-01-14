Brute - A password generator.

Usage:  ./brute [--help] [--alpha STR] [--len INT] [--maxlen INT] [--show]

  --help        Show this menu.

  --alpha STR   String of characters to use for password generation (default is all printable characters).

  --len INT     Length of passwords (default is 8).

  --maxlen INT  Length of passwords (includes passwords of size less than as well).

  --show        Shows the passwords in stderr (nice for viewing current password when redirecting passwords to a file).

Binary included is a statically stripped linux 32-bit binary.
