**What it does?**

A simple command-line tool written in C++ to block and unblock websites by modifying the system hosts file on macOS.

This project helped me understand how DNS resolution and the /etc/hosts file work internally.

Instead of DNS request going to the server, it is going to the hosts file and checking there only

This technique can be used in other Web Development projects also

We can also block advertisements like this, the logic remains the same

**When you block a domain, the tool adds entries like:**

127.0.0.1 google.com #BLOCKED_BY_BLOCKER
127.0.0.1 www.google.com #BLOCKED_BY_BLOCKER

This forces the system to resolve the website to 127.0.0.1 (localhost), effectively blocking it.

After modification, the DNS cache is flushed automatically.

**How to Run?**

Open terminal first and follow below steps

Step 1: Build

g++ blocker.cpp -o blocker

Step 2: Block a Website

sudo ./blocker add github.com

**Remove a blocked website**

Step 1: Build

g++ blocker.cpp -o blocker

Step 2: Remove from hosts file

sudo ./blocker remove github.com

**Lists Host file content**

sudo ./blocker list

🧠 **What I Learned?**

How DNS resolution works

Role of /etc/hosts file in our system

File handling in C++

Basic system-level programming concepts

Conclusion: Currently tested on macOS, Will make it cross-platform in the future.
