#!/usr/bin/python3
from Crypto import Random
from Crypto.Cipher import AES



plaintext = bytes.fromhex("255044462d312e350a25d0d4c5d80a34".lower())
ciphertext = bytes.fromhex("d06bf9d0dab8e8ef880660d2af65aa82".lower())
IV = bytes.fromhex("09080706050403020100A2B2C2D2E2F2".lower())


file = open('keys.txt')

keyList= file.readlines()

for key in keyList:

    x = key[:-1]
    currentKey = bytes.fromhex(x)
    cipher = AES.new(currentKey,AES.MODE_CBC,IV)
    compare = cipher.encrypt(plaintext)
    if(compare == ciphertext):
        print("key found: ", x)
        exit(0)
print("no key found")

