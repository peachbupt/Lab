1. Download [PSEXEC](!https://technet.microsoft.com/en-us/sysinternals/bb897553.aspx) and unzip to some folder.
2. Open an elevated CMD prompt as an administrator.
3. Navigate to the folder where you unzipped PSEXEC.EXE
4. Run:
     PSEXEC -i -s -d CMD
5. You will have a new CMD prompt open, as though by magic.
6. Type the following in the new CMD prompt to prove who you are:
     WHOAMI /USER

 https://blogs.technet.microsoft.com/askds/2008/10/22/getting-a-cmd-prompt-as-system-in-windows-vista-and-windows-server-2008/