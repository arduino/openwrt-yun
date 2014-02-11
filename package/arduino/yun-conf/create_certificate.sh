#!/bin/sh

#generating self-signed certificate
openssl req -new -x509 -keyout $1 -out $1 -days 3650 -nodes <<EOF
IT
Italy
Turin
Arduino SA
Yún
arduino.cc
support@arduino.cc
EOF

